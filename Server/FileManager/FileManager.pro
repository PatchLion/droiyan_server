TEMPLATE = vcapp
TARGET = FileManager
DESTDIR = ../bin
CONFIG -= flat
DEFINES += _AFXDLL
DEFINES -= UNICODE
INCLUDEPATH += . ./sources ../temp/GeneratedFiles ../Include

LIBS += -lwsock32 -lodbc32 -lAdvapi32

PRECOMPILED_HEADER = stdafx.h

UI_DIR = ../temp/GeneratedFiles
RCC_DIR = ../temp/GeneratedFiles
MOC_DIR = ../temp/GeneratedFiles
OBJECTS_DIR = ../temp/$(Platform)/$(Configuration)

HEADERS += ./sources/*.h
HEADERS += ./sources/*.h

SOURCES += ./sources/*.cpp

RC_ICONS = icon.ico
