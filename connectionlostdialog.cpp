#include "connectionlostdialog.h"
#include "ui_connectionlostdialog.h"

ConnectionLostDialog::ConnectionLostDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionLostDialog)
{
    ui->setupUi(this);

    setWindowTitle("Connection Error!");
}

ConnectionLostDialog::~ConnectionLostDialog()
{
    delete ui;
}

void ConnectionLostDialog::on_buttonBox_accepted()
{
    close();
}
