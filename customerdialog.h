#ifndef CUSTOMERDIALOG_H
#define CUSTOMERDIALOG_H

#include <QDialog>
#include "preprocessing.h"
#include <QListWidgetItem>
#include "processthread.h"
#include "logindialog.h"

namespace Ui {
class CustomerDialog;
}

class CustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerDialog(QWidget *parent = nullptr);
    ~CustomerDialog();
    static QList<QListWidgetItem *> usedOptions;
    static QList<QString> bannedAcc;
    static int wrongPass;

private slots:

    void on_reportButton_clicked();

    void on_saveButton_clicked();

    void on_quitButton_clicked();

    void on_programmerButton_clicked();

private:
    ProcessThread * thread;
    LoginDialog * dialog_Login;
/* To be accessed by progdialog.cpp save customer button */
public:
    static Ui::CustomerDialog *ui;
};

#endif // CUSTOMERDIALOG_H
