## Sistema Lua para Kayito MuEmu 0.97k

## - Emulator: MuEmu
## - Arquivos Lua Cliente: Ryzenn 
## - Adaptação GS e Main: Nilo Master | Gabriel "GDA"

- Sistema Lua Base: SSemu 99B
- MuServer: MuEmu
- Versão LuaLib: 5.4.3

## Atualizações de Scripts e Funções na Source

- Alteração feita na Função **LuaCommandCheckGameMasterLevel** no LuaFunction.cpp 
   - Modificação na Verificação de Nível de Game Master<br/> 
   **Código Anterior:**<br/> 
     **SSemu:** if (aValue > gGameMaster.GetGameMasterLevel(&gObj[aIndex])) <br/> 
   **Novo Código:**<br/>
     **MuEMu 97k:** if (gGameMaster.CheckGameMasterLevel(&gObj[aIndex], aValue) == false)<br/> 
   - Principais Mudanças:<br/> 
   Substituição do método de comparação direta por uma função dedicada<br/> 
   Utilização do método CheckGameMasterLevel que oferece uma verificação mais completa<br/> 
   Melhoria na lógica de validação de níveis de Game Master<br/> 

- Alteração na função **( CCommandManager::Load )**
   - Que envolve o gerenciamento de **IDs** dos comandos.<br/> 
    Foi implementada a linha **info.Index = lpReadScript->GetNumber();**<br/>
    **Propósito:** Ela Realiza a leitura dos identificadores únicos (IDs) dos comandos<br/> 
    a partir do arquivo de script armazena o valor numérico no membro Index da estrutura info<br/> 
    Este processo é fundamental para o sistema de gerenciamento de comandos, pois<br/> 
    permite que cada comando seja identificado de forma única no sistema.


