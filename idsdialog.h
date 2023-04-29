#ifndef IDSDIALOG_H
#define IDSDIALOG_H

#include <QDialog>
#include "missiddialog.h"

namespace Ui {
class IdsDialog;
}

class IdsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IdsDialog(QWidget *parent = nullptr);
    ~IdsDialog();

private slots:
    void on_missingButton_clicked();

    void on_okButton_clicked();

private:
    Ui::IdsDialog *ui;
    missIdDialog * dialog_missId;
};

#endif // IDSDIALOG_H
