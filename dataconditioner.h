#ifndef DATACONDITIONER_H
#define DATACONDITIONER_H

#include <QObject>

#include "dataset.h"

class DataConditioner : public QObject
{
    Q_OBJECT

public:
    explicit DataConditioner(QObject *parent = 0);
    virtual ~DataConditioner();

signals:
    void dataReady(DataSet* data);

public slots:
    virtual void newByte(unsigned char byte) = 0;

protected:
};

#endif // DATACONDITIONER_H
