#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();

private slots:
    void on_addBtn_clicked();

    void on_delBtn_clicked();

    void on_saveBtn_clicked();

    void on_closeBtn_clicked();

    void on_targetSel_clicked();

private:
    Ui::setting *ui;
};

#endif // SETTING_H
