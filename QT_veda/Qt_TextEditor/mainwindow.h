#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QTextEdit;
class QMdiArea;
class QFontComboBox;
class QDoubleSpinBox;
class QMdiSubWindow;


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
    // QTextEdit* textedit;
    QMdiArea* mdiArea;
    QFontComboBox* fontComboBox;
    QDoubleSpinBox* sizeSpinBox;
    QList<QAction*> actions;
    QTextEdit* prevTextEdit = nullptr;

public slots:
    QTextEdit *newFile();
    void alignText();
    void setTextFont(QFont font);
    void setTextSize(qreal size);
    void setFontWidget();
    void undo();
    void redo();
    void copy();
    void cut();
    void paste();
    void zoomIn();
    void zoomOut();
    void connectWindow(QMdiSubWindow*);
};
#endif // MAINWINDOW_H
