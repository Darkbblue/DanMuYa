#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected slots:
    void RcvMsg();

private:
    Ui::Widget *ui;
    QTcpSocket * sock;
    QByteArray buffer;
};

#endif // WIDGET_H
