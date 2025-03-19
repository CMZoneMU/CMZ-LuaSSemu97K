# Sistema Lua para Kayito MuEmu 0.97k

# - Emulator: MuEmu
# - Sistema Lua Base: SSemu 99B
# - Adaptação por: Nilo Master | Gabriel "GDA"

- MuServer: MuEmu
- Versão LuaLib: 5.4.3

# Atualizações de Scripts
- Alteração feita na Função GameMasterLevel LuaFunction.cpp 
- atualização na função ( CCommandManager::Load )
que envolve o gerenciamento de IDs dos comandos. 
A linha info.Index = lpReadScript->GetNumber(); 
foi adicionada com o seguinte propósito:
- Realiza a leitura dos identificadores únicos (IDs) dos comandos a partir do arquivo de script
- Armazena o valor numérico no membro Index da estrutura info
- Este processo é fundamental para o sistema de gerenciamento de comandos, pois permite que cada comando seja identificado de forma única no sistema

