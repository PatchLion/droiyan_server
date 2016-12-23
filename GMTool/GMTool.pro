TEMPLATE=app
TARGET = GMTool
DESTDIR=./bin

QT += gui widgets sql

UI_DIR = ./temp/GeneratedFiles
RCC_DIR = ./temp/GeneratedFiles
MOC_DIR = ./temp/GeneratedFiles
OBJECTS_DIR = ./temp/$(Platform)/$(Configuration)
INCLUDEPATH += ./temp/GeneratedFiles

INCLUDEPATH += ./QxOrm/include ./sources
LIBS += -L./QxOrm/lib/$(Configuration) -lQxOrm

win32{
    CONFIG -= flat
}


SOURCES += ./main.cpp \
    sources/GMMainWindow.cpp

FORMS += \
    sources/GMMainWindow.ui

HEADERS += \
    sources/GMMainWindow.h
