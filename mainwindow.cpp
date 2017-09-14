#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    channelsConfigurationBox = new QWidget;
    channelsConfigurationBoxLayout = new QVBoxLayout;

    availablePorts = new QActionGroup(this);
    operationModes = new QActionGroup(this);
    baudRates = new QActionGroup(this);

    baudRates->addAction("9600")->setCheckable(true);
    baudRates->addAction("14400")->setCheckable(true);
    baudRates->addAction("19200")->setCheckable(true);
    baudRates->addAction("28800")->setCheckable(true);
    baudRates->addAction("38400")->setCheckable(true);
    baudRates->addAction("56000")->setCheckable(true);
    baudRates->addAction("57600")->setCheckable(true);
    baudRates->addAction("115200")->setCheckable(true);
    baudRates->addAction("128000")->setCheckable(true);
    baudRates->addAction("153600")->setCheckable(true);
    baudRates->addAction("230400")->setCheckable(true);
    baudRates->addAction("256000")->setCheckable(true);
    baudRates->addAction("460800")->setCheckable(true);
    baudRates->addAction("921600")->setCheckable(true);

    baudRates->actions()[7]->setChecked(true);

    baudRates->setEnabled(false);

    channelsConfigurationBox->setLayout(channelsConfigurationBoxLayout);
    ui->channelsLayout->setWidget(channelsConfigurationBox);

    for (int portIndex = 0; portIndex < system.availablePorts().size(); portIndex++)
    {
        ui->menu_Port->addAction(system.availablePorts()[portIndex]);
        ui->menu_Port->actions()[portIndex]->setCheckable(true);

        availablePorts->addAction(ui->menu_Port->actions()[portIndex]);
    }

    ui->menu_Port->addSeparator();
    ui->menu_Port->addMenu("&Baudrate")->addActions(baudRates->actions());

    for (int modeIndex = 0; modeIndex < ui->menuOperation_Mode->actions().size(); modeIndex++)
        operationModes->addAction(ui->menuOperation_Mode->actions()[modeIndex]);

    allChannelsModificationEnabled = true;

    ui->menuOperation_Mode->setEnabled(false);
    ui->testSignalsLabel->setEnabled(false);
    ui->testSignalsComboBox->setEnabled(false);
    ui->sampleRateLabel->setEnabled(false);
    ui->sampleRateComboBox->setEnabled(false);

    connect(availablePorts, SIGNAL(triggered(QAction*)), this, SLOT(selectPort(QAction*)));
    connect(operationModes, SIGNAL(triggered(QAction*)), this, SLOT(toggleCascadeMode(QAction*)));
    connect(baudRates, SIGNAL(triggered(QAction*)), this, SLOT(selectBaudRate(QAction*)));
    connect(ui->sampleRateComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(selectSampleRate(QString)));
    connect(ui->testSignalsComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectTestSignal(int)));
}

MainWindow::~MainWindow()
{
    for (int index = 0; index < channelsCheckBoxes.size(); index++)
        delete channelsCheckBoxes[index];

    delete availablePorts;
    delete operationModes;
    delete baudRates;
    delete channelsConfigurationBoxLayout;
    delete channelsConfigurationBox;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    system.stop();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->channelsLayout->resize(event->size().width() - 20, event->size().height() - 115);

}

void MainWindow::toggleCascadeMode(QAction *operationMode)
{
    int channelsNumber;

    for (int index = 0; index < channelsCheckBoxes.size(); index++)
        delete channelsCheckBoxes[index];

    channelsCheckBoxes.clear();

    if (operationMode->text() == "&8 Channels")
        channelsNumber = 8;
    else
        channelsNumber = 16;

    channelsCheckBoxes.push_back(new ChannelLayout("<b><u>All Channels</u></b>"));
    channelsCheckBoxes[0]->activateTestMode(false);
    channelsCheckBoxes[0]->setGain(24);
    channelsConfigurationBoxLayout->addWidget(channelsCheckBoxes[0]);

    connect(channelsCheckBoxes[0], SIGNAL(channelSelected(int,bool)), this, SLOT(selectAllChannels(int,bool)));
    connect(channelsCheckBoxes[0], SIGNAL(channelGainChanged(int,int)), this, SLOT(changeAllChannelsGain(int,int)));
    connect(channelsCheckBoxes[0], SIGNAL(toTestSignalToggled(int,bool)), this, SLOT(connectAllChannelsToTest(int,bool)));

    for (int index = 0; index < channelsNumber; index++)
    {
        channelsCheckBoxes.push_back(new ChannelLayout("<u>Channel " + QString::number(index + 1) + "</u>"));

        connect(channelsCheckBoxes[index + 1], SIGNAL(channelSelected(int,bool)), this, SLOT(activateChannel(int,bool)));
        connect(channelsCheckBoxes[index + 1], SIGNAL(channelGainChanged(int,int)), this, SLOT(setChannelGain(int,int)));
        connect(channelsCheckBoxes[index + 1], SIGNAL(toTestSignalToggled(int,bool)), this, SLOT(toTestSignalToggled(int,bool)));

        channelsCheckBoxes[index + 1]->setChannelNumber(index);
        channelsCheckBoxes[index + 1]->activateTestMode(false);
        channelsCheckBoxes[index + 1]->setGain(24);

        channelsConfigurationBoxLayout->addWidget(channelsCheckBoxes[index + 1]);
    }

    system.activateAllChannels();
    system.updateChannels();
}

void MainWindow::selectPort(QAction *selectedPort)
{
    if (system.receivingData())
        system.stop();

    if (system.start(selectedPort->text(), 115200))
    {
        system.setSampleRate(System::at250Hz);
        ui->sampleRateComboBox->setCurrentIndex(0);

        ui->menuOperation_Mode->setEnabled(true);
        ui->testSignalsLabel->setEnabled(true);
        ui->testSignalsComboBox->setEnabled(true);
        ui->sampleRateLabel->setEnabled(true);
        ui->sampleRateComboBox->setEnabled(true);

        baudRates->setEnabled(true);

        ui->action_8_Channels->trigger();
    }

    else
    {
        ui->menuOperation_Mode->setEnabled(false);
        ui->testSignalsLabel->setEnabled(false);
        ui->testSignalsComboBox->setEnabled(false);
        ui->sampleRateLabel->setEnabled(false);
        ui->sampleRateComboBox->setEnabled(false);

        baudRates->setEnabled(false);

        for (int index = 0; index < channelsCheckBoxes.size(); index++)
            delete channelsCheckBoxes[index];

        channelsCheckBoxes.clear();
    }
}

void MainWindow::selectBaudRate(QAction *selectedBaudRate)
{
    QString portName;

    for (int availablePortsIndex = 0; availablePortsIndex < availablePorts->actions().size(); availablePortsIndex++)
        if (availablePorts->actions()[availablePortsIndex]->isChecked())
            portName = availablePorts->actions()[availablePortsIndex]->text();

    if (system.receivingData())
        system.stop();

    if (system.start(portName, selectedBaudRate->text().toInt()))
    {
        system.setSampleRate(System::at250Hz);
        ui->sampleRateComboBox->setCurrentIndex(0);

        ui->menuOperation_Mode->setEnabled(true);
        ui->testSignalsLabel->setEnabled(true);
        ui->testSignalsComboBox->setEnabled(true);
        ui->sampleRateLabel->setEnabled(true);
        ui->sampleRateComboBox->setEnabled(true);

        baudRates->setEnabled(true);

        ui->action_8_Channels->trigger();
    }

    else
    {
        ui->menuOperation_Mode->setEnabled(false);
        ui->testSignalsLabel->setEnabled(false);
        ui->testSignalsComboBox->setEnabled(false);
        ui->sampleRateLabel->setEnabled(false);
        ui->sampleRateComboBox->setEnabled(false);

        baudRates->setEnabled(false);

        for (int index = 0; index < channelsCheckBoxes.size(); index++)
            delete channelsCheckBoxes[index];

        channelsCheckBoxes.clear();
    }
}

void MainWindow::selectSampleRate(QString sampleRate)
{
    if (sampleRate == "250 [Hz]")
        system.setSampleRate(System::at250Hz);

    if (sampleRate == "500 [Hz]")
        system.setSampleRate(System::at500Hz);

    if (sampleRate == "1 [KHz]")
        system.setSampleRate(System::at1kHz);

    if (sampleRate == "2 [KHz]")
        system.setSampleRate(System::at2kHz);
}

void MainWindow::selectTestSignal(int testSignal)
{
    if (testSignal == 0)
    {
        for (int index = 0; index < channelsCheckBoxes.size(); index++)
            channelsCheckBoxes[index]->activateTestMode(false);
    }

    else
    {        
        system.setTestSignal(testSignal - 1);

        for (int index = 0; index < channelsCheckBoxes.size(); index++)
            channelsCheckBoxes[index]->activateTestMode(true);
    }
}

void MainWindow::activateChannel(int channel, bool activated)
{
    system.activateChannel(channel, activated);

    allChannelsModificationEnabled = false;

    if (!activated)
        channelsCheckBoxes[0]->select(false);

    else
    {
        bool channelsDeactivated = false;

        for (int index = 1; index < channelsCheckBoxes.size(); index++)
            if (!channelsCheckBoxes[index]->isActivated())
                channelsDeactivated = true;

        channelsCheckBoxes[0]->select(!channelsDeactivated);
    }

    allChannelsModificationEnabled = true;
}

void MainWindow::setChannelGain(int channel, int gain)
{
    switch (gain)
    {
    case 1:
        system.setChannelGain(channel, System::x1);
        break;
    case 2:
        system.setChannelGain(channel, System::x2);
        break;
    case 4:
        system.setChannelGain(channel, System::x4);
        break;
    case 6:
        system.setChannelGain(channel, System::x6);
        break;
    case 8:
        system.setChannelGain(channel, System::x8);
        break;
    case 16:
        system.setChannelGain(channel, System::x16);
        break;
    case 24:
        system.setChannelGain(channel, System::x24);
        break;
    }

    allChannelsModificationEnabled = false;

    if (channelsCheckBoxes.size() > 1)
    {
        bool equalGains = true;

        for (int channelGainIndex = 1; channelGainIndex < channelsCheckBoxes.size(); channelGainIndex++)
            if (channelsCheckBoxes[1]->channelGain() != channelsCheckBoxes[channelGainIndex]->channelGain())
                equalGains = false;

        if (equalGains)
        {
            channelsCheckBoxes[0]->toggleVoidGain(false);
            channelsCheckBoxes[0]->setGain(channelsCheckBoxes[1]->channelGain());
        }

        else
            channelsCheckBoxes[0]->toggleVoidGain(true);
    }

    allChannelsModificationEnabled = true;
}

void MainWindow::toTestSignalToggled(int channel, bool status)
{
    if (status)
        system.setChannelConnectionType(channel, System::test);

    else
        system.setChannelConnectionType(channel, System::input);

    allChannelsModificationEnabled = false;

    if (!status)
        channelsCheckBoxes[0]->connectToTestSignal(false);

    else
    {
        bool channelsDeactivated = false;

        for (int index = 1; index < channelsCheckBoxes.size(); index++)
            if (!channelsCheckBoxes[index]->isConnectedToTestSignal())
                channelsDeactivated = true;

        channelsCheckBoxes[0]->connectToTestSignal(!channelsDeactivated);
    }

    allChannelsModificationEnabled = true;
}

void MainWindow::selectAllChannels(int disregarded, bool status)
{
    if (allChannelsModificationEnabled)
        for (int index = 1; index < channelsCheckBoxes.size(); index++)
            channelsCheckBoxes[index]->select(status);

    system.updateChannels();
}

void MainWindow::changeAllChannelsGain(int disregarded, int gain)
{
    if (allChannelsModificationEnabled)
        for (int index = 1; index < channelsCheckBoxes.size(); index++)
            channelsCheckBoxes[index]->setGain(gain);

    system.updateChannels();
}

void MainWindow::connectAllChannelsToTest(int disregarded, bool status)
{
    if (allChannelsModificationEnabled)
        for (int index = 1; index < channelsCheckBoxes.size(); index++)
            channelsCheckBoxes[index]->connectToTestSignal(status);

    system.updateChannels();
}
