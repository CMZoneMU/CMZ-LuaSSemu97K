

MousePos = {}

MousePos.Open = false

-- Função para abrir a janela
function MousePos.OpenWindow()
    MousePos.Open  = true

end

-- Função para fechar a janela
function MousePos.CloseWindow()
    MousePos.Open  = false


end

-- Função para desenhar o painel
function MousePos.DrawInfo()
  
  if not MousePos.Open then
        return
    end

    local PosX = 70
    local PosY = 10
	

    local MousePosX = MousePosX()  
    local MousePosY = MousePosY()  
	

	RenderColor(PosX - 20, PosY - 5, 120, 10, 0.0, 0.0, 0.0, 0.5)
	
	--DisableAlphaBlend()
--	RenderTipText(PosX , PosY, string.format("Debug Mode: %d - %d", MousePosX, MousePosY))
    CreateCustomText(PosX , PosY, 1, 0, 5, string.format("Debug Mode: %d - %d", MousePosX, MousePosY), 0)
	

	
end

function MousePos.Active(keyIndex)
    if keyIndex == 116 then  -- 114 é o código da tecla para F3
        -- Alternar o estado da janela
        if MousePos.Open then
            MousePos.CloseWindow()
        else
            MousePos.OpenWindow()
        end

    end
end

function MousePos.Init()

InterfaceController.MainProcThread(MousePos.DrawInfo)

InterfaceController.KeyboardEvent(MousePos.Active)

end

MousePos.Init()

return MousePos