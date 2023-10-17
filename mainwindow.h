#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QThread>
#include <setting.h>

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
    void on_sync_button_clicked();
    void on_mount_button_clicked();
    void readOut();
    void readErr();
    void on_phone_button_clicked();
    void pushButton_text();
    void msg();
    void ayarlar();
    //void kopyala(QString,QString);
    //void kopyala(const std::filesystem::path&, const std::filesystem::path&);

private:
    Ui::MainWindow *ui;
    QString yol="/run/user/2203/gvfs/ftp:host=pinguxmini.pingux.ata,port=2557";
    QString yol2="/run/user/2203/gvfs/sftp:host=172.27.0.152,port=1743/pinguXmini";
    setting s;
};
#endif // MAINWINDOW_H
