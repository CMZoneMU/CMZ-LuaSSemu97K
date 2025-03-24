#pragma once

void LuaUserRegister(lua_State* L);

int GetPlayerName(lua_State* L);
int GetPlayerLevel(lua_State* L);
int GetPlayerReset(lua_State* L);
int GetPlayerMasterReset(lua_State* L);
int GetMuCoinsCount(lua_State* L);
int GetMaxMuCoinsCount(lua_State* L);
int GetPlayerAccountLevel(lua_State* L);
