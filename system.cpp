#include "system.h"

System::System(QObject *parent) : QObject(parent)
{
    bufferSize = 512;
    buffer.resize(bufferSize);

    channelGains.resize(8);

    for (unsigned channel = 0; channel < channelGains.size(); channel++)
        channelGains[channel] = 24;

    cascadeMode = false;
    firstRun = true;

    activateChannelsCommands   = "!@#$%^&*QWERTYUI";
    deactivateChannelsCommands = "12345678qwertyui";
    testSignalCommands = "0-=p[]";
    sampleRateCommands = "ASFG";

    channelConfigurationCommands.push_back("x1060110X");
    channelConfigurationCommands.push_back("x2060110X");
    channelConfigurationCommands.push_back("x3060110X");
    channelConfigurationCommands.push_back("x4060110X");
    channelConfigurationCommands.push_back("x5060110X");
    channelConfigurationCommands.push_back("x6060110X");
    channelConfigurationCommands.push_back("x7060110X");
    channelConfigurationCommands.push_back("x8060110X");
    channelConfigurationCommands.push_back("x9060110X");
    channelConfigurationCommands.push_back("x:060110X");
    channelConfigurationCommands.push_back("x;060110X");
    channelConfigurationCommands.push_back("x<060110X");
    channelConfigurationCommands.push_back("x=060110X");
    channelConfigurationCommands.push_back("x>060110X");
    channelConfigurationCommands.push_back("x?060110X");
    channelConfigurationCommands.push_back("x@060110X");

    graph.setWindowTitle("BioAmp - Graphics");

    logFile.setFile("log.html");

    connect(&acquisitionServer, SIGNAL(dataReady(DataSet)), this, SLOT(receiveData(DataSet)));
    connect(&acquisitionServer, SIGNAL(responseReceived(QByteArray)), this, SLOT(responseReceived(QByteArray)));
    connect(&acquisitionServer, SIGNAL(portConnectionError()), this, SLOT(portConnectionErrorSignalReceived()));
    connect(&ticker, SIGNAL(timeout()), this, SLOT(sendCommands()));
    connect(&impedanceTicker, SIGNAL(timeout()), this, SLOT(getChannelImpedance()));
}

System::~System()
{
    acquisitionServer.stopPort();
}

bool System::start(QString portName, int baudRate)
{
    acquisitionServer.setBaudRate(baudRate);
    bool result = acquisitionServer.startPort(portName);

    if (result)
    {
        if (firstRun)
        {
            logFile.logStart();

            send("s");
            send("?");
        }
        else
        {
            logFile.logRestart();

            send("s");
            send("?");
        }
    }

    return result;
}

void System::stop()
{
    if (acquisitionServer.portIsActive())
    {
        acquisitionServer.stopPort();

        logFile.logStop();
    }

    if (graph.isVisible())
        graph.close();
}

void System::pause()
{
    if (acquisitionServer.portIsActive())
    {
        acquisitionServer.stopPort();

        logFile.logPause();
    }
}

bool System::receivingData()
{
    return acquisitionServer.portIsActive();
}

bool System::sendingData()
{
    return ticker.isActive();
}

void System::send(QByteArray data)
{
    commandsBuffer.push_back(data);

    flush();
}

QList<QString> System::availablePorts()
{
    return acquisitionServer.availablePorts();
}

void System::flush()
{
    if (!ticker.isActive())
        ticker.start(50);

    if (!logFile.is_open())
        logFile.open(ios::app);
}

void System::activateChannel(int channel, bool activated)
{
    if (activated)
    {
        acquisitionServer.activateChannel(channel);
        commandsBuffer.push_back(activateChannelsCommands.mid(channel, 1));
    }

    else
    {
        acquisitionServer.deactivateChannel(channel);
        commandsBuffer.push_back(deactivateChannelsCommands.mid(channel, 1));
    }
}

void System::activateAllChannels()
{
    acquisitionServer.activateAllChannels();

    if (cascadeMode)
        commandsBuffer.push_back(activateChannelsCommands);

    else
        commandsBuffer.push_back(activateChannelsCommands.mid(0, 8));
}

void System::deactivateAllChannels()
{
    acquisitionServer.deactivateAllChannels();

    if (cascadeMode)
        commandsBuffer.push_back(deactivateChannelsCommands);

    else
        commandsBuffer.push_back(deactivateChannelsCommands.mid(0, 8));
}

void System::setTestSignal(int signal)
{
    commandsBuffer.push_back(testSignalCommands.mid(signal, 1));
}

void System::setChannelConnectionType(int channel, ConnectionType type)
{
    channelConfigurationCommands[channel][4] = QByteArray::number(type)[0];
    commandsBuffer.push_back(channelConfigurationCommands[channel]);
}

void System::setChannelGain(int channel, int gain)
{
    int realGain = 1;

    channelConfigurationCommands[channel][3] = QByteArray::number(gain)[0];
    commandsBuffer.push_back(channelConfigurationCommands[channel]);

    switch (gain) {
    case 0:
        realGain = 1;
        break;
    case 1:
        realGain = 2;
        break;
    case 2:
        realGain = 4;
        break;
    case 3:
        realGain = 6;
        break;
    case 4:
        realGain = 8;
        break;
    case 5:
        realGain = 16;
        break;
    case 6:
        realGain = 24;
        break;
    default:
        break;
    }

    channelGains[channel] = realGain;
}

void System::setChannelSRB2(int channel, bool set)
{
    channelConfigurationCommands[channel][6] = QByteArray::number(set)[0];
    commandsBuffer.push_back(channelConfigurationCommands[channel]);
}

void System::setSampleRate(int sampleRate)
{
    commandsBuffer.push_back(sampleRateCommands.mid(sampleRate, 1));
}

void System::toggleGraphVisibility()
{
    if (graph.isVisible())
        graph.hide();
    else
        graph.show();
}

void System::startCheckingChannelImpedance(int channel, System::ChannelTerminal terminal)
{
    switch (terminal)
    {
    case P_Terminal:
        commandsBuffer.push_back("z" + QByteArray::number(channel + 1) + "10Z");
        break;
    case N_Terminal:
        commandsBuffer.push_back("z" + QByteArray::number(channel + 1) + "01Z");
        break;
    default:
        break;
    }

    flush();

    impedanceTicker.start(500);

    channelCommandIndex = channel;
    channelCommandTerminal = terminal;
}

void System::stopCheckingChannelImpedance()
{
    impedanceTicker.stop();

    commandsBuffer.push_back("z" + QByteArray::number(channelCommandIndex + 1) + "00Z");
    commandsBuffer.push_back(channelConfigurationCommands[channelCommandIndex]);

    flush();
}

void System::connectToBIAS(int channel, bool connect)
{
    channelConfigurationCommands[channel][5] = QByteArray::number(connect)[0];
    commandsBuffer.push_back(channelConfigurationCommands[channel]);
}

void System::getChannelImpedance()
{
    if (channelCommandIndex < buffer[0].getDataType())
    {
        double rmsSum = 0;
        double rmsValue = 0;
        double impedance = 0;

        vector<double> filteredSignal = bandPassFilter.filter(buffer, channelCommandIndex);

        for (unsigned index = (filteredSignal.size() / 2); index < filteredSignal.size(); index++)
            rmsSum += (((filteredSignal[index] / (SIGNAL_MAX_VALUE * buffer[buffer.size() - 1].channelGain(channelCommandIndex))) * 4.5)
                       * ((filteredSignal[index] / (SIGNAL_MAX_VALUE * buffer[buffer.size() - 1].channelGain(channelCommandIndex))) * 4.5));

        rmsValue = sqrt(rmsSum / (bufferSize * 1.0));

        impedance = rmsValue / (0.000000006);

        emit impedanceCalculated(channelCommandIndex, channelCommandTerminal, impedance);
    }
}

void System::receiveData(DataSet data)
{
    for (unsigned channel = 0; channel < channelGains.size(); channel++)
        data.channelGain(channel) = channelGains[channel];

    buffer.pop_front();

    graph.addData(data);

    buffer.push_back(data);
}

void System::sendCommands()
{
    if (commandsBuffer.size() > 0)
    {
        acquisitionServer.write(commandsBuffer[0]);

        logFile.logCommand(commandsBuffer[0].toStdString());

        commandsBuffer.pop_front();
    }

    if (commandsBuffer.size() == 0)
    {
        ticker.stop();

        logFile.close();

        emit lastCommandSent();
    }
}

void System::responseReceived(QByteArray response)
{
    logFile.logResponse(response);

    if (firstRun)
        firstRun = false;

    send("b");
}

void System::portConnectionErrorSignalReceived()
{
    logFile.logError("Connection Error!");

    emit portConnectionError();
}
