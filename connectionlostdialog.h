#ifndef CONNECTIONLOSTDIALOG_H
#define CONNECTIONLOSTDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectionLostDialog;
}

class ConnectionLostDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionLostDialog(QWidget *parent = 0);
    ~ConnectionLostDialog();

signals:

public slots:

private slots:

    void on_buttonBox_accepted();

private:
    Ui::ConnectionLostDialog *ui;
};

#endif // CONNECTIONLOSTDIALOG_H
