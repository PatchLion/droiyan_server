# Microsoft Developer Studio Project File - Name="Server" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Server - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Server.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Server.mak" CFG="Server - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Server - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Server - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/드로이얀서버", VIAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Server - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD F90 /browser
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib ./LibsIncs/JvCryption.lib /nologo /subsystem:windows /map /machine:I386 /nodefaultlib:"LIBC" /opt:ref
# SUBTRACT LINK32 /pdb:none /debug

!ELSEIF  "$(CFG)" == "Server - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "d:\droiyan\DRCN_SERVER"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ws2_32.lib ./LibsIncs/JvCryptionD.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC" /out:"e:\DRCN_SERVER/Server.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Server - Win32 Release"
# Name "Server - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AccessoriUpTable.cpp
# End Source File
# Begin Source File

SOURCE=.\AccessoriUpTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AddEventItemTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BoxEventTable.cpp
# End Source File
# Begin Source File

SOURCE=.\BoxEventTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BufferEx.cpp
# End Source File
# Begin Source File

SOURCE=.\CBSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\CELL.cpp
# End Source File
# Begin Source File

SOURCE=.\CircularBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\CityNpcTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\COM.cpp
# End Source File
# Begin Source File

SOURCE=.\Compress.cpp
# End Source File
# Begin Source File

SOURCE=.\DBItemInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DNTable.cpp
# End Source File
# Begin Source File

SOURCE=.\DNTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DressingSet.cpp
# End Source File
# Begin Source File

SOURCE=.\EBodyIdentifyTable.cpp
# End Source File
# Begin Source File

SOURCE=.\EBodyIdentifyTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\EBodyStoreSet.cpp
# End Source File
# Begin Source File

SOURCE=.\EBodyTable.cpp
# End Source File
# Begin Source File

SOURCE=.\EBodyTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\EBodyUpgradeTable.cpp
# End Source File
# Begin Source File

SOURCE=.\EBodyUpgradeTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorLog.cpp
# End Source File
# Begin Source File

SOURCE=.\EVENT.cpp
# End Source File
# Begin Source File

SOURCE=.\EVENT_DATA.cpp
# End Source File
# Begin Source File

SOURCE=.\EventBlockingTable.cpp
# End Source File
# Begin Source File

SOURCE=.\EventItemNew.cpp
# End Source File
# Begin Source File

SOURCE=.\EventItemTable.cpp
# End Source File
# Begin Source File

SOURCE=.\EventItemTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\EventZone.cpp
# End Source File
# Begin Source File

SOURCE=.\EXEC.cpp
# End Source File
# Begin Source File

SOURCE=.\global.cpp
# End Source File
# Begin Source File

SOURCE=.\Guild.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildFortress.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildFortressSet.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildFortressTaxSet.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildHouse.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildHouseRankSet.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildHouseSet.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildHouseWar.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildMapInfoSet.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildMapInfoTable.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildStoreSet.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildStoreTable.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildUser.cpp
# End Source File
# Begin Source File

SOURCE=.\Hyper.cpp
# End Source File
# Begin Source File

SOURCE=.\InitItemTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\IOCPBASE.CPP
# End Source File
# Begin Source File

SOURCE=.\IOCPSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\Item.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemTable.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelUpTable.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelUpTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\LOGIC.cpp
# End Source File
# Begin Source File

SOURCE=.\LOGIC_ELSE.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicItemTable.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicItemTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\MAP.cpp
# End Source File
# Begin Source File

SOURCE=.\MechanicStoreSet.cpp
# End Source File
# Begin Source File

SOURCE=.\MemUser.cpp
# End Source File
# Begin Source File

SOURCE=.\MonsterPsiSet.cpp
# End Source File
# Begin Source File

SOURCE=.\MyDB.cpp
# End Source File
# Begin Source File

SOURCE=.\Npc.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcChat.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcChatSet.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcItem.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcItemSet.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcPosSet.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcSayEventSet.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcSayTable.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcTable.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcThread.cpp
# End Source File
# Begin Source File

SOURCE=.\PAMAExp.cpp
# End Source File
# Begin Source File

SOURCE=.\PAMAExpSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Path.cpp
# End Source File
# Begin Source File

SOURCE=.\PathFind.cpp
# End Source File
# Begin Source File

SOURCE=.\PoolBase.cpp
# End Source File
# Begin Source File

SOURCE=.\PsiStoreSet.cpp
# End Source File
# Begin Source File

SOURCE=.\PsiTable.cpp
# End Source File
# Begin Source File

SOURCE=.\PsiTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Recover.cpp
# End Source File
# Begin Source File

SOURCE=.\RecoverRate.cpp
# End Source File
# Begin Source File

SOURCE=.\RecoverRateSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RecoverSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Remodeling02TableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Remodeling03TableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RemodelingTable.cpp
# End Source File
# Begin Source File

SOURCE=.\RemodelingTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RoyalRumble.cpp
# End Source File
# Begin Source File

SOURCE=.\RoyalRumbleUser.cpp
# End Source File
# Begin Source File

SOURCE=.\Search.cpp
# End Source File
# Begin Source File

SOURCE=.\Server.cpp
# End Source File
# Begin Source File

SOURCE=.\Server.rc
# End Source File
# Begin Source File

SOURCE=.\ServerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerDlg2.cpp
# End Source File
# Begin Source File

SOURCE=.\SERVERINFO.cpp
# End Source File
# Begin Source File

SOURCE=.\SharedMemory.cpp
# End Source File
# Begin Source File

SOURCE=.\SharedQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\sinstance.cpp
# End Source File
# Begin Source File

SOURCE=.\SkillTable.cpp
# End Source File
# Begin Source File

SOURCE=.\SkillTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SocketManager.cpp
# End Source File
# Begin Source File

SOURCE=.\SResourceArray.cpp
# End Source File
# Begin Source File

SOURCE=.\SSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Store.cpp
# End Source File
# Begin Source File

SOURCE=.\StoreRepairSet.cpp
# End Source File
# Begin Source File

SOURCE=.\StoreSellSet.cpp
# End Source File
# Begin Source File

SOURCE=.\StoreSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SummonTable.cpp
# End Source File
# Begin Source File

SOURCE=.\TableItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ThrowItem.cpp
# End Source File
# Begin Source File

SOURCE=.\TownPotalTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\UNI_CHAR.cpp
# End Source File
# Begin Source File

SOURCE=.\UResourceArray.cpp
# End Source File
# Begin Source File

SOURCE=.\USER.cpp
# End Source File
# Begin Source File

SOURCE=.\USER2.cpp
# End Source File
# Begin Source File

SOURCE=.\UserLevelUpSet.cpp
# End Source File
# Begin Source File

SOURCE=.\UserLevelUpTable.cpp
# End Source File
# Begin Source File

SOURCE=.\UserManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ValItemTable.cpp
# End Source File
# Begin Source File

SOURCE=.\ValItemTableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\VirtualRoom.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneInfoSet.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AccessoriUpTable.h
# End Source File
# Begin Source File

SOURCE=.\AccessoriUpTableSet.h
# End Source File
# Begin Source File

SOURCE=.\AddEventItemTableSet.h
# End Source File
# Begin Source File

SOURCE=.\BoxEventTable.h
# End Source File
# Begin Source File

SOURCE=.\BoxEventTableSet.h
# End Source File
# Begin Source File

SOURCE=.\BufferEx.h
# End Source File
# Begin Source File

SOURCE=.\CBSocket.h
# End Source File
# Begin Source File

SOURCE=.\CELL.h
# End Source File
# Begin Source File

SOURCE=.\CircularBuffer.h
# End Source File
# Begin Source File

SOURCE=.\CityNpcTableSet.h
# End Source File
# Begin Source File

SOURCE=.\COM.h
# End Source File
# Begin Source File

SOURCE=.\Compress.h
# End Source File
# Begin Source File

SOURCE=.\DBItemInfo.h
# End Source File
# Begin Source File

SOURCE=.\Define.h
# End Source File
# Begin Source File

SOURCE=.\DNTable.h
# End Source File
# Begin Source File

SOURCE=.\DNTableSet.h
# End Source File
# Begin Source File

SOURCE=.\DressingSet.h
# End Source File
# Begin Source File

SOURCE=.\EBodyIdentifyTable.h
# End Source File
# Begin Source File

SOURCE=.\EBodyIdentifyTableSet.h
# End Source File
# Begin Source File

SOURCE=.\EBodyStoreSet.h
# End Source File
# Begin Source File

SOURCE=.\EBodyTable.h
# End Source File
# Begin Source File

SOURCE=.\EBodyTableSet.h
# End Source File
# Begin Source File

SOURCE=.\EBodyUpgradeTable.h
# End Source File
# Begin Source File

SOURCE=.\EBodyUpgradeTableSet.h
# End Source File
# Begin Source File

SOURCE=.\ErrorLog.h
# End Source File
# Begin Source File

SOURCE=.\EVENT.h
# End Source File
# Begin Source File

SOURCE=.\EVENT_DATA.h
# End Source File
# Begin Source File

SOURCE=.\EventBlockingTable.h
# End Source File
# Begin Source File

SOURCE=.\EventItemNew.h
# End Source File
# Begin Source File

SOURCE=.\EventItemTable.h
# End Source File
# Begin Source File

SOURCE=.\EventItemTableSet.h
# End Source File
# Begin Source File

SOURCE=.\EventZone.h
# End Source File
# Begin Source File

SOURCE=.\EXEC.h
# End Source File
# Begin Source File

SOURCE=.\Extern.h
# End Source File
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\Guild.h
# End Source File
# Begin Source File

SOURCE=.\GuildFortress.h
# End Source File
# Begin Source File

SOURCE=.\GuildFortressSet.h
# End Source File
# Begin Source File

SOURCE=.\GuildFortressTaxSet.h
# End Source File
# Begin Source File

SOURCE=.\GuildHouse.h
# End Source File
# Begin Source File

SOURCE=.\GuildHouseRankSet.h
# End Source File
# Begin Source File

SOURCE=.\GuildHouseSet.h
# End Source File
# Begin Source File

SOURCE=.\GuildHouseWar.h
# End Source File
# Begin Source File

SOURCE=.\GuildMapInfoSet.h
# End Source File
# Begin Source File

SOURCE=.\GuildMapInfoTable.h
# End Source File
# Begin Source File

SOURCE=.\GuildStoreSet.h
# End Source File
# Begin Source File

SOURCE=.\GuildStoreTable.h
# End Source File
# Begin Source File

SOURCE=.\GuildUser.h
# End Source File
# Begin Source File

SOURCE=.\Hyper.h
# End Source File
# Begin Source File

SOURCE=.\InitItemTableSet.h
# End Source File
# Begin Source File

SOURCE=.\IOCPBASE.h
# End Source File
# Begin Source File

SOURCE=.\IOCPSocket.h
# End Source File
# Begin Source File

SOURCE=.\Item.h
# End Source File
# Begin Source File

SOURCE=.\ItemTable.h
# End Source File
# Begin Source File

SOURCE=.\ItemTableSet.h
# End Source File
# Begin Source File

SOURCE=.\JvCryption.h
# End Source File
# Begin Source File

SOURCE=.\LevelUpTable.h
# End Source File
# Begin Source File

SOURCE=.\LevelUpTableSet.h
# End Source File
# Begin Source File

SOURCE=.\LOGIC.h
# End Source File
# Begin Source File

SOURCE=.\LOGIC_ELSE.h
# End Source File
# Begin Source File

SOURCE=.\MagicItemTable.h
# End Source File
# Begin Source File

SOURCE=.\MagicItemTableSet.h
# End Source File
# Begin Source File

SOURCE=.\MAP.h
# End Source File
# Begin Source File

SOURCE=.\Mcommon.h
# End Source File
# Begin Source File

SOURCE=.\MechanicStoreSet.h
# End Source File
# Begin Source File

SOURCE=.\MemUser.h
# End Source File
# Begin Source File

SOURCE=.\MonsterPsiSet.h
# End Source File
# Begin Source File

SOURCE=.\MyDB.h
# End Source File
# Begin Source File

SOURCE=.\Npc.h
# End Source File
# Begin Source File

SOURCE=.\NpcChat.h
# End Source File
# Begin Source File

SOURCE=.\NpcChatSet.h
# End Source File
# Begin Source File

SOURCE=.\NpcItem.h
# End Source File
# Begin Source File

SOURCE=.\NpcItemSet.h
# End Source File
# Begin Source File

SOURCE=.\NpcPosSet.h
# End Source File
# Begin Source File

SOURCE=.\NpcSayEventSet.h
# End Source File
# Begin Source File

SOURCE=.\NpcSayTable.h
# End Source File
# Begin Source File

SOURCE=.\NpcTable.h
# End Source File
# Begin Source File

SOURCE=.\NpcTableSet.h
# End Source File
# Begin Source File

SOURCE=.\NpcThread.h
# End Source File
# Begin Source File

SOURCE=.\ov.h
# End Source File
# Begin Source File

SOURCE=.\Packet.h
# End Source File
# Begin Source File

SOURCE=.\PAMAExp.h
# End Source File
# Begin Source File

SOURCE=.\PAMAExpSet.h
# End Source File
# Begin Source File

SOURCE=.\Path.h
# End Source File
# Begin Source File

SOURCE=.\PathFind.h
# End Source File
# Begin Source File

SOURCE=.\PoolBase.h
# End Source File
# Begin Source File

SOURCE=.\PsiStoreSet.h
# End Source File
# Begin Source File

SOURCE=.\PsiTable.h
# End Source File
# Begin Source File

SOURCE=.\PsiTableSet.h
# End Source File
# Begin Source File

SOURCE=.\Recover.h
# End Source File
# Begin Source File

SOURCE=.\RecoverRate.h
# End Source File
# Begin Source File

SOURCE=.\RecoverRateSet.h
# End Source File
# Begin Source File

SOURCE=.\RecoverSet.h
# End Source File
# Begin Source File

SOURCE=.\Remodeling02TableSet.h
# End Source File
# Begin Source File

SOURCE=.\Remodeling03TableSet.h
# End Source File
# Begin Source File

SOURCE=.\RemodelingTable.h
# End Source File
# Begin Source File

SOURCE=.\RemodelingTableSet.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RoyalRumble.h
# End Source File
# Begin Source File

SOURCE=.\RoyalRumbleUser.h
# End Source File
# Begin Source File

SOURCE=.\SCDefine.h
# End Source File
# Begin Source File

SOURCE=.\Search.h
# End Source File
# Begin Source File

SOURCE=.\Server.h
# End Source File
# Begin Source File

SOURCE=.\ServerDlg.h
# End Source File
# Begin Source File

SOURCE=.\SERVERINFO.h
# End Source File
# Begin Source File

SOURCE=.\SharedMemory.h
# End Source File
# Begin Source File

SOURCE=.\SharedQueue.h
# End Source File
# Begin Source File

SOURCE=.\sinstance.h
# End Source File
# Begin Source File

SOURCE=.\SkillTable.h
# End Source File
# Begin Source File

SOURCE=.\SkillTableSet.h
# End Source File
# Begin Source File

SOURCE=.\SockDataList.h
# End Source File
# Begin Source File

SOURCE=.\SocketManager.h
# End Source File
# Begin Source File

SOURCE=.\SResourceArray.h
# End Source File
# Begin Source File

SOURCE=.\SSocket.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Store.h
# End Source File
# Begin Source File

SOURCE=.\StoreRepairSet.h
# End Source File
# Begin Source File

SOURCE=.\StoreSellSet.h
# End Source File
# Begin Source File

SOURCE=.\StoreSet.h
# End Source File
# Begin Source File

SOURCE=.\SummonTable.h
# End Source File
# Begin Source File

SOURCE=.\TableItem.h
# End Source File
# Begin Source File

SOURCE=.\ThrowItem.h
# End Source File
# Begin Source File

SOURCE=.\TownPotalTableSet.h
# End Source File
# Begin Source File

SOURCE=.\UNI_CHAR.h
# End Source File
# Begin Source File

SOURCE=.\UResourceArray.h
# End Source File
# Begin Source File

SOURCE=.\USER.h
# End Source File
# Begin Source File

SOURCE=.\UserLevelUpSet.h
# End Source File
# Begin Source File

SOURCE=.\UserLevelUpTable.h
# End Source File
# Begin Source File

SOURCE=.\UserManager.h
# End Source File
# Begin Source File

SOURCE=.\ValItemTable.h
# End Source File
# Begin Source File

SOURCE=.\ValItemTableSet.h
# End Source File
# Begin Source File

SOURCE=.\VirtualRoom.h
# End Source File
# Begin Source File

SOURCE=.\ZoneInfoSet.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Server.ico
# End Source File
# Begin Source File

SOURCE=.\res\Server.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\Help_yskang.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\IMPLODE.LIB
# End Source File
# End Target
# End Project
