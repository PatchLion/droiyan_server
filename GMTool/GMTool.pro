TEMPLATE=app
TARGET = GMTool
DESTDIR=./bin

QT += gui widgets sql

UI_DIR = ./temp/GeneratedFiles
RCC_DIR = ./temp/GeneratedFiles
MOC_DIR = ./temp/GeneratedFiles
OBJECTS_DIR = ./temp/$(Platform)/$(Configuration)
INCLUDEPATH += ./temp/GeneratedFiles

INCLUDEPATH += \
# ./QxOrm/include/include \
                             ./sources \
                            ./sources/ItemsManager \
                            ./sources/ItemsManager/orm #\
                            #H:\git_repositories\boost_1_62_0

#LIBS += -L./QxOrm/lib/$(Configuration) -lQxOrm

win32{
    CONFIG -= flat
}


SOURCES += ./*.cpp \
    sources/*.cpp \
    sources/ItemsManager/*.cpp #\
    #sources/ItemsManager/orm/*.cpp

FORMS += \
    sources/*.ui

HEADERS += \
    sources/*.h \
    sources/ItemsManager/*.h#\
    #sources/ItemsManager/orm/*.h
