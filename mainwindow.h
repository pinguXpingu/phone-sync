#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QThread>

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
    void pushButton_text();
    void msg();

private:
    Ui::MainWindow *ui;
    QString yol="/run/user/2203/gvfs/ftp:host=pinguxmini.pingux.net,port=2557";
};
#endif // MAINWINDOW_H
