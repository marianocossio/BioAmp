#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>

#include <vector>

#include "acquisitionserver.h"
#include "dataconditioner.h"
#include "graph.h"

using namespace std;

class System : public QObject
{
    Q_OBJECT

public:
    explicit System(QObject *parent = 0);
    ~System();

    bool start(QString portName, int baudRate);
    void stop();
    bool receivingData();
    void send(QByteArray data);

    QList<QString> availablePorts();

signals:

public slots:    
    void activateChannel(int channel);
    void deactivateChannel(int channel);
    void activateAllChannels();
    void deactivateAllChannels();

private slots:
    void receiveData(DataSet data);

private:
    AcquisitionServer acquisitionServer;
    Graph graph;

    vector<DataSet> buffer;

    unsigned int bufferSize;
};

#endif // SYSTEM_H
