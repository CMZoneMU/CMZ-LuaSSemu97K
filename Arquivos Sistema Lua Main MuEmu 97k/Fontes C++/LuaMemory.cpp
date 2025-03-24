#include "stdafx.h"
#include "LuaMemory.h"
#include "Util.h"
#include "LuaSSEMU.h"


/*LUA MEMORY*/

int MemoryGetByte(DWORD offset) 
{
	return *(BYTE*)(offset);
}

void MemorySetByte(DWORD offset, int value) 
{
	SetByte(offset, (BYTE)value);
}

DWORD MemoryGetDword(DWORD offset) {
	return *(DWORD*)(offset);
}

void MemorySetDword(DWORD offset, DWORD value) 
{
	SetDword(offset, value);
}

float MemoryGetFloat(DWORD offset) 
{
	return *(float*)(offset);
}

void MemorySetFloat(DWORD offset, float value) 
{
	SetFloat(offset, value);
}

void MemorySetOffset(DWORD offset, DWORD value, DWORD size) 
{
	MemorySet(offset, value, size);
}


void HookCall(DWORD offset, DWORD woffset)
{
	SetCompleteHook(0xE8, offset, woffset);
}

void HookJmp(DWORD offset, DWORD woffset)
{
	SetCompleteHook(0xE9, offset, woffset);
}

int LuaMemoryGetByte(lua_State* L)
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}

	DWORD offset = luaL_checkinteger(L, 1);  
	BYTE value = MemoryGetByte(offset);

	lua_pushinteger(L, value); 
	return 1; 
}

int LuaMemorySetByte(lua_State* L)
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 2);
	}

	DWORD offset = luaL_checkinteger(L, 1);  // Leer el offset
	int value = luaL_checkinteger(L, 2);     // Leer el valor a escribir

	MemorySetByte(offset, value);  // Llamar a la función C++ que configura el byte

	return 0;  // No retornar nada
}

int LuaMemoryGetDword(lua_State* L)
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}

	DWORD offset = luaL_checkinteger(L, 1);  // Leer el offset
	DWORD value = MemoryGetDword(offset);     // Obtener el DWORD

	lua_pushinteger(L, value);  // Empujar el DWORD obtenido a la pila
	return 1;  // Retornar el DWORD
}

int LuaMemorySetDword(lua_State* L)
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 2);
	}

	DWORD offset = luaL_checkinteger(L, 1);  // Leer el offset
	DWORD value = luaL_checkinteger(L, 2);   // Leer el valor a escribir

	MemorySetDword(offset, value);  // Llamar a la función C++ que establece el DWORD

	return 0;  // No retornar nada
}

int LuaMemoryGetFloat(lua_State* L)
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 1);
	}

	DWORD offset = luaL_checkinteger(L, 1);  // Leer el offset
	float value = MemoryGetFloat(offset);    // Obtener el float

	lua_pushnumber(L, value);  // Empujar el float obtenido a la pila
	return 1;  // Retornar el float
}

int LuaMemorySetFloat(lua_State* L)
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 2);
	}

	DWORD offset = luaL_checkinteger(L, 1);  // Leer el offset
	float value = luaL_checknumber(L, 2);    // Leer el valor a escribir

	MemorySetFloat(offset, value);  // Llamar a la función C++ que establece el float

	return 0;  // No retornar nada
}
int LuaMemorySetOffset(lua_State* L)
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 3);
	}

	DWORD offset = luaL_checkinteger(L, 1);  // Leer el offset
	DWORD value = luaL_checkinteger(L, 2);   // Leer el valor
	DWORD size = luaL_checkinteger(L, 3);    // Leer el tamaño

	MemorySetOffset(offset, value, size);  // Llamar a la función C++ que establece el offset

	return 0;  // No retornar nada
}


int LuaHookCall(lua_State* L)
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 2);
	}

	DWORD offset = luaL_checkinteger(L, 1);  // Leer el offset
	DWORD woffset = luaL_checkinteger(L, 2); // Leer el woffset

	HookCall(offset, woffset);  // Llamar a la función C++ para hacer el hook

	return 0;  // No retornar nada
}
int LuaHookJmp(lua_State* L)
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 2);
	}

	DWORD offset = luaL_checkinteger(L, 1);  // Leer el offset
	DWORD woffset = luaL_checkinteger(L, 2); // Leer el woffset

	HookJmp(offset, woffset);  // Llamar a la función C++ para hacer el jump

	return 0;  // No retornar nada
}

int LuaMemoryCpy(lua_State* L)
{
	if (lua_gettop(L) != 3) {
		return luaL_error(L, SCRIPT_SSEMU_CODE_ERROR1, 3); // Asegura que haya 3 argumentos
	}

	// Obtener el offset, el valor (userdata o string) y el tamaño
	DWORD offset = luaL_checkinteger(L, 1);  // Offset en memoria
	size_t size = luaL_checkinteger(L, 3);   // Tamaño del bloque de memoria
	const char* value = luaL_checkstring(L, 2);  // Datos a copiar (como string o userdata)

	// Llamamos a MemoryCpy en C++ con los datos obtenidos de Lua
	MemoryCpy(offset, (void*)value, (DWORD)size);

	return 0;  // No es necesario retornar nada
}


void LuaMemoryRegister(lua_State* L) // OK
{
	/*LUA MEMORY*/
	lua_register(L, "MemoryGetByte", LuaMemoryGetByte);
	lua_register(L, "MemorySetByte", LuaMemorySetByte);
	lua_register(L, "MemoryGetDword", LuaMemoryGetDword);
	lua_register(L, "MemorySetDword", LuaMemorySetDword);
	lua_register(L, "MemoryGetFloat", LuaMemoryGetFloat);
	lua_register(L, "MemorySetFloat", LuaMemorySetFloat);
	lua_register(L, "MemorySetOffset", LuaMemorySetOffset);
	lua_register(L, "HookCall", LuaHookCall);
	lua_register(L, "HookJmp", LuaHookJmp);
	lua_register(L, "MemoryCpy", LuaMemoryCpy);
}
