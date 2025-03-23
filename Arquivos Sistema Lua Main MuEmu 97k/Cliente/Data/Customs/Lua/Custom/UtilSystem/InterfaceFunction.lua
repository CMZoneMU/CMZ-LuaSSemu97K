

WindowTypes = 
{
    Inventario = 0,
    Chat = 1,
    Tienda = 2,
    GuildCreador = 3,
    MoveList = 4,
    Character = 5,
    ChaosGoblin = 6,
    Party = 7,
    PersonalShop = 8,
    GoldenArcher = 9,
    Commandos = 10,
    Evento = 11,
    Guild = 12
}

function CheckWindosSystemLua(Type)
    local actions = 
	{
        [0] = function()
            InfoChar.Open = false
           InfoChar.CloseWindow()
        end,
        [1] = function()
            JewelBank.JewelBankOpen = false
            JewelBank.CloseWindow()
        end 
    }

   
    actions[Type]()
end

function UpdateKeyEsc(Key)
    if Key == 27 then
	
		CharacterLockAction(0) --Desbloquea el Usuario
        -- Llamamos a las funciones para cerrar las ventanas
        CheckWindosSystemLua(0)  -- Cerrar GiftCode (si está abierta)
        CheckWindosSystemLua(1)  -- Cerrar JewelBank (si está abierta)
		CheckWindosSystemLua(2)  -- Cerrar Make Item (si está abierta)
		CheckWindosSystemLua(3)  -- Cerrar Custom Menu (si está abierta)
        CheckWindosSystemLua(4)  -- Cerrar Custom CommandInfo (si está abierta)
    end
end


InterfaceController.KeyboardEvent(UpdateKeyEsc)