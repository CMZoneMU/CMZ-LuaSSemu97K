--############################################################################
-- RGProject MU Online Emulator
-- ---------------------------------------------------------------------------
-- © 2024 RGProject Development
-- This file is part of the RGP MuOnline Server files.
--############################################################################

-- ===========================================================================
-- ADVERTENCIA: Modificar este archivo puede afectar la funcionalidad del juego. 
-- Cualquier modificación incorrecta puede resultar en errores, fallos o comportamientos inesperados en el juego.

-- WARNING: Modifying this file may affect the functionality of the game.
-- Any incorrect modification can result in errors, crashes, or unexpected behavior in the game.
-- ===========================================================================
InterfaceController = {}

local MainLoader_Handle = {}

-- Manejo de MainLoader
function MainLoader()
    for _, handler in pairs(MainLoader_Handle) do
        handler.callback()
    end
end

function InterfaceController.MainLoader(callback)
    MainLoader_Handle[callback] = { callback = callback }
end

local MainProcThread_Handle = {}

-- Manejo de MainProcThread
function MainProcThread()
    for _, handler in pairs(MainProcThread_Handle) do
        handler.callback()
    end
end

function InterfaceController.MainProcThread(callback)
    MainProcThread_Handle[callback] = { callback = callback }
end

local KeyboardEvent_Handle = {}

-- Manejo de KeyboardEvent
function KeyboardEvent(index)
    for _, handler in pairs(KeyboardEvent_Handle) do
        handler.callback(index)
    end
end

function InterfaceController.KeyboardEvent(callback)
    KeyboardEvent_Handle[callback] = { callback = callback }
end

local ClientProtocol_Handle = {}

-- Manejo de ClientProtocol
function ClientProtocol(head, packet_name)
    for _, handler in pairs(ClientProtocol_Handle) do
        handler.callback(head, packet_name)
    end
end

function InterfaceController.ClientProtocol(callback)
    ClientProtocol_Handle[callback] = { callback = callback }
end

local ClientEvent_Handle = {}

-- Manejo de MainEvent
function ClientEvent(Event)
    for _, handler in pairs(ClientEvent_Handle) do
        handler.callback(Event)
    end
end

function InterfaceController.ClientEvent(callback)
    ClientEvent_Handle[callback] = { callback = callback }
end

local LoadImages_Handle = {}
-- Manejo de LoadImages
function LoadImages()
    for _, handler in pairs(LoadImages_Handle) do
        handler.callback()
    end
end

function InterfaceController.LoadImages(callback)
    LoadImages_Handle[callback] = { callback = callback }
end

return InterfaceController
