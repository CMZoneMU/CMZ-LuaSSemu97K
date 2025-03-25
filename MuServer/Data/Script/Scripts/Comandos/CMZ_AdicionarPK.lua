-- ===========================================================================
-- Base Lua SSeMU - MuEmu 97k Kayito
-- Créditos Adaptação: NiloMaster | Gabriel GDA 
-- https://www.youtube.com/cmzonecriandomuonline
-- Sistema Livre para estudos © CMZone Team 2025
-- ===========================================================================
-- Script Comando Addpk e Limparpk feito para estudos CMzone
-- ===========================================================================

-- Registra a função CommandAddPK no gerenciador de comandos
BridgeFunctionAttach("OnCommandManager", "CommandAddPK")  

-- Configuração dos comandos e seus códigos 
AddPK = {}
AddPK.Configs = {}
AddPK.Configs["Enabled"] = true   -- true = Ativar  | false = Desativar comando
AddPK.Configs["PKCommandCode"] = 32      -- Código do comando Command.txt
AddPK.Configs["PKCommandName"] = "/addpk"   -- Nome do comando para adicionar PK
AddPK.Configs["ClearCommandCode"] = 33    -- Código do comando Command.txt
AddPK.Configs["ClearCommandName"] = "/limparpk"  -- Nome do comando para limpar PK

function CommandAddPK(aIndex, code, arg)  -- Função principal que gerencia os comandos de PK
    -- Checa se o comando esta Habilitado
    if not AddPK.Configs["Enabled"] then
        NoticeSend(aIndex, 1, "[ Aviso ]: Comando desabilitado!")
        return 1
    end  
    
    if code == AddPK.Configs["PKCommandCode"] then
        local TargetName = arg  -- Armazena o nome do jogador alvo
        if TargetName == nil or TargetName == "" then  -- Verifica se o nome do jogador foi fornecido
            NoticeSend(aIndex, 1, "Syntax Error: Use /addpk <PlayerName>")  -- Envia mensagem de erro de sintaxe
            NoticeSend(aIndex, 1, "Example: /addpk PlayerTest")  -- Envia exemplo de uso
            return 1
        end

        local TargetIndex = GetObjectIndexByName(TargetName)  -- Obtém o índice do jogador pelo nome
        if TargetIndex == -1 then  -- Verifica se o jogador existe
            NoticeSend(aIndex, 1, string.format("Player [%s] não encontrado", TargetName))  -- Envia mensagem de jogador não encontrado
            return 1
        end
    
        -- Define Level PK: 4 | Pk Level 1
        -- Define Level PK: 5 | 1 Estagio Assasino
        -- Define Level PK: 6 | 2 Estagio Assasino
        PKLevelSend(TargetIndex, 6)  -- Define o nível PK do jogador para 6 (2º estágio assassino)
        NoticeSend(aIndex, 1, string.format("Player [%s] voce se tornou PK", TargetName))  -- Envia confirmação

   -- ... Limpar PK ...

    elseif code == AddPK.Configs["ClearCommandCode"] then
        local TargetName = arg  -- Armazena o nome do jogador alvo
        if TargetName == nil or TargetName == "" then  -- Verifica se o nome do jogador foi fornecido
            NoticeSend(aIndex, 1, "Syntax Error: Use /limparpk <PlayerName>")  -- Envia mensagem de erro de sintaxe
            NoticeSend(aIndex, 1, "Example: /limparpk PlayerTest")  -- Envia exemplo de uso
            return 1
        end

        local TargetIndex = GetObjectIndexByName(TargetName)  -- Obtém o índice do jogador pelo nome
        if TargetIndex == -1 then  -- Verifica se o jogador existe
            NoticeSend(aIndex, 1, string.format("Player [%s] não encontrado", TargetName))  -- Envia mensagem de jogador não encontrado
            return 1
        end
 
        -- Define Level Hero: 1 | Heroi Level 1
        -- Define Level Hero: 2 | Heroi Level 2
        -- Define Level Hero: 3 | Comun
        PKLevelSend(TargetIndex, 3)  -- Define o nível do jogador para 3 (comum)
        NoticeSend(aIndex, 1, string.format("Player [%s] teve seu PK removido", TargetName))  -- Envia confirmação

        return 1
    end

    return 0
end