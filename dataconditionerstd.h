#ifndef DATACONDITIONERSTD_H
#define DATACONDITIONERSTD_H

#include "dataconditioner.h"
#include "datasetstd.h"

class DataConditionerStd : public DataConditioner
{
    Q_OBJECT

public:
    DataConditionerStd();
    virtual ~DataConditionerStd();

signals:
    void dataReady(DataSet* data);

public slots:
    virtual void newByte(unsigned char byte);

private:
    int byteNumber;

    DataSet* conditionedData;
};

#endif // DATACONDITIONERSTD_H
