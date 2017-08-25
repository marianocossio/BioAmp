#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    availablePorts = new QActionGroup(this);
    operationModes = new QActionGroup(this);

    activateChannelsCommands   = "!@#$%^&*QWERTYUI";
    deactivateChannelsCommands = "12345678qwertyui";

    for (int portIndex = 0; portIndex < system.availablePorts().size(); portIndex++)
    {
        ui->menu_Port->addAction(system.availablePorts()[portIndex]);
        ui->menu_Port->actions()[portIndex]->setCheckable(true);

        availablePorts->addAction(ui->menu_Port->actions()[portIndex]);
    }

    for (int modeIndex = 0; modeIndex < ui->menuOperation_Mode->actions().size(); modeIndex++)
        operationModes->addAction(ui->menuOperation_Mode->actions()[modeIndex]);

    connect(availablePorts, SIGNAL(triggered(QAction*)), this, SLOT(selectPort(QAction*)));
    connect(operationModes, SIGNAL(triggered(QAction*)), this, SLOT(toggleCascadeMode(QAction*)));

    ui->action_8_Channels->trigger();
}

MainWindow::~MainWindow()
{
    for (int index = 0; index < channelsCheckBoxes.size(); index++)
        delete channelsCheckBoxes[index];

    delete availablePorts;
    delete operationModes;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    system.stop();
}

void MainWindow::configureChannels()
{
    for (int index = 0; index < channelsCheckBoxes.size(); index++)
    {
        if (channelsCheckBoxes[index]->isChecked())
        {
            system.send(activateChannelsCommands.mid(index,1));

            system.activateChannel(index);
        }

        else
        {
            system.send(deactivateChannelsCommands.mid(index,1));

            system.deactivateChannel(index);
        }
    }
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

    for (int index = 0; index < channelsNumber; index++)
    {
        channelsCheckBoxes.push_back(new QCheckBox("Channel " + QString::number(index + 1)));

        channelsCheckBoxes[index]->setChecked(true);

        system.activateAllChannels();

        ui->channelsLayout->addWidget(channelsCheckBoxes[index]);

        connect(channelsCheckBoxes[index], SIGNAL(stateChanged(int)), this, SLOT(configureChannels()));
    }
}

void MainWindow::selectPort(QAction *selectedPort)
{
    if (system.receivingData())
        system.stop();

    system.start(selectedPort->text(), 115200);
}
