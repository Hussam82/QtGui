#ifndef MISSIDDIALOG_H
#define MISSIDDIALOG_H

#include <QDialog>

namespace Ui {
class missIdDialog;
}

class missIdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit missIdDialog(QWidget *parent = nullptr);
    ~missIdDialog();

private slots:
    void on_reportButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::missIdDialog *ui;
};

#endif // MISSIDDIALOG_H
