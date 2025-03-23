

-- Inicializa a tabela JewelBank
JewelBank = {}

-- Vari�vel para controlar se a janela est� aberta ou fechada
JewelBank.JewelBankOpen = false

local ModeDeposito = true
local ModeRetiro = false

-- Fun��o para ativar a janela do banco de joias
function JewelBank.OpenWindow()
    JewelBank.JewelBankOpen = true
    ModeDeposito = true  -- Ativa o modo de dep�sito automaticamente
    ModeRetiro = false   -- Garante que o modo de retirada esteja desativado
    CharacterLockAction(1)
end

-- Fun��o para desativar a janela do banco de joias
function JewelBank.CloseWindow()
    JewelBank.JewelBankOpen = false
    CharacterLockAction(0)
end

local JewelNameCommand = {
    "chaos",
    "life",
    "soul",
    "bless",
    "creation"
}

local JewelNumberID = {
    chaos = 399,
    life = 464,
    soul = 462,
    bless = 461,
    creation = 470
}

local Menu_Texts = {}

Menu_Texts["Eng"] =
{
    [1] = "Jewel of Chaos",
    [2] = "Jewel of Life",
    [3] = "Jewel of Soul",
    [4] = "Jewel of Bless",
    [5] = "Jewel of Creation",
    [6] = "Custom Jewel Bank", 
    [7] = "Deposit",           
    [8] = "Withdraw",          
	[9] = "Bank State",
	[10] = "Close",
    [11] = "Welcome: %s",
    [12] = "Jewel Bank"
}

Menu_Texts["Por"] =
{
    [1] = "Jewel of Chaos",
    [2] = "Jewel of Life",
    [3] = "Jewel of Soul",
    [4] = "Jewel of Bless",
    [5] = "Jewel of Creation",
    [6] = "Banco de Joias",  
    [7] = "Dep�sito",        
    [8] = "Retiro",          
	[9] = "Banco",
	[10] = "Fechar",
    [11] = "Bem-vindo: %s",
    [12] = "Banco de Joias"
}

Menu_Texts["Spn"] =
{
    [1] = "Jewel of Chaos",
    [2] = "Jewel of Life",
    [3] = "Jewel of Soul",
    [4] = "Jewel of Bless",
    [5] = "Jewel of Creation",
    [6] = "Banco de Joyas",  
    [7] = "Dep�sito",        
    [8] = "Retiro",          
	[9] = "Banco",
	[10] = "Cerrar",
    [11] = "Bienvenido: %s",
    [12] = "Banco de Joyas"
}

-- Fun��o para desenhar o painel da interface do banco de joias
function JewelBank.DrawPanel()
    local PlayerState = GetPlayerState()

    -- Se o jogador n�o est� no jogo, n�o faz nada
    if PlayerState ~= 5 then
        return
    end

    -- Se a janela n�o est� ativa, n�o desenha nada
    if not JewelBank.JewelBankOpen then
        return
    end

	CheckWindosSystemLua(0)
	
	WindowSystem(0, 1)
	
    -- Vari�veis para posicionamento e tamanho da janela
    local MainWidth = 230
    local MainHeight = 150
    local PosX = (640 / 2) - (MainWidth / 2)
    local PosY = 80

    local playerName = GetPlayerName() -- Nome do personagem

    CharacterLockAction(1)

    -- Cria o painel principal com os textos do banco
	--CreateCustomWindows(PosX - 20, PosY - 20, 65, 8, MainWidth, MainHeight, Menu_Texts[SetLangUser()][6])
    CreateClassicWindows(PosX - 30, PosY - 25, MainWidth, MainHeight, JewelBank.JewelBankOpen)
    CreateCustomText(PosX + 45, PosY - 13, 1, 0, 0, string.format(CustomMenu_Texts[SetLangUser()][1]), 0)
        


    -- Mesnagem de bem-vinda com nome do player
    local welcomeMessage = string.format(Menu_Texts[SetLangUser()][11], playerName)

    -- Usa o CreateCustomText pra monstrar a mensagem formatada
    CreateCustomText(PosX + 20, PosY + 240, 1, 0, 0, welcomeMessage, 0)

    -- Verifica se ambos modos est�o inat�vos
    if ModeRetiro == false and ModeDeposito == false then
        -- Desenhar ambos bot�es porque nenhum est� at�vo
        if CreateCustomButton(PosX + 20, PosY, 15, 5, 60, 18, Menu_Texts[SetLangUser()][7]) then
            ModeDeposito = true
            ModeRetiro = false
        end

        if CreateCustomButton(PosX + 110, PosY, 15, 5, 60, 18, Menu_Texts[SetLangUser()][8]) then
            ModeRetiro = true
            ModeDeposito = false
        end
    else
        -- Se algum dos modos est� at�vo
        if ModeDeposito == true then
            -- Desenhar s� o bot�o de Retiro
            if CreateCustomButton(PosX + 110, PosY, 15, 5, 60, 18, Menu_Texts[SetLangUser()][8]) then
                ModeRetiro = true
                ModeDeposito = false
            end
        elseif ModeRetiro == true then
            -- Desenhar s� o bot�o de Dep�sito
            if CreateCustomButton(PosX + 20, PosY, 15, 5, 60, 18, Menu_Texts[SetLangUser()][7]) then
                ModeDeposito = true
                ModeRetiro = false
            end
        end


        -- Bot�o de consulta no Banco
        if CreateCustomButton(PosX + 110, PosY + 210, 10, 5, 60, 18, Menu_Texts[SetLangUser()][9]) then
            SendChat("/verbanco") 
        end

        -- Aqu�� � onde renderizamos as joias de maneira independente ao resto
        local offsetY = 10  -- 

        -- Renderiza as joias no painel
        RenderItem3D(PosX - 30, PosY + offsetY, 50, 50, JewelNumberID.chaos, 0, 0, 0, 0)
        offsetY = offsetY + 30   

        RenderItem3D(PosX - 30, PosY + offsetY - 5, 50, 50, JewelNumberID.life, 0, 0, 0, 0)
        offsetY = offsetY + 30  

        RenderItem3D(PosX - 30, PosY + offsetY - 2, 50, 50, JewelNumberID.soul, 0, 0, 0, 0)
        offsetY = offsetY + 30  

        RenderItem3D(PosX - 30, PosY + offsetY + 3, 50, 50, JewelNumberID.bless, 0, 0, 0, 0)
        offsetY = offsetY + 30  

        RenderItem3D(PosX - 30, PosY + offsetY + 9, 50, 50, JewelNumberID.creation, 0, 0, 0, 0)
    end

    -- Modo Dep�sito
    if ModeDeposito == true and ModeRetiro == false then
        -- Separa��o vertical entre os textos
        local offsetY = 40  -- Posi��o inicial em Y
        local spacing = 35  -- Espa�ado entre nomes

        -- Desenhar os nomes das joias e seus bot�es
        for i = 1, 5 do
            -- Desenhar o nome da joia (agora com o nome correto no idioma correspondente)
            CreateCustomText(PosX + 10, PosY + offsetY, 1, 0, 0, Menu_Texts[SetLangUser()][i], 0)

            -- Desenhar os bot�es com diferentes quantidades
            local commands = { "1", "10", "20", "30" }
            for j, quantity in ipairs(commands) do
                if CreateCustomButton(PosX + 85 + (j - 1) * 25, PosY + offsetY - 10, 7, 5, 20, 18, quantity) then
                    -- Enviar o comando correspondente a essa joia e quantidade
                    SendChat("/deposito " .. JewelNameCommand[i] .. " " .. quantity)
                end
            end

            -- Incrementar a posi��o Y pra pr�xima joia
            offsetY = offsetY + spacing
        end

        CreateCustomText(PosX + 50, PosY + 200, 1, 0, 4, Menu_Texts[SetLangUser()][7] .. ": ON", 0)
    end

    -- Modo Retiro
    if ModeRetiro == true and ModeDeposito == false then
        -- Separa��o vertical entre os textos
        local offsetY = 40   
        local spacing = 35  

        -- Desenhar os nomes das joias e seus bot�es
        for i = 1, 5 do
			-- Desenhar o nome da joia (agora com o nome correto no idioma correspondente)
            CreateCustomText(PosX + 10, PosY + offsetY, 1, 0, 0, Menu_Texts[SetLangUser()][i], 0)

            -- Desenhar os bot�es com diferentes quantidades
            local commands = { "1", "10", "20", "30" }
            for j, quantity in ipairs(commands) do
                if CreateCustomButton(PosX + 85 + (j - 1) * 25, PosY + offsetY - 10, 7, 5, 20, 18, quantity) then
                    -- Enviar o comando correspondente a essa joia e quantidade
                    SendChat("/retiro " .. JewelNameCommand[i] .. " " .. quantity)
                end
            end

            -- Incrementar a posi��o Y pra pr�xima joia
            offsetY = offsetY + spacing
        end
        CreateCustomText(PosX + 50, PosY + 200, 1, 0, 4, Menu_Texts[SetLangUser()][8] .. ": ON", 0)
    end

    -- Bot�o de Fechar
    if CreateCustomButton(PosX + 20, PosY + 210, 15, 5, 60, 18, Menu_Texts[SetLangUser()][10]) then
        JewelBank.CloseWindow() -- Fechar a janela quando acionar o bot�o "Close"
        ModeRetiro = false
        ModeDeposito = false
    end
end

function JewelBank.Active(keyIndex)
    -- Verifica se o chat est� ativo (retorno 1 indica ativo)
    if GetChatState() == 1 then
        return
    end

    if keyIndex == 74 then  -- 74 corresponde �tecla "J"
        if JewelBank.JewelBankOpen then
            JewelBank.CloseWindow()
            ModeRetiro = false
            ModeDeposito = false
        else
            JewelBank.OpenWindow()
        end
    end
end



function JewelBank.Init()

InterfaceController.MainProcThread(JewelBank.DrawPanel)
InterfaceController.KeyboardEvent(JewelBank.Active)

end


JewelBank.Init()

return JewelBank