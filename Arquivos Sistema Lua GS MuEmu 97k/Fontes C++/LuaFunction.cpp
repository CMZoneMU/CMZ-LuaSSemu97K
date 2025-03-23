#include "stdafx.h"
#include "CommandManager.h"
#include "Console.h"
#include "DefaultClassInfo.h"
#include "DSProtocol.h"
#include "EffectManager.h"
#include "GameMaster.h"
#include "Gate.h"
#include "GuildManager.h"
#include "ItemBagManager.h"
#include "JSProtocol.h"
#include "Log.h"
#include "Map.h"
#include "MapManager.h"
#include "Message.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "Notice.h"
#include "ObjectManager.h"
#include "Party.h"
#include "Path.h"
#include "Quest.h"
#include "ServerInfo.h"
#include "User.h"
#include "Util.h"
#include "Viewport.h"


static int sentinel_ = 0;

void InitLuaFunction(lua_State* L) // OK
{
	lua_register(L, "GET_ITEM", LuaGetItem);
	lua_register(L, "GetMinUserIndex", LuaGetMinUserIndex);
	lua_register(L, "GetMaxUserIndex", LuaGetMaxUserIndex);
	lua_register(L, "GetMinMonsterIndex", LuaGetMinMonsterIndex);
	lua_register(L, "GetMaxMonsterIndex", LuaGetMaxMonsterIndex);
	lua_register(L, "GetGameServerCode", LuaGetGameServerCode);
	lua_register(L, "GetGameServerCurUser", LuaGetGameServerCurUser);
	lua_register(L, "GetGameServerMaxUser", LuaGetGameServerMaxUser);

	lua_register(L, "GetGameServerVersion", LuaGetGameServerVersion); // ok

	lua_register(L, "GetLicenseCustomerName", LuaGetLicenseCustomerName);
	lua_register(L, "GetObjectConnected", LuaGetObjectConnected);
	lua_register(L, "GetObjectIpAddress", LuaGetObjectIpAddress);
	lua_register(L, "GetObjectHardwareId", LuaGetObjectHardwareId);
	lua_register(L, "GetObjectType", LuaGetObjectType);
	lua_register(L, "GetObjectAccount", LuaGetObjectAccount);
	lua_register(L, "GetObjectPassword", LuaGetObjectPassword);
	lua_register(L, "GetObjectName", LuaGetObjectName);
	lua_register(L, "GetObjectPersonalCode", LuaGetObjectPersonalCode);
	lua_register(L, "GetObjectClass", LuaGetObjectClass);
	lua_register(L, "GetObjectChangeUp", LuaGetObjectChangeUp);
	lua_register(L, "GetObjectLevel", LuaGetObjectLevel);
	lua_register(L, "GetObjectLevelUpPoint", LuaGetObjectLevelUpPoint);
	lua_register(L, "GetObjectMoney", LuaGetObjectMoney);
	lua_register(L, "GetObjectStrength", LuaGetObjectStrength);
	lua_register(L, "GetObjectDexterity", LuaGetObjectDexterity);
	lua_register(L, "GetObjectVitality", LuaGetObjectVitality);
	lua_register(L, "GetObjectEnergy", LuaGetObjectEnergy);
	lua_register(L, "GetObjectExtraStrength", LuaGetObjectExtraStrength);
	lua_register(L, "GetObjectExtraDexterity", LuaGetObjectExtraDexterity);
	lua_register(L, "GetObjectExtraVitality", LuaGetObjectExtraVitality);
	lua_register(L, "GetObjectExtraEnergy", LuaGetObjectExtraEnergy);
	lua_register(L, "GetObjectTotalStrength", LuaGetObjectTotalStrength);
	lua_register(L, "GetObjectTotalDexterity", LuaGetObjectTotalDexterity);
	lua_register(L, "GetObjectTotalVitality", LuaGetObjectTotalVitality);
	lua_register(L, "GetObjectTotalEnergy", LuaGetObjectTotalEnergy);
	lua_register(L, "GetObjectDefaultStrength", LuaGetObjectDefaultStrength);
	lua_register(L, "GetObjectDefaultDexterity", LuaGetObjectDefaultDexterity);
	lua_register(L, "GetObjectDefaultVitality", LuaGetObjectDefaultVitality);
	lua_register(L, "GetObjectDefaultEnergy", LuaGetObjectDefaultEnergy);
	lua_register(L, "GetObjectLive", LuaGetObjectLive);
	lua_register(L, "GetObjectLife", LuaGetObjectLife);
	lua_register(L, "GetObjectMaxLife", LuaGetObjectMaxLife);
	lua_register(L, "GetObjectMana", LuaGetObjectMana);
	lua_register(L, "GetObjectMaxMana", LuaGetObjectMaxMana);
	lua_register(L, "GetObjectBP", LuaGetObjectBP);
	lua_register(L, "GetObjectMaxBP", LuaGetObjectMaxBP);
	lua_register(L, "GetObjectDefense", LuaGetObjectDefense);
	lua_register(L, "GetObjectPKCount", LuaGetObjectPKCount);
	lua_register(L, "GetObjectPKLevel", LuaGetObjectPKLevel);
	lua_register(L, "GetObjectPKTimer", LuaGetObjectPKTimer);
	lua_register(L, "GetObjectMap", LuaGetObjectMap);
	lua_register(L, "GetObjectMapX", LuaGetObjectMapX);
	lua_register(L, "GetObjectMapY", LuaGetObjectMapY);
	lua_register(L, "GetObjectDeathMap", LuaGetObjectDeathMap);
	lua_register(L, "GetObjectDeathMapX", LuaGetObjectDeathMapX);
	lua_register(L, "GetObjectDeathMapY", LuaGetObjectDeathMapY);
	lua_register(L, "GetObjectAuthority", LuaGetObjectAuthority);
	lua_register(L, "GetObjectPartyNumber", LuaGetObjectPartyNumber);
	lua_register(L, "GetObjectGuildNumber", LuaGetObjectGuildNumber);
	lua_register(L, "GetObjectGuildStatus", LuaGetObjectGuildStatus);
	lua_register(L, "GetObjectGuildName", LuaGetObjectGuildName);
	lua_register(L, "GetObjectChange", LuaGetObjectChange);
	lua_register(L, "GetObjectInterface", LuaGetObjectInterface);
	lua_register(L, "GetObjectAccountLevel", LuaGetObjectAccountLevel);
	lua_register(L, "GetObjectAccountCoins", LuaGetObjectAccountCoins);
	lua_register(L, "GetObjectAccountExpireDate", LuaGetObjectAccountExpireDate);
	lua_register(L, "GetObjectReset", LuaGetObjectReset);
	lua_register(L, "GetObjectMasterReset", LuaGetObjectMasterReset);
	lua_register(L, "GetObjectOfflineFlag", LuaGetObjectOfflineFlag);
	lua_register(L, "GetObjectIndexByName", LuaGetObjectIndexByName);
	lua_register(L, "SetObjectLevel", LuaSetObjectLevel);
	lua_register(L, "SetObjectLevelUpPoint", LuaSetObjectLevelUpPoint);
	lua_register(L, "SetObjectMoney", LuaSetObjectMoney);
	lua_register(L, "SetObjectStrength", LuaSetObjectStrength);
	lua_register(L, "SetObjectDexterity", LuaSetObjectDexterity);
	lua_register(L, "SetObjectVitality", LuaSetObjectVitality);
	lua_register(L, "SetObjectEnergy", LuaSetObjectEnergy);
	lua_register(L, "SetObjectChatLimitTime", LuaSetObjectChatLimitTime);
	lua_register(L, "SetObjectPKCount", LuaSetObjectPKCount);
	lua_register(L, "SetObjectPKLevel", LuaSetObjectPKLevel);
	lua_register(L, "SetObjectPKTimer", LuaSetObjectPKTimer);
	lua_register(L, "SetObjectMap", LuaSetObjectMap);
	lua_register(L, "SetObjectMapX", LuaSetObjectMapX);
	lua_register(L, "SetObjectMapY", LuaSetObjectMapY);
	lua_register(L, "CharacterGetRespawnLocation", LuaCharacterGetRespawnLocation);
	lua_register(L, "ChatTargetSend", LuaChatTargetSend);
	lua_register(L, "CommandGetArgNumber", LuaCommandGetArgNumber);
	lua_register(L, "CommandGetArgString", LuaCommandGetArgString);
	lua_register(L, "CommandSend", LuaCommandSend);
	lua_register(L, "ConfigReadNumber", LuaConfigReadNumber);
	lua_register(L, "ConfigReadString", LuaConfigReadString);
	lua_register(L, "ConfigSaveString", LuaConfigSaveString);
	lua_register(L, "EffectAdd", LuaEffectAdd);
	lua_register(L, "EffectDel", LuaEffectDel);
	lua_register(L, "EffectCheck", LuaEffectCheck);
	lua_register(L, "EffectClear", LuaEffectClear);
	lua_register(L, "GetItemName", LuaGetItemName);
	lua_register(L, "GetMapName", LuaGetMapName);
	lua_register(L, "GetMonsterName", LuaGetMonsterName);
	lua_register(L, "FireworksSend", LuaFireworksSend);
	lua_register(L, "InventoryGetWearSize", LuaInventoryGetWearSize);
	lua_register(L, "InventoryGetMainSize", LuaInventoryGetMainSize);
	lua_register(L, "InventoryGetFullSize", LuaInventoryGetFullSize);
	lua_register(L, "InventoryGetItemTable", LuaInventoryGetItemTable);
	lua_register(L, "InventoryGetItemIndex", LuaInventoryGetItemIndex);
	lua_register(L, "InventoryGetItemCount", LuaInventoryGetItemCount);
	lua_register(L, "InventoryDelItemIndex", LuaInventoryDelItemIndex);
	lua_register(L, "InventoryDelItemCount", LuaInventoryDelItemCount);
	lua_register(L, "InventoryGetFreeSlotCount", LuaInventoryGetFreeSlotCount);
	lua_register(L, "InventoryCheckSpaceByItem", LuaInventoryCheckSpaceByItem);
	lua_register(L, "InventoryCheckSpaceBySize", LuaInventoryCheckSpaceBySize);
	lua_register(L, "ItemDrop", LuaItemDrop);
	lua_register(L, "ItemDropEx", LuaItemDropEx);
	lua_register(L, "ItemGive", LuaItemGive);
	lua_register(L, "ItemGiveEx", LuaItemGiveEx);
	lua_register(L, "LevelUpSend", LuaLevelUpSend);
	lua_register(L, "LogPrint", LuaLogPrint);
	lua_register(L, "LogColor", LuaLogColor);
	lua_register(L, "MapCheckAttr", LuaMapCheckAttr);
	lua_register(L, "MapGetItemTable", LuaMapGetItemTable);
	lua_register(L, "MessageGet", LuaMessageGet);
	lua_register(L, "MoneySend", LuaMoneySend);
	lua_register(L, "MonsterCount", LuaMonsterCount);
	lua_register(L, "MonsterCreate", LuaMonsterCreate);
	lua_register(L, "MonsterDelete", LuaMonsterDelete);
	lua_register(L, "MonsterSummonCreate", LuaMonsterSummonCreate);
	lua_register(L, "MonsterSummonDelete", LuaMonsterSummonDelete);
	lua_register(L, "MoveUser", LuaMoveUser);
	lua_register(L, "MoveUserEx", LuaMoveUserEx);
	lua_register(L, "MessageSend", LuaMessageSend);
	lua_register(L, "MessageSendToAll", LuaMessageSendToAll);
	lua_register(L, "MessageGlobalSend", LuaMessageGlobalSend);
	lua_register(L, "NoticeSend", LuaNoticeSend);
	lua_register(L, "NoticeSendToAll", LuaNoticeSendToAll);
	lua_register(L, "NoticeGlobalSend", LuaNoticeGlobalSend);
	lua_register(L, "PartyGetMemberCount", LuaPartyGetMemberCount);
	lua_register(L, "PartyGetMemberIndex", LuaPartyGetMemberIndex);
	lua_register(L, "ObjectGetCoin", LuaObjectGetCoin);
	lua_register(L, "ObjectAddCoin", LuaObjectAddCoin);
	lua_register(L, "ObjectSubCoin", LuaObjectSubCoin);
	lua_register(L, "PermissionCheck", LuaPermissionCheck);
	lua_register(L, "PermissionInsert", LuaPermissionInsert);
	lua_register(L, "PermissionRemove", LuaPermissionRemove);
	lua_register(L, "PKLevelSend", LuaPKLevelSend);
	lua_register(L, "QuestStateCheck", LuaQuestStateCheck);
	lua_register(L, "RandomGetNumber", LuaRandomGetNumber);
	lua_register(L, "SkinChangeSend", LuaSkinChangeSend);
	lua_register(L, "UserDisconnect", LuaUserDisconnect);
	lua_register(L, "UserGameLogout", LuaUserGameLogout);
	lua_register(L, "UserCalcAttribute", LuaUserCalcAttribute);
	lua_register(L, "UserInfoSend", LuaUserInfoSend);
	lua_register(L, "UserActionSend", LuaUserActionSend);
	lua_register(L, "UserSetAccountLevel", LuaUserSetAccountLevel);
	lua_register(L, "SQLConnect", LuaSQLConnect);
	lua_register(L, "SQLDisconnect", LuaSQLDisconnect);
	lua_register(L, "SQLCheck", LuaSQLCheck);
	lua_register(L, "SQLQuery", LuaSQLQuery);
	lua_register(L, "SQLClose", LuaSQLClose);
	lua_register(L, "SQLFetch", LuaSQLFetch);
	lua_register(L, "SQLGetResult", LuaSQLGetResult);
	lua_register(L, "SQLGetNumber", LuaSQLGetNumber);
	lua_register(L, "SQLGetSingle", LuaSQLGetSingle);
	lua_register(L, "SQLGetString", LuaSQLGetString);
	lua_register(L, "SQLAsyncConnect", LuaSQLAsyncConnect);
	lua_register(L, "SQLAsyncDisconnect", LuaSQLAsyncDisconnect);
	lua_register(L, "SQLAsyncCheck", LuaSQLAsyncCheck);
	lua_register(L, "SQLAsyncQuery", LuaSQLAsyncQuery);
	lua_register(L, "SQLAsyncGetResult", LuaSQLAsyncGetResult);
	lua_register(L, "SQLAsyncGetNumber", LuaSQLAsyncGetNumber);
	lua_register(L, "SQLAsyncGetSingle", LuaSQLAsyncGetSingle);
	lua_register(L, "SQLAsyncGetString", LuaSQLAsyncGetString);
	lua_register(L, "GetGameServerProtocol", LuaGetGameServerProtocol);

}

int LuaRequire(lua_State* L)
{
	char buff[256];

	wsprintf(buff, gPath.GetFullPath("\\Script\\%s.lua"), luaL_checklstring(L, 1, 0));

	lua_settop(L, 1);
	lua_getfield(L, LUA_REGISTRYINDEX, "_LOADED");
	lua_getfield(L, 2, buff);

	if (lua_toboolean(L, -1))
	{
		if (lua_touserdata(L, -1) == ((void*)&sentinel_))
		{
			LogAdd(LOG_RED, "[ScriptLoader] Error in Lua-file. %s", lua_tostring(L, -1));
			return 0;
		}
	}

	if (luaL_loadfile(L, buff))
	{
		LogAdd(LOG_RED, "[ScriptLoader] Could not load '%s'. %s", buff, lua_tostring(L, -1));
		return 0;
	}

	lua_pushlightuserdata(L, ((void*)&sentinel_));
	lua_setfield(L, 2, buff);
	lua_pushstring(L, buff);

	lua_call(L, 1, 1);

	if (lua_type(L, -1))
	{
		lua_setfield(L, 2, buff);
	}

	lua_getfield(L, 2, buff);

	if (lua_touserdata(L, -1) == ((void*)&sentinel_))
	{
		lua_pushboolean(L, 1);
		lua_pushvalue(L, -1);
		lua_setfield(L, 2, buff);
	}

	return 1;
}

int LuaGetItem(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));
	int bValue = static_cast<int>(lua_tointeger(L, 2));

	lua_pushinteger(L, GET_ITEM(aValue, bValue));
	return 1;
}

int LuaGetMaxIndex(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, MAX_OBJECT);
	return 1;
}

int LuaGetGameServerVersion(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, GAMESERVER_EXTRA);
	return 1;
}

int LuaGetMinUserIndex(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, OBJECT_START_USER);
	return 1;
}

int LuaGetMaxUserIndex(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, OBJECT_START_USER + MAX_OBJECT_USER);
	return 1;
}

int LuaGetMinMonsterIndex(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, OBJECT_START_MONSTER);
	return 1;
}

int LuaGetMaxMonsterIndex(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, OBJECT_START_MONSTER + MAX_OBJECT_MONSTER);
	return 1;
}

int LuaGetGameServerCode(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, gServerInfo.m_ServerCode);
	return 1;
}

int LuaGetGameServerCurUser(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, gObjTotalUser);
	return 1;
}

int LuaGetGameServerMaxUser(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, gServerInfo.m_ServerMaxUserNumber);
	return 1;
}

int LuaGetLicenseCustomerName(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushstring(L, "MuOnline");
	return 1;
}

int LuaGetObjectConnected(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Connected);
	return 1;
}

int LuaGetObjectIpAddress(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushstring(L, gObj[aIndex].IpAddr);
	return 1;
}

int LuaGetObjectHardwareId(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushstring(L, gObj[aIndex].HardwareID);
	return 1;
}

int LuaGetGameServerProtocol(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, MAX_LANGUAGE);
	return 1;
}

int LuaGetObjectType(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Type);
	return 1;
}

int LuaGetObjectAccount(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushstring(L, gObj[aIndex].Account);
	return 1;
}

int LuaGetObjectPassword(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushstring(L, gObj[aIndex].Password);
	return 1;
}

int LuaGetObjectName(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushstring(L, gObj[aIndex].Name);
	return 1;
}

int LuaGetObjectPersonalCode(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushstring(L, gObj[aIndex].PersonalCode);
	return 1;
}

int LuaGetObjectClass(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Class);
	return 1;
}

int LuaGetObjectChangeUp(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Change);
	return 1;
}

int LuaGetObjectLevel(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Level);
	return 1;
}

int LuaGetObjectLevelUpPoint(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].LevelUpPoint);
	return 1;
}

int LuaGetObjectMoney(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Money);
	return 1;
}

int LuaGetObjectStrength(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Strength);
	return 1;
}

int LuaGetObjectDexterity(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Dexterity);
	return 1;
}

int LuaGetObjectVitality(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Vitality);
	return 1;
}

int LuaGetObjectEnergy(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Energy);
	return 1;
}

int LuaGetObjectExtraStrength(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Strength);
	return 1;
}

int LuaGetObjectExtraDexterity(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Dexterity);
	return 1;
}

int LuaGetObjectExtraVitality(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Vitality);
	return 1;
}

int LuaGetObjectExtraEnergy(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Energy);
	return 1;
}

int LuaGetObjectTotalStrength(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, (gObj[aIndex].Strength + gObj[aIndex].Strength));
	return 1;
}

int LuaGetObjectTotalDexterity(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, (gObj[aIndex].Dexterity + gObj[aIndex].Dexterity));
	return 1;
}

int LuaGetObjectTotalVitality(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, (gObj[aIndex].Vitality + gObj[aIndex].Vitality));
	return 1;
}

int LuaGetObjectTotalEnergy(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, (gObj[aIndex].Energy + gObj[aIndex].Energy));
	return 1;
}

int LuaGetObjectDefaultStrength(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gDefaultClassInfo.GetCharacterDefaultStat(gObj[aIndex].Class, 0));
	return 1;
}

int LuaGetObjectDefaultDexterity(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gDefaultClassInfo.GetCharacterDefaultStat(gObj[aIndex].Class, 1));
	return 1;
}

int LuaGetObjectDefaultVitality(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gDefaultClassInfo.GetCharacterDefaultStat(gObj[aIndex].Class, 2));
	return 1;
}

int LuaGetObjectDefaultEnergy(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gDefaultClassInfo.GetCharacterDefaultStat(gObj[aIndex].Class, 3));
	return 1;
}

int LuaGetObjectLive(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Live);
	return 1;
}

int LuaGetObjectLife(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, (int)gObj[aIndex].Life);
	return 1;
}

int LuaGetObjectMaxLife(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, (int)gObj[aIndex].MaxLife);
	return 1;
}

int LuaGetObjectMana(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, (int)gObj[aIndex].Mana);
	return 1;
}

int LuaGetObjectMaxMana(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, (int)gObj[aIndex].MaxMana);
	return 1;
}

int LuaGetObjectBP(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].BP);
	return 1;
}

int LuaGetObjectMaxBP(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].MaxBP);
	return 1;
}

int LuaGetObjectDefense(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Defense);
	return 1;
}

int LuaGetObjectPKCount(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].PKCount);
	return 1;
}

int LuaGetObjectPKLevel(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].PKLevel);
	return 1;
}

int LuaGetObjectPKTimer(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].PKTime);
	return 1;
}

int LuaGetObjectMap(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Map);
	return 1;
}

int LuaGetObjectMapX(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].X);
	return 1;
}

int LuaGetObjectMapY(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Y);
	return 1;
}

int LuaGetObjectDeathMap(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].DeathMap);
	return 1;
}

int LuaGetObjectDeathMapX(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].DeathX);
	return 1;
}

int LuaGetObjectDeathMapY(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].DeathY);
	return 1;
}

int LuaGetObjectAuthority(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Authority);
	return 1;
}

int LuaGetObjectPartyNumber(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].PartyNumber);
	return 1;
}

int LuaGetObjectGuildNumber(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (gObj[aIndex].Guild == 0)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].GuildNumber);
	return 1;
}

int LuaGetObjectGuildStatus(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (gObj[aIndex].Guild == 0)
	{
		lua_pushinteger(L, -1);
		return 1;
	}

	lua_pushinteger(L, gObj[aIndex].GuildStatus);

	return 1;
}

int LuaGetObjectGuildName(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (gObj[aIndex].Guild == 0)
	{
		return 0;
	}

	lua_pushstring(L, gObj[aIndex].GuildName);
	return 1;
}

int LuaGetObjectChange(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Change);
	return 1;
}

int LuaGetObjectInterface(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Interface.type);
	return 1;
}

int LuaGetObjectAccountLevel(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].AccountLevel);
	return 1;
}

int LuaGetObjectAccountCoins(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].MuCoins);
	return 1;
}

int LuaGetObjectAccountExpireDate(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushstring(L, gObj[aIndex].AccountExpireDate);
	return 1;
}

int LuaGetObjectReset(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Reset);
	return 1;
}

int LuaGetObjectMasterReset(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].GrandReset);
	return 1;
}

int LuaGetObjectOfflineFlag(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	/*	if (gObj[aIndex].Attack.Offline != 0)
		{
			lua_pushinteger(L,1);
		}
		else
		{
			lua_pushinteger(L,0);
		}
	*/
	return 1;
}

int LuaGetObjectIndexByName(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	const char* aString = lua_tostring(L, 1);

	LPOBJ lpTarget = gObjFind((char*)aString);

	if (lpTarget == 0)
	{
		lua_pushinteger(L, -1);
	}
	else
	{
		lua_pushinteger(L, lpTarget->Index);
	}

	return 1;
}

int LuaSetObjectLevel(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	gObj[aIndex].Level = aValue;

	return 1;
}

int LuaSetObjectLevelUpPoint(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gObj[aIndex].LevelUpPoint = (aValue < 0) ? 0 : aValue;

	return 1;
}

int LuaSetObjectMoney(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gObj[aIndex].Money = (aValue < 0) ? 0 : aValue;
	gObj[aIndex].Money = (gObj[aIndex].Money > MAX_MONEY) ? MAX_MONEY : gObj[aIndex].Money;

	return 1;
}

int LuaSetObjectStrength(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	int Min = gDefaultClassInfo.GetCharacterDefaultStat(gObj[aIndex].Class, 0);
	int Max = gServerInfo.m_MaxStatPoint[gObj[aIndex].AccountLevel];

	gObj[aIndex].Strength = (aValue < Min) ? Min : ((aValue > Max) ? Max : aValue);

	return 1;
}

int LuaSetObjectDexterity(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	int Min = gDefaultClassInfo.GetCharacterDefaultStat(gObj[aIndex].Class, 1);
	int Max = gServerInfo.m_MaxStatPoint[gObj[aIndex].AccountLevel];

	gObj[aIndex].Dexterity = (aValue < Min) ? Min : ((aValue > Max) ? Max : aValue);

	return 1;
}

int LuaSetObjectVitality(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	int Min = gDefaultClassInfo.GetCharacterDefaultStat(gObj[aIndex].Class, 2);
	int Max = gServerInfo.m_MaxStatPoint[gObj[aIndex].AccountLevel];

	gObj[aIndex].Vitality = (aValue < Min) ? Min : ((aValue > Max) ? Max : aValue);

	return 1;
}

int LuaSetObjectEnergy(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	int Min = gDefaultClassInfo.GetCharacterDefaultStat(gObj[aIndex].Class, 3);
	int Max = gServerInfo.m_MaxStatPoint[gObj[aIndex].AccountLevel];

	gObj[aIndex].Energy = (aValue < Min) ? Min : ((aValue > Max) ? Max : aValue);

	return 1;
}

int LuaSetObjectChatLimitTime(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gObj[aIndex].ChatLimitTime = aValue;
	gObj[aIndex].ChatLimitTimeSec = 0;

	return 1;
}

int LuaSetObjectPKCount(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gObj[aIndex].PKCount = aValue;

	return 1;
}

int LuaSetObjectPKLevel(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gObj[aIndex].PKLevel = aValue;

	return 1;
}

int LuaSetObjectPKTimer(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gObj[aIndex].PKTime = aValue;

	return 1;
}

int LuaSetObjectMap(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	gObj[aIndex].Map = aValue;

	return 1;
}

int LuaSetObjectMapX(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	gObj[aIndex].X = aValue;

	return 1;
}

int LuaSetObjectMapY(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	gObj[aIndex].Y = aValue;

	return 1;
}

int LuaCharacterGetRespawnLocation(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gObjectManager.CharacterGetRespawnLocation(&gObj[aIndex]);

	return 1;
}

int LuaChatTargetSend(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int bIndex = static_cast<int>(lua_tointeger(L, 2));
	const char* aString = lua_tostring(L, 3);

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (bIndex != -1)
	{
		if (OBJECT_RANGE(bIndex) == 0)
		{
			return 0;
		}

		if (gObj[bIndex].Type != OBJECT_USER)
		{
			return 0;
		}

		GCChatTargetSend(&gObj[bIndex], aIndex, (char*)aString);
	}
	else
	{
		for (int n = 0; n < MAX_VIEWPORT; n++)
		{
			if (gObj[aIndex].VpPlayer2[n].state != VIEWPORT_NONE && gObj[aIndex].VpPlayer2[n].type == OBJECT_USER)
			{
				GCChatTargetSend(&gObj[gObj[aIndex].VpPlayer2[n].index], aIndex, (char*)aString);
			}
		}
	}

	return 1;
}



int LuaCommandGetArgNumber(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	const char* aString = lua_tostring(L, 1);
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	int value = gCommandManager.GetNumber((char*)aString, aValue);

	lua_pushinteger(L, value);
	return 1;
}

int LuaCommandGetArgString(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	const char* aString = lua_tostring(L, 1);
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	char value[256] = { 0 };

	gCommandManager.GetString((char*)aString, value, sizeof(value), aValue);

	lua_pushstring(L, value);
	return 1;
}

int LuaCommandSend(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	const char* aString = lua_tostring(L, 2);

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gCommandManager.ManagementCore(&gObj[aIndex], (char*)aString);

	return 1;
}

int LuaConfigReadNumber(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}

	const char* aString = lua_tostring(L, 1);
	const char* bString = lua_tostring(L, 2);
	const char* cString = lua_tostring(L, 3);

	int value = GetPrivateProfileInt(aString, bString, 0, cString);

	lua_pushinteger(L, value);
	return 1;
}

int LuaConfigReadString(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}

	const char* aString = lua_tostring(L, 1);
	const char* bString = lua_tostring(L, 2);
	const char* cString = lua_tostring(L, 3);

	char value[256] = { 0 };

	GetPrivateProfileString(aString, bString, "", value, sizeof(value), cString);

	lua_pushstring(L, value);
	return 1;
}

int LuaConfigSaveString(lua_State* L) // OK
{
	if (lua_gettop(L) != 4)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 4);
	}

	const char* aString = lua_tostring(L, 1);
	const char* bString = lua_tostring(L, 2);
	const char* cString = lua_tostring(L, 3);
	const char* dString = lua_tostring(L, 4);

	WritePrivateProfileString(aString, bString, cString, dString);

	return 1;
}

int LuaEffectAdd(lua_State* L) // OK
{
	if (lua_gettop(L) != 8)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 8);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));
	int bValue = static_cast<int>(lua_tointeger(L, 3));
	int cValue = static_cast<int>(lua_tointeger(L, 4));
	int dValue = static_cast<int>(lua_tointeger(L, 5));
	int eValue = static_cast<int>(lua_tointeger(L, 6));
	int fValue = static_cast<int>(lua_tointeger(L, 7));
	int gValue = static_cast<int>(lua_tointeger(L, 8));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	gEffectManager.AddEffect(&gObj[aIndex], ((aValue > 0) ? 1 : 0), bValue, ((aValue == 0) ? cValue : (int)(time(0) + cValue)), dValue, eValue, fValue, gValue);

	return 1;
}

int LuaEffectDel(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tonumber(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	gEffectManager.DelEffect(&gObj[aIndex], aValue);

	return 1;
}

int LuaEffectCheck(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tonumber(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gEffectManager.CheckEffect(&gObj[aIndex], aValue) == 0)
	{
		lua_pushinteger(L, 0);
	}
	else
	{
		lua_pushinteger(L, 1);
	}

	return 1;
}

int LuaEffectClear(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));


	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	gEffectManager.ClearAllEffect(&gObj[aIndex]);

	return 1;
}

int LuaGetItemName(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aValue = (int)lua_tonumber(L, 1);
	int bValue = (int)lua_tonumber(L, 2);

	lua_pushstring(L, gItemManager.GetItemName(GET_ITEM(aValue, bValue)));

	return 1;
}

int LuaGetMapName(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aValue = (int)lua_tonumber(L, 1);

	lua_pushstring(L, gMapManager.GetMapName(aValue));

	return 1;
}

int LuaGetMonsterName(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aValue = (int)lua_tonumber(L, 1);

	lua_pushstring(L, gMonsterManager.GetMonsterName(aValue));

	return 1;
}


int LuaInventoryGetWearSize(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, INVENTORY_WEAR_SIZE);
	return 1;
}

int LuaInventoryGetMainSize(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, INVENTORY_SIZE);
	return 1;
}

int LuaInventoryGetFullSize(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	lua_pushinteger(L, INVENTORY_SIZE);
	return 1;
}

int LuaInventoryGetItemTable(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (gObj[aIndex].Inventory[aValue].IsItem() == 0)
	{
		lua_pushnil(L);
		return 0;
	}

	lua_newtable(L);

	lua_pushstring(L, "Serial");
	lua_pushnumber(L, gObj[aIndex].Inventory[aValue].m_Serial);
	lua_settable(L, -3);

	lua_pushstring(L, "Index");
	lua_pushnumber(L, gObj[aIndex].Inventory[aValue].m_Index);
	lua_settable(L, -3);

	lua_pushstring(L, "Level");
	lua_pushnumber(L, gObj[aIndex].Inventory[aValue].m_Level);
	lua_settable(L, -3);

	lua_pushstring(L, "Durability");
	lua_pushnumber(L, gObj[aIndex].Inventory[aValue].m_Durability);
	lua_settable(L, -3);

	lua_pushstring(L, "Option1");
	lua_pushnumber(L, gObj[aIndex].Inventory[aValue].m_SkillOption);
	lua_settable(L, -3);

	lua_pushstring(L, "Option2");
	lua_pushnumber(L, gObj[aIndex].Inventory[aValue].m_LuckOption);
	lua_settable(L, -3);

	lua_pushstring(L, "Option3");
	lua_pushnumber(L, gObj[aIndex].Inventory[aValue].m_AddOption);
	lua_settable(L, -3);

	lua_pushstring(L, "NewOption");
	lua_pushnumber(L, gObj[aIndex].Inventory[aValue].m_ExceOption);
	lua_settable(L, -3);

	return 1;
}

int LuaInventoryGetItemIndex(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (gObj[aIndex].Inventory[aValue].IsItem() == 0)
	{
		lua_pushnil(L);
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Inventory[aValue].m_Index);
	return 1;
}

int LuaInventoryGetItemCount(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));
	int bValue = static_cast<int>(lua_tonumber(L, 3));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gItemManager.GetInventoryItemCount(&gObj[aIndex], aValue, bValue));
	return 1;
}

int LuaInventoryDelItemIndex(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gItemManager.InventoryDelItem(aIndex, aValue);
	gItemManager.GCItemDeleteSend(aIndex, aValue, 1);
	gItemManager.UpdateInventoryViewport(aIndex, aValue);

	return 1;
}

int LuaInventoryDelItemCount(lua_State* L) // OK
{
	if (lua_gettop(L) != 4)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 4);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));
	int bValue = static_cast<int>(lua_tonumber(L, 3));
	int cValue = static_cast<int>(lua_tointeger(L, 4));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gItemManager.DeleteInventoryItemCount(&gObj[aIndex], aValue, bValue, cValue);

	return 1;
}

int LuaInventoryGetFreeSlotCount(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));


	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_pushinteger(L, gItemManager.GetInventoryEmptySlotCount(&gObj[aIndex]));
	return 1;
}

int LuaInventoryCheckSpaceByItem(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (gItemManager.CheckItemInventorySpace(&gObj[aIndex], aValue) == 0)
	{
		lua_pushinteger(L, 0);
	}
	else
	{
		lua_pushinteger(L, 1);
	}

	return 1;
}

int LuaInventoryCheckSpaceBySize(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));
	int bValue = static_cast<int>(lua_tointeger(L, 3));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (gItemManager.CheckItemInventorySpace(&gObj[aIndex], aValue, bValue) == 0)
	{
		lua_pushinteger(L, 0);
	}
	else
	{
		lua_pushinteger(L, 1);
	}

	return 1;
}

int LuaItemDrop(lua_State* L) // OK
{
	if (lua_gettop(L) != 5)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 5);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));
	int bValue = static_cast<int>(lua_tointeger(L, 3));
	int cValue = static_cast<int>(lua_tointeger(L, 4));
	int dValue = static_cast<int>(lua_tointeger(L, 5));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	CItem item;

	if (gItemBagManager.GetItemBySpecialValue(dValue, &gObj[aIndex], &item) == 0)
	{
		return 0;
	}

	GDCreateItemSend(aIndex, aValue, bValue, cValue, item.m_Index, (BYTE)item.m_Level, (BYTE)item.m_Durability, item.m_SkillOption, item.m_LuckOption, item.m_AddOption, aIndex, item.m_ExceOption);

	return 1;
}

int LuaItemDropEx(lua_State* L) // OK
{
	if (lua_gettop(L) < 11)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR2, 11);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));
	int bValue = static_cast<int>(lua_tointeger(L, 3));
	int cValue = static_cast<int>(lua_tointeger(L, 4));
	int dValue = static_cast<int>(lua_tointeger(L, 5));
	int eValue = static_cast<int>(lua_tointeger(L, 6));
	int fValue = static_cast<int>(lua_tointeger(L, 7));
	int gValue = static_cast<int>(lua_tointeger(L, 8));
	int hValue = static_cast<int>(lua_tointeger(L, 9));
	int iValue = static_cast<int>(lua_tointeger(L, 10));
	int jValue = static_cast<int>(lua_tointeger(L, 11));
	int kValue = static_cast<int>(luaL_opt(L, lua_tointeger, 12, 0));
	int lValue = static_cast<int>(luaL_opt(L, lua_tointeger, 13, 0));
	int mValue = static_cast<int>(luaL_opt(L, lua_tointeger, 14, 0));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	// GDCreateItemSend(aIndex, aValue, bValue, cValue, dValue, eValue, fValue, gValue, hValue, iValue, -1, jValue);
	GDCreateItemSend(aIndex, aValue, bValue, cValue, dValue, eValue, fValue, gValue, hValue, iValue, (lValue == 0) ? aIndex : lValue, jValue);

	return 1;

}

int LuaItemGive(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	CItem item;

	if (gItemBagManager.GetItemBySpecialValue(aValue, &gObj[aIndex], &item) == 0)
	{
		return 0;
	}

	GDCreateItemSend(aIndex, 0xEB, 0, 0, item.m_Index, (BYTE)item.m_Level, (BYTE)item.m_Durability, item.m_SkillOption, item.m_LuckOption, item.m_AddOption, -1, item.m_ExceOption);

	return 1;
}

int LuaItemGiveEx(lua_State* L) // OK
{
	if (lua_gettop(L) < 8)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR2, 8);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));
	int bValue = static_cast<int>(lua_tointeger(L, 3));
	int cValue = static_cast<int>(lua_tointeger(L, 4));
	int dValue = static_cast<int>(lua_tointeger(L, 5));
	int eValue = static_cast<int>(lua_tointeger(L, 6));
	int fValue = static_cast<int>(lua_tointeger(L, 7));
	int gValue = static_cast<int>(lua_tointeger(L, 8));
	int hValue = static_cast<int>(luaL_opt(L, lua_tointeger, 9, 0));
	int iValue = static_cast<int>(luaL_opt(L, lua_tointeger, 10, 0));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	GDCreateItemSend(aIndex, 0xEB, 0, 0, aValue, bValue, cValue, dValue, eValue, fValue, -1, gValue);

	return 1;

}

int LuaLevelUpSend(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	GCLevelUpSend(&gObj[aIndex]);

	return 1;
}

int LuaLogPrint(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	const char* aString = lua_tostring(L, 1);

	gLog.Output(LOG_SCRIPT, "%s", aString);

	return 1;
}

int LuaLogColor(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));
	const char* aString = lua_tostring(L, 2);

	switch (aValue)
	{
	case 0:
		LogAdd(LOG_BLACK, "%s", aString);
		break;
	case 1:
		LogAdd(LOG_RED, "%s", aString);
		break;
	case 2:
		LogAdd(LOG_GREEN, "%s", aString);
		break;
	case 3:
		LogAdd(LOG_BLUE, "%s", aString);
		break;
	}

	return 1;
}

int LuaMapCheckAttr(lua_State* L) // OK
{
	if (lua_gettop(L) != 4)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 4);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));
	int bValue = static_cast<int>(lua_tointeger(L, 2));
	int cValue = static_cast<int>(lua_tointeger(L, 3));
	int dValue = static_cast<int>(lua_tointeger(L, 4));

	if (gMap[aValue].CheckAttr(bValue, cValue, dValue) != 0)
	{
		lua_pushinteger(L, 1);
	}
	else
	{
		lua_pushinteger(L, 0);
	}

	return 1;
}

int LuaMapGetItemTable(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (gMap[gObj[aIndex].Map].m_Item[aValue].IsItem() == 0)
	{
		lua_pushnil(L);
		return 0;
	}

	lua_newtable(L);

	lua_pushstring(L, "Serial");
	lua_pushnumber(L, gMap[gObj[aIndex].Map].m_Item[aValue].m_Serial);
	lua_settable(L, -3);

	lua_pushstring(L, "Index");
	lua_pushnumber(L, gMap[gObj[aIndex].Map].m_Item[aValue].m_Index);
	lua_settable(L, -3);

	lua_pushstring(L, "Level");
	lua_pushnumber(L, gMap[gObj[aIndex].Map].m_Item[aValue].m_Level);
	lua_settable(L, -3);

	lua_pushstring(L, "Durability");
	lua_pushnumber(L, gMap[gObj[aIndex].Map].m_Item[aValue].m_Durability);
	lua_settable(L, -3);

	lua_pushstring(L, "Option1");
	lua_pushnumber(L, gMap[gObj[aIndex].Map].m_Item[aValue].m_SkillOption);
	lua_settable(L, -3);

	lua_pushstring(L, "Option2");
	lua_pushnumber(L, gMap[gObj[aIndex].Map].m_Item[aValue].m_LuckOption);
	lua_settable(L, -3);

	lua_pushstring(L, "Option3");
	lua_pushnumber(L, gMap[gObj[aIndex].Map].m_Item[aValue].m_AddOption);
	lua_settable(L, -3);

	lua_pushstring(L, "NewOption");
	lua_pushnumber(L, gMap[gObj[aIndex].Map].m_Item[aValue].m_ExceOption);
	lua_settable(L, -3);


	return 1;
}

int LuaMessageGet(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int index = luaL_checkinteger(L, 1);
	int aIndex = luaL_checkinteger(L, 2);

	if (aIndex < 0 || aIndex >= MAX_OBJECT)
	{
		lua_pushstring(L, "Invalid player index!");
		return 1;
	}

	if (!gObjIsConnected(aIndex))
	{
		lua_pushstring(L, "Player not connected!");
		return 1;
	}

	int lang = gObj[aIndex].Lang;


	if (lang < LANGUAGE_ENGLISH || lang >= MAX_LANGUAGE)
	{
		lang = LANGUAGE_ENGLISH;
	}


	lua_pushstring(L, gMessage.GetTextMessage(index, lang));
	return 1;
}

int LuaMoneySend(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	GCMoneySend(aIndex, aValue);

	return 1;
}

int LuaMonsterCount(lua_State* L) // OK
{
	if (lua_gettop(L) < 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR2, 2);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));
	int bValue = static_cast<int>(lua_tointeger(L, 2));
	int cValue = static_cast<int>(luaL_optinteger(L, 3, 1));
	int dValue = static_cast<int>(luaL_optinteger(L, 4, 1));
	int eValue = static_cast<int>(luaL_optinteger(L, 5, 255));
	int fValue = static_cast<int>(luaL_optinteger(L, 6, 255));

	lua_pushinteger(L, MonsterCount(aValue, bValue, cValue, dValue, eValue, fValue));

	return 1;
}

int LuaMonsterCreate(lua_State* L) // OK
{
	if (lua_gettop(L) != 5)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 5);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));
	int bValue = static_cast<int>(lua_tointeger(L, 2));
	int cValue = static_cast<int>(lua_tointeger(L, 3));
	int dValue = static_cast<int>(lua_tointeger(L, 4));
	int eValue = static_cast<int>(lua_tointeger(L, 5));

	int index = gObjAddMonster(bValue);

	if (OBJECT_RANGE(index) == 0)
	{
		return 0;
	}

	LPOBJ lpMonster = &gObj[index];

	lpMonster->PosNum = -1;
	lpMonster->X = cValue;
	lpMonster->Y = dValue;
	lpMonster->TX = cValue;
	lpMonster->TY = dValue;
	lpMonster->OldX = cValue;
	lpMonster->OldY = dValue;
	lpMonster->StartX = cValue;
	lpMonster->StartY = dValue;
	lpMonster->Dir = (eValue == -1) ? (GetLargeRand() % 8) : (BYTE)eValue;
	lpMonster->Map = bValue;

	if (gObjSetMonster(index, aValue) == 0)
	{
		gObjDel(index);
		return 0;
	}

	lua_pushinteger(L, index);
	return 1;
}

int LuaMonsterDelete(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));


	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	gObjDel(aIndex);

	return 1;
}

int LuaMonsterSummonCreate(lua_State* L) // Incompleto
{
	if (lua_gettop(L) != 7)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 7);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));
	int bValue = static_cast<int>(lua_tointeger(L, 3));
	int cValue = static_cast<int>(lua_tointeger(L, 4));
	int dValue = static_cast<int>(lua_tointeger(L, 5));
	int eValue = static_cast<int>(lua_tointeger(L, 6));
	int fValue = static_cast<int>(lua_tointeger(L, 7));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (OBJECT_RANGE(gObj[aIndex].SummonIndex) != 0)
	{
		gObjSummonKill(aIndex);
		GCSummonLifeSend(aIndex, 0, 1);
		return 0;
	}

	int index = gObjAddSummon();

	if (OBJECT_RANGE(index) == 0)
	{
		gObjDel(index);
		return 0;
	}

	gObj[aIndex].SummonIndex = index;

	gObj[index].X = gObj[aIndex].X - 1;
	gObj[index].Y = gObj[aIndex].Y + 1;
	gObj[index].MTX = gObj[index].X;
	gObj[index].MTY = gObj[index].Y;
	gObj[index].Dir = 2;
	gObj[index].Map = gObj[aIndex].Map;

	gObjSetMonster(index, aValue);

	gObj[index].Life += (float)((__int64)gObj[index].Life * bValue) / 100;
	gObj[index].MaxLife += (float)((__int64)gObj[index].MaxLife * bValue) / 100;
	gObj[index].Defense += ((__int64)gObj[index].Defense * cValue) / 100;
	gObj[index].DefenseSuccessRate += ((__int64)gObj[index].DefenseSuccessRate * dValue) / 100;
	gObj[index].PhysiDamageMin += ((__int64)gObj[index].PhysiDamageMin * eValue) / 100;
	gObj[index].PhysiDamageMax += ((__int64)gObj[index].PhysiDamageMax * eValue) / 100;
	gObj[index].AttackSuccessRate += ((__int64)gObj[index].AttackSuccessRate * fValue) / 100;
	gObj[index].SummonIndex = aIndex;
	//gObj[index].Attribute = ATTRIBUTE_SUMMONED;
	gObj[index].TargetNumber = -1;
	//gObj[index].ActionState.Reset;
	gObj[index].PathCount = 0;
	gObj[index].MoveRange = 15;

	GCSummonLifeSend(gObj[index].SummonIndex, (int)gObj[index].Life, (int)gObj[index].MaxLife);

	lua_pushinteger(L, index);
	return 1;
}

int LuaMonsterSummonDelete(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (OBJECT_RANGE(gObj[aIndex].SummonIndex) == 0)
	{
		return 0;
	}

	gObjSummonKill(aIndex);
	GCSummonLifeSend(aIndex, 0, 1);
	return 1;
}

int LuaMoveUser(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}


	gObjMoveGate(aIndex, aValue);


	return 1;
}

int LuaMoveUserEx(lua_State* L) // OK
{
	if (lua_gettop(L) != 4)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 4);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));
	int bValue = static_cast<int>(lua_tointeger(L, 3));
	int cValue = static_cast<int>(lua_tointeger(L, 4));


	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gObjTeleport(aIndex, aValue, bValue, cValue);

	return 1;
}

int LuaMessageSend(lua_State* L) // OK
{
	if (lua_gettop(L) != 4)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 4);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));
	int bValue = static_cast<int>(lua_tointeger(L, 3));
	const char* aString = lua_tostring(L, 4);

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	GCNewMessageSend(aIndex, aValue, bValue, "%s", aString);

	return 1;
}

int LuaMessageSendToAll(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));
	int bValue = static_cast<int>(lua_tointeger(L, 2));
	const char* aString = lua_tostring(L, 3);

	GCNewMessageSendToAll(aValue, bValue, "%s", aString);

	return 1;
}

int LuaMessageGlobalSend(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));
	int bValue = static_cast<int>(lua_tointeger(L, 2));
	const char* aString = lua_tostring(L, 3);

	GDGlobalMessageSend(aValue, bValue, "%s", aString);

	return 1;
}

int LuaNoticeSend(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	const char* aString = lua_tostring(L, 3);

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gNotice.GCNoticeSend(aIndex, aValue, "%s", aString);

	return 1;
}

int LuaNoticeSendToAll(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));
	const char* aString = lua_tostring(L, 2);

	gNotice.GCNoticeSendToAll(aValue, "%s", aString);

	return 1;
}

int LuaNoticeGlobalSend(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));
	const char* aString = lua_tostring(L, 2);

	GDGlobalNoticeSend(aValue, (char*)aString);

	return 1;
}

int LuaPartyGetMemberCount(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));

	int value = gParty.GetMemberCount(aValue);

	lua_pushinteger(L, value);
	return 1;
}

int LuaPartyGetMemberIndex(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));
	int bValue = static_cast<int>(lua_tointeger(L, 2));

	int value = gParty.GetMemberIndex(aValue, bValue);

	lua_pushinteger(L, value);
	return 1;
}

int LuaObjectGetCoin(lua_State* L) // Em teste Adaptado 
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	lua_newtable(L);

	lua_pushstring(L, "Coin1");
	lua_pushnumber(L, gObj[aIndex].MuCoins);
	lua_settable(L, -3);


	return 1;
}

int LuaObjectAddCoin(lua_State* L) // incompleto
{
	if (lua_gettop(L) != 4)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 4);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));



	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	return 1;
}

int LuaObjectSubCoin(lua_State* L) // incompleto
{
	if (lua_gettop(L) != 4)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 4);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));


	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	//gObjCoinSub(aIndex, aValue, 0, 0);

	return 1;
}

int LuaPermissionCheck(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 4);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (aValue < 0 || aValue >= 50)
	{
		return 0;
	}

	lua_pushinteger(L, gObj[aIndex].Permission[aValue]);

	return 1;
}

int LuaPermissionInsert(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (aValue < 0 || aValue >= 50)
	{
		return 0;
	}

	gObj[aIndex].Permission[aValue] = 1;

	return 1;
}

int LuaPermissionRemove(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (aValue < 0 || aValue >= 50)
	{
		return 0;
	}

	gObj[aIndex].Permission[aValue] = 0;

	return 1;
}

int LuaPKLevelSend(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	GCPKLevelSend(aIndex, aValue);

	return 1;
}

int LuaQuestStateCheck(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (gQuest.CheckQuestListState(&gObj[aIndex], aValue, QUEST_FINISH) != 0)
	{
		lua_pushinteger(L, 1);
	}
	else
	{
		lua_pushinteger(L, 0);
	}

	return 1;
}

int LuaRandomGetNumber(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));

	int value = GetLargeRand() % ((aValue < 1) ? 1 : aValue);

	lua_pushinteger(L, value);
	return 1;
}

int LuaSkinChangeSend(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gObj[aIndex].Change = aValue;
	gObjViewportListProtocolCreate(&gObj[aIndex]);

	return 1;
}

int LuaUserDisconnect(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));


	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	CloseClient(aIndex);

	return 1;
}

int LuaUserGameLogout(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	gObj[aIndex].CloseType = ((aValue < 0) ? 0 : (aValue > 2) ? 2 : aValue);
	gObj[aIndex].CloseCount = 6;

	return 1;
}

int LuaUserCalcAttribute(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gObjectManager.CharacterCalcAttribute(aIndex);

	return 1;
}

int LuaUserInfoSend(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	gObjCalcExperience(&gObj[aIndex]);
	GCNewCharacterInfoSend(&gObj[aIndex]);
	GDCharacterInfoSaveSend(aIndex);

	return 1;
}

int LuaUserActionSend(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int bIndex = static_cast<int>(lua_tointeger(L, 2));
	int aValue = static_cast<int>(lua_tointeger(L, 3));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (OBJECT_RANGE(bIndex) == 0)
	{
		return 0;
	}

	if (gObj[bIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	GCActionSend(&gObj[aIndex], aValue, aIndex, bIndex);

	return 1;
}

int LuaUserSetAccountLevel(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}

	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));
	int bValue = static_cast<int>(lua_tointeger(L, 3));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	GJAccountLevelSaveSend(aIndex, aValue, bValue);
	GJAccountLevelSend(aIndex);

	return 1;
}

int LuaSQLConnect(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}

	const char* aString = lua_tostring(L, 1);
	const char* bString = lua_tostring(L, 2);
	const char* cString = lua_tostring(L, 3);

	if (gQueryManager.Connect((char*)aString, (char*)bString, (char*)cString) == 0)
	{
		LogAdd(LOG_RED, "[LuaFunction][SQLConnect] Could not connect to database [%s][%s][%s]", aString, bString, cString);
		lua_pushinteger(L, 0);
	}
	else
	{
		lua_pushinteger(L, 1);
	}

	return 1;
}

int LuaSQLDisconnect(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	gQueryManager.Disconnect();

	return 1;
}

int LuaSQLCheck(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	if (gQueryManager.GetStatus() == 0)
	{
		lua_pushinteger(L, 0);
	}
	else
	{
		lua_pushinteger(L, 1);
	}

	return 1;
}

int LuaSQLQuery(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	const char* aString = lua_tostring(L, 1);

	if (gQueryManager.ExecQuery("%s", aString) == 0)
	{
		lua_pushinteger(L, 0);
	}
	else
	{
		lua_pushinteger(L, 1);
	}

	return 1;
}

int LuaSQLClose(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	gQueryManager.Close();

	return 1;
}

int LuaSQLFetch(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	if (gQueryManager.Fetch() == SQL_NO_DATA)
	{
		lua_pushinteger(L, 0);
	}
	else
	{
		lua_pushinteger(L, 1);
	}

	return 1;
}

int LuaSQLGetResult(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));


	int value = gQueryManager.GetResult(aValue);

	lua_pushinteger(L, value);
	return 1;
}

int LuaSQLGetNumber(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	const char* aString = lua_tostring(L, 1);

	int value = gQueryManager.GetAsInteger((char*)aString);

	lua_pushinteger(L, value);
	return 1;
}

int LuaSQLGetSingle(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	const char* aString = lua_tostring(L, 1);

	float value = gQueryManager.GetAsFloat((char*)aString);

	lua_pushnumber(L, value);
	return 1;
}

int LuaSQLGetString(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	const char* aString = lua_tostring(L, 1);

	char value[256] = { 0 };

	gQueryManager.GetAsString((char*)aString, value, sizeof(value));

	lua_pushstring(L, value);
	return 1;
}

int LuaSQLAsyncConnect(lua_State* L) // OK
{
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}

	const char* aString = lua_tostring(L, 1);
	const char* bString = lua_tostring(L, 2);
	const char* cString = lua_tostring(L, 3);

	if (gQueryManager.Connect((char*)aString, (char*)bString, (char*)cString) == 0)
	{
		LogAdd(LOG_RED, "[LuaFunction][SQLAsyncConnect] Could not connect to database [%s][%s][%s]", aString, bString, cString);
		lua_pushinteger(L, 0);
	}
	else
	{
		lua_pushinteger(L, 1);
	}

	return 1;
}

int LuaSQLAsyncDisconnect(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	gQueryManager.Disconnect();

	return 1;
}

int LuaSQLAsyncCheck(lua_State* L) // OK
{
	if (lua_gettop(L) != 0)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR0);
	}

	if (gQueryManager.GetStatus() == 0)
	{
		lua_pushinteger(L, 0);
	}
	else
	{
		lua_pushinteger(L, 1);
	}

	return 1;
}

int LuaSQLAsyncQuery(lua_State* L) // OK
{
	if (lua_gettop(L) < 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR2, 1);
	}

	const char* aString = lua_tostring(L, 1);

	const char* bString = luaL_optstring(L, 2, "");

	const char* cString = luaL_optstring(L, 3, "");

	static LUA_QUEUE_INFO QueueInfo;

	memset(&QueueInfo, 0, sizeof(QueueInfo));

	strcpy_s(QueueInfo.label, bString);

	strcpy_s(QueueInfo.query, aString);

	strcpy_s(QueueInfo.param, cString);

	gScriptLoader.SetInfo(&QueueInfo);

	return 1;
}

int LuaSQLAsyncGetResult(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	int aValue = static_cast<int>(lua_tointeger(L, 1));


	int value = gQueryManager.GetResult(aValue);

	lua_pushinteger(L, value);
	return 1;
}

int LuaSQLAsyncGetNumber(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	const char* aString = lua_tostring(L, 1);

	int value = gQueryManager.GetAsInteger((char*)aString);

	lua_pushinteger(L, value);
	return 1;
}

int LuaSQLAsyncGetSingle(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	const char* aString = lua_tostring(L, 1);

	float value = gQueryManager.GetAsFloat((char*)aString);

	lua_pushnumber(L, value);
	return 1;
}

int LuaSQLAsyncGetString(lua_State* L) // OK
{
	if (lua_gettop(L) != 1)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 1);
	}

	const char* aString = lua_tostring(L, 1);

	char value[256] = { 0 };

	gQueryManager.GetAsString((char*)aString, value, sizeof(value));

	lua_pushstring(L, value);
	return 1;
}


// =============================================================================================================
// Customs Modificadas
// =============================================================================================================

int LuaCommandCheckGameMasterLevel(lua_State* L) // OK
{
	if (lua_gettop(L) != 2)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 2);
	}


	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));

	if (OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if (gGameMaster.CheckGameMasterLevel(&gObj[aIndex], aValue) == false)
	{
		lua_pushinteger(L, 0);
	}
	else
	{
		lua_pushinteger(L, 1);
	}

	return 1;
}

int LuaFireworksSend(lua_State* L) // OK
{
	// Verifica se o n�mero de par�metros passados para o Lua est� correto (deve ser 3)
	if (lua_gettop(L) != 3)
	{
		return luaL_error(L, LUA_SCRIPT_CODE_ERROR1, 3);
	}

	// Obt�m o �ndice do jogador, as coordenadas X e Y a partir dos par�metros do Lua
	int aIndex = static_cast<int>(lua_tointeger(L, 1));
	int aValue = static_cast<int>(lua_tointeger(L, 2));
	int bValue = static_cast<int>(lua_tointeger(L, 3));

	// Verifica se o �ndice do jogador � v�lido
	if (!OBJECT_RANGE(aIndex))
	{
		return 0;  // Se o jogador n�o for v�lido, retorna 0
	}

	// Se as coordenadas X ou Y forem -1, usa as coordenadas do jogador
	int x = (aValue == -1) ? gObj[aIndex].X : aValue;
	int y = (bValue == -1) ? gObj[aIndex].Y : bValue;

	// Chama a fun��o do servidor para enviar os fogos de artif�cio
	// GCFireworksSend agora deve ser chamada com o objeto do jogador e as coordenadas
	LPOBJ lpObj = &gObj[aIndex];  // Obt�m o objeto do jogador
	GCFireworksSend(lpObj, x, y);  // Passa o objeto e as coordenadas para a fun��o de fogos

	return 1; // Retorna 1, indicando que o comando foi executado com sucesso
}