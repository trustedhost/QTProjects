#include "mainwindow.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create a QTextEdit widget and set it as the central widget
    QTextEdit* textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    // Create a menu bar
    QMenuBar* menubar = this->menuBar();

    // Create an Action
    // QAction *newAct = makeAction("new.png", "&New", "Ctrl+N", "make new file", this, SLOT(newFile()));
    QAction *newAct = makeAction("new.png", tr("&New"), QKeySequence::New, tr("make new file"), this, SLOT(newFile()));
    // QAction *newAct = new QAction(QIcon("new.png"), "&New", this);
    // newAct->setShortcut(tr("Ctrl+N"));
    // newAct->setStatusTip(tr("make new file"));
    // connect(newAct, SIGNAL(triggered()), SLOT(newFile()));

    // QAction *quitAct = makeAction("quit.png", tr("&Quit"), tr("Ctrl+Q"), tr("Quit this program"), qApp, SLOT(quit()));
    QAction *quitAct = makeAction("quit.png", tr("&Quit"), tr("Ctrl+Q"), tr("Quit this program"), [](){
        qDebug() << "let's see";
        qApp->quit();});

    // Add an Action to the menu bar
    QMenu *fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(quitAct);
}

MainWindow::~MainWindow() {}

template <typename T>
QAction *MainWindow::makeAction(QString icon, QString text, T shortCut, QString toolTip, QObject *recv, const char *slot)
{
    QAction *newAct = new QAction(text, this);
    if(icon.length()) newAct->setIcon(QIcon(icon));
    newAct->setShortcut(shortCut);
    newAct->setStatusTip(toolTip);
    connect(newAct, SIGNAL(triggered()), recv, slot);
    return newAct;
}

template <>
QAction *MainWindow::makeAction(QString icon, QString text, const char* shortCut, QString toolTip, QObject *recv, const char *slot)
{
    QAction *newAct = new QAction(text, this);
    if(icon.length()) newAct->setIcon(QIcon(icon));
    newAct->setShortcut(QString(shortCut));
    newAct->setStatusTip(toolTip);
    connect(newAct, SIGNAL(triggered()), recv, slot);
    return newAct;
}



template<typename T, typename Functor>
QAction *MainWindow::makeAction(QString icon, QString text, T shortCut, QString toolTip, Functor lambda)
{
    QAction *newAct = new QAction(text, this);
    if(icon.length()) newAct->setIcon(QIcon(icon));
    newAct->setShortcut(QString(shortCut));
    newAct->setStatusTip(toolTip);
    connect(newAct, &QAction::triggered, lambda);
    return newAct;

}

void MainWindow::newFile()
{
    qDebug() << "make new File";
}
