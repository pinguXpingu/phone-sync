#include "setting.h"
#include "ui_setting.h"
#include "QFileDialog"

setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);

    //veritabanı ekle
    QString devName="pinguXmini";
    QString devAddr="ftp://pinguXmini.pinguXnet:2557";
    QString mntPath="/run/user/2203/gvfs/ftp:host=pinguxmini.pinguxnet,port=2557";
    QString targPath="/home/ata/İndirilenler";

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

    dizinler.remove(-1,1);
    QStringList liste=dizinler.split(",");

    ui->devName->setText(devName);
    ui->devAddr->setText(devAddr);
    ui->mntPath->setText(mntPath);
    ui->targetPath->setText(targPath);
    ui->folderList->addItems(liste);
}

setting::~setting()
{
    delete ui;
}

void setting::on_addBtn_clicked()
{
    QString fileName=QFileDialog::getExistingDirectory(this, "Seç...", QDir::homePath(), QFileDialog::ShowDirsOnly);
    int a=0;

    for (int i=0; i<ui->folderList->count(); ++i) {
        if (ui->folderList->count()!=0 && ui->folderList->item(i)->text()==fileName){
            a++;
        }
    }
    if (a==0){
        ui->folderList->addItem(fileName);
    }
}

void setting::on_delBtn_clicked()
{
    delete ui->folderList->currentItem();
}

void setting::on_saveBtn_clicked()
{
    QString secilenler="";
    for (int i=0; i<(ui->folderList->count()); i++){
        secilenler+=(ui->folderList->item(i)->text())+" ";
    }
    secilenler.remove(-1,1);
    qDebug() << "seçilen klasörler:" << secilenler;
    this->close();
}

void setting::on_closeBtn_clicked()
{
    this->close();
}

void setting::on_targetSel_clicked()
{
    QString fileName=QFileDialog::getExistingDirectory(this, "Seç...", ui->targetPath->text(), QFileDialog::ShowDirsOnly);
    ui->targetPath->setText(fileName);
}

