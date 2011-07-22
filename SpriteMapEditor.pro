
QT       += core gui
LIBS     += -L ./ -lgpscene

TARGET = SpriteMapEditor
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    inmapitemdialog.cpp

HEADERS  += mainwindow.h\
            mapinfo.h\
            mapbase.h\
            mapmanager.h\
            sprite.h \
    mapitem.h \
    inmapitemdialog.h

FORMS    += mainwindow.ui \
    inmapitemdialog.ui
