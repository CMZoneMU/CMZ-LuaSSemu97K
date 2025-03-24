#pragma once
#include "stdafx.h"

#define SCRIPT_SSEMU_CODE_ERROR0 "[No argument's allowed]"
#define SCRIPT_SSEMU_CODE_ERROR1 "[%d argument's expected]"
#define SCRIPT_SSEMU_CODE_ERROR2 "[Minimum %d argument's expected]"

void InitLua();
void LuaOnStartMain();
void LuaOnTimerThread();
void LuaLockActions();
extern int LockCharacterAction;
