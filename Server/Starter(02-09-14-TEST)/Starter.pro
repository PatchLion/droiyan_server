TEMPLATE = app
TARGET = Starter
DESTDIR = ../bin

include(../public.pri)

INCLUDEPATH += . ../Include
LIBS += -lwsock32

PRECOMPILED_HEADER = stdafx.h

RC_FILE = Starter.rc

HEADERS += ./Resource.h \
    ./sources/Service.h \
    ./sources/Starter.h \
    ./sources/StarterCom.h

SOURCES += ./sources/Msg.cpp \
    ./sources/Net.cpp \
    ./sources/Service.cpp \
    ./sources/ServiceMain.cpp \
    ./sources/SessDesc.cpp \
    ./sources/Starter.cpp \
    ./sources/StarterCom.cpp
