#ifndef INTERFACEQT_H
#define INTERFACEQT_H

#include "interface.h"
#include "mainwindow.h"

class InterfaceQt : public Interface
{
    Q_OBJECT

public:
    explicit InterfaceQt(QWidget *parent = 0);
    virtual ~InterfaceQt();
    virtual void show();

signals:

public slots:
    virtual void displayData(DataSet *data);

private slots:

private:
    MainWindow mainWindow;
};

#endif // INTERFACEQT_H
