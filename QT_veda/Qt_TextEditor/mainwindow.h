#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QAction *makeAction(QString icon, QString text, QString shortCut , \
                        QString toolTip, QObject* recv, const char* slot);

public slots:
    void newFile();
};
#endif // MAINWINDOW_H
