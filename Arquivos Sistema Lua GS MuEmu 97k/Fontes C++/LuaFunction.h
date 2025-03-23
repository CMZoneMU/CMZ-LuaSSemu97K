#pragma once

#define LUA_SCRIPT_CODE_ERROR0 "[No argument's allowed]"
#define LUA_SCRIPT_CODE_ERROR1 "[%d argument's expected]"
#define LUA_SCRIPT_CODE_ERROR2 "[Minimum %d argument's expected]"


// ===================================================================
// ##  Fun��es de Carregamento do Lua
// ===================================================================

void InitLuaFunction(lua_State* L);      // Inicializa todas as fun��es Lua dispon�veis no servidor
int LuaRequire(lua_State* L);            // Carrega e executa m�dulos/bibliotecas Lua externos

// ===================================================================
// ##  Fun��es de Sistema e Servidor
// ===================================================================
int LuaGetGameServerCode(lua_State* L);      // Obt�m o c�digo identificador do servidor
int LuaGetGameServerVersion(lua_State* L);   // Obt�m a vers�o atual do servidor
int LuaGetGameServerCurUser(lua_State* L);   // Obt�m n�mero atual de usu�rios conectados
int LuaGetGameServerProtocol(lua_State* L);  // Obt�m o protocolo do servidor
int LuaGetGameServerMaxUser(lua_State* L);   // Obt�m limite m�ximo de usu�rios
int LuaGetLicenseCustomerName(lua_State* L); // Obt�m nome do cliente da licen�a

// ===================================================================
// ##  Fun��es de �ndice e Limites
// ===================================================================
int LuaGetMaxIndex(lua_State* L);            // Obt�m �ndice m�ximo geral do servidor
int LuaGetMinUserIndex(lua_State* L);        // Obt�m menor �ndice de usu�rio permitido
int LuaGetMaxUserIndex(lua_State* L);        // Obt�m maior �ndice de usu�rio permitido
int LuaGetMinMonsterIndex(lua_State* L);     // Obt�m menor �ndice de monstro permitido
int LuaGetMaxMonsterIndex(lua_State* L);     // Obt�m maior �ndice de monstro permitido

// ===================================================================
// ##  Informa��es do Objeto/Personagem
// ===================================================================
int LuaGetObjectConnected(lua_State* L);     // Verifica se objeto est� conectado
int LuaGetObjectIpAddress(lua_State* L);     // Obt�m endere�o IP do objeto
int LuaGetObjectHardwareId(lua_State* L);    // Obt�m ID do hardware do cliente
int LuaGetObjectType(lua_State* L);          // Obt�m tipo do objeto (player/monster/npc)
int LuaGetObjectAccount(lua_State* L);       // Obt�m nome da conta
int LuaGetObjectPassword(lua_State* L);      // Obt�m senha da conta
int LuaGetObjectName(lua_State* L);          // Obt�m nome do personagem
int LuaGetObjectPersonalCode(lua_State* L);  // Obt�m c�digo pessoal do personagem

// ===================================================================
// ##  Atributos do Personagem
// ===================================================================
int LuaGetObjectClass(lua_State* L);         // Obt�m classe do personagem
int LuaGetObjectChangeUp(lua_State* L);      // Obt�m n�vel de evolu��o
int LuaGetObjectLevel(lua_State* L);         // Obt�m n�vel atual
int LuaGetObjectLevelUpPoint(lua_State* L);  // Obt�m pontos dispon�veis
int LuaGetObjectMoney(lua_State* L);         // Obt�m quantidade de zen
int LuaGetObjectStrength(lua_State* L);      // Obt�m for�a atual
int LuaGetObjectDexterity(lua_State* L);     // Obt�m agilidade atual
int LuaGetObjectVitality(lua_State* L);      // Obt�m vitalidade atual
int LuaGetObjectEnergy(lua_State* L);        // Obt�m energia atual


// ===================================================================
// ##  Status do Personagem
// ===================================================================
int LuaGetObjectLive(lua_State* L);          // Verifica se personagem est� vivo
int LuaGetObjectLife(lua_State* L);          // Obt�m HP atual
int LuaGetObjectMaxLife(lua_State* L);       // Obt�m HP m�ximo
int LuaGetObjectMana(lua_State* L);          // Obt�m MP atual
int LuaGetObjectMaxMana(lua_State* L);       // Obt�m MP m�ximo
int LuaGetObjectBP(lua_State* L);            // Obt�m AG atual
int LuaGetObjectMaxBP(lua_State* L);         // Obt�m AG m�ximo
int LuaGetObjectDefense(lua_State* L);       // Obt�m defesa total

// ===================================================================
// ##  Sistema PK e Localiza��o
// ===================================================================
// # Consultar o estado atual do sistema PK de um jogador.
int LuaGetObjectPKCount(lua_State* L);       // Obt�m contagem de PKs
int LuaGetObjectPKLevel(lua_State* L);       // Obt�m n�vel PK atual
int LuaGetObjectPKTimer(lua_State* L);       // Obt�m tempo restante de PK
int LuaGetObjectDeathMap(lua_State* L);      // Obt�m mapa onde o personagem morreu
int LuaGetObjectDeathMapX(lua_State* L);     // Obt�m coordenada X da morte
int LuaGetObjectDeathMapY(lua_State* L);     // Obt�m coordenada Y da morte

// # Modificar o estado do sistema PK de um jogador.
int LuaSetObjectPKCount(lua_State* L);       // Define quantidade de PKs
int LuaSetObjectPKLevel(lua_State* L);       // Define n�vel PK
int LuaSetObjectPKTimer(lua_State* L);       // Define tempo do timer PK
int LuaSetObjectMap(lua_State* L);           // Define mapa atual
int LuaSetObjectMapX(lua_State* L);          // Define posi��o X no mapa
int LuaSetObjectMapY(lua_State* L);          // Define posi��o Y no mapa
int LuaCharacterGetRespawnLocation(lua_State* L); // Obt�m local de renascimento

// ===================================================================
// ##  Guild e Party
// ===================================================================
int LuaGetObjectAuthority(lua_State* L);     // Obt�m n�vel de autoridade na guild
int LuaGetObjectPartyNumber(lua_State* L);   // Obt�m n�mero do grupo
int LuaGetObjectGuildNumber(lua_State* L);   // Obt�m n�mero da guild
int LuaGetObjectGuildStatus(lua_State* L);   // Obt�m status na guild
int LuaGetObjectGuildName(lua_State* L);     // Obt�m nome da guild

// ===================================================================
// ##  Sistema Master e Reset
// ===================================================================
int LuaGetObjectReset(lua_State* L);         // Obt�m quantidade de resets
int LuaGetObjectMasterReset(lua_State* L);   // Obt�m quantidade de master resets

// ===================================================================
// ## Fun��es de Modifica��o
// ===================================================================
int LuaSetObjectLevel(lua_State* L);         // Define n�vel do personagem
int LuaSetObjectLevelUpPoint(lua_State* L);  // Define pontos de level up
int LuaSetObjectMoney(lua_State* L);         // Define quantidade de zen
int LuaSetObjectStrength(lua_State* L);      // Define pontos de for�a
int LuaSetObjectDexterity(lua_State* L);     // Define pontos de agilidade
int LuaSetObjectVitality(lua_State* L);      // Define pontos de vitalidade
int LuaSetObjectEnergy(lua_State* L);        // Define pontos de energia

// ===================================================================
// ## Fun��es de Invent�rio
// ===================================================================
int LuaInventoryGetWearSize(lua_State* L);   // Obt�m tamanho do equipamento
int LuaInventoryGetMainSize(lua_State* L);   // Obt�m tamanho do invent�rio principal
int LuaInventoryGetFullSize(lua_State* L);   // Obt�m tamanho total do invent�rio
int LuaInventoryGetItemTable(lua_State* L);  // Obt�m tabela de itens
int LuaInventoryGetItemIndex(lua_State* L);  // Obt�m �ndice do item
int LuaInventoryGetItemCount(lua_State* L);  // Obt�m quantidade do item
int LuaInventoryDelItemIndex(lua_State* L);  // Remove item por �ndice
int LuaInventoryDelItemCount(lua_State* L);  // Remove quantidade de itens

// ===================================================================
// ## Fun��es de Comunica��o
// ===================================================================
int LuaChatTargetSend(lua_State* L);         // Envia mensagem para alvo espec�fico
int LuaMessageSend(lua_State* L);            // Envia mensagem normal
int LuaMessageSendToAll(lua_State* L);       // Envia mensagem para todos
int LuaMessageGlobalSend(lua_State* L);      // Envia mensagem global
int LuaNoticeSend(lua_State* L);             // Envia notifica��o
int LuaNoticeSendToAll(lua_State* L);        // Envia notifica��o para todos
	int LuaNoticeGlobalSend(lua_State* L);  // Envia notifica��o global para todos os servidores conectados


// ===================================================================
// ## Fun��es de Efeitos e Visuais
// ===================================================================
int LuaEffectAdd(lua_State* L);          // Adiciona efeito visual ao personagem
int LuaEffectDel(lua_State* L);          // Remove efeito visual do personagem
int LuaEffectCheck(lua_State* L);        // Verifica se efeito est� ativo
int LuaEffectClear(lua_State* L);        // Remove todos os efeitos
int LuaFireworksSend(lua_State* L);      // Cria efeito de fogos de artif�cio

// ===================================================================
// ## Fun��es de Movimenta��o e Cria��o
// ===================================================================
int LuaMoveUser(lua_State* L);           // Move jogador para coordenada espec�fica
int LuaMoveUserEx(lua_State* L);         // Move jogador (vers�o estendida com mais op��es)
int LuaMonsterCreate(lua_State* L);      // Cria monstro no mapa
int LuaMonsterDelete(lua_State* L);      // Remove monstro do mapa
int LuaMonsterSummonCreate(lua_State* L);// Cria monstro invocado
int LuaMonsterSummonDelete(lua_State* L);// Remove monstro invocado

// ===================================================================
// ##  Fun��es de SQL
// ===================================================================
int LuaSQLConnect(lua_State* L);         // Estabelece conex�o com banco de dados
int LuaSQLDisconnect(lua_State* L);      // Encerra conex�o com banco de dados
int LuaSQLCheck(lua_State* L);           // Verifica status da conex�o
int LuaSQLQuery(lua_State* L);           // Executa query SQL
int LuaSQLClose(lua_State* L);           // Fecha conex�o atual
int LuaSQLFetch(lua_State* L);           // Busca pr�xima linha do resultado
int LuaSQLGetResult(lua_State* L);       // Obt�m resultado da query
int LuaSQLGetNumber(lua_State* L);       // Obt�m valor num�rico do resultado
int LuaSQLGetSingle(lua_State* L);       // Obt�m valor �nico do resultado
int LuaSQLGetString(lua_State* L);       // Obt�m string do resultado

// ===================================================================
// ##  Fun��es de SQL Ass�ncrono
// ===================================================================
int LuaSQLAsyncConnect(lua_State* L);    // Conex�o ass�ncrona com banco de dados
int LuaSQLAsyncDisconnect(lua_State* L); // Desconex�o ass�ncrona
int LuaSQLAsyncCheck(lua_State* L);      // Verifica status da conex�o ass�ncrona
int LuaSQLAsyncQuery(lua_State* L);      // Executa query SQL ass�ncrona
int LuaSQLAsyncGetResult(lua_State* L);  // Obt�m resultado ass�ncrono
int LuaSQLAsyncGetNumber(lua_State* L);  // Obt�m n�mero do resultado ass�ncrono
int LuaSQLAsyncGetSingle(lua_State* L);  // Obt�m valor �nico ass�ncrono
int LuaSQLAsyncGetString(lua_State* L);  // Obt�m string do resultado ass�ncrono

// ===================================================================
// ##  Gerenciamento de Objetos e Conta
// ===================================================================
int LuaGetObjectAccountLevel(lua_State* L);      // Obt�m n�vel da conta
int LuaGetObjectAccountCoins(lua_State* L);      // Obt�m moedas da conta
int LuaGetObjectAccountExpireDate(lua_State* L); // Obt�m data de expira��o da conta
int LuaGetObjectChange(lua_State* L);            // Verifica mudan�as no objeto
int LuaGetObjectInterface(lua_State* L);         // Obt�m interface atual do objeto
int LuaGetObjectOfflineFlag(lua_State* L);       // Verifica status offline
int LuaGetObjectIndexByName(lua_State* L);       // Busca �ndice por nome

// ===================================================================
// ##  Comandos e Configura��es
// ===================================================================
int LuaCommandCheckGameMasterLevel(lua_State* L); // Verifica n�vel de GM
int LuaCommandGetArgNumber(lua_State* L);         // Obt�m argumento num�rico
int LuaCommandGetArgString(lua_State* L);         // Obt�m argumento string
int LuaCommandSend(lua_State* L);                 // Envia comando
int LuaConfigReadNumber(lua_State* L);            // L� n�mero da configura��o
int LuaConfigReadString(lua_State* L);            // L� string da configura��o
int LuaConfigSaveString(lua_State* L);            // Salva string na configura��o

// ===================================================================
// ##  Sistema de Itens e Invent�rio
// ===================================================================
int LuaGetItem(lua_State* L);                     // Obt�m informa��es do item
int LuaGetItemName(lua_State* L);                 // Obt�m nome do item
int LuaItemDrop(lua_State* L);                    // Dropa item no mapa
int LuaItemDropEx(lua_State* L);                  // Dropa item (vers�o estendida)
int LuaItemGive(lua_State* L);                    // D� item ao jogador
int LuaItemGiveEx(lua_State* L);                  // D� item (vers�o estendida)
int LuaInventoryGetFreeSlotCount(lua_State* L);   // Conta slots livres
int LuaInventoryCheckSpaceByItem(lua_State* L);   // Verifica espa�o por item
int LuaInventoryCheckSpaceBySize(lua_State* L);   // Verifica espa�o por tamanho

// ===================================================================
// ##  Fun��es de Usu�rio
// ===================================================================
int LuaUserDisconnect(lua_State* L);        // Desconecta usu�rio do servidor
int LuaUserGameLogout(lua_State* L);        // Realiza logout do jogo
int LuaUserCalcAttribute(lua_State* L);     // Recalcula atributos do usu�rio
int LuaUserInfoSend(lua_State* L);          // Envia informa��es do usu�rio
int LuaUserActionSend(lua_State* L);        // Envia a��o do usu�rio
int LuaUserSetAccountLevel(lua_State* L);   // Define n�vel da conta

// ===================================================================
// ##  Sistema de Party
// ===================================================================
int LuaPartyGetMemberCount(lua_State* L);   // Obt�m n�mero de membros no grupo
int LuaPartyGetMemberIndex(lua_State* L);   // Obt�m �ndice de membro espec�fico

// ===================================================================
// ##  Sistema de Moedas
// ===================================================================
int LuaObjectGetCoin(lua_State* L);         // Obt�m quantidade de moedas
int LuaObjectAddCoin(lua_State* L);         // Adiciona moedas
int LuaObjectSubCoin(lua_State* L);         // Remove moedas
int LuaMoneySend(lua_State* L);             // Envia atualiza��o de moedas

// ===================================================================
// ##  Sistema de Permiss�es
// ===================================================================
int LuaPermissionCheck(lua_State* L);       // Verifica permiss�o
int LuaPermissionInsert(lua_State* L);      // Adiciona permiss�o
int LuaPermissionRemove(lua_State* L);      // Remove permiss�o

// ===================================================================
// ## Fun��es Diversas
// ===================================================================
int LuaGetMapName(lua_State* L);            // Obt�m nome do mapa
int LuaGetMonsterName(lua_State* L);        // Obt�m nome do monstro
int LuaLevelUpSend(lua_State* L);           // Envia notifica��o de level up
int LuaLogPrint(lua_State* L);              // Imprime log no console
int LuaLogColor(lua_State* L);              // Imprime log colorido
int LuaMapCheckAttr(lua_State* L);          // Verifica atributos do mapa
int LuaMapGetItemTable(lua_State* L);       // Obt�m tabela de itens do mapa
int LuaMessageGet(lua_State* L);            // Obt�m mensagem do sistema
int LuaMonsterCount(lua_State* L);          // Conta monstros no mapa
int LuaPKLevelSend(lua_State* L);           // Envia n�vel PK atualizado
int LuaQuestStateCheck(lua_State* L);       // Verifica estado da quest
int LuaRandomGetNumber(lua_State* L);       // Gera n�mero aleat�rio
int LuaSkinChangeSend(lua_State* L);        // Envia mudan�a de apar�ncia
int LuaMessageGetByPlayer(lua_State* L);    // Obt�m mensagem espec�fica do jogador
int LuaSetObjectChatLimitTime(lua_State* L);// Define limite de tempo do chat