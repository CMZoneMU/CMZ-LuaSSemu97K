#include "stdafx.h"
#include "LuaSSEMU.h"
#include "LuaLoader.h"
#include "Offsets.h"
#include "Util.h"
#include "LuaMemory.h"
#include "LuaSocket.h"
#include "LuaFunction.h"
#include "LuaMemory.h"
#include "LuaUser.h"

int LockCharacterAction = 0;

void InitLua() // OK
{

	SetCompleteHook(0xE8,0x00510DEF,&LuaOnStartMain); //5B0581

	SetCompleteHook(0xE8,0x00521D60,&LuaOnTimerThread); //5C2ECC

	SetCompleteHook(0xE8,0x00524B05,&LuaOnTimerThread); //5C6631

	SetCompleteHook(0xE8,0x00525D26,&LuaOnTimerThread); //5C7C0E

	SetCompleteHook(0xE8,0x00525972,&LuaLockActions); //5C7782

}

void LuaOnStartMain() // OK
{

	gLuaLoader.MainLoader();

	((void(*)())0x0050F030)(); //5ADA30

}

void LuaOnTimerThread() // OK
{

	gLuaLoader.MainProcThread();

	((void(*)())0x004BFFA0)(); //548490

}

void LuaLockActions() // OK
{

	if(LockCharacterAction != 0)
	{
		return;
	}

	((void(*)())0x004ACEF0)(); //5340C0

}

