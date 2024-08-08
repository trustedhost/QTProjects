#include "mainwindow.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create a QTextEdit widget and set it as the central widget
    QTextEdit* textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    // Create a menu bar
    QMenuBar* menubar = this->menuBar();

    // Create an Action
    QAction *newAct = makeAction("new.png", "&New", "Ctrl+N", "make new file", this, SLOT(newFile()));
    // QAction *newAct = new QAction(QIcon("new.png"), "&New", this);
    // newAct->setShortcut(tr("Ctrl+N"));
    // newAct->setStatusTip(tr("make new file"));
    // connect(newAct, SIGNAL(triggered()), SLOT(newFile()));

    // Add an Action to the menu bar
    QMenu *fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
}

MainWindow::~MainWindow() {}

QAction *MainWindow::makeAction(QString icon, QString text, QString shortCut, QString toolTip, QObject *recv, const char *slot)
{
    QAction *newAct = new QAction(QIcon(icon), text, this);
    newAct->setShortcut(shortCut);
    newAct->setStatusTip(toolTip);
    connect(newAct, SIGNAL(triggered()), recv, slot);
    return newAct;
}

void MainWindow::newFile()
{
    qDebug() << "make new File";
}
