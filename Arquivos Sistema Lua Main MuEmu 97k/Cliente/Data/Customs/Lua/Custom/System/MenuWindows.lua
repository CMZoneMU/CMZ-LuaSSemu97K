

-- Tabela de traduções para o título

CustomMenu = {}

CustomMenu.Open = false

-- Configuração da Janela
local WINDOW = {
    WIDTH = 190,
    HEIGHT = 100,
    X = 420,  -- Posição X ajustada para uma melhor visualização
    Y = 160,  -- Posição Y ajustada para centralização vertical
    BUTTON = {
        WIDTH = 100,
        HEIGHT = 25,
        OFFSET_X = 30,
        SPACING = 30
    }
}

CustomMenu_Texts = 
{
    ["Eng"] = { -- Ingles
        [1] = "Jewel Bank",        
        [2] = "Gift Code",         
        [3] = "Make Item",         
        [4] = "Custom Menu"        
    },
    ["Por"] = { -- Portugues
        [1] = "Banco de Joias",    
        [2] = "Codigo de Presente",
        [3] = "Criaco de Itens",  
        [4] = "Menu Custom" 
    },
    ["Spn"] = { -- Espanol
        [1] = "Banco de Joyas",    
        [2] = "Codigo de Regalo",  
        [3] = "Creacion de Items", 
        [4] = "Menu Custom" 
    }
}


-- Función para abrir la ventana
function CustomMenu.OpenWindow()
    CustomMenu.Open  = true
    --CursorBlock(1)  -- Bloquear el cursor cuando la ventana está abierta
    CharacterLockAction(1)
end

-- Función para cerrar la ventana
function CustomMenu.CloseWindow()
    CustomMenu.Open  = false
    --CursorBlock(0)  -- Liberar el cursor cuando la ventana está cerrada
    CharacterLockAction(0)

end


function CustomMenu.DrawWindows()
    local PlayerState = GetPlayerState()

    if PlayerState ~= 5 or not CustomMenu.Open then
        return
    end

    CreateClassicWindows(WINDOW.X - 20, WINDOW.Y - 20, WINDOW.WIDTH, WINDOW.HEIGHT, CustomMenu.Open)

    -- Botón de Jewel Bank
    if CreateCustomButton(WINDOW.X + WINDOW.BUTTON.OFFSET_X, WINDOW.Y + 20, 
        20, 10, WINDOW.BUTTON.WIDTH, WINDOW.BUTTON.HEIGHT, 
        CustomMenu_Texts[SetLangUser()][1]) then
        JewelBank.OpenWindow() 
        CustomMenu.CloseWindow()
    end
    

    DisableAlphaBlend()

end


function CustomMenu.Active(keyIndex)
    if keyIndex == 117 then  -- 114 es el código de tecla para F3
        -- Alternar el estado de la ventana
        if CustomMenu.Open then
            CustomMenu.CloseWindow()
        else
            CustomMenu.OpenWindow()
        end
    end
end


function CustomMenu.Init()

InterfaceController.MainProcThread(CustomMenu.DrawWindows)
InterfaceController.KeyboardEvent(CustomMenu.Active)

end

CustomMenu.Init()

return CustomMenu