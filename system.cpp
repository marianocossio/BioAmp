#include "system.h"

System::System(QObject *parent) : QObject(parent)
{
    bufferSize = 512;
    buffer.resize(bufferSize);

    channelGains.resize(8);

    for (unsigned channel; channel < channelGains.size(); channel++)
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

    filterConstants.push_back({1, -13.1330890463812, 86.7784872836581, -380.154499706078, 1231.76150961663, -3126.66462411918, 6435.20098201258, -10977.1500958741, 15741.6236667157, -19148.7033440180, 19857.2374540384, -17582.4815948128, 13271.8204992033, -8497.85959163263, 4574.24465519683, -2040.67574249725, 738.164127997152, -209.179349710925, 43.8433089871770, -6.09247706997514, 0.425964099270843});
    filterConstants.push_back({0.00785946987492684, -0.104044286384076, 0.694992078450746, -3.08758847339235, 10.1799255063858, -26.3878972459921, 55.6681125194456, -97.7075026504831, 144.744094480407, -182.623439386185, 197.231038442379, -182.623439386184, 144.744094480406, -97.7075026504830, 55.6681125194456, -26.3878972459920, 10.1799255063857, -3.08758847339234, 0.694992078450744, -0.104044286384076, 0.00785946987492682});

    connect(&acquisitionServer, SIGNAL(dataReady(DataSet)), this, SLOT(receiveData(DataSet)));
    connect(&acquisitionServer, SIGNAL(responseReceived(string)), this, SLOT(responseReceived(string)));
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
            firstRun = false;

            //acquisitionServer.write("?");

            logFile.open("log.log");
        }
        else
            logFile.open("log.log", ios::app);

        logFile << "BioAmp 1.0 - Start "
                << QDate::currentDate().year()
                << QDate::currentDate().month();

        if (QDate::currentDate().day() < 10)
            logFile << "0";

        logFile << QDate::currentDate().day()
                << "-";

        if (QTime::currentTime().hour() < 10)
            logFile << "0";

        logFile << QTime::currentTime().hour() << ":";

        if (QTime::currentTime().minute() < 10)
            logFile << "0";

        logFile << QTime::currentTime().minute() << ":";

        if (QTime::currentTime().second() < 10)
            logFile << "0";

        logFile << QTime::currentTime().second() << endl;

        logFile.close();

        send("b");
    }

    return result;
}

void System::stop()
{
    if (acquisitionServer.portIsActive())
    {
        acquisitionServer.write("s");

        acquisitionServer.stopPort();

        if (!logFile.is_open())
            logFile.open("log.log", ios::app);

        logFile << "BioAmp 1.0 - Stop "
                << QDate::currentDate().year()
                << QDate::currentDate().month();

        if (QDate::currentDate().day() < 10)
            logFile << "0";

        logFile << QDate::currentDate().day()
                << "-";

        if (QTime::currentTime().hour() < 10)
            logFile << "0";

        logFile << QTime::currentTime().hour() << ":";

        if (QTime::currentTime().minute() < 10)
            logFile << "0";

        logFile << QTime::currentTime().minute() << ":";

        if (QTime::currentTime().second() < 10)
            logFile << "0";

        logFile << QTime::currentTime().second() << endl;

        logFile.close();
    }

    if (graph.isVisible())
        graph.close();
}

void System::pause()
{
    if (acquisitionServer.portIsActive())
    {
        acquisitionServer.write("s");

        acquisitionServer.stopPort();

        if (!logFile.is_open())
            logFile.open("log.log", ios::app);

        logFile << "BioAmp 1.0 - Pause "
                << QDate::currentDate().year()
                << QDate::currentDate().month();

        if (QDate::currentDate().day() < 10)
            logFile << "0";

        logFile << QDate::currentDate().day()
                << "-";

        if (QTime::currentTime().hour() < 10)
            logFile << "0";

        logFile << QTime::currentTime().hour() << ":";

        if (QTime::currentTime().minute() < 10)
            logFile << "0";

        logFile << QTime::currentTime().minute() << ":";

        if (QTime::currentTime().second() < 10)
            logFile << "0";

        logFile << QTime::currentTime().second() << endl;

        logFile.close();
    }
}

bool System::receivingData()
{
    return acquisitionServer.portIsActive();
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
        logFile.open("log.log", ios::app);
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
    int realGain;

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

        vector < double > filteredSignal, input;

        for (unsigned index = 0; index < filterConstants[0].size(); index++)
        {
            filteredSignal.push_back(0);
            input.push_back(0);
        }

        for (unsigned index = 0; index < buffer.size(); index++)
        {
            input.push_back(buffer[index].channelData(channelCommandIndex));
        }

        for (unsigned n = filterConstants[1].size(); n < input.size(); n++)
        {
            double Yn = filterConstants[1][0] * input[n];

            for (unsigned k = 1; k < filterConstants[0].size(); k++)
                Yn = Yn + (filterConstants[1][k] * input[n - k]) - (filterConstants[0][k] * filteredSignal[n - k]);

            Yn = Yn / filterConstants[0][0];

            filteredSignal.push_back(Yn);
        }

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

        if (!logFile.is_open())
            logFile.open("log.log", ios::app);

        logFile << "Command Sent: " << commandsBuffer[0].toStdString() << " - ";

        if (QTime::currentTime().hour() < 10)
            logFile << "0";

        logFile << QTime::currentTime().hour() << ":";

        if (QTime::currentTime().minute() < 10)
            logFile << "0";

        logFile << QTime::currentTime().minute() << ":";

        if (QTime::currentTime().second() < 10)
            logFile << "0";

        logFile << QTime::currentTime().second() << ".";

        if (QTime::currentTime().msec() < 100)
            logFile << "0";

        if (QTime::currentTime().msec() < 10)
            logFile << "00";

        logFile << QTime::currentTime().msec() << endl;

        commandsBuffer.pop_front();
    }

    if (commandsBuffer.size() == 0)
    {
        ticker.stop();

        logFile.close();
    }
}

void System::responseReceived(string response)
{
    if (!logFile.is_open())
        logFile.open("log.log", ios::app);

    logFile << "Response Received at ";

    if (QTime::currentTime().hour() < 10)
        logFile << "0";

    logFile << QTime::currentTime().hour() << ":";

    if (QTime::currentTime().minute() < 10)
        logFile << "0";

    logFile << QTime::currentTime().minute() << ":";

    if (QTime::currentTime().second() < 10)
        logFile << "0";

    logFile << QTime::currentTime().second() << ".";

    if (QTime::currentTime().msec() < 100)
        logFile << "0";

    if (QTime::currentTime().msec() < 10)
        logFile << "00";

    logFile << QTime::currentTime().msec() << endl;

    logFile << response << endl;

    logFile.close();
}
