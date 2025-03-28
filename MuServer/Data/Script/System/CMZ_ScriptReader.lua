--[[ 
    Base LuaScript SSeMU
    Sistema Adaptado: NiloMaster 25/03/2025
	
	Sistema ScriptLua liberado para estudos..
]]

Reader = {}

function Reader:Load(path)
    local this = {
        path = path,
        file = nil,
        LineCount = 0,
        ColumnTable = {},
        ColumnReader = 1,
        cache = {},
        encoding = "UTF-8"
    }

    -- Tratamento de erros na abertura do arquivo
    local success, err = pcall(function()
        this.file = io.open(this.path, "r")
    end)

    if not success or this.file == nil then
        error(string.format("Failed to open file: %s. Error: %s", path, err))
        return nil
    end

    -- Cache system
    function this:CacheFile()
        local content = {}
        for line in self.file:lines() do
            table.insert(content, line)
        end
        self.cache = content
        self.file:seek("set")
    end

    function this:Close()
        if self.file then
            self.file:close()
            self.cache = {}
        end
    end

    function this:GetLine(end_text)
        self.LineCount = self.LineCount + 1
        self.ColumnTable = {}
        self.ColumnReader = 1

        local line = self.file:read()
        if not line then return false end

        -- Validação UTF-8
        if not self:ValidateUTF8(line) then
            error(string.format("Invalid UTF-8 sequence at line %d", self.LineCount))
            return false
        end

        -- Processamento da linha com tratamento de erro
        local success, result = pcall(function()
            return self:ProcessLine(line)
        end)

        if not success then
            error(string.format("Error processing line %d: %s", self.LineCount, result))
            return false
        end

        if #self.ColumnTable == 0 then
            return self:GetLine(end_text)
        elseif self.ColumnTable[1] == end_text then
            return false
        end

        return true
    end

    -- Validação UTF-8
    function this:ValidateUTF8(str)
        return string.match(str, "^[%z\1-\127\194-\244][\128-\191]*$") ~= nil
    end

    -- Processamento de linha melhorado
    function this:ProcessLine(line)
        local LastStr = 0
        local LastCmt = 0
        local LastRow = nil

        for char in string.gmatch(line, ".") do
            if (char == " " or char == "\t") and LastStr == 0 then
                if LastRow ~= nil then
                    table.insert(self.ColumnTable, LastRow)
                    LastRow = nil
                end
            else
                if char == "/" and LastStr == 0 then
                    if LastCmt == 0 then 
                        LastCmt = 1 
                    else 
                        break 
                    end
                else
                    if char == "\"" then
                        LastStr = (LastStr == 0) and 1 or 0
                    else
                        LastRow = (LastRow == nil) and char or LastRow..char
                    end
                end
            end
        end

        if LastRow ~= nil then
            table.insert(self.ColumnTable, LastRow)
        end
    end

    -- Getters melhorados com validação
    function this:GetAsString()
        if self.ColumnReader > #self.ColumnTable then
            return ""
        end
        local value = self.ColumnTable[self.ColumnReader]
        self.ColumnReader = self.ColumnReader + 1
        return value or ""
    end

    function this:GetAsNumber()
        if self.ColumnReader > #self.ColumnTable then
            return 0
        end
        local value = self.ColumnTable[self.ColumnReader]
        self.ColumnReader = self.ColumnReader + 1

        if value == "*" then
            return -1
        end

        local num = tonumber(value)
        if not num then
            error(string.format("Invalid number format at line %d, column %d", self.LineCount, self.ColumnReader-1))
            return 0
        end
        return num
    end

    -- Inicializa cache para arquivos pequenos
    if this.file:seek("end") < 1024 * 1024 then -- Cache apenas arquivos menores que 1MB
        this:CacheFile()
    end

    return this
end