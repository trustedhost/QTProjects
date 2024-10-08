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
#include <QMdiArea>
#include <QMdiSubWindow>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create a QTextEdit widget and set it as the central widget
    mdiArea = new QMdiArea(this);
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(setFontWidget()));
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(connectWindow(QMdiSubWindow*)));
    setCentralWidget(mdiArea);
#if 0 // edit 메뉴를 수정한 후 0으로 변경 (test 기법임. 0과 1 을 바꿔가면서 테스팅 할 수 있는거임. )
    QTextEdit *textedit = new QTextEdit(this);
    mdiArea->addSubWindow(textedit);
#else
    QTextEdit *textedit = newFile();
#endif

    // Create an Action
    QAction *newAct = makeAction(":icons/new.png", tr("&New"), QKeySequence::New, tr("make new file"), this, SLOT(newFile()));
    QAction *quitAct = makeAction(":icons/quit.png", tr("&Quit"), tr("Ctrl+Q"), tr("Quit this program"), [](){
        qDebug() << "let's see";
        qApp->quit();});

    //editor 창에 종속. 각각 event 에 해당하는 slot 을 구현하는 방식으로 구현.
    QAction *undoAct = makeAction(":icons/undo.png", tr("Undo"), QKeySequence::Undo, tr("undo"), this, SLOT(undo()));
    QAction *redoAct = makeAction(":icons/redo.png", tr("Redo"), QKeySequence::Redo, tr("redo"), this, SLOT(redo()));
    QAction *copyAct = makeAction(":icons/copy.png", tr("Copy"),QKeySequence::Copy, tr("copy"), this, SLOT(copy()));
    QAction *cutAct = makeAction(":icons/cut.png", tr("Cut"), QKeySequence::Cut, tr("cut"), this, SLOT(cut()));
    QAction *pasteAct = makeAction(":icons/paste.png", tr("Paste"), QKeySequence::Paste, tr("paste"), this, SLOT(paste()));
    QAction *zoomInAct = makeAction(":icons/zoomin.png", tr("Zoom in"),QKeySequence::ZoomIn, tr("zoom in"), this, SLOT(zoomIn()));
    QAction *zoomOutAct = makeAction(":icons/zoomout.png", tr("Zoom out"),QKeySequence::ZoomOut, tr("zoom out"), this, SLOT(zoomOut()));

    actions.append(undoAct);
    actions.append(redoAct);
    actions.append(copyAct);
    actions.append(cutAct);
    actions.append(pasteAct);
    actions.append(zoomInAct);
    actions.append(zoomOutAct);


    //editor 창에 종속. 하나의 slot 에서 event 를 처리하는 방식으로 구현.
    QAction *alignCenterAct = new QAction("&Center", this);
    connect(alignCenterAct, SIGNAL(triggered()), SLOT(alignText()));
    QAction *alignLeftAct = new QAction("&Left", this);
    connect(alignLeftAct, SIGNAL(triggered()), SLOT(alignText()));
    QAction *alignRightAct = new QAction("&Right", this);
    connect(alignRightAct, SIGNAL(triggered()), SLOT(alignText()));
    QAction *alignJustifyAct = new QAction("&Justify", this);
    connect(alignJustifyAct, SIGNAL(triggered()), SLOT(alignText()));

    //mdi window 에 종속.
    QAction *activateNextSubWindowAct = new QAction("&NextWindow", this);
    connect(activateNextSubWindowAct, &QAction::triggered, mdiArea, &QMdiArea::activateNextSubWindow);
    QAction *activatePreviousSubWindowAct = new QAction("&PreviousWindow", this);
    connect(activatePreviousSubWindowAct, &QAction::triggered, mdiArea, &QMdiArea::activatePreviousSubWindow);
    QAction *cascadeSubWindowsAct = new QAction("&CascadeSubWindows", this);
    connect(cascadeSubWindowsAct, &QAction::triggered, mdiArea, &QMdiArea::cascadeSubWindows);
    QAction *closeActiveSubWindowAct = new QAction("&CloseActiveSubWindows", this);
    connect(closeActiveSubWindowAct, &QAction::triggered, mdiArea, &QMdiArea::closeActiveSubWindow);
    QAction *closeAllWindowsAct = new QAction("&CloseAllSubWindows", this);
    connect(closeAllWindowsAct, &QAction::triggered, mdiArea, &QMdiArea::closeAllSubWindows);
    QAction *tileSubWindowsAct = new QAction("&TileSubWindows", this);
    connect(tileSubWindowsAct, &QAction::triggered, mdiArea, &QMdiArea::tileSubWindows);


    // Create a ToolBar
    QToolBar *fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    // Add action to the ToolBar
    fileToolBar->addAction(newAct);
    // Add seperator to the Toolbar
    fileToolBar->addSeparator();
    // Add action to the ToolBar
    fileToolBar->addAction(quitAct);
    fileToolBar->addSeparator();



    //add StatusBar
    QStatusBar *statusbar = this->statusBar();
    QLabel *statusLabel = new QLabel(tr("Text Editor"), statusbar);
    statusLabel->setObjectName("StatusLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started", 1500);


    //add widget to the toolbar
    fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), SLOT(setTextFont(QFont)));
    sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(qreal)), SLOT(setTextSize(qreal)));

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
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(zoomInAct);
    editMenu->addAction(zoomOutAct);
    editMenu->addSeparator();

    QMenu *alignMenu = editMenu->addMenu("&Align");
    alignMenu->addAction(alignCenterAct);
    alignMenu->addAction(alignLeftAct);
    alignMenu->addAction(alignRightAct);
    alignMenu->addAction(alignJustifyAct);


    QMenu *mdiLocateMenu = editMenu->addMenu("&MdiLocate");
    mdiLocateMenu->addAction(activateNextSubWindowAct);
    mdiLocateMenu->addAction(activatePreviousSubWindowAct);
    mdiLocateMenu->addAction(cascadeSubWindowsAct);
    mdiLocateMenu->addAction(closeActiveSubWindowAct);
    mdiLocateMenu->addAction(closeAllWindowsAct);
    mdiLocateMenu->addAction(tileSubWindowsAct);

}

MainWindow::~MainWindow() {}

QTextEdit *MainWindow::newFile()
{
    qDebug() << "Make new file";
    QTextEdit *textedit = new QTextEdit;
    mdiArea->addSubWindow(textedit);
    textedit->show();
    return textedit;
}

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

void MainWindow::alignText()
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if (subWindow != nullptr) {
        QTextEdit *textedit = qobject_cast<QTextEdit*>(subWindow->widget());
        QAction *action = qobject_cast<QAction*>(sender());
        if(action->text().contains("Left", Qt::CaseInsensitive)) {
        textedit->setAlignment(Qt::AlignLeft);
        } else if (action->text().contains("Center", Qt::CaseInsensitive)) {
        textedit->setAlignment(Qt::AlignCenter);
        } else if (action->text().contains("Right", Qt::CaseInsensitive)) {
        textedit->setAlignment(Qt::AlignRight);
        } else if (action->text().contains("Justify", Qt::CaseInsensitive)) {
        textedit->setAlignment(Qt::AlignJustify);
        }
    }
}

void MainWindow::setTextFont(QFont font)
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if (subWindow != nullptr) {
        QTextEdit *textedit = qobject_cast<QTextEdit*>(subWindow->widget());
        textedit->setCurrentFont(font);
    }
}

void MainWindow::setTextSize(qreal size)
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if (subWindow != nullptr) {
        QTextEdit *textedit = qobject_cast<QTextEdit*>(subWindow->widget());
        QFont font = textedit->currentFont();
        font.setPointSizeF(size);
        textedit->setCurrentFont(font);
    }
}

void MainWindow::setFontWidget()
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if (subWindow != nullptr) {
        QTextEdit *textedit = qobject_cast<QTextEdit*>(subWindow->widget());
        QFont font = textedit->currentFont();
        fontComboBox->setCurrentFont(font);
        sizeSpinBox->setValue(font.pointSizeF());
    }
}

void MainWindow::undo()
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if (subWindow != nullptr) {
        QTextEdit* textedit = qobject_cast<QTextEdit*>(subWindow->widget());
        textedit->undo();
    }
}

void MainWindow::redo()
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if (subWindow != nullptr) {
        QTextEdit* textedit = qobject_cast<QTextEdit*>(subWindow->widget());
        textedit->redo();
    }
}

void MainWindow::copy()
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if (subWindow != nullptr) {
        QTextEdit* textedit = qobject_cast<QTextEdit*>(subWindow->widget());
        textedit->copy();
    }
}

void MainWindow::cut()
{

    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if (subWindow != nullptr) {
        QTextEdit* textedit = qobject_cast<QTextEdit*>(subWindow->widget());
        textedit->cut();
    }
}

void MainWindow::paste()
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if (subWindow != nullptr) {
        QTextEdit* textedit = qobject_cast<QTextEdit*>(subWindow->widget());
        textedit->paste();
    }

}

void MainWindow::zoomIn()
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if (subWindow != nullptr) {
        QTextEdit* textedit = qobject_cast<QTextEdit*>(subWindow->widget());
        textedit->zoomIn();
    }

}

void MainWindow::zoomOut()
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if (subWindow != nullptr) {
        QTextEdit* textedit = qobject_cast<QTextEdit*>(subWindow->widget());
        textedit->zoomOut();
    }

}

void MainWindow::connectWindow(QMdiSubWindow * window)
{
    // qDebug() << actions;
    if (window == nullptr) {
        prevTextEdit = nullptr;
    } else {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(window->widget());

        if (prevTextEdit != nullptr) {
            for(QAction* action : actions) {
                action->disconnect(prevTextEdit);
            }
        }
        prevTextEdit = textEdit;
        const char* methods[7] = {
            SLOT(undo()),
            SLOT(redo()),
            SLOT(copy()),
            SLOT(cut()),
            SLOT(paste()),
            SLOT(zoomIn()),
            SLOT(zoomOut())
        };
        int cnt = 0;
        Q_FOREACH(QAction* action, actions) {
            connect(action, SIGNAL(triggered()), textEdit, methods[cnt++]);
        }
    }
}
