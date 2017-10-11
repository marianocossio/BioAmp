#ifndef WAITFORCLOSEDIALOG_H
#define WAITFORCLOSEDIALOG_H

#include <QDialog>

namespace Ui {
class WaitForCloseDialog;
}

class WaitForCloseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitForCloseDialog(QWidget *parent = 0);
    ~WaitForCloseDialog();

private:
    Ui::WaitForCloseDialog *ui;
};

#endif // WAITFORCLOSEDIALOG_H
