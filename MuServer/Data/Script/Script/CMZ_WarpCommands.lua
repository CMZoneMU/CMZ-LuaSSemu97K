--[[ 
    Eevento Sobrevivencia
    Criado por:  Anthony Rosas o gambasoxd
    Modificado por: CMZone 25/07/2024
	
	Script Lua liberado para estudos..
]]

-- Vinculamos as funções de ponte às nossas funções personalizadas
-- ===========================================================================
BridgeFunctionAttach('OnShutScript', 'WarpCommands_OnShutScript')
BridgeFunctionAttach('OnCommandManager', 'WarpCommands_OnCommandManager')
-- ===========================================================================

-- Quando o script é carregado
function WarpCommands_OnShutScript()
    -- Validamos se o script foi carregado corretamente com um log
    LogColor(2, "[WarpCommands] O script foi iniciado")
end

function WarpCommands_OnCommandManager(aIndex, code, arguments)
    if (WarpCommandsConfig.Switch) then
        for __, option in pairs(WarpCommandsConfig.Commands) do
            if (option.IndexCommand == code and GetObjectLevel(aIndex) >= option.Level) then
                MoveUserEx(aIndex, option.IndexMap, option.MapCoordinateX, option.MapCoordinateY)
                if (option.MessageSwitch) then
                    NoticeSend(aIndex, WarpCommandsConfig.TypeMessage, option.Message)
                end
                LogPrint("[WarpCommands] O usuário " .. GetObjectName(aIndex) .. " usou o comando " .. option.IndexCommand .. " ao nível " .. GetObjectLevel(aIndex))
                return 1
            end
        end
    end
    return 0
end