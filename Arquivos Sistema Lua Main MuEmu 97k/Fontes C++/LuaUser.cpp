#include "stdafx.h"
#include "LuaUser.h"
#include "LuaLoader.h"
#include "LuaSSEMU.h"
#include "PrintPlayer.h"
//#include "MuCoin.h"

void LuaUserRegister(lua_State* L) // OK
{
	/*INFO PLAYER*/
	lua_register(L, "GetPlayerName", GetPlayerName); // Player Name OK
	lua_register(L, "GetPlayerLevel", GetPlayerLevel); // Player Level OK
	lua_register(L, "GetPlayerReset", GetPlayerReset); // Player Reset OK
	lua_register(L, "GetPlayerMasterReset", GetPlayerMasterReset); // Player Master Reset OK
	lua_register(L, "GetPlayerMuCoins", GetMuCoinsCount); // Player Mu Coins OK
	lua_register(L, "GetPlayerMaxMuCoins", GetMaxMuCoinsCount); // Player Max Mu Coins OK
	lua_register(L, "GetAccountLevel", GetPlayerAccountLevel); // Player Account Level OK
}

int GetPlayerName(lua_State* L)
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	char Name[100];

	STRUCT_DECRYPT1

	sprintf_s(Name, "%s", (char*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x00));

	STRUCT_ENCRYPT1

	lua_pushstring(L, Name);

	return 1;
}

int GetPlayerLevel(lua_State* L)
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}


	char Name[100];

	STRUCT_DECRYPT;

	sprintf_s(Name, "%d", *(WORD*)(CharacterAttribute + 0x0E));

	STRUCT_ENCRYPT;

	lua_pushstring(L, Name);
	/*
	DWORD PlayerLevel = gPrintPlayer.ViewLevel;

	lua_pushinteger(L, PlayerLevel);*/

	return 1;  // Devolvemos el valor del nivel como resultado.
}

int GetPlayerReset(lua_State* L)
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	DWORD PlayerReset = gPrintPlayer.ViewReset;

	lua_pushinteger(L, PlayerReset);

	return 1;  // Devolvemos el valor del nivel como resultado.
}


int GetPlayerMasterReset(lua_State* L)
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	DWORD PlayerMasterReset = gPrintPlayer.ViewGrandReset;

	lua_pushinteger(L, PlayerMasterReset);

	return 1;  // Devolvemos el valor del nivel como resultado.
}


int GetMuCoinsCount(lua_State* L)
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	DWORD PlayerMuCoins = gPrintPlayer.PcPointMin;

	lua_pushinteger(L, PlayerMuCoins);

	return 1;  // Devolvemos el valor del nivel como resultado.
}

int GetMaxMuCoinsCount(lua_State* L)
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	DWORD PlayerMuCoinsMax = gPrintPlayer.PcPointMax;

	lua_pushinteger(L, PlayerMuCoinsMax);

	return 1;  // Devolvemos el valor del nivel como resultado.
}

int GetPlayerAccountLevel(lua_State* L)
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR0);
	}

	DWORD AccountLevel = 0;// gRenderSCoin.AccountLevel;

	lua_pushinteger(L, AccountLevel);

	return 1;  // Devolvemos el valor del nivel como resultado.
}
