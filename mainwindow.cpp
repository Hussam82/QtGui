#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customerdialog.h"
#include "progdialog.h"
#include "logindialog.h"
#include <QPixmap>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QPixmap pix("/home/farid/Desktop/GP/Configuration-GUI/images/conf.png");
    //ui->label->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_customerModeButton_clicked()
{
//    std::unique_ptr<CustomerDialog> dialog = {new CustomerDialog(this)};
    CustomerDialog * dialog = new CustomerDialog(this);
    dialog->exec();
}

void MainWindow::on_programmerModeButton_clicked()
{
    LoginDialog * dialog = new LoginDialog(this);
    dialog->exec();
}


