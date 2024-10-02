#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QCheckBox;
class QButtonGroup;
class QLabel;

class Widget : public QWidget
{
    Q_OBJECT

private:
    QCheckBox* checkBox[4];
    QButtonGroup* buttonGroup;
    QLabel* label;
    int i;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void selectButton(int id);
};
#endif // WIDGET_H
