#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    this->setFixedSize(310, 70);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_pushButton_clicked()
{
    emit StartConnection(ui->lineEdit->text().toInt());
    this->hide();
}
