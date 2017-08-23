#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>

#include <vector>

#include "interface.h"
#include "interfaceqt.h"

#include "acquisitionserver.h"
#include "acquisitionserverqt.h"

#include "dataconditioner.h"
#include "dataconditionerstd.h"

using namespace std;

class System : public QObject
{
    Q_OBJECT

public:
    explicit System(QObject *parent = 0);
    ~System();
    void run();

signals:

public slots:

private slots:
    void receiveData(DataSet *data);

private:
    Interface *interface;
    AcquisitionServer *acquisitionServer;
    DataConditioner *dataConditioner;
    vector<DataSetStd*> buffer;

    unsigned int bufferSize;
};

#endif // SYSTEM_H
