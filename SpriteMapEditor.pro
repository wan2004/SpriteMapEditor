#-------------------------------------------------
#
# Project created by QtCreator 2011-02-08T12:31:12
#
#-------------------------------------------------

QT       += core gui
LIBS     += -L ./ -lgpscene

TARGET = SpriteMapEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h\
            mapinfo.h\
            mapbase.h\
            mapmanager.h\
            sprite.h \
    mapitem.h


FORMS    += mainwindow.ui
