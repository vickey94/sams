#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <user.h>
#include <QMessageBox>
#include <QDialog>
#include <util.h>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();

private:

    void clearAll();
    Ui::RegisterDialog *ui;


    User *user;

private slots:
    void backBtnSlot();
    void resetBtnSlot();
    void registerBtnSlot();

};

#endif // REGISTERDIALOG_H
