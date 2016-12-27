TEMPLATE=app
TARGET = DropEdit
DESTDIR=./bin


DEFINES += TOOL_CODE

QT += gui widgets

UI_DIR = ./temp/GeneratedFiles
RCC_DIR = ./temp/GeneratedFiles
MOC_DIR = ./temp/GeneratedFiles
OBJECTS_DIR = ./temp/$(Platform)/$(Configuration)
INCLUDEPATH += ./temp/GeneratedFiles

INCLUDEPATH +=. \
                        ../../Server/Server/sources

win32{
    CONFIG -= flat
}


SOURCES += ./*.cpp \
    PercentItemDelegate.cpp \
    KeyMapManager.cpp

FORMS +=./*.ui

HEADERS += ./*.h \
          ../../Server/Server/sources/NpcItem.h \
    PercentItemDelegate.h \
    KeyMapManager.h
