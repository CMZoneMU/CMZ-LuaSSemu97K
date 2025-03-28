--############################################################################
-- SSeMU MU Online Emulator
-- https://www.ssemu.com.ar
-- https://www.facebook.com/ssemuemulator
-- https://www.youtube.com/@ssemu
-- ---------------------------------------------------------------------------
-- © 2023 SetecSoft Development
-- This file is part of the SSeMU MuOnline Server files.
--############################################################################

-- ===========================================================================
-- Atención: Este archivo debe usarse únicamente para requerir otros archivos.
-- No debes agregar código en este archivo. Si deseas agregar scripts personalizados,
-- crea un nuevo archivo basado en el ejemplo 'TemplateScript.lua'.
-- Asegúrate de no eliminar la línea require('System\ScriptCore'), ya que sin ella, ningún script funcionará.
-- Para agregar nuevos scripts, debes hacerlo utilizando la sintaxis require('Nombre del archivo')."

-- Attention: This file should only be used to require other files.
-- You should not add code to this file. If you want to add custom scripts,
-- create a new file based on the example 'TemplateScript.lua'.
-- Make sure not to remove the line require('System\ScriptCore'), as without it, no script will work.
-- To add new scripts, you must use the syntax require('File Name').
-- ===========================================================================

SQLConnect("MuOnline97_new", "sa", "!@#Cmzone");

require('System\\CMZ_ScriptCore')
require('System\\CMZ_ScriptReader')
require('Script\\CMZ_TemplateScript')
require('Script\\CMZ_WelcomeMessage')
require('Script\\CMZ_MonsterKill')

