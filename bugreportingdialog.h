#ifndef BUGREPORTINGDIALOG_H
#define BUGREPORTINGDIALOG_H

#include <QDialog>

namespace Ui {
class bugReportingDialog;
}

class bugReportingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bugReportingDialog(QWidget *parent = 0);
    ~bugReportingDialog();

private slots:
    void on_submitReportButton_clicked();

    void on_backButton_clicked();

private:
    Ui::bugReportingDialog *ui;
};

#endif // BUGREPORTINGDIALOG_H
