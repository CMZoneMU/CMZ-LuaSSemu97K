#pragma once

/*LUA MEMORY*/
void LuaMemoryRegister(lua_State* L);
int LuaMemoryGetByte(lua_State* L);
int LuaMemorySetByte(lua_State* L);
int LuaMemoryGetDword(lua_State* L);
int LuaMemorySetDword(lua_State* L);
int LuaMemoryGetFloat(lua_State* L);
int LuaMemorySetFloat(lua_State* L);
int LuaMemorySetOffset(lua_State* L);
int LuaHookCall(lua_State* L);
int LuaHookJmp(lua_State* L);
int LuaMemoryCpy(lua_State* L);
