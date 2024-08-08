#include "mainwindow.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QToolBar>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QtTypes>
#include <QStatusBar>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create a QTextEdit widget and set it as the central widget
    QTextEdit* textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    // Create an Action
    QAction *newAct = makeAction(":icons/new.png", tr("&New"), QKeySequence::New, tr("make new file"), this, SLOT(newFile()));
    QAction *quitAct = makeAction(":icons/quit.png", tr("&Quit"), tr("Ctrl+Q"), tr("Quit this program"), [](){
        qDebug() << "let's see";
        qApp->quit();});



    // Create a ToolBar
    QToolBar *fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    // Add action to the ToolBar
    fileToolBar->addAction(newAct);
    // Add seperator to the Toolbar
    fileToolBar->addSeparator();
    // Add action to the ToolBar
    fileToolBar->addAction(quitAct);


    //add StatusBar
    QStatusBar *statusbar = this->statusBar();
    QLabel *statusLabel = new QLabel(tr("Text Editor"), statusbar);
    statusLabel->setObjectName("StatusLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started", 1500);




    //add widget to the toolbar
    QFontComboBox *fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), textedit, SLOT(setCurrentFont(QFont)));
    QDoubleSpinBox *sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)), textedit, SLOT(setFontPointSize(qreal)));

    addToolBarBreak();

    QToolBar *formatToolbar = addToolBar("&Format");
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);


    // Create a menu bar
    QMenuBar* menubar = this->menuBar();

    // Add Actions to the menu bar
    QMenu *fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(quitAct);

    // Add the ToolBar to the MenuBar
    QMenu *windowMenu = menubar->addMenu("&Window");
    QMenu *toolbarMenu = windowMenu->addMenu("&Toolbar");
    toolbarMenu->addAction(fileToolBar->toggleViewAction());

    QMenu *editMenu = menubar->addMenu("&Edit");
    editMenu->addAction(makeAction(":icons/undo.png", tr("Undo"), QKeySequence::Undo, tr("undo"), [textedit](){textedit->undo();} ));
    editMenu->addAction(makeAction(":icons/undo.png", tr("Redo"), QKeySequence::Redo, tr("redo"), [textedit](){textedit->redo();} ));
    editMenu->addAction(makeAction(":icons/undo.png", tr("Copy"),QKeySequence::Copy, tr("copy"), [textedit](){textedit->copy();} ));
    editMenu->addAction(makeAction(":icons/undo.png", tr("Cut"), QKeySequence::Cut, tr("cut"), [textedit](){textedit->cut();} ));
    editMenu->addAction(makeAction(":icons/undo.png", tr("Paste"), QKeySequence::Paste, tr("paste"), [textedit](){textedit->paste();} ));
    editMenu->addAction(makeAction(":icons/undo.png", tr("Zoom in"),QKeySequence::ZoomIn, tr("zoom in"), [textedit](){textedit->zoomIn(1);} ));
    editMenu->addAction(makeAction(":icons/undo.png", tr("Zoom out"),QKeySequence::ZoomOut, tr("zoom out"), [textedit](){textedit->zoomOut(1);} ));



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
    newAct->setShortcut(shortCut);
    newAct->setStatusTip(toolTip);
    connect(newAct, &QAction::triggered, lambda);
    return newAct;

}

void MainWindow::newFile()
{
    qDebug() << "make new File";
}
