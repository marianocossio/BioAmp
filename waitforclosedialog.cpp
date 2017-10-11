#include "waitforclosedialog.h"
#include "ui_waitforclosedialog.h"

WaitForCloseDialog::WaitForCloseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitForCloseDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Popup);
}

WaitForCloseDialog::~WaitForCloseDialog()
{
    delete ui;
}
