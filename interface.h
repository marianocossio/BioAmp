#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>

#include "dataset.h"

class Interface : public QObject
{
    Q_OBJECT

public:
    explicit Interface(QObject *parent = 0);
    virtual ~Interface();
    virtual void show() = 0;

signals:

public slots:
    virtual void displayData(DataSet* data) = 0;
};

#endif // INTERFACE_H
