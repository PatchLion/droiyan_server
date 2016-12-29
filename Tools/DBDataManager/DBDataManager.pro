TEMPLATE=app
include(../public.pri)
include(DBDataManager.pri)
CONFIG += console
TARGET = DBDataManager
DESTDIR=./bin/$(Platform)/$(Configuration)/

QT += widgets

INCLUDEPATH += ./src

SOURCES += main.cpp ./src/*.cpp
HEADERS += ./src/*.h
