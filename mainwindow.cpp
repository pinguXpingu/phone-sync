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
        ui->textBrowser->append("Bağlı");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    QProcess *prosess=new QProcess;
    if(prosess)
    {
        prosess->setEnvironment( QProcess::systemEnvironment());
        prosess->setProcessChannelMode( QProcess::MergedChannels);

        if (ui->pushButton_3->text()=="Ayır")
        {
            prosess->start("gio", QStringList() << "mount" << "-u" << "ftp://pinguXmini.pinguXnet:2557");
        }
        else
        {
            prosess->start("gio", QStringList() << "mount" << "ftp://pinguXmini.pinguXnet:2557");
        }

        prosess->waitForStarted();
        connect(prosess,SIGNAL(readyRead()),this,SLOT(readOut()));
        connect(prosess,SIGNAL(finished(int)),this,SLOT(pushButton_text()));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!QDir(yol).exists())
    {
        ui->textBrowser->append("<span style=\"color:fuchsia;\">Bağlı değil ki</span>");
    }
    else
    {
        QProcess *proses=new QProcess;
        if (proses)
        {
            ui->textBrowser->append("<span style=\"color:deepskyblue;\">###################EŞİTLENİYOR#################</span>");
            ui->pushButton_3->setDisabled(true);
            ui->pushButton_2->setDisabled(true);
            proses->setEnvironment( QProcess::systemEnvironment());
            proses->setProcessChannelMode( QProcess::MergedChannels);

            proses->setWorkingDirectory(yol);
            proses->start("sh",QStringList() << "aTa/yedekle.sh");


            proses->waitForStarted();
            connect(proses,SIGNAL(readyReadStandardOutput()),this,SLOT(readOut()));
            connect(proses,SIGNAL(readyReadStandardError()),this,SLOT(readErr()));
            connect(proses,SIGNAL(readChannelFinished()),this,SLOT(msg()));
        }
    }
}

void MainWindow::readOut()
{
    QProcess *p = dynamic_cast<QProcess *>(sender());
    if (p)
    {
        ui->textBrowser->append(p->readAllStandardOutput());
    }
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
        /*QProcess::execute("nautilus "+yol);*/

        //QObject *obje;
        QString program="nautilus";
        QStringList argumanlar;
        argumanlar << yol;

        //QProcess *konumAc=new QProcess(obje);
        QProcess *konumAc=new QProcess();
        konumAc->start(program, argumanlar);
    }
    else
    {
        ui->textBrowser->append("<span style=\"color:fuchsia;\">Bağlı değil ki</span>");
    }
}

void MainWindow::pushButton_text()
{
    for (int i=0; i<10;i++)
    {
        if(QDir(yol).exists() && i==9)
        {
            ui->pushButton_3->setText("Ayır");
            ui->textBrowser->append("<span style=\"color:greenyellow;\">####################BAĞLANDI##################</span>");
        }
        else
        {
            if (ui->pushButton_3->text()=="Ayır" && i==9)
            {
                ui->pushButton_3->setText("Bağla");
                ui->textBrowser->append("<span style=\"color:red;\">#####################AYRILDI###################</span>");
            }
        }
    }
}

void MainWindow::msg()
{
    ui->textBrowser->append("<span style=\"color:deepskyblue;\">#####################BİTTİ#####################</span>");
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
}
