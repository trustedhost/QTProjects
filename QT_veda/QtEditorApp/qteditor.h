#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>
#include <QHash>

class QAction;
class QMdiArea;
class QTextEdit;
class QFontComboBox;
class QDoubleSpinBox;

class QtEditor : public QMainWindow
{
    Q_OBJECT

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

private:
    template <typename T>
    QAction *makeAction(QString icon, QString text, T shortCut, \
                        QString toolTip, QObject* recv, const char* slot);
    template <>
    QAction *makeAction(QString icon, QString text, const char* shortCut, \
                        QString toolTip, QObject* recv, const char* slot);
    template <typename T, typename Functor>
    QAction *makeAction(QString icon, QString text, T shortCut,
                        QString toolTip, Functor lambda);

    QMdiArea *mdiArea;
    QFontComboBox *fontComboBox;
    QDoubleSpinBox *sizeSpinBox;
    QMenu *windowMenu;
    QHash<QAction*, QWidget*> windowHash;

private slots:
    QTextEdit* newFile( );
    void openFile( );
    void saveFile( );
    void saveasFile( );
    void printFile( );

    /* Edit Menu */
    void undo();
    void redo();
    void copy();
    void cut();
    void paste();
    void zoomIn();
    void zoomOut();

    void setFontWidget( );
    void setTextFont(QFont font);
    void setTextSize(qreal size);

    /* format */
    void setColor();
    void setFont();
    void alignText( );

    /* help */
    void about();

    void selectWindow();
};
#endif // QTEDITOR_H
