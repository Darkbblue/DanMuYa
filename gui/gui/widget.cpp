#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowOpacity(0.85); // 透明度设置
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint); // 窗口置顶
    sock = new QTcpSocket(this);
    sock->connectToHost("127.0.0.1", 12000); // 本机中转端口
    connect(sock, &QTcpSocket::readyRead, this, &Widget::RcvMsg);
}

Widget::~Widget()
{
    delete ui;
    delete sock;
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
