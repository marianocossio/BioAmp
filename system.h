#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>

#include <QTimer>
#include <QTime>

#include <vector>

#include "acquisitionserver.h"
#include "dataconditioner.h"
#include "graph.h"

using namespace std;

class System : public QObject
{
    Q_OBJECT

public:
    enum Channel {
        channel1, channel2, channel3, channel4, channel5, channel6, channel7, channel8
    };

    enum ConnectionType {
        input, short_circuit, BIAS, MVDD, temp, test, BIAS_DRP, BIAS_DRN
    };

    enum TestSignal {
        GND, SQ1875x097, SQ1875x195, DC, SQ3750x097, SQ3750x195
    };

    enum Gain {
        x1, x2, x4, x6, x8, x16, x24
    };

    enum SampleRate {
        at2kHz, at1kHz, at500Hz, at250Hz
    };

    explicit System(QObject *parent = 0);
    ~System();

    bool start(QString portName, int baudRate);
    void stop();
    void pause();
    bool receivingData();
    void send(QByteArray data);

    QList<QString> availablePorts();

    void flush();

signals:

public slots:    
    void activateChannel(int channel, bool activated);
    void activateAllChannels();
    void deactivateAllChannels();

    void setTestSignal(int signal);

    void setChannelConnectionType(int channel, ConnectionType type);
    void setChannelGain(int channel, int gain);
    void setChannelSRB2(int channel, bool set);

    void setSampleRate(int sampleRate);

    void toggleGraphVisibility();

private slots:
    void receiveData(DataSet data);
    void sendCommands();

private:
    AcquisitionServer acquisitionServer;
    Graph graph;

    vector<DataSet> buffer;

    unsigned int bufferSize;

    bool cascadeMode;
    int dataOutput;
    int channelCommandIndex;

    QByteArray activateChannelsCommands, deactivateChannelsCommands, testSignalCommands, sampleRateCommands;
    QVector<QByteArray> channelConfigurationCommands, commandsBuffer;

    QTimer ticker;
};

#endif // SYSTEM_H
