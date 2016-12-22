TEMPLATE = lib
CONFIG += staticlib

include(../public.pri)

TARGET = ServerComp
DESTDIR = ./lib/$(Platform)/$(Configuration)

PRECOMPILED_HEADER = stdafx.h

INCLUDEPATH += ./sources .

HEADERS += ./sources/IOCPBASE.h \
           ./sources/CBSocket.h \
           ./sources/IOCPSocket.h \
           ./sources/PoolBase.h

SOURCES += ./sources/IOCPBASE.cpp \
           ./sources/CBSocket.cpp \
           ./sources/IOCPSocket.cpp \
           ./sources/PoolBase.cpp

