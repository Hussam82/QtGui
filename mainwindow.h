#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "processthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /*
     We used static keyword to be able to access
     this variable without creating a class object.
     Don't forget to define it in the .cpp file.
     */
    static QList<QString> bannedAcc;
    static int wrongPass;

private slots:
    void on_customerModeButton_clicked();

    void on_programmerModeButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
