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
    template <typename T>
    QAction *makeAction(QString icon, QString text, T shortCut , \
                        QString toolTip, QObject* recv, const char* slot);

    template <typename T, typename Functor>
    QAction *makeAction(QString icon, QString text, T shortCut, \
                        QString toolTip, Functor lambda);

public slots:
    void newFile();
};
#endif // MAINWINDOW_H
