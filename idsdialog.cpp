#include "idsdialog.h"
#include "ui_idsdialog.h"
#include "preprocessing.h"
#include "QMessageBox"
#include "logindialog.h"
#include <QDebug>


/* Constructor */
IdsDialog::IdsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IdsDialog)
{
    ui->setupUi(this);


    setWindowTitle("Available IDs");


    for(int i = 0; i < NUM_OF_EMPLOYEES; i++)
    {
        ui->comboBox->addItem(LoginDialog::listOfIds[i]);
    }


    /* Construct any dialogs here to avoid re-construction */
    dialog_missId = new missIdDialog(this);
}


/* Destructor */
IdsDialog::~IdsDialog()
{
    qDebug() << "Ids destructor call";
    delete ui;
    delete dialog_missId;
}

/* Report a missing ID */
void IdsDialog::on_missingButton_clicked()
{
    dialog_missId->exec();
}

/* Select the chosen ID to login using it */
void IdsDialog::on_okButton_clicked()
{
    LoginDialog::selectedId = ui->comboBox->currentText().toInt();
}
