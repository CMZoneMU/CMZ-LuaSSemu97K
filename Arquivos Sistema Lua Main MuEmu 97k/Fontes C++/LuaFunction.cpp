#include "stdafx.h"
#if SCRIPT_SSEMU
#include "LuaSSEMU.h"
#include "Util.h"
#include "Offsets.h"
#include "LuaFunction.h"
#include "InterfaceElemental.h"
#include "Interface.h"
#include "Sha256\\Sha256.h"
#include "Language.h"
#include "Protect.h"
#include "Console.h"
#include "MoveList.h"
#include "LuaLoader.h"
#include "CWideScreen.h"
static int sentinel_ = 0;


void LuaFunction(lua_State* L) // OK
{
	/*UTILITY*/
	lua_register(L, "UtilConsole", LuaUtilConsole);
	lua_register(L, "GetServerName", LuaWindowsName);

	/*COLOR*/
	lua_register(L, "glColor3f", LuaColor3f); // esto
	lua_register(L, "glColor4f", LuaColor4b); // esto
	lua_register(L, "EnableAlphaBlend", LuaEnableAlphaBlend);
	lua_register(L, "EnableAlphaBlend2", LuaEnableAlphaBlend2);
	lua_register(L, "EnableAlphaBlendMinus", LuaEnableAlphaBlendMinus);
	lua_register(L, "EnableAlphaTest", LuaEnableAlphaTest);
	lua_register(L, "EnableLightMap", LuaEnableLightMap);
	lua_register(L, "DisableAlphaBlend", LuaDisableAlphaBlend);
	lua_register(L, "RenderColor", LuaRenderColor);
	lua_register(L, "SetBackColor", LuaSetBackColor); // esto
	lua_register(L, "SetTextColor", LuaSetTextColor);

	/*TEXT*/
	//lua_register(L, "RenderText", LuaRenderText); // esto (no funciona)
	lua_register(L, "RenderTipText", LuaRenderTipText);
	lua_register(L, "RenderMessage", LuaRenderMessage);
	lua_register(L, "CreateCustomText", LuaRenderTextCustom); // Custom Text OK
	lua_register(L, "SetWindowText", LuaWindowsText);
	lua_register(L, "RenderItemName", LuaRenderItemName); //Ok ambos?


	/*GRAPHIC*/
	lua_register(L, "RenderItem3D", LuaRenderItem3D);
	lua_register(L, "RenderBitmap", LuaRenderBitmap);
	lua_register(L, "RenderBitmapRotate", LuaRenderBitRotation);
	lua_register(L, "CreateClassicWindows", LuaRenderWindowsClassic); // Classic Windows OK
	lua_register(L, "CreateCustomButton", LuaRenderButtonCustom); // Custom Button OK 
	lua_register(L, "DrawIMG", Lua_DrawIMG);
	lua_register(L, "BindObject", Lua_BindObject);
	lua_register(L, "WidescreenX", LuaWidescreenX);
	lua_register(L, "WidescreenScale", LuaWidescreenScale);


	/*CONTROLLER*/
	lua_register(L, "MouseLButtonPush", LuaMouseLButtonPush); // esto chequear 
	lua_register(L, "MouseRButtonPush", LuaMouseRButtonPush); // esto chequear
	lua_register(L, "MousePosX", LuaMousePosX); // esto
	lua_register(L, "MousePosY", LuaMousePosY); // esto
	lua_register(L, "MouseLButton", LuaMouseLButton); // esto
	lua_register(L, "MouseRButton", LuaMouseRButton); // esto
	lua_register(L, "CheckMouseIn", LuaCheckMouseIn); // esto (sacar 1 parametro)
	lua_register(L, "CursorBlock", LuaCursorBloq); // OK
	lua_register(L, "IsWorkZone", Lua_IsWorkZone);
	lua_register(L, "WindowSystem", LuaCheckWindows); // OK OPEN - CLOSE VENTANAS
	lua_register(L, "CheckWindowSystem", LuaCheckWindowStatus); // OK OPEN - CLOSE VENTANAS
	lua_register(L, "ChatState", LuaChatWindows);
	lua_register(L, "SendChat", LuaSendChat); //OK

	/*Character*/
	lua_register(L, "GetCharacterMap", LuaGetObjectMap);
	lua_register(L, "CharacterLockAction", LuaCharacterLockAction);
	lua_register(L, "GetPlayerState", GetPlayerState); // OK
	lua_register(L, "SetLangUser", LuaSetLang);

		/*OTHER*/
	lua_register(L, "SetFontType", LuaSetFontType); // esto
	lua_register(L, "LoadImage", LuaLoadImage);
	lua_register(L, "LoadSound", LuaLoadSound);
	lua_register(L, "PlaySound", LuaPlaySound);
	lua_register(L, "GetMainScene", LuaGetMainScene);
	lua_register(L, "GetMainResolution", LuaGetMainResolution);

}


int LuaRequire(lua_State* L)
{
	char buff[256];

	const char* moduleName = luaL_checklstring(L, 1, 0);
	const char* key = luaL_optstring(L, 2, 0);
	wsprintf(buff, "Data\\Custom\\Lua\\%s.lua", moduleName);

	lua_settop(L, 1);
	lua_getfield(L, LUA_REGISTRYINDEX, "_LOADED");
	lua_getfield(L, 2, buff);

	if (lua_toboolean(L, -1))
	{
		if (lua_touserdata(L, -1) == ((void*)&sentinel_))
		{
			UtilConsole(1, "[ScriptLoader] Error in Lua-file. %s", lua_tostring(L, -1));
			return 0;
		}
	}

	if (key) 
	{
		SCRIPT_HEADER HeaderInfo;
		HANDLE file = CreateFile(buff, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (file == INVALID_HANDLE_VALUE) {
			return luaL_error(L, "[ScriptLoader] Cannot open encrypted file: %s", buff);
		}

		DWORD size;
		if (ReadFile(file, &HeaderInfo, sizeof(HeaderInfo), &size, 0) == 0) {
			CloseHandle(file);
			return luaL_error(L, "[ScriptLoader] Error reading encrypted file: %s", buff);
		}

		// Compare the hash of the key with the hash stored in the file
		if (std::strncmp(HeaderInfo.key, sha256(key).c_str(), 128) != 0) {
			CloseHandle(file);
			return luaL_error(L, "[ScriptLoader] Invalid key in encrypted file: %s", buff);
		}

		// Decrypt the file content
		BYTE buffer[65536];
		ReadFile(file, buffer, sizeof(buffer), &size, 0);

		for (DWORD n = 0; n < size; ++n) {
			buffer[n] ^= key[n % strlen(key)];  // Decrypt using the key
		}

		CloseHandle(file);

		if (luaL_loadbuffer(L, (char*)buffer, size, buff)) {
			return luaL_error(L, "[ScriptLoader] Could not load '%s'. %s", buff, lua_tostring(L, -1));
		}
	}
	else {
		if (luaL_loadfile(L, buff)) {
			char errorMessage[512];
			snprintf(errorMessage, sizeof(errorMessage), "Could not find Lua script: \"%s\". Please check if the file exists.", buff);
			MessageBox(0, errorMessage, "Require Error", MB_ICONERROR | MB_OK);

			UtilConsole(1, "[ScriptLoader] Could not load '%s'. %s", buff, lua_tostring(L, -1));
			return 0;
		}
	}

	lua_pushlightuserdata(L, ((void*)&sentinel_));
	lua_setfield(L, 2, buff);
	lua_pushstring(L, buff);

	lua_call(L, 1, 1);

	if (lua_type(L, -1))
	{
		lua_setfield(L, 2, buff);
	}

	lua_getfield(L, 2, buff);
	if (lua_touserdata(L, -1) == ((void*)&sentinel_))
	{
		lua_pushboolean(L, 1);
		lua_pushvalue(L, -1);
		lua_setfield(L, 2, buff);
	}

	return 1;
}

int LuaUtilConsole(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 2);
	}

	int aValue = lua_tointeger(L, 1);

	const char* aString = lua_tostring(L, 2);

	UtilConsole(aValue, "%s", aString);

	return 1;
}

int LuaColor3f(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 3);
	}

	float aValue = (float)lua_tonumber(L, 1);

	float bValue = (float)lua_tonumber(L, 2);

	float cValue = (float)lua_tonumber(L, 3);

	glColor3f(aValue, bValue, cValue);

	return 1;
}

int LuaColor4b(lua_State* L) // OK
{
	if (lua_gettop(L) != 4)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 4);
	}

	float aValue = (float)lua_tonumber(L, 1);

	float bValue = (float)lua_tonumber(L, 2);

	float cValue = (float)lua_tonumber(L, 3);

	float dValue = (float)lua_tonumber(L, 4);

	glColor4b(aValue, bValue, cValue, dValue);

	return 1;
}

int LuaEnableAlphaBlend(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	EnableAlphaBlend();

	return 1;
}

int LuaEnableAlphaBlend2(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	EnableAlphaBlend2();

	return 1;
}

int LuaEnableAlphaBlendMinus(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	EnableAlphaBlendMinus();

	return 1;
}

int LuaEnableAlphaTest(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}

	int aValue = lua_tointeger(L, 1);

	EnableAlphaTest(((aValue != 0) ? true : false));

	return 1;
}

int LuaEnableLightMap(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	EnableLightMap();

	return 1;
}

int LuaDisableAlphaBlend(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	DisableAlphaBlend();

	return 1;
}

int LuaRenderTipText(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 3);
	}

	int aValue = lua_tointeger(L, 1);

	int bValue = lua_tointeger(L, 2);

	const char* cValue = lua_tostring(L, 3);

	RenderTipText(aValue, bValue, (char*)cValue);

	return 1;
}

int LuaSetBackColor(lua_State* L) // OK
{
	if (lua_gettop(L) != 4)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 4);
	}

	int aValue = lua_tointeger(L, 1);

	int bValue = lua_tointeger(L, 2);

	int cValue = lua_tointeger(L, 3);

	int dValue = lua_tointeger(L, 4);

	SetBackgroundTextColor = ((dValue << 24) + (cValue << 16) + (bValue << 8) + aValue);

	return 1;
}

int LuaSetFontType(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}

	int aValue = lua_tointeger(L, 1);

	switch (aValue)
	{
	case 0:
		SelectObject(m_hFontDC, g_hFont);
		break;
	case 1:
		SelectObject(m_hFontDC, g_hFontBold);
		break;
	case 2:
		SelectObject(m_hFontDC, g_hFontBig);
		break;
	}

	return 1;
}

int LuaSetTextColor(lua_State* L) // OK
{
	if (lua_gettop(L) != 4)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 4);
	}

	int aValue = lua_tointeger(L, 1);

	int bValue = lua_tointeger(L, 2);

	int cValue = lua_tointeger(L, 3);

	int dValue = lua_tointeger(L, 4);

	SetTextColor = ((dValue << 24) + (cValue << 16) + (bValue << 8) + aValue);

	return 1;
}

int LuaRenderColor(lua_State* L) // OK
{
	if (lua_gettop(L) != 8)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 8);
	}

	float aValue = (float)lua_tonumber(L, 1);

	float bValue = (float)lua_tonumber(L, 2);

	float cValue = (float)lua_tonumber(L, 3);

	float dValue = (float)lua_tonumber(L, 4);

	float eValue = (float)lua_tonumber(L, 5);

	float fValue = (float)lua_tonumber(L, 6);

	float gValue = (float)lua_tonumber(L, 7);

	float hValue = (float)lua_tonumber(L, 8);


	gInterface.DrawBarForm(aValue, bValue, cValue, dValue, eValue, fValue, gValue, hValue);

	return 1;
}

int LuaRenderItem3D(lua_State* L) // OK
{
	if (lua_gettop(L) != 9)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 9);
	}

	float aValue = (float)lua_tonumber(L, 1);

	float bValue = (float)lua_tonumber(L, 2);

	float cValue = (float)lua_tonumber(L, 3);

	float dValue = (float)lua_tonumber(L, 4);

	int eValue = lua_tointeger(L, 5);

	int fValue = lua_tointeger(L, 6);

	int gValue = lua_tointeger(L, 7);

	int hValue = lua_tointeger(L, 8);

	int iValue = lua_tointeger(L, 9);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	pglViewport2(0, 0, *(DWORD*)MAIN_RESOLUTION_X, *(DWORD*)MAIN_RESOLUTION_Y);
	pgluPerspective2(1.f, (float)(*(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y), 20.f, 2000.f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	pGetOpenGLMatrix(pCameraMatrix);
	pEnableDepthTest();
	pEnableDepthMask();

	pRenderItem3D(aValue, bValue, cValue, dValue, eValue, fValue, gValue, hValue, iValue);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	pBeginBitmap();

	glColor3f(1, 1, 1);

	EnableAlphaTest(true);

	return 1;
}

int LuaRenderMessage(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 2);
	}

	const char* aValue = lua_tostring(L, 1);

	int bValue = lua_tointeger(L, 2);

	pDrawMessage((char*)aValue, bValue);

	return 1;
}

int LuaRenderBitmap(lua_State* L) // OK
{
	if (lua_gettop(L) != 11)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 11);
	}

	int aValue = lua_tointeger(L, 1);

	float bValue = (float)lua_tonumber(L, 2);

	float cValue = (float)lua_tonumber(L, 3);

	float dValue = (float)lua_tonumber(L, 4);

	float eValue = (float)lua_tonumber(L, 5);

	float fValue = (float)lua_tonumber(L, 6);

	float gValue = (float)lua_tonumber(L, 7);

	float hValue = (float)lua_tonumber(L, 8);

	float iValue = (float)lua_tonumber(L, 9);

	int jValue = lua_tointeger(L, 10);

	int kValue = lua_tointeger(L, 11);

	pDrawImage(aValue, bValue, cValue, dValue, eValue, fValue, gValue, hValue, iValue, jValue, kValue, 0.0);

	return 1;
}

int LuaRenderBitRotation(lua_State* L) // OK
{
	if (lua_gettop(L) != 6)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 6);
	}

	int aValue = lua_tointeger(L, 1);

	float bValue = (float)lua_tonumber(L, 2);

	float cValue = (float)lua_tonumber(L, 3);

	float dValue = (float)lua_tonumber(L, 4);

	float eValue = (float)lua_tonumber(L, 5);

	float fValue = (float)lua_tonumber(L, 6);

	pRenderBitmapRotate(aValue, bValue, cValue, dValue, eValue, fValue);

	return 1;
}
int LuaLoadImage(lua_State* L)
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 3);
	}

	int aValue = lua_tointeger(L, 1);

	const char* bValue = lua_tostring(L, 2);

	int cValue = lua_tointeger(L, 3);

	switch (aValue)
	{
		case 0:
		{
			OpenJPG((char*)bValue, cValue, 0x2600, 0x2900, 0, 1); // -> JPG
		}
		break;
		case 1:
		{
			OpenTGA((char*)bValue, cValue, 0x2600, 0x2900, 0, 1); // -> TGA
		}
		break;
	}
	return 1;
}


int LuaLoadSound(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 2);
	}

	int aValue = lua_tointeger(L, 1);

	const char* bValue = lua_tostring(L, 2);

	LoadWaveFile(aValue, (char*)bValue, 2, 1);

	return 1;
}

int LuaPlaySound(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 2);
	}

	int aValue = lua_tointeger(L, 1);

	int bValue = lua_tointeger(L, 2);

	pPlayBuffer(aValue, 0, bValue);

	return 1;
}

int LuaMousePosX(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	lua_pushinteger(L, MouseX);

	return 1;
}

int LuaMousePosY(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	lua_pushinteger(L, MouseY);

	return 1;
}




int LuaMouseLButton(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	lua_pushinteger(L, MouseLButton);

	return 1;
}

int LuaMouseRButton(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	lua_pushinteger(L, MouseRButton);

	return 1;
}


int LuaCheckMouseIn(lua_State* L) // OK
{
	if (lua_gettop(L) != 4)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 4);
	}

	int aValue = lua_tointeger(L, 1);

	int bValue = lua_tointeger(L, 2);

	int cValue = lua_tointeger(L, 3);

	int dValue = lua_tointeger(L, 4);

	lua_pushinteger(L, pCheckMouseOver(aValue, bValue, cValue, dValue));//

	return 1;
}

int LuaGetMainResolution(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	lua_pushinteger(L, *(DWORD*)(MAIN_RESOLUTION));

	return 1;
}

int LuaGetMainScene(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	lua_pushinteger(L, *(DWORD*)(SceneFlag));

	return 1;
}

int LuaGetObjectMap(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	lua_pushinteger(L, *(DWORD*)(World));

	return 1;
}


int LuaCharacterLockAction(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}

	int aValue = lua_tointeger(L, 1);

	if (aValue == 1)
	{
		*(BYTE*)(*(DWORD*)(Hero)+782) = 0;

		pSetPlayerStop(*(DWORD*)(Hero));
	}

	LockCharacterAction = aValue;

	return 1;
}

int LuaCursorBloq(lua_State* L)
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}

	int aValue = lua_tointeger(L, 1);

	SetCursorFocus(aValue);

	return 1;

}


int LuaMouseLButtonPush(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	lua_pushinteger(L, MouseLButtonPush);

	return 1;
}

int LuaMouseRButtonPush(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	lua_pushinteger(L, MouseRButtonPush);

	return 1;
}

int GetPlayerState(lua_State* L)
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	lua_pushinteger(L, pPlayerState); // Devolver el valor de pPlayerState a Lua
	return 1;
}

int LuaCheckWindows(lua_State* L)
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 2);
	}

	int windowType = lua_tointeger(L, 1);
	int stateValue = lua_tointeger(L, 2);  // Este valor puede ser 0 o 1, como un booleano

	// Usamos un switch para asignar el valor de la ventana correspondiente
	switch (windowType)
	{
	case 0:
		InventoryOpened = stateValue;
		break;
	case 1:
		pChatWindow = stateValue;
		break;
	case 2:
		
		break;
	case 3:
		GuildCreatorOpened = stateValue;
		break;
	case 4:
		 gMoveList.MoveListSwitch = stateValue;
		break;
	case 5:
		CharacterOpened = stateValue;
		break;
	case 6:
		ChaosGoblinOpened = stateValue;
		break;
	case 7:
		PartyOpened = stateValue;
		break;
	case 8:
		
		break;
	case 9:
		GoldenArcherOpened = stateValue;
		break;
	case 10:

		break;
	case 11:
		
		break;
	case 12:
		GuildOpened = stateValue;
		break;
	default:
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 2);
	}

	return 1;
}

int LuaCheckWindowStatus(lua_State* L)
{
	if (lua_gettop(L) != 1)  // Verificamos que solo haya un argumento
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}

	int windowType = lua_tointeger(L, 1);  // Obtenemos el tipo de ventana

	// Verificamos el estado de la ventana
	bool windowState = false;  // Por defecto, asumimos que la ventana está cerrada (false)

	switch (windowType)
	{
	case 0:  // Inventario
		windowState = !InventoryOpened;  // Si está cerrado (por convención, !true = false, !false = true)
		break;
	case 1:  // pChatWindow
		windowState = !pChatWindow;
		break;
	case 2:  // Almacen
		windowState = 0;
		break;
	case 3:  // GuildCreator
		windowState = !GuildCreatorOpened;
		break;
	case 4:  // MoveList
		windowState = !gMoveList.MoveListSwitch;
		break;
	case 5:  // Character
		windowState = !CharacterOpened;
		break;
	case 6:  // ChaosGoblin
		windowState = !ChaosGoblinOpened;
		break;
	case 7:  // Party
		windowState = !PartyOpened;
		break;
	case 8:  // PersonalShop
		windowState = !0;
		break;
	case 9:  // EventChip
		windowState = !GoldenArcherOpened;
		break;
	case 10:  // CommandClose
		windowState = 0;  // Aquí asumes que la ventana está "cerrada" cuando `!CommandClose` es true
		break;
	case 11:  // Evento
		windowState = !0;
		break;
	case 12:  // Guild
		windowState = !GuildOpened;
		break;
	default:
		return luaL_error(L, "Error: Tipo de ventana no reconocido.", 1);
	}

	// Retornar el resultado de la verificación (1 si la ventana está cerrada, 0 si está abierta)
	lua_pushboolean(L, windowState);  // Empuja el estado de la ventana como un valor booleano
	return 1;
}


void WindowRenderTextLua(int x, int y, int font, int align, int color, const char* text, ...) // OK
{
	char buff[256];

	memset(buff, 0, sizeof(buff));

	va_list arg;
	va_start(arg, text);
	vsprintf_s(buff, text, arg);
	va_end(arg);

	SIZE sz;

	// Obtener el tamaño del texto
	GetTextExtentPoint(m_hFontDC, buff, strlen(buff), &sz);

	int py = (y - (480 * sz.cy / *(DWORD*)MAIN_RESOLUTION_Y >> 1));
	EnableAlphaTest(true);

	// Selección de la fuente según el valor de 'font'
	if (font == 1) 
	{
		// Fuente en negrita
		SelectObject(m_hFontDC, g_hFontBold);
	}
	else if (font == 2) 
	{
		// Fuente grande
		SelectObject(m_hFontDC, g_hFontBig);
	}
	else 
	{
		// Fuente normal (valor por defecto)
		SelectObject(m_hFontDC, g_hFont);
	}

	// Configuración del color
	SetBackgroundTextColor = 0;

	if (color == 0) 
	{ // Gris claro
		SetTextColor = Color4b(220, 220, 220, 255);
	}
	else if (color == 1) 
	{ // Dorado
		SetTextColor = Color4b(223, 191, 103, 255);
	}
	else if (color == 2) 
	{ // Rojo intenso
		SetTextColor = Color4b(230, 5, 5, 255);
	}
	else if (color == 3) 
	{ // Verde brillante
		SetTextColor = Color4b(73, 183, 0, 255);
	}
	else if (color == 4) 
	{ // Azul claro
		SetTextColor = Color4b(100, 150, 255, 255);
	}
	else if (color == 5) { // Verde esmeralda
		SetTextColor = Color4b(0, 225, 139, 255);
	}

	// Alineación del texto
	if (align == 1) 
	{ // Centrado
		x -= (640 * sz.cx / *(DWORD*)MAIN_RESOLUTION_X >> 1);
		RenderText(x, py, buff, 0, 0, 0);
	}
	else if (align == 2) 
	{ // De derecha a izquierda
		x -= (640 * sz.cx / *(DWORD*)MAIN_RESOLUTION_X >> 1) * 2;
		RenderText(x, py, buff, 0, 0, 0);
	}
	else 
	{
		RenderText(x, py, buff, 0, 0, 0);
	}

	// Restaurar la fuente normal después de renderizar
	SelectObject(m_hFontDC, g_hFont);
	SetTextColor = Color4b(255, 255, 255, 255);


}

int LuaRenderTextCustom(lua_State* L)
{
	// Verificamos que se pasen los 7 parámetros esperados
	if (lua_gettop(L) != 7)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 7);
	}

	// Obtener los parámetros pasados desde Lua
	int x = lua_tointeger(L, 1);          // Posición X
	int y = lua_tointeger(L, 2);          // Posición Y
	int font = lua_tointeger(L, 3);       // Tipo de fuente (0 normal, 1 bold, 2 big)
	int align = lua_tointeger(L, 4);      // Alineación del texto (1 centrar, 2 derecha, otros izquierda)
	int color = lua_tointeger(L, 5);      // Color del texto (0, 1, 2, ...)
	const char* text = lua_tostring(L, 6); // El texto a mostrar
	int size = lua_tointeger(L, 7);       // Tamaño adicional, si lo necesitas (opcional, no utilizado en este caso)

	// Llamar a la función WindowRenderText con los parámetros obtenidos
	WindowRenderTextLua(x, y, font, align, color, text);

	// Empujar 'true' al stack de Lua (asumiendo que la función fue exitosa)
	lua_pushboolean(L, true);

	return 1; // Devolver un valor (el booleano de éxito)
}

bool DrawButton(float PosX, float PosY, float TextX, float TextY, float SizeButton, int SizeButtonY, char* ButtonText)
{
	EnableAlphaTest(true);
	glColor3f(1.0, 1.0, 1.0);
	//============Button
	float SizeButtonW = SizeButton;
	float SizeButtonH = (SizeButton * 20) / 100;
	if (SizeButtonY != 0)
	{
		SizeButtonW = SizeButtonY;
	}

	float StartX = PosX;
	float StartY = PosY;
	bool mreturn = false;

	//=====================Button 1
	if (pCheckMouseOver(StartX, StartY, SizeButton, SizeButtonY) == 1 && !gElemental.LockButtonHover)
	{
		glColor3f(1.0f, 0.6742f, 0.15f);
		if (GetTickCount() - gInterface.Data[eWindowElemental].EventTick > 300) //Click
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(0.72f, 0.438f, 0.0432f);


				gInterface.Data[eWindowElemental].EventTick = GetTickCount();
				mreturn = true;
			}
		}
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);

	}

	RenderBitmap(1563, StartX, StartY, SizeButton, SizeButtonY, 0.0, 0.0, 170.0f / 256.0f, 28.0f / 32.0f, 1, 1);

	gInterface.DrawFormat(eGold, StartX + TextX, StartY + TextY, SizeButton, 3, ButtonText);
	//=====================================
	glColor3f(1.0f, 1.0f, 1.0f); //Xoa mau
	DeleteObject(ButtonText);
	DisableAlphaBlend();
	EnableAlphaTest(0);
	return mreturn;
}

int LuaRenderButtonCustom(lua_State* L)
{
	// Verificamos que se pasen los 7 parámetros esperados
	if (lua_gettop(L) != 7)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 7);
	}


	// Obtener los parámetros de Lua
	int aValue = lua_tointeger(L, 1);
	int bValue = lua_tointeger(L, 2);
	int cValue = lua_tointeger(L, 3);
	int dValue = lua_tointeger(L, 4);
	int eValue = lua_tointeger(L, 5);
	int fValue = lua_tointeger(L, 6);

	// Obtener el nombre de la ventana
	 char* gValue = (char*)lua_tostring(L, 7);

	// Llamar a la función y obtener el valor de retorno
	bool result = DrawButton(aValue, bValue, cValue, dValue, eValue, fValue, gValue);

	// Empujar el resultado booleano a Lua
	lua_pushboolean(L, result);

	return 1; // Devolver 1 valor (el booleano)
}


void DrawWindowClassic(float PosX, float PosY, float WindowW, float WindowE, short ObjectID)
{
	EnableAlphaTest(true);
	SetBackgroundTextColor = Color4b(255, 255, 255, 0);

	RenderBitmap(260, PosX, PosY, WindowW, WindowE, 0, 0, 190.0 / 256.0, 256.0 / 256.0f, 1, 1);

	RenderBitmap(261, PosX, PosY + WindowE, WindowW, WindowE, 0, 0, 190.0 / 256.0, 177.0 / 256.0, 1, 1);

	float buttonWidth = 24.0f;
	float buttonHeight = 24.0f;
	float buttonPosX = PosX + buttonWidth;
	float buttonPosY = PosY + WindowE + WindowE - buttonHeight * 1.5;

	pDrawImage(280, buttonPosX, buttonPosY, buttonWidth, buttonHeight, 0.0f, 0.0f, 24.0f / 32.0f, 24.0f / 32.0f, 1, 1, 0.0f);
	if (pCheckMouseOver(buttonPosX, buttonPosY, buttonWidth, buttonHeight))
	{
		
		RenderTipText(buttonPosX + 5, buttonPosY - 13, "Close");
		if (MouseLButtonPush)
		{
			RenderBitmap(281, buttonPosX, buttonPosY, buttonWidth, buttonHeight, 0, 0, 0.80, 0.80, 1, 1);

			SetCursorFocus(0);
			ObjectID = false;
		}
	}
}




int LuaRenderWindowsClassic(lua_State* L)
{
	if (lua_gettop(L) != 5)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 5);
	}

	// Obtener los parámetros de Lua
	int aValue = lua_tointeger(L, 1);
	int bValue = lua_tointeger(L, 2);
	int cValue = lua_tointeger(L, 3);
	int dValue = lua_tointeger(L, 4);
	int eValue = lua_tointeger(L, 5);



	// Empujar el resultado booleano a Lua
	//lua_pushboolean(L, DrawWindowClassic(aValue, bValue, cValue, dValue, eValue));
	DrawWindowClassic(aValue, bValue, cValue, dValue, eValue);
	return 0; // Devolver 1 valor (el booleano)
}



int LuaRenderItemName(lua_State* L) 
{
	// Verificar que se reciban exactamente 2 argumentos
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}

	int aValue = lua_tointeger(L, 1);
	char* itemName = GetItemName(aValue);

	if (itemName == nullptr) // Validar el resultado
	{
		lua_pushnil(L); // Empujar nil si no se pudo obtener el nombre
	}
	else
	{
		lua_pushstring(L, itemName); // Empujar el nombre como string a la pila de Lua
		free(itemName); // Liberar la memoria asignada por _strdup
	}

	return 1; // Devolver 1 valor (el string o nil)
}

int LuaSendChat(lua_State* L)
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}
	const char* command = lua_tostring(L, 1);
	if (!command)
	{
		return luaL_error(L, "Invalid argument: expected a string.");
	}

	// Llamar a SendChat con el comando
	SendChat(command);

	// Opcionalmente, puedes devolver true para indicar éxito
	lua_pushboolean(L, 1);
	return 1; // Retornar un valor (el booleano)
}

int LuaSetLang(lua_State* L)
{
	// Suponiendo que 'gLanguage.m_Language' es la variable que contiene el idioma actual.
	const char* lang = gLanguage.m_Language; // Esto debe ser una cadena como "Eng", "Por", "Spn"

	// Verificar el idioma y ajustar las configuraciones correspondientes
	if (_strcmpi(lang, "Eng") == 0)
	{
		strcpy_s(gLanguage.m_TextBMD, "Data\\Local\\Eng\\Text_Eng.bmd");
		strcpy_s(gLanguage.m_DialogBMD, "Data\\Local\\Eng\\Dialog_Eng.bmd");
		gLanguage.LangNum = LANGUAGE_ENGLISH;
	}
	else if (_strcmpi(lang, "Spn") == 0)
	{
		strcpy_s(gLanguage.m_TextBMD, "Data\\Local\\Spn\\Text_Spn.bmd");
		strcpy_s(gLanguage.m_DialogBMD, "Data\\Local\\Spn\\Dialog_Spn.bmd");
	
		gLanguage.LangNum = LANGUAGE_SPANISH;
	}
	else if (_strcmpi(lang, "Por") == 0)
	{
		strcpy_s(gLanguage.m_TextBMD, "Data\\Local\\Por\\Text_Por.bmd");
		strcpy_s(gLanguage.m_DialogBMD, "Data\\Local\\Por\\Dialog_Por.bmd");
	
		gLanguage.LangNum = LANGUAGE_PORTUGUESE;
	}
	else
	{
		// Si el idioma no es válido, por defecto se usa inglés
		strcpy_s(gLanguage.m_TextBMD, "Data\\Local\\Eng\\Text_Eng.bmd");
		strcpy_s(gLanguage.m_DialogBMD, "Data\\Local\\Eng\\Dialog_Eng.bmd");
		
		gLanguage.LangNum = LANGUAGE_ENGLISH;
	}

	// Luego, retornamos el idioma actual como una cadena a Lua
	lua_pushstring(L, lang);  // Empujar el idioma a Lua (por ejemplo, "Eng", "Por", "Spn")
	return 1;  // Devolver un valor
}

int Lua_DrawIMG(lua_State* L) 
{
	// Asegurarse de que tenemos 5 parámetros
	if (lua_gettop(L) != 5) 
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 5);
		
	}

	int ModelID = luaL_checkinteger(L, 1);  // ModelID
	float PosX = luaL_checknumber(L, 2);    // PosX
	float PosY = luaL_checknumber(L, 3);    // PosY
	float ScaleX = luaL_checknumber(L, 4);   // Width
	float ScaleY = luaL_checknumber(L, 5);  // Height
	// Llamar a la función original de C++ directamente
	gInterface.DrawIMG(ModelID, PosX, PosY, ScaleX, ScaleY);  // Usar valores predeterminados de escala (ScaleX = 1, ScaleY = 1)
	
	return 0;  // Retornar 0 para indicar que no hay valores de retorno
}

int Lua_BindObject(lua_State* L) 
{
	// Asegurarse de que recibimos 6 parámetros de Lua
	if (lua_gettop(L) != 6) 
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 6);
		
	}

	short MonsterID = luaL_checkinteger(L, 1);     // MonsterID
	DWORD ModelID = luaL_checkinteger(L, 2);       // ModelID
	float Width = luaL_checknumber(L, 3);           // Width
	float Height = luaL_checknumber(L, 4);          // Height
	float X = luaL_checknumber(L, 5);              // X
	float Y = luaL_checknumber(L, 6);              // Y

	// Llamar a la función original en C++
	gInterface.BindObject(MonsterID, ModelID, Width, Height, X, Y);

	return 0;  // Retornar 0 para indicar que no hay valores de retorno
}

int Lua_IsWorkZone(lua_State* L)
{
	// Asegurarse de que recibimos 1 parámetro de Lua (ObjectID)
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}

	short ObjectID = luaL_checkinteger(L, 1);  // ObjectID

	// Acceder a las coordenadas y dimensiones del objeto desde gInterface
	float sx = gInterface.Data[ObjectID].X;
	float sy = gInterface.Data[ObjectID].Y;
	float cx = gInterface.Data[ObjectID].Width;
	float cy = gInterface.Data[ObjectID].Height;

	// Obtener las coordenadas del ratón
	float pMouseX = MouseX;  // Reemplazar con tu función real para obtener la posición X del ratón
	float pMouseY = MouseY;  // Reemplazar con tu función real para obtener la posición Y del ratón

	// Comprobar si el ratón está dentro del área del objeto
	if (pMouseX >= sx && pMouseX <= (sx + cx) && pMouseY >= sy && pMouseY <= (sy + cy))
	{
		lua_pushboolean(L, 1);  // Retornar verdadero
	}
	else
	{
		lua_pushboolean(L, 0);  // Retornar falso
	}

	return 1;  // Retornar un valor
}

int LuaChatWindows(lua_State* L)
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}

	int aValue = lua_tointeger(L, 1);

	pChatWindow = aValue;

	return 1;

}

// Definir el array de InterfaceObject
InterfaceObject gInterfaceData[100]; // Suponemos que hay 100 objetos


int LuaWindowsText(lua_State* L)
{

	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}

	char szBuffer[500] = { 0 };

	const char* newText = luaL_checkstring(L, 1);  
 
	sprintf_s(szBuffer, sizeof(szBuffer), "%s", newText);

	SetWindowText(*(HWND*)(g_hWnd), szBuffer);

	return 0;  
}
int LuaWindowsName(lua_State* L)
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);  
	}

	lua_pushstring(L, gProtect.m_MainInfo.WindowName);  

	return 1;  
}


int LuaWidescreenX(lua_State* L)
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	
	lua_pushnumber(L, gCWideScreen.WCenter);

	return 1;
}

int LuaWidescreenScale(lua_State* L)
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	float Screen;

	if (m_Resolution >= R1280x720)
	{
		Screen = gCWideScreen.Scale;
		
	}
	else
	{
		Screen = 1;
	}


	lua_pushnumber(L, Screen);

	return 1;
}

#endif
