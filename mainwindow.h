#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void readOut();
    void readErr();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QProcess *proses=new QProcess;
    QString yol="/run/user/2203/gvfs/ftp:host=172.27.0.152,port=2557";
};
#endif // MAINWINDOW_H
