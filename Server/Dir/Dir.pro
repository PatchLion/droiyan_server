TEMPLATE = vcapp
TARGET = Dir
DESTDIR = ../bin
CONFIG -= flat
DEFINES += _AFXDLL
DEFINES -= UNICODE
INCLUDEPATH += . ./sources ../temp/GeneratedFiles

LIBS +=  -lwsock32 -lodbc32

QT-= gui widgets

PRECOMPILED_HEADER = stdafx.h

UI_DIR = ../temp/GeneratedFiles
RCC_DIR = ../temp/GeneratedFiles
MOC_DIR = ../temp/GeneratedFiles
OBJECTS_DIR = ../temp/$(Platform)/$(Configuration)


HEADERS += ./sources/*.h

SOURCES += ./sources/*.cpp

RC_ICONS = icon.ico
