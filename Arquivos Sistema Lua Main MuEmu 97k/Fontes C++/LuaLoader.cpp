// LuaLoader.cpp: implementation of the CLuaLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LuaLoader.h"
#include "LuaSSEMU.h"
#include "CriticalSection.h"
#include "Util.h"
#include "LuaMemory.h"
#include "LuaFunction.h"
#include "LuaUser.h"
#include "Protect.h"
#include "LuaSocket.h"
CLuaLoader gLuaLoader;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLuaLoader::CLuaLoader() // OK
{
	this->m_luaState = NULL;
	/*
	this->m_luaState = luaL_newstate();

	luaL_openlibs(this->m_luaState);
	lua_gc(this->m_luaState, LUA_GCCOLLECT, 0);

	LuaFunction(this->m_luaState);
	LuaMemoryRegister(this->m_luaState);
	LuaUserRegister(this->m_luaState);*/
}

CLuaLoader::~CLuaLoader() // OK
{
	/**
	if (this->m_luaState != NULL)
	{
		lua_close(this->m_luaState);
		this->m_luaState = NULL;
	}*/
}

void CLuaLoader::Load(char* path) // OK
{

	this->m_critical.lock();

	HANDLE file = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (file == INVALID_HANDLE_VALUE)
	{
		char errorMessage[512];
		snprintf(errorMessage, sizeof(errorMessage), "Error: Could not find or access the script file '%s'. Ensure the file path is correct and the file exists.", path);
		MessageBox(0, errorMessage, "Script Load Error", MB_ICONERROR | MB_OK);
		return;
	}

	this->m_luaState = 0;

	lua_State* lua = luaL_newstate();

	luaL_openlibs(lua);
	lua_pushcclosure(lua, LuaRequire, 0);
	lua_setglobal(lua, "require");
	lua_gc(lua, LUA_GCCOLLECT, 0);

	LuaFunction(lua);
	LuaMemoryRegister(lua); // Lua Memory
    LuaUserRegister(lua);// Lua User
	gSocket.SetGlobalFunctions(lua);


	if (luaL_loadfile(lua, path) != 0)
	{
		char errorMessage[512];
		snprintf(errorMessage, sizeof(errorMessage), "Error: Could not load Lua script '%s'. Lua error message: %s\nThe client will now close.", path, lua_tostring(lua, -1));
		MessageBox(0, errorMessage, "Script Load Error", MB_ICONERROR | MB_OK);
		gConsole.UtilConsole(1, "Could not load '%s'. %s", path, lua_tostring(lua, -1));
		CloseHandle(file);
		this->m_critical.unlock();
		return;
	}

	if (lua_pcall(lua, 0, 0, 0) != 0)
	{
		char errorMessage[512];
		snprintf(errorMessage, sizeof(errorMessage), "Error: Lua runtime error in file '%s'. Lua error message: %s\nThe client will now close.", path, lua_tostring(lua, -1));
		MessageBox(0, errorMessage, "Script Execution Error", MB_ICONERROR | MB_OK);
		gConsole.UtilConsole(1, "Error in Lua-file. %s", lua_tostring(lua, -1));
		CloseHandle(file);
		this->m_critical.unlock();
		return;
	}

	this->m_luaState = lua;

	CloseHandle(file);

	this->m_critical.unlock();

}


void CLuaLoader::MainLoader() // OK
{

	this->m_critical.lock();

	if(this->m_luaState == 0)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"MainLoader");

	if(lua_pcall(this->m_luaState,0,0,0) != 0)
	{
		gConsole.UtilConsole(1,"%s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();

}


void CLuaLoader::MainProcThread() // OK
{

	this->m_critical.lock();

	if(this->m_luaState == 0)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"MainProcThread");

	if(lua_pcall(this->m_luaState,0,0,0) != 0)
	{
		gConsole.UtilConsole(1,"%s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();

}

void CLuaLoader::KeyboardEvent(int index) // OK
{

	this->m_critical.lock();

	if(this->m_luaState == 0)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"KeyboardEvent");

	lua_pushinteger(this->m_luaState,index);

	if(lua_pcall(this->m_luaState,1,0,0) != 0)
	{
		gConsole.UtilConsole(1,"%s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();

}


void CLuaLoader::ClientProtocol(BYTE head, char* packet_name)
{

	this->m_critical.lock();

	if (this->m_luaState == 0) // Verificamos que el estado de Lua sea válido
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState, "ClientProtocol"); // Obtenemos la función global "ClientProtocol"

	lua_pushinteger(this->m_luaState, head);           // Pasamos el parámetro 'head' a la pila de Lua
	lua_pushstring(this->m_luaState, packet_name);     // Pasamos el parámetro 'packet_name' a la pila de Lua

	if (lua_pcall(this->m_luaState, 2, 0, 0) != 0)     // Llamamos la función Lua con 2 argumentos y sin retorno
	{
		gConsole.UtilConsole(1, "%s", lua_tostring(this->m_luaState, -1)); // Imprimimos el error en caso de fallo
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();


}



void CLuaLoader::LoadImages() // OK
{


	this->m_critical.lock();

	if (this->m_luaState == 0)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState, "LoadImages");

	if (lua_pcall(this->m_luaState, 0, 0, 0) != 0)
	{
		gConsole.UtilConsole(1, "%s", lua_tostring(this->m_luaState, -1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();


}

lua_State* CLuaLoader::GetState()
{
	return this->m_luaState;
}

