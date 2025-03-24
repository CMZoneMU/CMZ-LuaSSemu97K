#pragma once
#include "stdafx.h"
#if SCRIPT_SSEMU
struct SCRIPT_HEADER
{
#pragma pack(1)
	char key[128];
	DWORD size;
#pragma pack()
};



void LuaFunction(lua_State* L);
int LuaRequire(lua_State* L);
int LuaUtilConsole(lua_State* L);
int LuaColor3f(lua_State* L);
int LuaColor4b(lua_State* L);
int LuaEnableAlphaBlend(lua_State* L);
int LuaEnableAlphaBlend2(lua_State* L);
int LuaEnableAlphaBlendMinus(lua_State* L);
int LuaEnableAlphaTest(lua_State* L);
int LuaEnableLightMap(lua_State* L);
int LuaDisableAlphaBlend(lua_State* L);
int LuaRenderTipText(lua_State* L);
int LuaSetBackColor(lua_State* L);
int LuaSetFontType(lua_State* L);
int LuaSetTextColor(lua_State* L);
int LuaRenderColor(lua_State* L);
int LuaRenderItem3D(lua_State* L);
int LuaRenderMessage(lua_State* L);
int LuaRenderBitmap(lua_State* L);
int LuaRenderBitRotation(lua_State* L);
int LuaLoadImage(lua_State* L);

int LuaLoadSound(lua_State* L);
int LuaPlaySound(lua_State* L);
int LuaMousePosX(lua_State* L);
int LuaMousePosY(lua_State* L);
int LuaMouseLButton(lua_State* L);
int LuaMouseRButton(lua_State* L);
int LuaCheckMouseIn(lua_State* L);
int LuaGetMainResolution(lua_State* L);
int LuaGetMainScene(lua_State* L);
int LuaGetObjectMap(lua_State* L);
int LuaCharacterLockAction(lua_State* L);
/*NUEVAS RGP*/
int LuaMouseLButtonPush(lua_State* L);
int LuaMouseRButtonPush(lua_State* L);
int GetPlayerState(lua_State* L);
int LuaCursorBloq(lua_State* L);
int LuaCheckWindows(lua_State* L);
int LuaCheckWindowStatus(lua_State* L);
int LuaRenderTextCustom(lua_State* L);
int LuaRenderButtonCustom(lua_State* L);
int LuaRenderWindowsClassic(lua_State* L);
int LuaRenderItemName(lua_State* L);
int LuaSendChat(lua_State* L);
int LuaSetLang(lua_State* L);
int Lua_DrawIMG(lua_State* L);
int Lua_BindObject(lua_State* L);
int Lua_IsWorkZone(lua_State* L);
int LuaChatWindows(lua_State* L);
int LuaWindowsText(lua_State* L);
int LuaWindowsName(lua_State* L);
int LuaWidescreenX(lua_State* L);
int LuaWidescreenScale(lua_State* L);

#endif