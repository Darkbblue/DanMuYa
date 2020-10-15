#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QWidget>

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = nullptr);
    ~ConfigWindow();
    void DisplayAlpha(QString str); // 显示透明度
    void DisplayFont(QString str); // 显示字号

signals:
    void SetAlpha(QString str); // 设置透明度
    void SetFont(QString str); // 设置字号

private slots:
    void on_pushButtonAlpha_clicked();

    void on_pushButtonFont_clicked();

private:
    Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_H
