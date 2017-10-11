#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>

#include <QTimer>
#include <QTime>
#include <QDate>

#include <deque>
#include <vector>

#include "acquisitionserver.h"
#include "chebyshev3035.h"
#include "graph.h"
#include "logger.h"

using namespace std;

/**
 * @brief
 *
 */
class System : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     */
    enum Channel {
        channel1, channel2, channel3, channel4, channel5, channel6, channel7, channel8
    };

    /**
     * @brief
     *
     */
    enum ConnectionType {
        input, short_circuit, BIAS, MVDD, temp, test, BIAS_DRP, BIAS_DRN
    };

    /**
     * @brief
     *
     */
    enum TestSignal {
        GND, SQ1875x097, SQ1875x195, DC, SQ3750x097, SQ3750x195
    };

    /**
     * @brief
     *
     */
    enum Gain {
        x1, x2, x4, x6, x8, x16, x24
    };

    /**
     * @brief
     *
     */
    enum SampleRate {
        at2kHz, at1kHz, at500Hz, at250Hz
    };

    /**
     * @brief
     *
     */
    enum ChannelTerminal {
        P_Terminal, N_Terminal
    };

    /**
     * @brief
     *
     * @param parent
     */
    explicit System(QObject *parent = 0);
    /**
     * @brief
     *
     */
    ~System();

    /**
     * @brief
     *
     * @param portName
     * @param baudRate
     * @return bool
     */
    bool start(QString portName, int baudRate);
    /**
     * @brief
     *
     */
    void stop();
    /**
     * @brief
     *
     */
    void pause();
    /**
     * @brief
     *
     * @return bool
     */
    bool receivingData();
    /**
     * @brief
     *
     * @return bool
     */
    bool sendingData();
    /**
     * @brief
     *
     * @param data
     */
    void send(QByteArray data);

    /**
     * @brief
     *
     * @return QList<QString>
     */
    QList<QString> availablePorts();

    /**
     * @brief
     *
     */
    void flush();

signals:
    /**
     * @brief
     *
     * @param channelNumber
     * @param terminal
     * @param impedance
     */
    void impedanceCalculated(int channelNumber, System::ChannelTerminal terminal, double impedance);
    /**
     * @brief
     *
     */
    void portConnectionError();
    /**
     * @brief
     *
     */
    void lastCommandSent();

public slots:    
    /**
     * @brief
     *
     * @param channel
     * @param activated
     */
    void activateChannel(int channel, bool activated);
    /**
     * @brief
     *
     */
    void activateAllChannels();
    /**
     * @brief
     *
     */
    void deactivateAllChannels();

    /**
     * @brief
     *
     * @param signal
     */
    void setTestSignal(int signal);

    /**
     * @brief
     *
     * @param channel
     * @param type
     */
    void setChannelConnectionType(int channel, ConnectionType type);
    /**
     * @brief
     *
     * @param channel
     * @param gain
     */
    void setChannelGain(int channel, int gain);
    /**
     * @brief
     *
     * @param channel
     * @param set
     */
    void setChannelSRB2(int channel, bool set);

    /**
     * @brief
     *
     * @param sampleRate
     */
    void setSampleRate(int sampleRate);

    /**
     * @brief
     *
     */
    void toggleGraphVisibility();

    /**
     * @brief
     *
     * @param channel
     * @param terminal
     */
    void startCheckingChannelImpedance(int channel, System::ChannelTerminal terminal);
    /**
     * @brief
     *
     */
    void stopCheckingChannelImpedance();

    /**
     * @brief
     *
     * @param channel
     * @param connect
     */
    void connectToBIAS(int channel, bool connect);

private slots:
    /**
     * @brief
     *
     */
    void getChannelImpedance();
    /**
     * @brief
     *
     * @param data
     */
    void receiveData(DataSet data);
    /**
     * @brief
     *
     */
    void sendCommands();
    /**
     * @brief
     *
     * @param response
     */
    void responseReceived(QByteArray response);
    /**
     * @brief
     *
     */
    void portConnectionErrorSignalReceived();

private:
    AcquisitionServer acquisitionServer; /**< TODO: describe */
    Graph graph; /**< TODO: describe */

    deque<DataSet> buffer; /**< TODO: describe */
    vector<int> channelGains; /**< TODO: describe */

    Logger logFile; /**< TODO: describe */

    unsigned int bufferSize; /**< TODO: describe */

    bool cascadeMode, firstRun; /**< TODO: describe */
    int channelCommandIndex; /**< TODO: describe */
    ChannelTerminal channelCommandTerminal; /**< TODO: describe */

    QByteArray activateChannelsCommands, deactivateChannelsCommands, testSignalCommands, sampleRateCommands; /**< TODO: describe */
    QVector<QByteArray> channelConfigurationCommands, commandsBuffer; /**< TODO: describe */

    QTimer ticker, impedanceTicker; /**< TODO: describe */

    Chebyshev3035 bandPassFilter; /**< TODO: describe */
};

#endif // SYSTEM_H
