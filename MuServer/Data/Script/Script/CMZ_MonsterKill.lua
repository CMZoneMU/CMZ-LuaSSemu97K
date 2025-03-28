--[[ 
    Eevento Sobrevivencia
    Criado por: Morado7773 
    Modificado por: CMZone 26/03/2025
	
    Script Lua liberado para estudos..
]]


-- ===========================================================================
BridgeFunctionAttach('OnMonsterDie','MonsterMessage_OnMonsterDie')
-- ===========================================================================

function MonsterMessage_OnMonsterDie(aIndex, bIndex)
   
    local MonsterClass = GetObjectClass(aIndex)
    local CharacterName = GetObjectName(bIndex)

if MonsterClass == 55 then -- Death King

NoticeSendToAll(0, string.format("O Death King foi derrotado por %s", CharacterName))
   
    elseif MonsterClass == 78 then  -- Golden Goblin
   
        NoticeSendToAll(0, string.format("O Goblin foi derrotado por %s", CharacterName))

elseif MonsterClass == 53 then  -- Golden Tarkan
   
        NoticeSendToAll(0, string.format("O Tarkan foi derrotado por %s", CharacterName))

elseif MonsterClass == 79 then  -- Golden Dragon
   
        NoticeSendToAll(0, string.format("O Dragon foi derrotado por %s", CharacterName))

elseif MonsterClass == 80 then  -- Golden Lizard
   
        NoticeSendToAll(0, string.format("O Lizard foi derrotado por %s", CharacterName))

elseif MonsterClass == 82 then  -- Golden Tantalos
   
        NoticeSendToAll(0, string.format("O Tantallo foi derrotado por %s", CharacterName))

elseif MonsterClass == 42 then  -- Dragon Rojo
   
        NoticeSendToAll(0, string.format("[%s] derrotou o Dragão Vermelho", CharacterName))

elseif MonsterClass == 135 then  -- White Wizard
   
        NoticeSendToAll(0, string.format("[%s] ha derrotado al Wizard", CharacterName))

    end
end