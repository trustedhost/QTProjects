#include "widget.h"
#include <QButtonGroup>
#include <QCheckBox>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(140, 140);

    label = new QLabel("hello", this);

    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(idClicked(int)), SLOT(selectButton(int)));

    label->move(10, 10);
    label->resize(30, 30);
    i = 7;
    int k = 7;
    connect(buttonGroup, &QButtonGroup::idClicked, [=](int id) mutable {
        label->setText(QString::number(id + 1));
        i++;
        k++;
        qDebug() << i << '\n';
        qDebug() << k << '\n';

    });
    for (int i = 0; i < 4; ++i) {
        QString str = QString("Checkbox%1").arg(i + 1);
        checkBox[i] = new QCheckBox(str, this);
        checkBox[i]->move(10, 50 + 20 * i);
        buttonGroup->addButton(checkBox[i], i);
    }
}

Widget::~Widget() {}

void Widget::selectButton(int id)
{
    QButtonGroup* buttonGroup = qobject_cast<QButtonGroup*>(sender());
    QCheckBox* button = qobject_cast<QCheckBox*>(buttonGroup->button(id));
    qDebug("CheckBox%d is selected(%s)", id+1, (button->isChecked() ? "On" : "Off"));
    qDebug() << i ;
}
