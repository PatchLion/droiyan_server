TEMPLATE=app
include(../public.pri)
include(DBDataManager.pri)
#CONFIG += console
TARGET = DBDataManager
DESTDIR=./bin/$(Platform)/$(Configuration)/

QT += widgets sql

INCLUDEPATH +=  . ./src \
../PublicClasses
#./DB_Classes/drgame/*.cpp \
#./DB_Classes/droiyan/*.cpp \
SOURCES += main.cpp \
./src/*.cpp \
../PublicClasses/ThreeStatesTreeWidget.cpp

#./DB_Classes/drgame/*.h \
#./DB_Classes/droiyan/*.h \
HEADERS += ./src/*.h \
../PublicClasses/ThreeStatesTreeWidget.h

FORMS += ./src/*.ui
