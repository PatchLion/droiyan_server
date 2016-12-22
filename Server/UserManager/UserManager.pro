TEMPLATE = app
TARGET = UserManager
DESTDIR = ../bin

include(../public.pri)

INCLUDEPATH += . ./sources ../Include
LIBS +=-lwsock32  -lodbc32
PRECOMPILED_HEADER = stdafx.h

RC_FILE = UserManager.rc
HEADERS += ./sources/Session.h \
    ./sources/UserManager.h \
    ./sources/UserManagerCom.h
SOURCES += ./sources/Msg.cpp \
    ./sources/Net.cpp \
    ./sources/ServiceMain.cpp \
    ./sources/SessDesc.cpp \
    ./sources/UserManager.cpp \
    ./sources/UserManagerCom.cpp
