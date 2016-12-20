@echo off
CL /nologo /O1 /G5 /GD /GX /LD ShootSunApi.cpp /FeShootSunApi.dll /link /OPT:NOWIN98 /MERGE:.rdata=.text /MERGE:.text=.data /MERGE:.bss=.data /SECTION:.data,ERWS /IGNORE:4078,4092 /BASE:0XAFEC0000 /ENTRY:DllMain /EXPORT:Init /EXPORT:HooksCanUnloadNow KERNEL32.lib USER32.lib msvcrt.lib GainSunStaticLib.lib DataFunc.lib ws2_32.lib
if exist ShootSunApi.exp del ShootSunApi.exp
if exist ShootSunApi.lib del ShootSunApi.lib
if exist ShootSunApi.obj del ShootSunApi.obj
copy ShootSunApi.dll ..\..\shootsundroiyan\debug\ShootSunApi.dll
copy ShootSunApi.dll ..\..\shootsundroiyan\release\ShootSunApi.dll
rem pause
cls