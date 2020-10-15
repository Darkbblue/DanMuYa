#include "configwindow.h"
#include "ui_configwindow.h"

ConfigWindow::ConfigWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

void ConfigWindow::DisplayAlpha(QString str) // 显示透明度
{
    ui->lineEditAlpha->setText(str);
}

void ConfigWindow::DisplayFont(QString str) // 显示字号
{
    ui->lineEditFont->setText(str);
}

void ConfigWindow::on_pushButtonAlpha_clicked()
{
    emit SetAlpha(ui->lineEditAlpha->text()); // 发送设置透明度信号
}

void ConfigWindow::on_pushButtonFont_clicked()
{
    emit SetFont(ui->lineEditFont->text()); // 发送设置字号信号
}
