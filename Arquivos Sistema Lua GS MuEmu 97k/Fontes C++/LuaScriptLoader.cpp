// ScriptLoader.cpp: implementation of the CScriptLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Log.h"
#include "ServerInfo.h"
#include "Util.h"
#include "SocketManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CScriptLoader gScriptLoader;
CScriptLoader::CScriptLoader() // OK
{
	this->m_luaState = NULL;
	this->m_Reloading = true;
}

CScriptLoader::~CScriptLoader() // OK
{
	this->OnShutScript();

	this->m_luaQueue.ClearQueue();
}

void CScriptLoader::Load(char* path) // OK
{
	this->m_critical.lock();

	this->m_luaQueue.ClearQueue();

	this->m_luaState = NULL;

	lua_State* lua = luaL_newstate();

	luaL_openlibs(lua);
	lua_pushcclosure(lua,LuaRequire,0);
	lua_setglobal(lua,"require");
	lua_gc(lua,LUA_GCCOLLECT,0);

	InitLuaFunction(lua);


	if(luaL_loadfile(lua,path) != 0)
    {
		LogAdd(LOG_RED,"[ScriptLoader] Could not load '%s'. %s",path,lua_tostring(lua,-1));
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(lua,-1));
		lua_close(lua);
		this->m_critical.unlock();
        return;
    }

	if(lua_pcall(lua,0,0,0) != 0)
    {
		LogAdd(LOG_RED,"[ScriptLoader] Error in Lua-file. %s",lua_tostring(lua,-1));
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(lua,-1));
		lua_close(lua);
		this->m_critical.unlock();
        return;
    }

	this->m_luaState = lua;

	this->m_critical.unlock();
}

void CScriptLoader::SetInfo(LUA_QUEUE_INFO* lpInfo) // OK
{
	this->m_luaQueue.AddToQueue(lpInfo);
}

void CScriptLoader::OnReadScript() // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnReadScript");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnReadScript' is not defined.");
		this->m_critical.unlock();
		return;
    }

	if(lua_pcall(this->m_luaState,0,0,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();
}

void CScriptLoader::OnShutScript() // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnShutScript");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnShutScript' is not defined.");
		this->m_critical.unlock();
		return;
    }

	if(lua_pcall(this->m_luaState,0,0,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();
}

void CScriptLoader::OnTimerThread() // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnTimerThread");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnTimerThread' is not defined.");
		this->m_critical.unlock();
		return;
    }

	if(lua_pcall(this->m_luaState,0,0,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();
}

int CScriptLoader::OnCommandManager(int aIndex,int code,char* arg) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return 0;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnCommandManager");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnCommandManager' is not defined.");
		this->m_critical.unlock();
		return 0;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	lua_pushinteger(this->m_luaState,code);

	lua_pushstring(this->m_luaState,arg);

	if(lua_pcall(this->m_luaState,3,1,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return 0;
	}

	if(lua_isnumber(this->m_luaState,-1) == 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: 'OnCommandManager' must return a value.");
		this->m_critical.unlock();
		return 0;
	}

	int value = static_cast<int>(lua_tointeger(this->m_luaState, -1));
	
	lua_pop(this->m_luaState,1);

	this->m_critical.unlock();
	return value;
}

void CScriptLoader::OnCommandDone(int aIndex,int code) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnCommandDone");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnCommandDone' is not defined.");
		this->m_critical.unlock();
		return;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	lua_pushinteger(this->m_luaState,code);

	if(lua_pcall(this->m_luaState,2,0,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();
}

void CScriptLoader::OnCharacterEntry(int aIndex) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnCharacterEntry");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnCharacterEntry' is not defined.");
		this->m_critical.unlock();
		return;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	if(lua_pcall(this->m_luaState,1,0,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();
}

void CScriptLoader::OnCharacterClose(int aIndex) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnCharacterClose");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnCharacterClose' is not defined.");
		this->m_critical.unlock();
		return;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	if(lua_pcall(this->m_luaState,1,0,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();
}

int CScriptLoader::OnNpcTalk(int aIndex,int bIndex) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return 0;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnNpcTalk");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnNpcTalk' is not defined.");
		this->m_critical.unlock();
		return 0;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	lua_pushinteger(this->m_luaState,bIndex);

	if(lua_pcall(this->m_luaState,2,1,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return 0;
	}

	if(lua_isnumber(this->m_luaState,-1) == 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: 'OnNpcTalk' must return a value.");
		this->m_critical.unlock();
		return 0;
	}

	//int value = lua_tointeger(this->m_luaState,-1);

	int value = static_cast<int>(lua_tointeger(this->m_luaState, -1));
	
	lua_pop(this->m_luaState,1);

	this->m_critical.unlock();
	return value;
}

void CScriptLoader::OnMonsterDie(int aIndex,int bIndex) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnMonsterDie");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnMonsterDie' is not defined.");
		this->m_critical.unlock();
		return;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	lua_pushinteger(this->m_luaState,bIndex);

	if(lua_pcall(this->m_luaState,2,0,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();
}

void CScriptLoader::OnUserDie(int aIndex,int bIndex) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnUserDie");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnUserDie' is not defined.");
		this->m_critical.unlock();
		return;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	lua_pushinteger(this->m_luaState,bIndex);

	if(lua_pcall(this->m_luaState,2,0,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();
}

void CScriptLoader::OnUserMove(int aIndex,int MapIndex) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnUserMove");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnUserMove' is not defined.");
		this->m_critical.unlock();
		return;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	lua_pushinteger(this->m_luaState,MapIndex);

	if(lua_pcall(this->m_luaState,2,0,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();
}

void CScriptLoader::OnUserRespawn(int aIndex,int KillerType) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnUserRespawn");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnUserRespawn' is not defined.");
		this->m_critical.unlock();
		return;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	lua_pushinteger(this->m_luaState,KillerType);

	if(lua_pcall(this->m_luaState,2,0,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();
}

int CScriptLoader::OnCheckUserTarget(int aIndex,int bIndex) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return 1;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnCheckUserTarget");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnCheckUserTarget' is not defined.");
		this->m_critical.unlock();
		return 1;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	lua_pushinteger(this->m_luaState,bIndex);

	if(lua_pcall(this->m_luaState,2,1,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return 1;
	}

	if(lua_isnumber(this->m_luaState,-1) == 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: 'OnCheckUserTarget' must return a value.");
		this->m_critical.unlock();
		return 1;
	}

	int value = static_cast<int>(lua_tointeger(this->m_luaState, -1));
	
	lua_pop(this->m_luaState,1);

	this->m_critical.unlock();
	return value;
}

int CScriptLoader::OnCheckUserKiller(int aIndex,int bIndex) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return 1;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnCheckUserKiller");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnCheckUserKiller' is not defined.");
		this->m_critical.unlock();
		return 1;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	lua_pushinteger(this->m_luaState,bIndex);

	if(lua_pcall(this->m_luaState,2,1,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return 1;
	}

	if(lua_isnumber(this->m_luaState,-1) == 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: 'OnCheckUserKiller' must return a value.");
		this->m_critical.unlock();
		return 1;
	}

	int value = static_cast<int>(lua_tointeger(this->m_luaState, -1));
	
	lua_pop(this->m_luaState,1);

	this->m_critical.unlock();
	return value;
}

int CScriptLoader::OnUserItemPick(int aIndex,int slot) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return 1;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnUserItemPick");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnUserItemPick' is not defined.");
		this->m_critical.unlock();
		return 1;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	lua_pushinteger(this->m_luaState,slot);

	if(lua_pcall(this->m_luaState,2,1,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return 1;
	}

	if(lua_isnumber(this->m_luaState,-1) == 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: 'OnUserItemPick' must return a value.");
		this->m_critical.unlock();
		return 1;
	}

	int value = static_cast<int>(lua_tointeger(this->m_luaState, -1));
	
	lua_pop(this->m_luaState,1);

	this->m_critical.unlock();
	return value;
}

int CScriptLoader::OnUserItemDrop(int aIndex,int slot,int x,int y) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return 1;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnUserItemDrop");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnUserItemDrop' is not defined.");
		this->m_critical.unlock();
		return 1;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	lua_pushinteger(this->m_luaState,slot);

	lua_pushinteger(this->m_luaState,x);

	lua_pushinteger(this->m_luaState,y);

	if(lua_pcall(this->m_luaState,4,1,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return 1;
	}

	if(lua_isnumber(this->m_luaState,-1) == 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: 'OnUserItemDrop' must return a value.");
		this->m_critical.unlock();
		return 1;
	}

	
	int value = static_cast<int>(lua_tointeger(this->m_luaState, -1));

	lua_pop(this->m_luaState,1);

	this->m_critical.unlock();
	return value;
}

int CScriptLoader::OnUserItemMove(int aIndex,int aFlag,int aSlot,int bFlag,int bSlot) // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return 1;
	}

	lua_getglobal(this->m_luaState,"BridgeFunction_OnUserItemMove");

	if(lua_isfunction(this->m_luaState,-1) == 0)
    {
        gLog.Output(LOG_SCRIPT,"Error: Function 'OnUserItemMove' is not defined.");
		this->m_critical.unlock();
		return 1;
    }

	lua_pushinteger(this->m_luaState,aIndex);

	lua_pushinteger(this->m_luaState,aFlag);

	lua_pushinteger(this->m_luaState,aSlot);

	lua_pushinteger(this->m_luaState,bFlag);

	lua_pushinteger(this->m_luaState,bSlot);

	if(lua_pcall(this->m_luaState,5,1,0) != 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
		this->m_critical.unlock();
		return 1;
	}

	if(lua_isnumber(this->m_luaState,-1) == 0)
	{
		gLog.Output(LOG_SCRIPT,"Error: 'OnUserItemMove' must return a value.");
		this->m_critical.unlock();
		return 1;
	}
	
	int value = static_cast<int>(lua_tointeger(this->m_luaState, -1));

	lua_pop(this->m_luaState,1);

	this->m_critical.unlock();
	return value;
}

void CScriptLoader::OnSQLAsyncResult() // OK
{
	this->m_critical.lock();

	if(this->m_luaState == NULL)
	{
		this->m_critical.unlock();
		return;
	}

	if(gQueryManager.GetStatus() == SQL_NULL_HANDLE)
	{
		this->m_critical.unlock();
		return;
	}

	static LUA_QUEUE_INFO QueueInfo;

	if(this->m_luaQueue.GetFromQueue(&QueueInfo) != 0)
	{
		int result = ((gQueryManager.ExecQuery(QueueInfo.query) == 0 || gQueryManager.Fetch() == SQL_NO_DATA)?0:1);

		gQueryManager.Close();

		lua_getglobal(this->m_luaState,"BridgeFunction_OnSQLAsyncResult");

		if(lua_isfunction(this->m_luaState,-1) == 0)
		{
			gLog.Output(LOG_SCRIPT,"Error: Function 'OnSQLAsyncResult' is not defined.");
			this->m_critical.unlock();
			return;
		}

		lua_pushstring(this->m_luaState,QueueInfo.label);

		lua_pushstring(this->m_luaState,QueueInfo.param);

		lua_pushinteger(this->m_luaState,result);

		if(lua_pcall(this->m_luaState,3,0,0) != 0)
		{
			gLog.Output(LOG_SCRIPT,"Error: %s",lua_tostring(this->m_luaState,-1));
			this->m_critical.unlock();
			return;
		}
	}

	this->m_critical.unlock();
}


void CScriptLoader::ProcessErrorLog(lua_State* L, std::string func, int nStatus)
{
	if (nStatus != 0)
	{
		std::string szError = luaL_checklstring(L, -1, 0);
		szError = "[" + func + "] error: " + szError;
		LogAdd(LOG_RED, (char*)szError.c_str());
		lua_pop(L, 1);
	}
}


