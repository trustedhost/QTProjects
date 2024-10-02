#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QString>

class Thread;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Thread* thread;

public slots:
    void threadControl(bool flag);
    void setText(QString);
};
#endif // WIDGET_H
