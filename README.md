# Sistema Lua para Kayito MuEmu 0.97k

# - Emulator: MuEmu
# - Sistema Lua Base: SSemu 99B
# - Adaptação por: Nilo Master | Gabriel "GDA"

- MuServer: MuEmu
- Versão LuaLib: 5.4.3

# Atualizações de Scripts

- Script WelcomeMessage refeito usando a nova função **( LuaMessageGetByPlayer )**
   - Esta função foi implementada no LuaFunction.cpp para gerenciar o suporte a múltiplos idiomas no sistema de mensagens do jogo. <br/>
     Ela atua como uma ponte entre os scripts Lua e o sistema central de mensagens do jogo, permitindo a recuperação <br/>
     dinâmica de mensagens com base no idioma selecionado pelo jogador.

- Alteração feita na Função **LuaCommandCheckGameMasterLevel** no LuaFunction.cpp 

- atualização na função **( CCommandManager::Load )**
   - Que envolve o gerenciamento de IDs dos comandos.<br/> 
    Foi implementada a linha **info.Index = lpReadScript->GetNumber();**<br/> 
    **Propósito:** Ela Realiza a leitura dos identificadores únicos (IDs) dos comandos<br/> 
    a partir do arquivo de script armazena o valor numérico no membro Index da estrutura info<br/> 
    Este processo é fundamental para o sistema de gerenciamento de comandos, pois permite que cada comando seja identificado de forma única no sistema.


