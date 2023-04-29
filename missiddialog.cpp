#include "missiddialog.h"
#include "ui_missiddialog.h"
#include "QMessageBox"
#include "preprocessing.h"

missIdDialog::missIdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::missIdDialog)
{
    ui->setupUi(this);


    setWindowTitle("Report your ID");


    /* Place holder text */
    ui->missIdLineEdit->setPlaceholderText("Enter your missing ID");

    /* Enable Clear button */
    ui->missIdLineEdit->setClearButtonEnabled(true);

    /* Add icons */
    QIcon user(CVISION_IMAGES_DIRECTORY"/user.png");

    /* Add actions */
    ui->missIdLineEdit->addAction(user, QLineEdit::LeadingPosition);
}

missIdDialog::~missIdDialog()
{
    delete ui;
}

void missIdDialog::on_reportButton_clicked()
{
    QMessageBox idErr;
    if(ui->missIdLineEdit->text().length() != 6)
    {
        idErr.critical(this,
                       tr("Note"),
                       tr("ID should be 6 digits"));
    }
    else
    {
        QMessageBox missMB;
        missMB.setText("On it");
        missMB.setInformativeText("Are you sure that this is the ID you want to report about?");
        missMB.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        missMB.setDefaultButton(QMessageBox::Yes);
        int ret = missMB.exec();
        if(ret == QMessageBox::Yes)
        {
            accept();
        }
        else
        {
            reject();
        }
    }
}


void missIdDialog::on_cancelButton_clicked()
{
    reject();
}

