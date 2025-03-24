// LuaLoader.h: interface for the CLuaLoader class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "CriticalSection.h"

static char* LoaderLua = "Data\\Custom\\Lua\\Main.lua";


class CLuaLoader
{
public:
	CLuaLoader();
	virtual ~CLuaLoader();
	void Load(char* path);
	void MainLoader();
	void MainProcThread();
	void KeyboardEvent(int index);
	void LoadImages();
	void ClientProtocol(BYTE head, char* packet_name);

	lua_State* GetState();

	lua_State* m_luaState;
	CCriticalSection m_critical;

};

extern CLuaLoader gLuaLoader;
