#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *settingAction = ui->menuBar->addAction("Ayarlar");
    connect(settingAction, SIGNAL(triggered()), this, SLOT(ayarlar()));

    //veritabanı ekle


    if(QDir(yol).exists() || QDir(yol2).exists())
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
    if(!QDir(yol).exists() && !QDir(yol2).exists())
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

            QDir(yol).exists() ? proses->setWorkingDirectory(yol): proses->setWorkingDirectory(yol2);
            //proses->start("sh",QStringList() << "aTa/yedekle.sh");

            //veritabanından oku
            QString dizinler = "aTa," \
                "Alarms," \
                "Android/data/com.mobile.myeye/files/XMEye/videorecord," \
                "Android/data/com.pozitron.iscep/files Android/media," \
                "'Canon EOS 4000D'," \
                "Call," \
                "DCIM," \
                "Documents," \
                "Download," \
                "Movies," \
                "Music," \
                "Notifications," \
                "Pictures," \
                "Ringtones," \
                "Telegram," \
                "'Voice Recorder',";
            QString dosyalar=dizinler.replace(","," ");
/*
            QString dosyalar = "aTa " \
                                "Alarms " \
                                "Android/data/com.mobile.myeye/files/XMEye/videorecord " \
                                "Android/data/com.pozitron.iscep/files Android/media " \
                                "'Canon EOS 4000D' " \
                                "Call " \
                                "DCIM " \
                                "Documents " \
                                "Download " \
                                "Movies " \
                                "Music " \
                                "Notifications " \
                                "Pictures " \
                                "Ringtones " \
                                "Telegram " \
                                "'Voice Recorder' ";
*/
            proses->start("/bin/bash",QStringList() << "-c" <<
"$(mkdir -p $(xdg-user-dir DOWNLOAD)/pngtel); \
son=$(cat Android/.sonsync | head -n1); \
simdi=$(date +%s); \
dakika=$(((($simdi-$son)/60)+1)); \
find "+dosyalar+" \
-cmin -$(echo $dakika) -exec cp --no-preserve=all --parents -vf {} $(xdg-user-dir DOWNLOAD)/pngtel \\;;\
date +%s > Android/.sonsync; \
find $(xdg-user-dir DOWNLOAD)/pngtel -type d -empty -delete");

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
        QDir(yol).exists() ? argumanlar << yol : argumanlar << yol2;

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

void MainWindow::ayarlar()
{
    s.setWindowModality(Qt::WindowModality(2));
    s.setWindowFlag(Qt::WindowStaysOnTopHint);
    s.show();
}

/*TODO
 * Device Name
 * Device Url
 * Device Mount Path
 *
 * Target Dir
 * Source Dir(s)
 *
 * Last Sync Date/Time
 * */

/*
void MainWindow::kopyala(QString kaynak, QString hedef)
{
    QDir kaynakDizin(kaynak);
    QDir hedefDizin(hedef);

    if (!kaynakDizin.exists()){
        ui->textBrowser->append("Kaynak dizin bulunamadı!");
    }
    if (!hedefDizin.exists()){
        hedefDizin.mkdir(hedef);
    }

    QStringList dosyalar = kaynakDizin.entryList(QDir::Files);

    for (int i = 0; i < dosyalar.count(); ++i) {
        QString kaynakAd = kaynakDizin + "/" + dosyalar[i];
        QString hedefAd = hedefDizin + "/" + dosyalar[i];
        QFile::copy(kaynakAd,hedefAd);
    }
    dosyalar.clear();

    dosyalar = kaynakDizin.entryList(QDir::AllDirs | QDir::NoDotDot);
    for (int i = 0; i < dosyalar.count(); ++i) {
        QString kaynakAd = kaynakDizin + "/" + dosyalar[i];
        QString hedefAd = hedefDizin + "/" + dosyalar[i];
        kopyala(kaynakAd,hedefAd);
    }
}
*/
/*
// Recursively copies all files and folders from src to target and overwrites existing files in target.
void MainWindow::kopyala(const std::filesystem::path& src, const std::filesystem::path& target)
{
    try
    {
        std::filesystem::copy(src, target, std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }
}
*/
