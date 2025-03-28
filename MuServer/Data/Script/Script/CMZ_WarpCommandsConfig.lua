--############################################################################
-- SSeMU MU Online Emulator
-- https://www.ssemu.com.ar
-- https://www.facebook.com/ssemuemulator
-- https://www.youtube.com/@ssemu
-- ---------------------------------------------------------------------------
-- � 2024 Creado por Anthony Rosas o gambasoxd
-- Descripci�n: Este archivo es un script de configuraci�n para los Warp Commands
-- Version: 1.0.0
--############################################################################

WarpCommandsConfig = {}
WarpCommandsConfig.Switch = true
WarpCommandsConfig.MessageSwitch = true
WarpCommandsConfig.TypeMessage = 0 -- 0 = mensaje central, 1 = mensaje en sistema

WarpCommandsConfig.Commands = {
    ['Herrero'] = {
        ['IndexCommand'] = 30,
        ['IndexMap'] = 0,
        ['MapCoordinateX'] = 118,
        ['MapCoordinateY'] = 141,
        ['Level'] = 10,
        ['Message'] = 'Bem vindo ao Ferreiro!'
    },
    ['PetTrainer'] = {
        ['IndexCommand'] = 31,
        ['IndexMap'] = 3,
        ['MapCoordinateX'] = 173,
        ['MapCoordinateY'] = 123,
        ['Level'] = 10,
        ['Message'] = 'Bem vindo a Elf Lala!'
    },
    ['Bar'] = {
        ['IndexCommand'] = 32,
        ['IndexMap'] = 3,
        ['MapCoordinateX'] = 179,
        ['MapCoordinateY'] = 101,
        ['Level'] = 10,
        ['Message'] = 'Bem vindo ao Maquina de Chaos!'
    },
    ['Arena1'] = {
        ['IndexCommand'] = 33,
        ['IndexMap'] = 2,
        ['MapCoordinateX'] = 217,
        ['MapCoordinateY'] = 25,
        ['Level'] = 30,
        ['Message'] = 'Bem vindo a Igreja!'
    },
    ['Refineria'] = {
        ['IndexCommand'] = 36,
        ['IndexMap'] = 0,
        ['MapCoordinateX'] = 121,
        ['MapCoordinateY'] = 113,
        ['Level'] = 300,
        ['Message'] = 'Bem vindo a Maga!'
    },
    ['Selupan'] = {
        ['IndexCommand'] = 37,
        ['IndexMap'] = 2,
        ['MapCoordinateX'] = 222,
        ['MapCoordinateY'] = 69,
        ['Level'] = 300,
        ['Message'] = 'Bem vindo a Saida de Devias!'
    }
}