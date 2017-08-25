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
    void dataReady(DataSet data);

public slots:
    virtual void newByte(unsigned char byte);

    virtual void activateChannel(int channel);
    virtual void deactivateChannel(int channel);
    virtual void activateAllChannels();
    virtual void deactivateAllChannels();

protected:

private:
    int byteNumber;

    DataSet conditionedData;
};

#endif // DATACONDITIONER_H
