#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include "startwindow.h"
#include "configwindow.h"

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
    void StartConnection(int port); // 开始连接

    void RcvMsg(); // 接收信息

private slots:
    void SetAlpha(QString str); // 设置透明度
    void SetFont(QString str); // 设置字号

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket * sock; // 通信
    QByteArray buffer; // 通信数据缓存
    StartWindow * startWindow; // 初始化窗口
    ConfigWindow * configWindow; // 设置窗口

    double alpha = 0.85; // 透明度
    int fontSize = 10; // 字号
};

#endif // WIDGET_H
