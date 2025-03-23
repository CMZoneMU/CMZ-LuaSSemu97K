#pragma once

#define LUA_SCRIPT_CODE_ERROR0 "[No argument's allowed]"
#define LUA_SCRIPT_CODE_ERROR1 "[%d argument's expected]"
#define LUA_SCRIPT_CODE_ERROR2 "[Minimum %d argument's expected]"


// ===================================================================
// ##  Funções de Carregamento do Lua
// ===================================================================

void InitLuaFunction(lua_State* L);      // Inicializa todas as funções Lua disponíveis no servidor
int LuaRequire(lua_State* L);            // Carrega e executa módulos/bibliotecas Lua externos

// ===================================================================
// ##  Funções de Sistema e Servidor
// ===================================================================
int LuaGetGameServerCode(lua_State* L);      // Obtém o código identificador do servidor
int LuaGetGameServerVersion(lua_State* L);   // Obtém a versão atual do servidor
int LuaGetGameServerCurUser(lua_State* L);   // Obtém número atual de usuários conectados
int LuaGetGameServerProtocol(lua_State* L);  // Obtém o protocolo do servidor
int LuaGetGameServerMaxUser(lua_State* L);   // Obtém limite máximo de usuários
int LuaGetLicenseCustomerName(lua_State* L); // Obtém nome do cliente da licença

// ===================================================================
// ##  Funções de Índice e Limites
// ===================================================================
int LuaGetMaxIndex(lua_State* L);            // Obtém índice máximo geral do servidor
int LuaGetMinUserIndex(lua_State* L);        // Obtém menor índice de usuário permitido
int LuaGetMaxUserIndex(lua_State* L);        // Obtém maior índice de usuário permitido
int LuaGetMinMonsterIndex(lua_State* L);     // Obtém menor índice de monstro permitido
int LuaGetMaxMonsterIndex(lua_State* L);     // Obtém maior índice de monstro permitido

// ===================================================================
// ##  Informações do Objeto/Personagem
// ===================================================================
int LuaGetObjectConnected(lua_State* L);     // Verifica se objeto está conectado
int LuaGetObjectIpAddress(lua_State* L);     // Obtém endereço IP do objeto
int LuaGetObjectHardwareId(lua_State* L);    // Obtém ID do hardware do cliente
int LuaGetObjectType(lua_State* L);          // Obtém tipo do objeto (player/monster/npc)
int LuaGetObjectAccount(lua_State* L);       // Obtém nome da conta
int LuaGetObjectPassword(lua_State* L);      // Obtém senha da conta
int LuaGetObjectName(lua_State* L);          // Obtém nome do personagem
int LuaGetObjectPersonalCode(lua_State* L);  // Obtém código pessoal do personagem

// ===================================================================
// ##  Atributos do Personagem
// ===================================================================
int LuaGetObjectClass(lua_State* L);         // Obtém classe do personagem
int LuaGetObjectChangeUp(lua_State* L);      // Obtém nível de evolução
int LuaGetObjectLevel(lua_State* L);         // Obtém nível atual
int LuaGetObjectLevelUpPoint(lua_State* L);  // Obtém pontos disponíveis
int LuaGetObjectMoney(lua_State* L);         // Obtém quantidade de zen
int LuaGetObjectStrength(lua_State* L);      // Obtém força atual
int LuaGetObjectDexterity(lua_State* L);     // Obtém agilidade atual
int LuaGetObjectVitality(lua_State* L);      // Obtém vitalidade atual
int LuaGetObjectEnergy(lua_State* L);        // Obtém energia atual


// ===================================================================
// ##  Status do Personagem
// ===================================================================
int LuaGetObjectLive(lua_State* L);          // Verifica se personagem está vivo
int LuaGetObjectLife(lua_State* L);          // Obtém HP atual
int LuaGetObjectMaxLife(lua_State* L);       // Obtém HP máximo
int LuaGetObjectMana(lua_State* L);          // Obtém MP atual
int LuaGetObjectMaxMana(lua_State* L);       // Obtém MP máximo
int LuaGetObjectBP(lua_State* L);            // Obtém AG atual
int LuaGetObjectMaxBP(lua_State* L);         // Obtém AG máximo
int LuaGetObjectDefense(lua_State* L);       // Obtém defesa total

// ===================================================================
// ##  Sistema PK e Localização
// ===================================================================
// # Consultar o estado atual do sistema PK de um jogador.
int LuaGetObjectPKCount(lua_State* L);       // Obtém contagem de PKs
int LuaGetObjectPKLevel(lua_State* L);       // Obtém nível PK atual
int LuaGetObjectPKTimer(lua_State* L);       // Obtém tempo restante de PK
int LuaGetObjectDeathMap(lua_State* L);      // Obtém mapa onde o personagem morreu
int LuaGetObjectDeathMapX(lua_State* L);     // Obtém coordenada X da morte
int LuaGetObjectDeathMapY(lua_State* L);     // Obtém coordenada Y da morte

// # Modificar o estado do sistema PK de um jogador.
int LuaSetObjectPKCount(lua_State* L);       // Define quantidade de PKs
int LuaSetObjectPKLevel(lua_State* L);       // Define nível PK
int LuaSetObjectPKTimer(lua_State* L);       // Define tempo do timer PK
int LuaSetObjectMap(lua_State* L);           // Define mapa atual
int LuaSetObjectMapX(lua_State* L);          // Define posição X no mapa
int LuaSetObjectMapY(lua_State* L);          // Define posição Y no mapa
int LuaCharacterGetRespawnLocation(lua_State* L); // Obtém local de renascimento

// ===================================================================
// ##  Guild e Party
// ===================================================================
int LuaGetObjectAuthority(lua_State* L);     // Obtém nível de autoridade na guild
int LuaGetObjectPartyNumber(lua_State* L);   // Obtém número do grupo
int LuaGetObjectGuildNumber(lua_State* L);   // Obtém número da guild
int LuaGetObjectGuildStatus(lua_State* L);   // Obtém status na guild
int LuaGetObjectGuildName(lua_State* L);     // Obtém nome da guild

// ===================================================================
// ##  Sistema Master e Reset
// ===================================================================
int LuaGetObjectReset(lua_State* L);         // Obtém quantidade de resets
int LuaGetObjectMasterReset(lua_State* L);   // Obtém quantidade de master resets

// ===================================================================
// ## Funções de Modificação
// ===================================================================
int LuaSetObjectLevel(lua_State* L);         // Define nível do personagem
int LuaSetObjectLevelUpPoint(lua_State* L);  // Define pontos de level up
int LuaSetObjectMoney(lua_State* L);         // Define quantidade de zen
int LuaSetObjectStrength(lua_State* L);      // Define pontos de força
int LuaSetObjectDexterity(lua_State* L);     // Define pontos de agilidade
int LuaSetObjectVitality(lua_State* L);      // Define pontos de vitalidade
int LuaSetObjectEnergy(lua_State* L);        // Define pontos de energia

// ===================================================================
// ## Funções de Inventário
// ===================================================================
int LuaInventoryGetWearSize(lua_State* L);   // Obtém tamanho do equipamento
int LuaInventoryGetMainSize(lua_State* L);   // Obtém tamanho do inventário principal
int LuaInventoryGetFullSize(lua_State* L);   // Obtém tamanho total do inventário
int LuaInventoryGetItemTable(lua_State* L);  // Obtém tabela de itens
int LuaInventoryGetItemIndex(lua_State* L);  // Obtém índice do item
int LuaInventoryGetItemCount(lua_State* L);  // Obtém quantidade do item
int LuaInventoryDelItemIndex(lua_State* L);  // Remove item por índice
int LuaInventoryDelItemCount(lua_State* L);  // Remove quantidade de itens

// ===================================================================
// ## Funções de Comunicação
// ===================================================================
int LuaChatTargetSend(lua_State* L);         // Envia mensagem para alvo específico
int LuaMessageSend(lua_State* L);            // Envia mensagem normal
int LuaMessageSendToAll(lua_State* L);       // Envia mensagem para todos
int LuaMessageGlobalSend(lua_State* L);      // Envia mensagem global
int LuaNoticeSend(lua_State* L);             // Envia notificação
int LuaNoticeSendToAll(lua_State* L);        // Envia notificação para todos
	int LuaNoticeGlobalSend(lua_State* L);  // Envia notificação global para todos os servidores conectados


// ===================================================================
// ## Funções de Efeitos e Visuais
// ===================================================================
int LuaEffectAdd(lua_State* L);          // Adiciona efeito visual ao personagem
int LuaEffectDel(lua_State* L);          // Remove efeito visual do personagem
int LuaEffectCheck(lua_State* L);        // Verifica se efeito está ativo
int LuaEffectClear(lua_State* L);        // Remove todos os efeitos
int LuaFireworksSend(lua_State* L);      // Cria efeito de fogos de artifício

// ===================================================================
// ## Funções de Movimentação e Criação
// ===================================================================
int LuaMoveUser(lua_State* L);           // Move jogador para coordenada específica
int LuaMoveUserEx(lua_State* L);         // Move jogador (versão estendida com mais opções)
int LuaMonsterCreate(lua_State* L);      // Cria monstro no mapa
int LuaMonsterDelete(lua_State* L);      // Remove monstro do mapa
int LuaMonsterSummonCreate(lua_State* L);// Cria monstro invocado
int LuaMonsterSummonDelete(lua_State* L);// Remove monstro invocado

// ===================================================================
// ##  Funções de SQL
// ===================================================================
int LuaSQLConnect(lua_State* L);         // Estabelece conexão com banco de dados
int LuaSQLDisconnect(lua_State* L);      // Encerra conexão com banco de dados
int LuaSQLCheck(lua_State* L);           // Verifica status da conexão
int LuaSQLQuery(lua_State* L);           // Executa query SQL
int LuaSQLClose(lua_State* L);           // Fecha conexão atual
int LuaSQLFetch(lua_State* L);           // Busca próxima linha do resultado
int LuaSQLGetResult(lua_State* L);       // Obtém resultado da query
int LuaSQLGetNumber(lua_State* L);       // Obtém valor numérico do resultado
int LuaSQLGetSingle(lua_State* L);       // Obtém valor único do resultado
int LuaSQLGetString(lua_State* L);       // Obtém string do resultado

// ===================================================================
// ##  Funções de SQL Assíncrono
// ===================================================================
int LuaSQLAsyncConnect(lua_State* L);    // Conexão assíncrona com banco de dados
int LuaSQLAsyncDisconnect(lua_State* L); // Desconexão assíncrona
int LuaSQLAsyncCheck(lua_State* L);      // Verifica status da conexão assíncrona
int LuaSQLAsyncQuery(lua_State* L);      // Executa query SQL assíncrona
int LuaSQLAsyncGetResult(lua_State* L);  // Obtém resultado assíncrono
int LuaSQLAsyncGetNumber(lua_State* L);  // Obtém número do resultado assíncrono
int LuaSQLAsyncGetSingle(lua_State* L);  // Obtém valor único assíncrono
int LuaSQLAsyncGetString(lua_State* L);  // Obtém string do resultado assíncrono

// ===================================================================
// ##  Gerenciamento de Objetos e Conta
// ===================================================================
int LuaGetObjectAccountLevel(lua_State* L);      // Obtém nível da conta
int LuaGetObjectAccountCoins(lua_State* L);      // Obtém moedas da conta
int LuaGetObjectAccountExpireDate(lua_State* L); // Obtém data de expiração da conta
int LuaGetObjectChange(lua_State* L);            // Verifica mudanças no objeto
int LuaGetObjectInterface(lua_State* L);         // Obtém interface atual do objeto
int LuaGetObjectOfflineFlag(lua_State* L);       // Verifica status offline
int LuaGetObjectIndexByName(lua_State* L);       // Busca índice por nome

// ===================================================================
// ##  Comandos e Configurações
// ===================================================================
int LuaCommandCheckGameMasterLevel(lua_State* L); // Verifica nível de GM
int LuaCommandGetArgNumber(lua_State* L);         // Obtém argumento numérico
int LuaCommandGetArgString(lua_State* L);         // Obtém argumento string
int LuaCommandSend(lua_State* L);                 // Envia comando
int LuaConfigReadNumber(lua_State* L);            // Lê número da configuração
int LuaConfigReadString(lua_State* L);            // Lê string da configuração
int LuaConfigSaveString(lua_State* L);            // Salva string na configuração

// ===================================================================
// ##  Sistema de Itens e Inventário
// ===================================================================
int LuaGetItem(lua_State* L);                     // Obtém informações do item
int LuaGetItemName(lua_State* L);                 // Obtém nome do item
int LuaItemDrop(lua_State* L);                    // Dropa item no mapa
int LuaItemDropEx(lua_State* L);                  // Dropa item (versão estendida)
int LuaItemGive(lua_State* L);                    // Dá item ao jogador
int LuaItemGiveEx(lua_State* L);                  // Dá item (versão estendida)
int LuaInventoryGetFreeSlotCount(lua_State* L);   // Conta slots livres
int LuaInventoryCheckSpaceByItem(lua_State* L);   // Verifica espaço por item
int LuaInventoryCheckSpaceBySize(lua_State* L);   // Verifica espaço por tamanho

// ===================================================================
// ##  Funções de Usuário
// ===================================================================
int LuaUserDisconnect(lua_State* L);        // Desconecta usuário do servidor
int LuaUserGameLogout(lua_State* L);        // Realiza logout do jogo
int LuaUserCalcAttribute(lua_State* L);     // Recalcula atributos do usuário
int LuaUserInfoSend(lua_State* L);          // Envia informações do usuário
int LuaUserActionSend(lua_State* L);        // Envia ação do usuário
int LuaUserSetAccountLevel(lua_State* L);   // Define nível da conta

// ===================================================================
// ##  Sistema de Party
// ===================================================================
int LuaPartyGetMemberCount(lua_State* L);   // Obtém número de membros no grupo
int LuaPartyGetMemberIndex(lua_State* L);   // Obtém índice de membro específico

// ===================================================================
// ##  Sistema de Moedas
// ===================================================================
int LuaObjectGetCoin(lua_State* L);         // Obtém quantidade de moedas
int LuaObjectAddCoin(lua_State* L);         // Adiciona moedas
int LuaObjectSubCoin(lua_State* L);         // Remove moedas
int LuaMoneySend(lua_State* L);             // Envia atualização de moedas

// ===================================================================
// ##  Sistema de Permissões
// ===================================================================
int LuaPermissionCheck(lua_State* L);       // Verifica permissão
int LuaPermissionInsert(lua_State* L);      // Adiciona permissão
int LuaPermissionRemove(lua_State* L);      // Remove permissão

// ===================================================================
// ## Funções Diversas
// ===================================================================
int LuaGetMapName(lua_State* L);            // Obtém nome do mapa
int LuaGetMonsterName(lua_State* L);        // Obtém nome do monstro
int LuaLevelUpSend(lua_State* L);           // Envia notificação de level up
int LuaLogPrint(lua_State* L);              // Imprime log no console
int LuaLogColor(lua_State* L);              // Imprime log colorido
int LuaMapCheckAttr(lua_State* L);          // Verifica atributos do mapa
int LuaMapGetItemTable(lua_State* L);       // Obtém tabela de itens do mapa
int LuaMessageGet(lua_State* L);            // Obtém mensagem do sistema
int LuaMonsterCount(lua_State* L);          // Conta monstros no mapa
int LuaPKLevelSend(lua_State* L);           // Envia nível PK atualizado
int LuaQuestStateCheck(lua_State* L);       // Verifica estado da quest
int LuaRandomGetNumber(lua_State* L);       // Gera número aleatório
int LuaSkinChangeSend(lua_State* L);        // Envia mudança de aparência
int LuaMessageGetByPlayer(lua_State* L);    // Obtém mensagem específica do jogador
int LuaSetObjectChatLimitTime(lua_State* L);// Define limite de tempo do chat