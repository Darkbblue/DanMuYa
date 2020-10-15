#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 外观设置
    setWindowOpacity(0.85); // 透明度
    this->setStyleSheet("background-color: #272822; color: white"); // 整体背景色
    ui->textBrowser->setStyleSheet("border-width: 0; border-style: outset"); // 文字框
    ui->pushButton->setStyleSheet("border-width: 0; border-style: outset"); // 按钮
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint); // 窗口置顶

    // 通信初始化
    sock = new QTcpSocket(this);

    // 子窗体 - 设置窗体
    configWindow = new ConfigWindow();
    configWindow->DisplayAlpha(QString::number(alpha));
    configWindow->DisplayFont(QString::number(fontSize));
    connect(configWindow, &ConfigWindow::SetAlpha, this, &Widget::SetAlpha);
    connect(configWindow, &ConfigWindow::SetFont, this, &Widget::SetFont);

    // 子窗体 - 初始化窗体
    startWindow = new StartWindow();
    connect(startWindow, &StartWindow::StartConnection, this, &Widget::StartConnection);
    startWindow->show();
}

Widget::~Widget()
{
    delete ui;
    delete sock;
    delete startWindow;
    delete configWindow;
}

void Widget::StartConnection(int port) // 开始连接
{
    sock->connectToHost("127.0.0.1", port); // 本机中转端口
    connect(sock, &QTcpSocket::readyRead, this, &Widget::RcvMsg);
}

void Widget::RcvMsg()
{
    buffer.append(sock->readAll()); // 获取数据
    while (buffer.length() >= 3) // 切割粘包 (进入循环体后一定有完整包头)
    {
        int len = (buffer[0] - '0') * 100 + (buffer[1] - '0') * 10 + (buffer[2] - '0'); // 计算包长
        if (buffer.length() < len) // 若包不完整，则等待下次接收再处理
            break;
        ui->textBrowser->append(buffer.mid(3, len - 3)); // 打印当前包数据
        buffer = buffer.mid(len); // 删除当前包
    }
}

void Widget::SetAlpha(QString str) // 设置透明度
{
    double new_alpha = str.toDouble();
    if (0.5 <= new_alpha && new_alpha <= 1) // 若是合法输入
    {
        alpha = new_alpha;
        this->setWindowOpacity(alpha); // 设置新的透明度
    }
    configWindow->DisplayAlpha(QString::number(alpha)); // 更新显示
}

void Widget::SetFont(QString str) // 设置字号
{
    if (int new_fontSize = str.toInt()) // 若是合法输入
    {
        fontSize = new_fontSize;
        ui->textBrowser->setFontPointSize(fontSize); // 设置新的字号
    }
    configWindow->DisplayFont(QString::number(fontSize)); // 更新显示
}

void Widget::on_pushButton_clicked()
{
    configWindow->show();
}
