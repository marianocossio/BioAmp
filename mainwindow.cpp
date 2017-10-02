#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    channelsConfigurationBox = new QWidget;
    channelsConfigurationBoxLayout = new QVBoxLayout;

    channelsAdvancedConfigurationBox = new QWidget;
    channelsAdvancedConfigurationBoxLayout = new QVBoxLayout;

    availablePorts = new QActionGroup(this);
    operationModes = new QActionGroup(this);
    /*
    baudRates = new QActionGroup(this);


    QFile configurations("conf.conf");
    int formerBaudrate;

    if (configurations.open(QFile::Text | QFile::ReadOnly))
    {
        formerBaudrate = configurations.readLine().toInt();
        configurations.close();
    }

    else
        formerBaudrate = 115200;

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

    for (int index = 0; index < baudRates->actions().size(); index++)
    {
        if (baudRates->actions()[index]->text() == QString::number(formerBaudrate))
            baudRates->actions()[index]->setChecked(true);

        else
            baudRates->actions()[7]->setChecked(true);
    }


    baudRates->setEnabled(false);
    */

    allChannelsModificationEnabled = true;
    baudrate = 115200;

    channelsConfigurationBox->setLayout(channelsConfigurationBoxLayout);
    ui->channelsLayout->setWidget(channelsConfigurationBox);

    channelsAdvancedConfigurationBox->setLayout(channelsAdvancedConfigurationBoxLayout);
    ui->channelsAdvancedLayout->setWidget(channelsAdvancedConfigurationBox);

    for (int portIndex = 0; portIndex < system.availablePorts().size(); portIndex++)
    {
        ui->menu_Port->addAction(system.availablePorts()[portIndex]);
        ui->menu_Port->actions()[portIndex]->setCheckable(true);

        availablePorts->addAction(ui->menu_Port->actions()[portIndex]);
    }

    /*
    ui->menu_Port->addSeparator();
    ui->menu_Port->addMenu("&Baudrate")->addActions(baudRates->actions());
    */

    for (int modeIndex = 0; modeIndex < ui->menuOperation_Mode->actions().size(); modeIndex++)
        operationModes->addAction(ui->menuOperation_Mode->actions()[modeIndex]);

    ui->menuOperation_Mode->setEnabled(false);
    ui->testSignalsLabel->setEnabled(false);
    ui->testSignalsComboBox->setEnabled(false);
    ui->sampleRateLabel->setEnabled(false);
    ui->sampleRateComboBox->setEnabled(false);

    ui->showGraphPushButton->setToolTip("Show/Hide Graph");
    ui->connectButton->setToolTip("Connect/Disconnect BioAmp");
    ui->connectionStatusImage->setToolTip("BioAmp Connection Status");

    ui->showGraphPushButton->setIcon(QIcon(":/screen/screen.png"));
    ui->connectButton->setIcon(QIcon(":/connection/connect.png"));
    ui->connectionStatusImage->setPixmap(QPixmap(":/connection/disconnected.png").scaledToHeight(ui->connectionStatusImage->height()));

    ui->showGraphPushButton->setEnabled(false);
    ui->connectButton->setEnabled(false);
    ui->connectionStatusImage->setEnabled(false);

    setWindowTitle("BioAmp - Configuration Window");

    connect(availablePorts, SIGNAL(triggered(QAction*)), this, SLOT(selectPort(QAction*)));
    connect(operationModes, SIGNAL(triggered(QAction*)), this, SLOT(toggleCascadeMode(QAction*)));
    /*
    connect(baudRates, SIGNAL(triggered(QAction*)), this, SLOT(selectBaudRate(QAction*)));
    */
    connect(ui->sampleRateComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(selectSampleRate(QString)));
    connect(ui->testSignalsComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectTestSignal(int)));
    connect(ui->showGraphPushButton, SIGNAL(clicked()), &system, SLOT(toggleGraphVisibility()));
}

MainWindow::~MainWindow()
{
    for (int index = 0; index < channelsCheckBoxes.size(); index++)
        delete channelsCheckBoxes[index];

    for (int index = 0; index < channelsAdvancedCheckBoxes.size(); index++)
        delete channelsAdvancedCheckBoxes[index];

    delete availablePorts;
    delete operationModes;
    /*
    delete baudRates;
    */
    delete channelsConfigurationBoxLayout;
    delete channelsConfigurationBox;
    delete channelsAdvancedConfigurationBoxLayout;
    delete channelsAdvancedConfigurationBox;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    /*
    QFile configurations("conf.conf");

    if (configurations.open(QFile::Text | QFile::WriteOnly | QFile::Truncate))
    {
        for (int index; index < baudRates->actions().size(); index++)
            if (baudRates->actions()[index]->isChecked())
                configurations.write(baudRates->actions()[index]->text().toUtf8());

        configurations.close();
    }
    */

    system.stop();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->tabWidget->resize(event->size().width() - 10, event->size().height() - 35);
    ui->channelsLayout->resize(ui->tabWidget->width() - 15, ui->tabWidget->height() - 110);
    ui->channelsAdvancedLayout->resize(ui->tabWidget->width() - 15, ui->tabWidget->height() - 45);

    ui->showGraphPushButton->move(event->size().width() - 90, 5);
    ui->connectButton->move(event->size().width() - 60, 5);
    ui->connectionStatusImage->move(event->size().width() - 30, 10);

}

void MainWindow::toggleCascadeMode(QAction *operationMode)
{
    int channelsNumber;

    for (int index = 0; index < channelsCheckBoxes.size(); index++)
        delete channelsCheckBoxes[index];

    channelsCheckBoxes.clear();

    for (int index = 0; index < channelsAdvancedCheckBoxes.size(); index++)
        delete channelsAdvancedCheckBoxes[index];

    channelsAdvancedCheckBoxes.clear();

    if (operationMode->text() == "&8 Channels")
        channelsNumber = 8;
    else
        channelsNumber = 16;

    channelsCheckBoxes.push_back(new ChannelLayout("<b><u>All Channels</u></b>"));
    channelsCheckBoxes[0]->activateTestMode(false);
    channelsCheckBoxes[0]->setGain(24);
    channelsConfigurationBoxLayout->addWidget(channelsCheckBoxes[0]);

    channelsAdvancedCheckBoxes.push_back(new ChannelLayoutAdvanced("<b><u>All Channels</u></b>"));
    channelsAdvancedConfigurationBoxLayout->addWidget(channelsAdvancedCheckBoxes[0]);

    channelsAdvancedCheckBoxes[0]->setChannelNumber(-1);

    connect(channelsCheckBoxes[0], SIGNAL(channelSelected(int,bool)), this, SLOT(selectAllChannels(int,bool)));
    connect(channelsCheckBoxes[0], SIGNAL(channelGainChanged(int,int)), this, SLOT(changeAllChannelsGain(int,int)));
    connect(channelsCheckBoxes[0], SIGNAL(toTestSignalToggled(int,bool)), this, SLOT(connectAllChannelsToTest(int,bool)));
    connect(channelsCheckBoxes[0], SIGNAL(bipolarConfigurationToggled(int,bool)), this, SLOT(setAllChannelsBipolarConfiguration(int,bool)));

    connect(channelsAdvancedCheckBoxes[0], SIGNAL(connectToBIASToggled(int,bool)), this, SLOT(connectAllChannelsToBIAS(int,bool)));

    for (int index = 0; index < channelsNumber; index++)
    {
        channelsCheckBoxes.push_back(new ChannelLayout("<u>Channel " + QString::number(index + 1) + "</u>"));
        channelsAdvancedCheckBoxes.push_back(new ChannelLayoutAdvanced("<u>Channel " + QString::number(index + 1) + "</u>"));

        channelsCheckBoxes[index + 1]->setChannelNumber(index);
        channelsCheckBoxes[index + 1]->activateTestMode(false);
        channelsCheckBoxes[index + 1]->setGain(24);

        channelsAdvancedCheckBoxes[index + 1]->setChannelNumber(index);

        connect(channelsCheckBoxes[index + 1], SIGNAL(channelSelected(int,bool)), this, SLOT(activateChannel(int,bool)));
        connect(channelsCheckBoxes[index + 1], SIGNAL(channelGainChanged(int,int)), this, SLOT(setChannelGain(int,int)));
        connect(channelsCheckBoxes[index + 1], SIGNAL(toTestSignalToggled(int,bool)), this, SLOT(toTestSignalToggled(int,bool)));
        connect(channelsCheckBoxes[index + 1], SIGNAL(bipolarConfigurationToggled(int,bool)), this, SLOT(bipolarConfigurationToggled(int,bool)));

        connect(channelsAdvancedCheckBoxes[index + 1], SIGNAL(startCheckingImpedanceRequested(int,System::ChannelTerminal)), &system, SLOT(startCheckingChannelImpedance(int,System::ChannelTerminal)));
        connect(channelsAdvancedCheckBoxes[index + 1], SIGNAL(stopCheckingImpedanceRequested()), &system, SLOT(stopCheckingChannelImpedance()));
        connect(channelsAdvancedCheckBoxes[index + 1], SIGNAL(connectToBIASToggled(int,bool)), this, SLOT(BIASToggled(int,bool)));
        connect(&system, SIGNAL(impedanceCalculated(int,System::ChannelTerminal,double)), channelsAdvancedCheckBoxes[index + 1], SLOT(updateImpedanceValue(int,System::ChannelTerminal,double)));

        channelsConfigurationBoxLayout->addWidget(channelsCheckBoxes[index + 1]);
        channelsAdvancedConfigurationBoxLayout->addWidget(channelsAdvancedCheckBoxes[index + 1]);
    }

    ui->testSignalsComboBox->setCurrentIndex(0);
    ui->sampleRateComboBox->setCurrentIndex(0);

    system.activateAllChannels();
    system.flush();
}

void MainWindow::selectPort(QAction *selectedPort)
{
    /*
    for (int index = 0; index < baudRates->children().size(); index++)
        if (baudRates->actions()[index]->isChecked())
            baudrate = baudRates->actions()[index]->text().toInt();

    if (system.receivingData())
        system.stop();
    */

    if (system.start(selectedPort->text(), baudrate))
    {
        system.setSampleRate(System::at250Hz);
        system.flush();

        ui->sampleRateComboBox->setCurrentIndex(0);

        ui->menuOperation_Mode->setEnabled(true);
        ui->testSignalsLabel->setEnabled(true);
        ui->testSignalsComboBox->setEnabled(true);
        ui->sampleRateLabel->setEnabled(true);
        ui->sampleRateComboBox->setEnabled(true);

        /*
        baudRates->setEnabled(true);
        */

        ui->connectionStatusImage->setPixmap(QPixmap(":/connection/connected.png").scaledToHeight(ui->connectionStatusImage->height()));

        ui->showGraphPushButton->setEnabled(true);
        ui->connectButton->setEnabled(true);
        ui->connectionStatusImage->setEnabled(true);

        ui->action_8_Channels->trigger();
    }

    else
    {
        ui->menuOperation_Mode->setEnabled(false);
        ui->testSignalsLabel->setEnabled(false);
        ui->testSignalsComboBox->setEnabled(false);
        ui->sampleRateLabel->setEnabled(false);
        ui->sampleRateComboBox->setEnabled(false);

        /*
        baudRates->setEnabled(false);
        */

        ui->connectionStatusImage->setPixmap(QPixmap(":/connection/disconnected.png").scaledToHeight(ui->connectionStatusImage->height()));

        ui->showGraphPushButton->setEnabled(false);
        ui->connectButton->setEnabled(false);
        ui->connectionStatusImage->setEnabled(false);

        for (int index = 0; index < channelsCheckBoxes.size(); index++)
            delete channelsCheckBoxes[index];

        channelsCheckBoxes.clear();
    }
}

/*
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
        system.flush();

        ui->sampleRateComboBox->setCurrentIndex(0);

        ui->menuOperation_Mode->setEnabled(true);
        ui->testSignalsLabel->setEnabled(true);
        ui->testSignalsComboBox->setEnabled(true);
        ui->sampleRateLabel->setEnabled(true);
        ui->sampleRateComboBox->setEnabled(true);

        baudRates->setEnabled(true);

        ui->connectionStatusImage->setPixmap(QPixmap(":/connection/connected.png").scaledToHeight(ui->connectionStatusImage->height()));

        ui->showGraphPushButton->setEnabled(true);
        ui->connectButton->setEnabled(true);
        ui->connectionStatusImage->setEnabled(true);

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

        ui->connectionStatusImage->setPixmap(QPixmap(":/connection/disconnected.png").scaledToHeight(ui->connectionStatusImage->height()));

        ui->showGraphPushButton->setEnabled(false);
        ui->connectButton->setEnabled(false);
        ui->connectionStatusImage->setEnabled(false);

        for (int index = 0; index < channelsCheckBoxes.size(); index++)
            delete channelsCheckBoxes[index];

        channelsCheckBoxes.clear();
    }
}
*/

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

    system.flush();
}

void MainWindow::selectTestSignal(int testSignal)
{
    if (testSignal == 0)
    {
        for (int index = 0; index < channelsCheckBoxes.size(); index++)
        {
            channelsCheckBoxes[index]->connectToTestSignal(false);
            channelsCheckBoxes[index]->activateTestMode(false);
        }
    }

    else
    {        
        system.setTestSignal(testSignal - 1);

        channelsCheckBoxes[0]->activateTestMode(true);

        for (int index = 1; index < channelsCheckBoxes.size(); index++)
        {
            channelsCheckBoxes[index]->activateTestMode(true);

            if (channelsCheckBoxes[index]->isConnectedToTestSignal())
                system.setChannelConnectionType(index - 1, System::test);

            else
                system.setChannelConnectionType(index - 1, System::input);
        }

        system.flush();
    }
}

void MainWindow::activateChannel(int channel, bool activated)
{
    system.activateChannel(channel, activated);
    system.flush();

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

    system.flush();

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

    system.flush();

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

void MainWindow::bipolarConfigurationToggled(int channel, bool status)
{
    system.setChannelSRB2(channel, status);
    system.flush();

    allChannelsModificationEnabled = false;

    if (!status)
        channelsCheckBoxes[0]->setBipolarConfiguration(false);

    else
    {
        bool channelsDeactivated = false;

        for (int index = 1; index < channelsCheckBoxes.size(); index++)
            if (!channelsCheckBoxes[index]->isBipolarModeActivated())
                channelsDeactivated = true;

        channelsCheckBoxes[0]->setBipolarConfiguration(!channelsDeactivated);
    }

    allChannelsModificationEnabled = true;
}

void MainWindow::BIASToggled(int channel, bool status)
{
    system.connectToBIAS(channel, status);
    system.flush();

    allChannelsModificationEnabled = false;

    if (!status)
        channelsAdvancedCheckBoxes[0]->setConnectedToBIAS(false);

    else
    {
        bool channelsDeactivated = false;

        for (int index = 1; index < channelsAdvancedCheckBoxes.size(); index++)
            if (!channelsAdvancedCheckBoxes[index]->isConnectedToBIAS())
                channelsDeactivated = true;

        channelsAdvancedCheckBoxes[0]->setConnectedToBIAS(!channelsDeactivated);
    }

    allChannelsModificationEnabled = true;
}

void MainWindow::selectAllChannels(int disregarded, bool status)
{
    if (allChannelsModificationEnabled)
        for (int index = 1; index < channelsCheckBoxes.size(); index++)
            channelsCheckBoxes[index]->select(status);
}

void MainWindow::changeAllChannelsGain(int disregarded, int gain)
{
    if (allChannelsModificationEnabled)
        for (int index = 1; index < channelsCheckBoxes.size(); index++)
            channelsCheckBoxes[index]->setGain(gain);
}

void MainWindow::connectAllChannelsToTest(int disregarded, bool status)
{
    if (allChannelsModificationEnabled)
        for (int index = 1; index < channelsCheckBoxes.size(); index++)
            channelsCheckBoxes[index]->connectToTestSignal(status);
}

void MainWindow::setAllChannelsBipolarConfiguration(int disregarded, bool status)
{
    if (allChannelsModificationEnabled)
        for (int index = 1; index < channelsCheckBoxes.size(); index++)
            channelsCheckBoxes[index]->setBipolarConfiguration(status);
}

void MainWindow::connectAllChannelsToBIAS(int disregarded, bool status)
{
    if (allChannelsModificationEnabled)
        for (int index = 1; index < channelsAdvancedCheckBoxes.size(); index++)
            channelsAdvancedCheckBoxes[index]->setConnectedToBIAS(status);
}

void MainWindow::on_connectButton_clicked()
{
    if (system.receivingData())
    {
        system.pause();

        ui->connectionStatusImage->setPixmap(QPixmap(":/connection/disconnected.png").scaledToHeight(ui->connectionStatusImage->height()));
    }

    else
    {
        QString presentPort;

        /*
        for (int index = 0; index < baudRates->children().size(); index++)
            if (baudRates->actions()[index]->isChecked())
                baudrate = baudRates->actions()[index]->text().toInt();
        */

        for (int index = 0; index < availablePorts->actions().size(); index++)
            if (availablePorts->actions()[index]->isChecked())
                presentPort = availablePorts->actions()[index]->text();

        system.start(presentPort, baudrate);

        ui->connectionStatusImage->setPixmap(QPixmap(":/connection/connected.png").scaledToHeight(ui->connectionStatusImage->height()));
    }
}
