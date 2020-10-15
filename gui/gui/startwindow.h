#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>

namespace Ui {
class StartWindow;
}

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

signals:
    void StartConnection(int port); // 建立连接

private slots:
    void on_pushButton_clicked();

private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H
