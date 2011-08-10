
QT       += core gui
LIBS     += -L ./ -lgpscene

TARGET = SpriteMapEditor
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    inmapitemdialog.cpp \
    dragreceiveritem.cpp

HEADERS  += mainwindow.h\
            mapinfo.h\
            mapbase.h\
            mapmanager.h\
            sprite.h \
    mapitem.h \
    inmapitemdialog.h \
    dragreceiveritem.h

FORMS    += mainwindow.ui \
    inmapitemdialog.ui
