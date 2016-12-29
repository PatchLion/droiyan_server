TEMPLATE=app
TARGET = DropEdit
DESTDIR=./bin


DEFINES += TOOL_CODE

QT += gui widgets sql

UI_DIR = ./temp/GeneratedFiles
RCC_DIR = ./temp/GeneratedFiles
MOC_DIR = ./temp/GeneratedFiles
OBJECTS_DIR = ./temp/$(Platform)/$(Configuration)
INCLUDEPATH += ./temp/GeneratedFiles

INCLUDEPATH +=.  \
			../../Server/Server/sources \
			../../../boost_1_62_0
						
LIBS += -L../../QxOrmLib/lib/$(Platform)/$(Configuration)/ -lQxOrm

win32{
    CONFIG -= flat
}


SOURCES += ./*.cpp 

FORMS +=./*.ui

HEADERS += ./*.h \
          ../../Server/Server/sources/NpcItem.h
