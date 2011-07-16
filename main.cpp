#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec* local = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForTr(local);
    QTextCodec::setCodecForLocale(local);
    QTextCodec::setCodecForCStrings(local);
    MainWindow w;
    w.show();

    return a.exec();
}
