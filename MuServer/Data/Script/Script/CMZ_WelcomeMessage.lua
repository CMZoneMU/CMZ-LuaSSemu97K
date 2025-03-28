--[[ 
    Base LuaScript SSeMU 
    Sistema Adaptado: NiloMaster 25/03/2025
	
	Sistema ScriptLua liberado para estudos..
]]

-- ===========================================================================
BridgeFunctionAttach('OnCharacterEntry','WelcomeMessage_OnCharacterEntry')
BridgeFunctionAttach('OnCharacterClose','WelcomeMessage_OnCharacterClose')
-- ===========================================================================

function WelcomeMessage_OnCharacterEntry(aIndex)
	
	local UserName = GetObjectName(aIndex)
	
	local UserAccountLevel = GetObjectAccountLevel(aIndex)
	
	local UserAccountExpireDate = GetObjectAccountExpireDate(aIndex)

   -- Mensagem de boas-vindas no idioma correto do jogador
    NoticeSend(aIndex, 0, string.format(MessageGet(154, aIndex), UserName))

	-- Exibe a expiração da conta conforme o nível
	if UserAccountLevel == 0 then 
		
		  NoticeSend(aIndex, 1, string.format(MessageGet(155, aIndex), UserAccountExpireDate))
		
	elseif UserAccountLevel == 1 then
		
		 NoticeSend(aIndex, 1, string.format(MessageGet(156, aIndex), UserAccountExpireDate))
		
	elseif UserAccountLevel == 2 then
		
		NoticeSend(aIndex, 1, string.format(MessageGet(157, aIndex), UserAccountExpireDate))
		
	elseif UserAccountLevel == 3 then
		
		 NoticeSend(aIndex, 1, string.format(MessageGet(158, aIndex), UserAccountExpireDate))
		
	end
	
	-- Verifica se o jogador é Game Master
	local GameMasterLevel = CommandCheckGameMasterLevel(aIndex,2)
	
	if GameMasterLevel == 1 then
		
		 NoticeSendToAll(0, string.format(MessageGet(159, aIndex), UserName))
		
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
		
		 NoticeSendToAll(0, string.format(MessageGet(160, aIndex), UserName))
		
	end
end