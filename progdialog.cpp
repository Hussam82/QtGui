#include "progdialog.h"
#include "ui_progdialog.h"
#include <QFileDialog>
#include <QSettings>
#include <QListWidget>
#include "preprocessing.h"
#include <QMessageBox>
#include <QPushButton>
#include "customerdialog.h"
#include "ui_customerdialog.h"
#include <QDebug>


/* Static slave class variables */QList<QListWidgetItem *> ProgDialog::custArr;
QListWidgetItem * ProgDialog::progArr;

//void ProgDialog::onMyWidgetClosed(QObject *widget) {
//    qDebug() << "The widget has been closed.";
//}

ProgDialog::ProgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgDialog)
{
    ui->setupUi(this);


    setWindowTitle("Programmer mode");
    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);

//    /* Remove all items from the list widget */
//    while (ui->listWidget->count() > 0) {
//        QListWidgetItem *item = ui->listWidget->takeItem(0);
//        delete item;
//    }

    /* Load previously saved data */
    QSettings settings("Options", "Configured");
    QString index = "Current %1";


    settings.beginGroup("Main");
    QVariant savedPathsLen = settings.value(index.arg(0));
    for(int i = 1; i <= savedPathsLen.toInt(); i++)
    {
        ui->listWidget->addItem( settings.value( index.arg( QString::number(i) ) ).toString() );
    }
    settings.endGroup();
//    connect(this, &QDialog::destroyed, this, &ProgDialog::onMyWidgetClosed);
}

ProgDialog::~ProgDialog()
{
    qDebug() << "Programmer destructor";
    delete ui;
}

/* Add some programming option */
void ProgDialog::on_addButton_clicked()
{
    /* Select a file using GUI */
    QStringList fileName = QFileDialog::getOpenFileNames( this,
                                                          tr("Select all features"),
                                                          tr(CVISION_MODELS_DIRECTORY),
                                                          tr("Files (*-exe)") );
    /* Save path if the file is not empty */
    if(fileName.isEmpty())
    {
        return;
    }
    int fileNameLen = fileName.length();
    int listWidgetLen = ui->listWidget->count();
    for(int i = 0; i < listWidgetLen; i++)
    {
        for(int j = 0; j < fileNameLen; j++)
        {
            if(ui->listWidget->item(i)->text() == fileName[j])
            {
                QMessageBox includeErr;
                includeErr.critical(this,
                                    tr("Select carefully"),
                                    tr("You're trying to add one or more existing files"),
                                    QMessageBox::Ok);
                return;
            }
        }
    }
    ui->listWidget->addItems(fileName);
    return;
}

/* Remove some programming options */
void ProgDialog::on_deleteButton_clicked()
{
    QList<QListWidgetItem *> highlighted = ui->listWidget->selectedItems();
    QList<int> indices;
    int selectedItemsLen = highlighted.count();
    int listWidgetLen = ui->listWidget->count();
    /* Compare each item in the list widget to all the highlighted items */
    for(int i = 0; i < listWidgetLen; i++)
    {
        for(int j = 0; j < selectedItemsLen; j++)
        {
            if(ui->listWidget->item(i)->text() == highlighted[j]->text())
            {
                /* Return the list widget index of the highlighted item */
                indices.append(i);
            }
        }
    }
    int removed = 0;
    for(int i = 0; i < indices.length(); i++)
    {
        /* Reset customer configurations since you're removing features */
        CustomerDialog::ui->listWidget->clear();
        ui->listWidget->takeItem(indices[i] - removed);
        removed++;
        ui->listWidget->setCurrentRow(-1);
    }
    /* Do this if you want to delete only 1 highlighted item using currentRowChanged signal */
 //    if(mnSelected != -1)
 //    {
 //        QListWidgetItem * it = ui->listWidget->takeItem(mnSelected);
 //        delete it;
 //        ui->listWidget->setCurrentRow(-1);
 //    }
}

void ProgDialog::on_listWidget_currentRowChanged(int currentRow)
{
    mnSelected = currentRow;
}

/* Save highlighted to customer options */
void ProgDialog::on_pushButton_clicked()
{
    custArr = ui->listWidget->selectedItems();
}

/* List customer options */
void ProgDialog::on_pushButton_3_clicked()
{
    /* Load previously saved data from ProgDialog.cpp customer save button */
    QSettings settings("Customer", "Configured");
    QString index = "Current %1";
    settings.beginGroup("Customer");
    QVariant savedPathsLen = settings.value(index.arg(0));
    int pathsLen = savedPathsLen.toInt();
    for(int i = 1; i <= pathsLen; i++)
    {
        qDebug() << settings.value(index.arg(QString::number(i)), custArr.at(i-1)->text());
    }
    settings.endGroup();
}

/* Save the list widget */
void ProgDialog::on_saveButton_clicked()
{
    int listWidgetSize = ui->listWidget->count();
    QSettings settings1("Options", "Configured");
    QString index = "Current %1";
    settings1.beginGroup("Main");
    /* Store here the number of paths */
    settings1.setValue(index.arg(0), listWidgetSize);
    /* Store all the shown paths from indices 1->end */
    for(int i = 1; i <= listWidgetSize; i++)
    {
        settings1.setValue(index.arg(QString::number(i)), ui->listWidget->item(i-1)->text());
    }
    settings1.endGroup();
    QSettings settings2("Customer", "Configured");
    settings2.beginGroup("Customer");
    /* Store here the number of paths */
    settings2.setValue(index.arg(0), custArr.count());
    /* Clear the list to type the new contentss */
    CustomerDialog::ui->listWidget->clear();
    /* Store all the highlighted paths */
    for(int i = 1; i <= custArr.count(); i++)
    {
        settings2.setValue(index.arg(QString::number(i)), custArr.at(i-1)->text());
        /* Write the new contents immediatly */
        CustomerDialog::ui->listWidget->addItem(custArr.at(i-1)->text());
    }
    settings2.endGroup();
    accept();
}

/* Close button */
void ProgDialog::on_loadButton_clicked()
{
    accept();
}
