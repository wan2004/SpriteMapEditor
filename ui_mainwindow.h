/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun May 15 15:47:57 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *newAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *mapbaseAction;
    QAction *mapitemAction;
    QAction *openAction;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *lineEdit_name;
    QLabel *label_2;
    QLineEdit *lineEdit_type;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_bgcolor;
    QPushButton *pushButton;
    QLabel *label_color;
    QSpinBox *width_spinBox;
    QSpinBox *height_spinBox;
    QGraphicsView *items_GraphicsView;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 720);
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        newAction = new QAction(MainWindow);
        newAction->setObjectName(QString::fromUtf8("newAction"));
        newAction->setFont(font);
        saveAction = new QAction(MainWindow);
        saveAction->setObjectName(QString::fromUtf8("saveAction"));
        saveAction->setFont(font);
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        exitAction->setFont(font);
        mapbaseAction = new QAction(MainWindow);
        mapbaseAction->setObjectName(QString::fromUtf8("mapbaseAction"));
        mapbaseAction->setCheckable(true);
        mapbaseAction->setChecked(true);
        mapbaseAction->setFont(font);
        mapitemAction = new QAction(MainWindow);
        mapitemAction->setObjectName(QString::fromUtf8("mapitemAction"));
        mapitemAction->setCheckable(true);
        mapitemAction->setEnabled(true);
        mapitemAction->setFont(font);
        openAction = new QAction(MainWindow);
        openAction->setObjectName(QString::fromUtf8("openAction"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 800, 651));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(810, 10, 181, 641));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 51, 16));
        lineEdit_name = new QLineEdit(groupBox);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(10, 40, 161, 21));
        lineEdit_name->setMaxLength(255);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 80, 51, 16));
        lineEdit_type = new QLineEdit(groupBox);
        lineEdit_type->setObjectName(QString::fromUtf8("lineEdit_type"));
        lineEdit_type->setGeometry(QRect(10, 100, 161, 21));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 140, 61, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 200, 54, 20));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 260, 54, 16));
        lineEdit_bgcolor = new QLineEdit(groupBox);
        lineEdit_bgcolor->setObjectName(QString::fromUtf8("lineEdit_bgcolor"));
        lineEdit_bgcolor->setGeometry(QRect(10, 280, 121, 20));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(140, 280, 31, 21));
        label_color = new QLabel(groupBox);
        label_color->setObjectName(QString::fromUtf8("label_color"));
        label_color->setGeometry(QRect(70, 260, 101, 16));
        label_color->setStyleSheet(QString::fromUtf8("QLabel{background:#000000}"));
        width_spinBox = new QSpinBox(groupBox);
        width_spinBox->setObjectName(QString::fromUtf8("width_spinBox"));
        width_spinBox->setGeometry(QRect(10, 160, 81, 22));
        height_spinBox = new QSpinBox(groupBox);
        height_spinBox->setObjectName(QString::fromUtf8("height_spinBox"));
        height_spinBox->setGeometry(QRect(10, 220, 81, 22));
        items_GraphicsView = new QGraphicsView(groupBox);
        items_GraphicsView->setObjectName(QString::fromUtf8("items_GraphicsView"));
        items_GraphicsView->setGeometry(QRect(10, 320, 161, 311));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 20));
        menuBar->setFont(font);
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setFont(font);
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(newAction);
        menu->addAction(openAction);
        menu->addAction(saveAction);
        menu->addSeparator();
        menu->addAction(exitAction);
        menu_2->addAction(mapbaseAction);
        menu_2->addAction(mapitemAction);
        menu_2->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\234\260\345\233\276\347\274\226\350\276\221\345\231\250", 0, QApplication::UnicodeUTF8));
        newAction->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\234\260\345\233\276", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        newAction->setToolTip(QApplication::translate("MainWindow", "\346\226\260\345\273\272\344\270\200\344\270\252\345\234\260\345\233\276\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        newAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        saveAction->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\234\260\345\233\276", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveAction->setToolTip(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\234\260\345\233\276", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        exitAction->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\347\250\213\345\272\217", 0, QApplication::UnicodeUTF8));
        exitAction->setShortcut(QApplication::translate("MainWindow", "Alt+Q", 0, QApplication::UnicodeUTF8));
        mapbaseAction->setText(QApplication::translate("MainWindow", "\346\231\256\351\200\232\350\264\264\345\233\276", 0, QApplication::UnicodeUTF8));
        mapitemAction->setText(QApplication::translate("MainWindow", "\347\211\251\345\223\201\350\264\264\345\233\276", 0, QApplication::UnicodeUTF8));
        openAction->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\345\234\260\345\233\276", 0, QApplication::UnicodeUTF8));
        openAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        groupBox->setWhatsThis(QApplication::translate("MainWindow", "done", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        groupBox->setTitle(QApplication::translate("MainWindow", "\345\270\270\350\247\204\345\261\236\346\200\247", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\345\234\260\345\233\276\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\345\234\260\345\233\276\347\247\215\347\261\273", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "\345\256\275\345\272\246", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "\351\253\230\345\272\246", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "\350\203\214\346\231\257\351\242\234\350\211\262", 0, QApplication::UnicodeUTF8));
        lineEdit_bgcolor->setInputMask(QApplication::translate("MainWindow", "HHHHHH; ", 0, QApplication::UnicodeUTF8));
        lineEdit_bgcolor->setText(QApplication::translate("MainWindow", "000000", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_color->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221(&E)", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
