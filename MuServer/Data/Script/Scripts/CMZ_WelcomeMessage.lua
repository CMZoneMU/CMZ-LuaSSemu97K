-- ===========================================================================
-- Base Lua SSeMU - MuEmu 97k Kayito
-- Créditos Adaptação: NiloMaster | Gabriel GDA 
-- https://www.youtube.com/cmzonecriandomuonline
-- Sistema Livre para estudos © CMZone Team 2025
-- ===========================================================================
-- Este arquivo faz parte dos arquivos do Mu Server MuEmu 97k.
-- ===========================================================================

-- [Por]
-- Sistema de Mensagens Multilíngue e Notificações
-- Funcionalidades:
-- - Exibe mensagem personalizada de boas-vindas aos jogadores
-- - Informa o status VIP do jogador
-- - Notifica sobre Staff Online no servidor
-- Características:
-- - Integração com sistema multilíngue (Português, English, Español)
-- - Mensagens obtidas diretamente das tabelas Message_Por, Message_Eng e Message_Spn
-- - Compatibilidade com a seleção de idioma feita pelo jogador no Option Menu
-- - Sistema dinâmico que respeita a preferência de idioma configurada no cliente

-- [Spn]
-- Sistema de Mensajes Multilingüe y Notificaciones
-- Funcionalidades:
-- - Muestra mensaje personalizado de bienvenida a los jugadores
-- - Informa el estado VIP del jugador
-- - Notifica sobre Staff Online en el servidor
-- Características:
-- - Integración con sistema multilingüe (Portugués, Inglés, Español)
-- - Mensajes obtenidos directamente de las tablas Message_Por, Message_Eng y Message_Spn
-- - Compatibilidad con la selección de idioma hecha por el jugador en el Option Menu
-- - Sistema dinámico que respeta la preferencia de idioma configurada en el cliente

-- [Eng]
-- Multilingual Message and Notification System
-- Features:
-- - Displays customized welcome message to players
-- - Informs player's VIP status
-- - Notifies about Staff Online on server
-- Characteristics:
-- - Integration with multilingual system (Portuguese, English, Spanish)
-- - Messages obtained directly from Message_Por, Message_Eng and Message_Spn tables
-- - Compatibility with language selection made by player in Option Menu
-- - Dynamic system that respects language preference configured in client
-- ===========================================================================

-- ===========================================================================
BridgeFunctionAttach('OnCharacterEntry','WelcomeMessage_OnCharacterEntry')
BridgeFunctionAttach('OnCharacterClose','WelcomeMessage_OnCharacterClose')
-- ===========================================================================

function WelcomeMessage_OnCharacterEntry(aIndex)
	
	local UserName = GetObjectName(aIndex)
	
	local UserAccountLevel = GetObjectAccountLevel(aIndex)
	
	local UserAccountExpireDate = GetObjectAccountExpireDate(aIndex)

  NoticeSend(aIndex, 0, string.format(MessageGetByPlayer(154, aIndex), UserName))

	-- Exibe a expiração da conta conforme o nível
	if UserAccountLevel == 0 then 
		
		  NoticeSend(aIndex, 1, string.format(MessageGetByPlayer(155, aIndex), UserAccountExpireDate))
		
	elseif UserAccountLevel == 1 then
		
		 NoticeSend(aIndex, 1, string.format(MessageGetByPlayer(156, aIndex), UserAccountExpireDate))
		
	elseif UserAccountLevel == 2 then
		
		NoticeSend(aIndex, 1, string.format(MessageGetByPlayer(157, aIndex), UserAccountExpireDate))
		
	elseif UserAccountLevel == 3 then
		
		 NoticeSend(aIndex, 1, string.format(MessageGetByPlayer(158, aIndex), UserAccountExpireDate))
		
	end
	
	-- Verifica se o jogador é Game Master
	local GameMasterLevel = CommandCheckGameMasterLevel(aIndex,8) 
	
	if GameMasterLevel == 1 then
		
		 NoticeSendToAll(0, string.format(MessageGetByPlayer(159, aIndex), UserName))
		
	end
	
	-- Mensagens personalizadas ao jogador
	MessageSend(aIndex,2,2,"Testando Sistema Lua da SSemu")
	
	MessageSend(aIndex,2,6,"Adaptado na Source MueMu Kayito 97k")
	
	MessageSend(aIndex,2,6,"Video Aulas + Downloads Arquivos CMZone")
		
end

function WelcomeMessage_OnCharacterClose(aIndex)

	local UserName = GetObjectName(aIndex)
	
	local GameMasterLevel = CommandCheckGameMasterLevel(aIndex,8)
	
	if GameMasterLevel == 1 then
		
		 NoticeSendToAll(0, string.format(MessageGetByPlayer(160, aIndex), UserName))
		
	end
end

LogColor(2, "[CMZ LUA] - [WelcomeMessage]: Carregado com sucesso!");
