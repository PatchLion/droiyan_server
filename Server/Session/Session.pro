TEMPLATE = app
TARGET = Session
DESTDIR = ../bin

include(../public.pri)

DEFINES += _INTERNET_USAGE
INCLUDEPATH += . ./sources ./lib/include ./protocols

PRECOMPILED_HEADER = stdafx.h

LIBS += -L./lib/ServerComp/$(Configuration) \
        -lwsock32 -lws2_32 -lodbc32 -lServerComp

RC_FILE = Session.rc
HEADERS +=./sources/BankSerial.h \
    ./sources/CP_IP_MASKTable.h \
    ./sources/Database.h \
    ./sources/Define.h \
    ./sources/Iocp.h \
    ./sources/LogSet.h \
    ./sources/mcommon.h \
    ./sources/Recordset.h \
    ./Resource.h \
    ./sources/SerialKey.h \
    ./sources/SerialSet.h \
    ./sources/Session.h \
    ./sources/SessionCom.h \
    ./sources/SocketManager.h \
    ./sources/SResourceArray.h \
    ./sources/UResourceArray.h \
    ./sources/UserManager.h \
    ./sources/UserServerManager.h \
    ./sources/UserSet.h \
    ./sources/USResourceArray.h
SOURCES += ./sources/BankSerial.cpp \
    ./sources/ConsoleManager.cpp \
    ./sources/CP_IP_MASKTable.cpp \
    ./sources/Database.cpp \
    ./sources/LogSet.cpp \
    ./sources/Msg.cpp \
    ./sources/Recordset.cpp \
    ./sources/SerialKey.cpp \
    ./sources/SerialSet.cpp \
    ./sources/ServiceMain.cpp \
    ./sources/SessDesc.cpp \
    ./sources/Session.cpp \
    ./sources/SessionCom.cpp \
    ./sources/SocketManager.cpp \
    ./sources/SResourceArray.cpp \
    ./sources/UResourceArray.cpp \
    ./sources/UserManager.cpp \
    ./sources/UserServerManager.cpp \
    ./sources/UserSet.cpp \
    ./sources/USResourceArray.cpp
