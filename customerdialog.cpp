#include "customerdialog.h"
#include "ui_customerdialog.h"
#include <QSettings>
#include "processthread.h"
#include <QPixmap>
#include <QDebug>


/* Static master class variables */
QList<QListWidgetItem *> CustomerDialog::usedOptions;
int CustomerDialog::wrongPass = 0;
QList<QString> CustomerDialog::bannedAcc;
Ui::CustomerDialog *CustomerDialog::ui = new Ui::CustomerDialog;


/* Constructor */
CustomerDialog::CustomerDialog(QWidget *parent) :
    QDialog(parent)
{
    ui->setupUi(this);


    /* Load previously saved data from ProgDialog.cpp customer save button */
    QSettings settings1("Customer", "Configured");
    QString index = "Current %1";
    settings1.beginGroup("Customer");
    QVariant savedPathsLen = settings1.value(index.arg(0));
    for(int i = 1; i <= savedPathsLen.toInt(); i++)
    {
        ui->listWidget->addItem(settings1.value( index.arg( QString::number(i) ) ).toString());
    }
    settings1.endGroup();

    if (ui->listWidget->count() == 0)
    {
        qDebug() << "You don't have access to any features";
    }
    else
    {
        /* Load the chosen options and run */
        QSettings settings2("Used", "Saved");
        settings2.beginGroup("Used");
        thread = new ProcessThread( settings2.value( index.arg(QString::number(1)) ).toString() );
        thread->start();
        settings2.endGroup();
    }


    /* Load the agency button image */
//    QImage img;
//    QPixmap pixmap;
//    img.load("/etc/GP-qt5-materials/images/mech.jpg");
//    pixmap = QPixmap::fromImage(img).scaled(80, 80);
//    ui->programmerButton->setIcon(QIcon(pixmap));
//    ui->programmerButton->setIconSize(QSize(80, 80));


    /* Construct any dialogs here to avoid re-construction */
    dialog_Login = new LoginDialog(this);
}


/* Destructor */
CustomerDialog::~CustomerDialog()
{
    qDebug() << "Customer destructor call";
    delete thread;
    delete ui;
    delete dialog_Login;
}


/* Report bugs to the agency */
void CustomerDialog::on_reportButton_clicked()
{

}


/* Save the selected application to future use */
void CustomerDialog::on_saveButton_clicked()
{
    usedOptions = ui->listWidget->selectedItems();
    if(usedOptions.isEmpty())
    {
        return;
    }
    QString index = "Current %1";

    /* Load the chosen options and run */
    QSettings settings("Used", "Saved");
    settings.beginGroup("Used");
    /* Store here the number of paths */
    settings.setValue(index.arg(0), usedOptions.count());
    /* Store all the highlighted paths */
    for(int i = 1; i <= usedOptions.count(); i++)
    {
        settings.setValue(index.arg(QString::number(i)), usedOptions.at(i-1)->text());
    }
    settings.endGroup();
    /* Delete the previous thread, create new one and run */
    delete thread;
//    qDebug() << "Old thread pointer is deleted";
    thread = new ProcessThread(usedOptions.at(0)->text());
    thread->start();
}


/* Quit the whole application */
void CustomerDialog::on_quitButton_clicked()
{
    reject();
}

/* Go to agency login */
void CustomerDialog::on_programmerButton_clicked()
{
    qDebug() << "hi = ";
    dialog_Login->exec();
}
