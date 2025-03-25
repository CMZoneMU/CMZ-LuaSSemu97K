
-- ===========================================================================
-- Base Lua SSeMU - MuEmu 97k Kayito
-- Créditos Adaptação: NiloMaster | Gabriel GDA 
-- https://www.youtube.com/cmzonecriandomuonline
-- ===========================================================================
-- Eevento Sobrevivencia
-- Criado por: Kellington Ricardo
-- Modificado por: CMZone 25/03/2025
-- Script Lua liberado para estudos..
-- ===========================================================================


-- Anexar funções de evento
BridgeFunctionAttach("OnReadScript", "Colosseum_ReadScript")
BridgeFunctionAttach("OnShutScript", "Colosseum_ShutScript")
BridgeFunctionAttach("OnTimerThread", "Colosseum_TimerThread")
BridgeFunctionAttach("OnCommandManager", "Colosseum_CommandManager")
BridgeFunctionAttach("OnCommandDone", "Colosseum_CommandDone")
BridgeFunctionAttach("OnCharacterEntry", "Colosseum_CharacterEntry")
BridgeFunctionAttach("OnCharacterClose", "Colosseum_CharacterClose")
BridgeFunctionAttach("OnUserDie", "Colosseum_UserDie")
BridgeFunctionAttach("OnUserRespawn", "Colosseum_UserRespawn")
BridgeFunctionAttach("OnCheckUserTarget", "Colosseum_CheckUserTarget")
BridgeFunctionAttach("OnCheckUserKiller", "Colosseum_CheckUserKiller")

local SYSTEM_MAIN = {
    UserCache = {}, -- Cache para consultas rápidas de usuários
    MessagePrefix = ". : [ Sobrevivencia ] : .", -- Prefixo padrão para mensagens
    LogPrefix = "[Sobrevivencia]: " -- Prefixo padrão para logs
}
local SYSTEM_CONFIG = {}
local nextID = 1

function Colosseum_ReadScript()
    -- Configurations of the event
    SYSTEM_CONFIG.Timer = { "13:46:00", "22:00:00" }
    SYSTEM_CONFIG.TimerAlert = 2 -- Tempo de alerta em minutos
    SYSTEM_CONFIG.MaxUsers = 20
    SYSTEM_CONFIG.MinUsers = 1
    SYSTEM_CONFIG.Map = 2
    SYSTEM_CONFIG.CordXY = { 90, 160 }
    SYSTEM_CONFIG.nmCommandEntry = "/IrEvent"
    SYSTEM_CONFIG.cdCommandEntry = 61
    SYSTEM_CONFIG.EventDuration = 120 -- 5 minutos em segundos
    SYSTEM_CONFIG.CashReward = 1000 -- Valor da premiação em Cash

    LogColor(3, "[Sobrevivencia]: Configuração carregada com sucesso!")
end

-- Função para atualizar o cash do vencedor
function rewardWinner(aIndex)
    local query = string.format("UPDATE MEMB_INFO SET cash = cash + %d WHERE memb___id = '%s'", SYSTEM_CONFIG.CashReward, GetObjectAccount(aIndex))
    if not SQLQuery(query) then
        LogColor(1, string.format("[Sobrevivencia]: Falha ao recompensar cash para o jogador %s", GetObjectName(aIndex)))
        return false
    end
    return true
end

function Colosseum_ShutScript()
    if SYSTEM_MAIN.Stage then
        Colosseum_Finalize(2)
    end
    LogColor(3, "[Sobrevivencia]: Script encerrado com sucesso.")
end

function Colosseum_TimerThread()
    if not SYSTEM_MAIN.Stage then
        for _, timer in ipairs(SYSTEM_CONFIG.Timer) do
            if os.date("%X") == timer then
                iniciarRegistro()  -- Iniciar registro quando chegar a hora certa
                break
            end
        end
    elseif SYSTEM_MAIN.Stage == 1 then
        gerenciarRegistro()  -- Gerenciar periodo de reggistro.
    elseif SYSTEM_MAIN.Stage == 2 then
        gerenciarFaseDeBatalha()  -- Gerenciar fase de batalha
    end
end

function iniciarRegistro()
    SYSTEM_MAIN.Stage = 1
    SYSTEM_MAIN.UserCount = 0
    SYSTEM_MAIN.Count = 0
    SYSTEM_MAIN.Users = {}
    SYSTEM_MAIN.TimerAlert = SYSTEM_CONFIG.TimerAlert
    LogColor(3, "[Sobrevivencia]: Período de registro iniciado.")
    NoticeSendToAll(0, ". : [ Sobrevivencia ] : .")
    NoticeSendToAll(0, "Registro está aberto! Digite " .. SYSTEM_CONFIG.nmCommandEntry .. " para se registrar!")
end

function gerenciarRegistro()
    SYSTEM_MAIN.Count = SYSTEM_MAIN.Count + 1
    if SYSTEM_MAIN.Count % 60 == 0 then  -- Minuto de entrada
        if SYSTEM_MAIN.TimerAlert == 0 then
            if #SYSTEM_MAIN.Users >= SYSTEM_CONFIG.MinUsers then
                iniciarEvento()
            else
                cancelarEvento()
            end
        else
            alertarInicioEvento()
            SYSTEM_MAIN.TimerAlert = SYSTEM_MAIN.TimerAlert - 1
        end
    end
end

function iniciarEvento()
    SYSTEM_MAIN.Stage = 2
    SYSTEM_MAIN.Count = 0
    SYSTEM_MAIN.EventEndTime = os.time() + SYSTEM_CONFIG.EventDuration

    NoticeSendToAll(0, ". : [ Sobrevivencia ] : .")
    NoticeSendToAll(0, "O evento começou! Que vença o melhor lutador!")
    LogColor(3, "[Sobrevivencia]: O evento começou com " .. #SYSTEM_MAIN.Users .. " participantes.")

    for _, user in ipairs(SYSTEM_MAIN.Users) do
        teleportUserToArena(user.Index)
    end
end

function cancelarEvento()
    while #SYSTEM_MAIN.Users > 0 do
        local userIndex = SYSTEM_MAIN.Users[1].Index
        NoticeSend(userIndex, 1, "[Sobrevivencia]: O evento foi cancelado devido a participantes insuficientes.")
        SYSTEM_MAIN.DelUser(userIndex)
    end

    resetEventVariables()

    NoticeSendToAll(0, ". : [ Sobrevivencia ] : .")
    NoticeSendToAll(0, "O evento foi cancelado. Número mínimo de participantes não atingido.")
    LogColor(3, "[Sobrevivencia]: Evento cancelado por falta de participantes.")
end

function alertarInicioEvento()
    NoticeSendToAll(0, ". : [ Sobrevivencia ] : .")
    NoticeSendToAll(0, "O evento começará em " .. SYSTEM_MAIN.TimerAlert .. " minuto(s).")
end

function gerenciarFaseDeBatalha()
    local currentTime = os.time()
    if currentTime >= SYSTEM_MAIN.EventEndTime then
        Colosseum_Finalize(3) -- Finaliza devido ao tempo limite
    else
        local remainingTime = SYSTEM_MAIN.EventEndTime - currentTime
        
        -- Verificar se só resta um jogador
        if #SYSTEM_MAIN.Users == 1 then
            Colosseum_Finalize(1)  -- Finaliza se restar apenas um jogador
            return
        end
        if remainingTime % 60 == 0 then
            NoticeSendToAll(0, "[Sobrevivência]: " .. math.floor(remainingTime / 60) .. " minutos restantes!")
        end
    end
end

function Colosseum_CommandManager(aIndex, code, arg)
    if code == SYSTEM_CONFIG.cdCommandEntry then
        if SYSTEM_MAIN.Stage and SYSTEM_MAIN.Stage == 1 then
            if SYSTEM_MAIN.GetUser(aIndex) ~= 0 then
                NoticeSend(aIndex, 1, "[Sobrevivência]: Você já está participando deste evento!")
            else
                SYSTEM_MAIN.AddUser(aIndex)
            end
        else
            NoticeSend(aIndex, 1, "[Sobrevivência]: O período de registro está fechado. Tente na próxima vez!")
        end
        return 1
    end
    return 0
end

function Colosseum_CommandDone(aIndex, code)
    if code == SYSTEM_CONFIG.cdCommandEntry then
        LogColor(3, "[Sobrevivencia]: Comando executado por " .. GetObjectName(aIndex))
    end
end

function Colosseum_CharacterEntry(aIndex)
    if SYSTEM_MAIN.Stage and SYSTEM_MAIN.Stage > 1 then
        local userIndex = SYSTEM_MAIN.GetUser(aIndex)
        if userIndex ~= 0 then
            teleportUserToArena(aIndex)
            LogColor(3, "[Sobrevivencia]: Jogador " .. GetObjectName(aIndex) .. " retornou à arena do evento.")
        end
    end
end

function Colosseum_CharacterClose(aIndex)
    if SYSTEM_MAIN.Stage and SYSTEM_MAIN.GetUser(aIndex) ~= 0 then
        SYSTEM_MAIN.DelUser(aIndex)
        SYSTEM_MAIN.Message(1, "[Sobrevivência]: Jogador " .. GetObjectName(aIndex) .. " desconectou e foi removido do evento.")
    end
end

function Colosseum_UserDie(aIndex, aTargetIndex)
    if SYSTEM_MAIN.Stage == 2 then
        if SYSTEM_MAIN.GetUser(aIndex) ~= 0 then
            SYSTEM_MAIN.DelUser(aIndex)
            NoticeSend(aIndex, 1, "[Sobrevivência]: Você foi eliminado do evento!")
            LogColor(3, "[Sobrevivência]: Jogador " .. GetObjectName(aIndex) .. " foi eliminado.")

            -- Verifica se só resta um jogador e finaliza o evento
            if #SYSTEM_MAIN.Users == 1 then
                Colosseum_Finalize(1)  -- Finaliza se restar apenas um jogador
            end
        end
    end
end

function Colosseum_UserRespawn(aIndex)
    -- Não teleporta jogadores que já foram eliminados
    if SYSTEM_MAIN.Stage == 2 and SYSTEM_MAIN.GetUser(aIndex) ~= 0 and SYSTEM_MAIN.UserCache[aIndex] then
        teleportUserToArena(aIndex)
    end
end

function Colosseum_CheckUserTarget(aIndex, bIndex)
    if SYSTEM_MAIN.Stage == 2 and SYSTEM_MAIN.GetUser(aIndex) ~= 0 and SYSTEM_MAIN.GetUser(bIndex) ~= 0 then
        return 1 -- Permitir PvP entre participantes
    end
    return 0
end

function Colosseum_CheckUserKiller(aIndex, bIndex)
    if SYSTEM_MAIN.Stage == 2 and SYSTEM_MAIN.GetUser(aIndex) ~= 0 and SYSTEM_MAIN.GetUser(bIndex) ~= 0 then
        return 0 -- Não aplicar status PK para mortes durante o evento
    end
    return 1
end

function Colosseum_Finalize(reason)
    if SYSTEM_MAIN.EventFinalized then
        return  -- Se o evento já foi finalizado, não faça nada
    end
    
    SYSTEM_MAIN.EventFinalized = true  -- Marca que o evento foi finalizado

    if reason == 1 then  -- A condição para vencedor
        NoticeSendToAll(0, ". : [ Sobrevivência ] : .")
        NoticeSendToAll(0, "O evento terminou!")
        LogColor(3, "[Sobrevivência]: Evento finalizado com sucesso.")
        
        if #SYSTEM_MAIN.Users == 1 then 
            local winnerName = GetObjectName(SYSTEM_MAIN.Users[1].Index)
            NoticeSendToAll(0, "Parabéns a " .. winnerName .. " por vencer o evento!")
            NoticeSendToAll(0, winnerName .. " recebeu " .. SYSTEM_CONFIG.CashReward .. " Cash como recompensa!")
            ItemGive(SYSTEM_MAIN.Users[1].Index,23)
            rewardWinner(SYSTEM_MAIN.Users[1].Index)
        end
    elseif reason == 2 then
        NoticeSendToAll(0, ". : [ Sobrevivência ] : .")
        NoticeSendToAll(0, "O evento foi cancelado!")
        LogColor(3, "[Sobrevivência]: Evento cancelado.")
    elseif reason == 3 then
        NoticeSendToAll(0, ". : [ Sobrevivência ] : .")
        NoticeSendToAll(0, "O evento terminou devido ao limite de tempo!")
        LogColor(3, "[Sobrevivência]: Evento terminou devido ao limite de tempo.")
    end

    -- Redefinir variaveis
    resetEventVariables()
end

function resetEventVariables()
    SYSTEM_MAIN.Stage = nil
    SYSTEM_MAIN.Users = {}
    SYSTEM_MAIN.UserCache = {} -- Limpa o cache
    SYSTEM_MAIN.UserCount = 0
    SYSTEM_MAIN.Count = 0
    SYSTEM_MAIN.EventEndTime = nil
    SYSTEM_MAIN.EventFinalized = false
end

function teleportUserToArena(userIndex)
    -- Teleport user to the Colosseum map
    local x = SYSTEM_CONFIG.CordXY[1] + math.random(-10, 10)
    local y = SYSTEM_CONFIG.CordXY[2] + math.random(-10, 10)
    MoveUserEx(userIndex, SYSTEM_CONFIG.Map, x, y)
end

function SYSTEM_MAIN.AddUser(aIndex)
    if #SYSTEM_MAIN.Users >= SYSTEM_CONFIG.MaxUsers then
        NoticeSend(aIndex, 1, SYSTEM_MAIN.LogPrefix .. "O evento está cheio. Por favor, tente novamente mais tarde!")
        return
    end

    local newIndex = #SYSTEM_MAIN.Users + 1
    SYSTEM_MAIN.Users[newIndex] = { Index = aIndex }
    SYSTEM_MAIN.UserCache[aIndex] = newIndex -- Atualiza o cache
    
    NoticeSend(aIndex, 1, SYSTEM_MAIN.LogPrefix .. "Você se registrou com sucesso para o evento!")
    LogColor(3, SYSTEM_MAIN.LogPrefix .. "Jogador " .. GetObjectName(aIndex) .. " se registrou para o evento.")
end

function SYSTEM_MAIN.DelUser(aIndex)
    local userIndex = SYSTEM_MAIN.GetUser(aIndex)
    if userIndex == 0 then return end

    table.remove(SYSTEM_MAIN.Users, userIndex)
    SYSTEM_MAIN.UserCache[aIndex] = nil -- Remove do cache
    
    -- Atualiza o cache para os usuários restantes
    for i, v in ipairs(SYSTEM_MAIN.Users) do
        SYSTEM_MAIN.UserCache[v.Index] = i
    end
    
    NoticeSend(aIndex, 1, SYSTEM_MAIN.LogPrefix .. "Você foi removido do evento.")
    LogColor(3, SYSTEM_MAIN.LogPrefix .. "Jogador " .. GetObjectName(aIndex) .. " removido do evento.")
end

function SYSTEM_MAIN.GetUser(aIndex)
    -- Verifica primeiro no cache
    if SYSTEM_MAIN.UserCache[aIndex] then
        return SYSTEM_MAIN.UserCache[aIndex]
    end
    
    -- Se não estiver no cache, procura na lista
    for i, v in ipairs(SYSTEM_MAIN.Users) do
        if v.Index == aIndex then
            SYSTEM_MAIN.UserCache[aIndex] = i -- Atualiza o cache
            return i
        end
    end
    return 0
end

-- Função para mandar mesnagem para todos os usuarios
function SYSTEM_MAIN.Message(type, message)
    for _, user in ipairs(SYSTEM_MAIN.Users) do
        NoticeSend(user.Index, type, message)
    end
end
