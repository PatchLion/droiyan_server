TEMPLATE = app
TARGET = Dir
DESTDIR = ../bin
include(../public.pri)

INCLUDEPATH += . ./sources

LIBS +=  -lwsock32 -lodbc32

QT-= gui widgets

PRECOMPILED_HEADER = stdafx.h

HEADERS += ./sources/*.h
SOURCES += ./sources/*.cpp

RC_ICONS = icon.ico
