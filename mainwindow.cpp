#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(QDir(yol).exists())
    {
        ui->pushButton_3->setText("Ayır");
        ui->textBrowser->append("###BAĞLI###");
    }
    else
    {
        ui->pushButton_3->setText("Bağla");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    if(ui->pushButton_3->text()=="Ayır")
    {
        proses->execute("gio mount -u ftp://172.27.0.152:2557");
        ui->textBrowser->append("###AYRILDI###");
        ui->pushButton_3->setText("Bağla");
    }
    else
    {
        proses->execute("gio mount ftp://172.27.0.152:2557");
        ui->textBrowser->append("###BAĞLANDI###");
        ui->pushButton_3->setText("Ayır");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    //proses->execute("clear");
    if (proses)
    {
      proses->setEnvironment( QProcess::systemEnvironment() );
      proses->setProcessChannelMode( QProcess::MergedChannels );

      proses->start( "echo", QStringList() << "oldu bu iş" );
      proses->waitForStarted();

      connect( proses, SIGNAL(readyReadStandardOutput()), this, SLOT(readOut()) );
      connect( proses, SIGNAL(readyReadStandardError()), this, SLOT(readErr()) );
    }
}

void MainWindow::readOut()
{
    QProcess *p = dynamic_cast<QProcess *>(sender());

    if (p)
      ui->textBrowser->append(p->readAllStandardOutput());
}

void MainWindow::readErr()
{
    QProcess *p = dynamic_cast<QProcess *>(sender());

    if (p)
      ui->textBrowser->append(p->readAllStandardError());
}

void MainWindow::on_pushButton_clicked()
{
    if(QDir(yol).exists())
    {
        QProcess::execute("nautilus "+yol);
    }
    else
    {
        ui->textBrowser->append("###BAĞLI DEĞİLKİ###");
    }
}
