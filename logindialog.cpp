#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "preprocessing.h"
#include "customerdialog.h"
#include <QDebug>


/* Static sub-master class variables */
QList<QString> LoginDialog::validID;
QList<QString> LoginDialog::listOfIds;
QList<QString> LoginDialog::listOfPass;
int LoginDialog::selectedId = 0;


/* Constructor */
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);


    setWindowTitle("Login window");


    /* Place holder text */
    ui->idLineEdit->setPlaceholderText("Enter a valid ID");
    ui->passLineEdit->setPlaceholderText("Password");

    /* Enable Clear button */
    ui->idLineEdit->setClearButtonEnabled(true);
    ui->passLineEdit->setClearButtonEnabled(true);

    /* Set password mode */
    ui->passLineEdit->setEchoMode(QLineEdit::Password);

    /* Add icon photos */
    QIcon user(CVISION_IMAGES_DIRECTORY"/user.png");
    QIcon password(CVISION_IMAGES_DIRECTORY"/pass.png");

    /* Add actions */
    ui->idLineEdit->addAction(user, QLineEdit::LeadingPosition);
    ui->passLineEdit->addAction(password, QLineEdit::LeadingPosition);

    /* The available employees */
    listOfIds = {EMPLOYEE_ID1,
                 EMPLOYEE_ID2,
                 EMPLOYEE_ID3,
                 EMPLOYEE_ID4};

    /* The available employees passwords (in the same order of listOfIds) */
    listOfPass = {EMPLOYEE_PASSWORD1,
                  EMPLOYEE_PASSWORD2,
                  EMPLOYEE_PASSWORD3,
                  EMPLOYEE_PASSWORD4};


    /* Construct any dialogs here to avoid re-construction */
    dialog_Id = new IdsDialog(this);
}


/* Destructor */
LoginDialog::~LoginDialog()
{
    qDebug() << "Login destructor call";
    delete ui;
    delete dialog_Prog;
    delete dialog_Id;
}


/* Show the available IDs to choose 1 (if you don't remember yours) */
void LoginDialog::on_validIdsButton_clicked()
{
    dialog_Id->exec();
}


/* Submit the ID and password */
void LoginDialog::on_submitButton_clicked()
{
    /* SEF confirms a safe entry, WPF gives an error and BAF informs a banned acc */
    bool submitEntryFlag = FALSE, wrongPassFlag = FALSE, bannedAccFlag = FALSE;
    /* Check whether ID and password matches listOfIds and listOfPass */
    for(int i = 0; i < NUM_OF_EMPLOYEES; i++)
    {
        if( ( ui->idLineEdit->text() == EMPTY ) || ( ui->passLineEdit->text() == EMPTY ) )
        {
            /* Skip this function if ID or password field is empty */
            break;
        }
        /* Stop looping at the end of banned accounts length */
        if(i < CustomerDialog::bannedAcc.length())
        {
            /* Loop on all of the banned accounts and check if the input is one of them */
            if(ui->idLineEdit->text() == CustomerDialog::bannedAcc[i])
            {
                bannedAccFlag = TRUE;
                /* You don't have to check password if the ID is banned */
                break;
            }
        }
        else
        {
            /* Do nothing */
        }
        /* Confirm a valid entry if the ID and password matches */
        if( ( ui->idLineEdit->text() == listOfIds[i] ) && ( ui->passLineEdit->text() == listOfPass[i] ) )
        {
            submitEntryFlag = TRUE;
            break;
        }
        else
        {
            /* Block entrance since the ID is not banned but password is incorrect */
            wrongPassFlag = TRUE;
        }
    }
    if(submitEntryFlag == TRUE)
    {
        dialog_Prog = new ProgDialog(this);
        dialog_Prog->exec();
        delete dialog_Prog;
        accept();
    }
    else if(bannedAccFlag == TRUE)
    {
        QMessageBox bannMB;
        bannMB.critical(this,
                       tr("Your account is banned"),
                       tr("Contact a supervisor to unlock").arg(5 - CustomerDialog::wrongPass),
                       QMessageBox::Ok | QMessageBox::Cancel);
    }
    else if(wrongPassFlag == TRUE)
    {
        /* Increment number of consecutive wrong passwords of this ID */
        CustomerDialog::wrongPass++;
        QMessageBox passMB;
        switch(CustomerDialog::wrongPass)
        {
            case 4:
                passMB.warning(this,
                                tr("Incorrect ID or password"),
                                tr("You only have 1 trial before bann!!"),
                                QMessageBox::Ok | QMessageBox::Cancel);

                break;
            case 5:
                CustomerDialog::bannedAcc.append(ui->idLineEdit->text());
                passMB.critical(this,
                               tr("Your account is banned"),
                               tr("Contact a supervisor to unlock").arg(5 - CustomerDialog::wrongPass),
                               QMessageBox::Ok | QMessageBox::Cancel);
                // To get here again the next time.
                CustomerDialog::wrongPass--;
                reject();
                break;
            /* Case [1-3] */
            default:
                passMB.information(this,
                                   tr("Incorrect ID or password"),
                                   tr("You still have %1 trials").arg(5 - CustomerDialog::wrongPass),
                                   QMessageBox::Ok | QMessageBox::Cancel);
                break;
        }
    }
    /* ID or password input is empty */
    else
    {
        /* Do nothing */
    }
    /* Clear your ID and password before exiting as the object is not destroyed */
    if(submitEntryFlag || bannedAccFlag)
    {
        ui->idLineEdit->clear();
        ui->passLineEdit->clear();
    }
    else if(wrongPassFlag)
    {
        ui->passLineEdit->clear();
    }
    else
    {
        /* Do nothing */
    }
}

