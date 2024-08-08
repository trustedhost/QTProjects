#include "widget.h"

#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent), m_isFirst(true)
{
    m_label = new QLabel("0", this);
    m_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_label->setFrameShape(QFrame::Box);
    m_label->setMaximumHeight(30);


    //버튼에 표시될 문자열
    const char ButtonChar[16][2] = {
        "7", "8", "9", "/",
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };
    QGridLayout *gridLayout = new QGridLayout();
    buttonGroup = new QButtonGroup(this);
    connect(buttonGroup, SIGNAL(idClicked(int)), SLOT(click(int)));


    for (int y = 0; y < WIDTH; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int n = x + y * WIDTH;
            buttonGroup->addButton(new QPushButton(ButtonChar[n], this), n);
            gridLayout->addWidget(buttonGroup->button(n), n/WIDTH, n%WIDTH);
        }
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_label);
    mainLayout->addLayout(gridLayout);

    setLayout(mainLayout);
}

Widget::~Widget()
{
    delete m_label;
    qDeleteAll(buttonGroup->buttons());
}

void Widget::click(int id) {
    QPushButton* button = qobject_cast<QPushButton*>(buttonGroup->button(id));
    QString bStr;
    if (button != nullptr) bStr = button->text();
    switch(id) {
    case 0: case 1: case 2: case 4: case 5: case 6: case 8: case 9: case 10: case 12:
        if (m_label != nullptr) {
            QString lStr = m_label->text();
            m_label->setText((lStr == "0" || m_isFirst) ? bStr : lStr + bStr);
            m_isFirst = false;
        }
        break;
    case 3: case 7: case 11: case 15:
        if (m_label != nullptr) {
            m_num1 = m_label->text();
        }
        m_op = bStr;
        m_isFirst = true;
        break;
    case 13:
        if (m_label != nullptr) {
            m_label->setText("0");
            m_isFirst = true;
        }
        break;
    case 14:
        if (m_label != nullptr && !m_num1.isEmpty() && !m_op.isEmpty()) {
            double num1 = m_num1.toDouble();
            double num2 = m_label->text().toDouble();
            double result = 0.0;
            if (m_op == "+") result = num1 + num2;
            else if (m_op == "-") result = num1 - num2;
            else if (m_op == "x") result = num1 * num2;
            else if (m_op == "/") result = num2 != 0 ? num1 / num2 : 0.0;
            m_label->setText(QString::number(result));
        }
        m_isFirst = true;
        break;
    }
}

