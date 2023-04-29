#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "idsdialog.h"
#include "progdialog.h"
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    static QList<QString> validID;
    static QList<QString> listOfIds;
    static QList<QString> listOfPass;
    static int selectedId;

private slots:
    void on_validIdsButton_clicked();

    void on_submitButton_clicked();

private:
    Ui::LoginDialog *ui;
    ProgDialog * dialog_Prog;
    IdsDialog * dialog_Id;
    // This'll block doing an object of this class.
    // void setupUi();
};

#endif // LOGINDIALOG_H
