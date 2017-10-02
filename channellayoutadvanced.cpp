#include "channellayoutadvanced.h"

ChannelLayoutAdvanced::ChannelLayoutAdvanced(QString displayedText, QWidget *parent) : QWidget(parent)
{
    externalLayout = new QVBoxLayout(this);
    configLayout = new QHBoxLayout();
    checkBoxesLayout = new QHBoxLayout();
    impedanceLayout = new QVBoxLayout();
    impedanceInnerSupLayout = new QHBoxLayout();
    impedanceInnerInfLayout = new QHBoxLayout();

    pTerminalImpedancePushButton = new QPushButton("Check P-Terminal Impedance");
    nTerminalImpedancePushButton = new QPushButton("Check N-Terminal Impedance");
    pTerminalImpedanceLabel = new QLabel();
    nTerminalImpedanceLabel = new QLabel();

    BIASCheckBox = new QCheckBox("Connect to BIAS");

    channelNameLabel.setText(displayedText);

    BIASCheckBox->setChecked(true);

    pTerminalImpedancePushButton->setFixedWidth(200);
    nTerminalImpedancePushButton->setFixedWidth(200);
    pTerminalImpedanceLabel->setFixedWidth(110);
    nTerminalImpedanceLabel->setFixedWidth(110);
    BIASCheckBox->setFixedWidth(150);

    impedanceInnerSupLayout->addWidget(pTerminalImpedancePushButton);
    impedanceInnerSupLayout->addWidget(pTerminalImpedanceLabel);
    impedanceInnerInfLayout->addWidget(nTerminalImpedancePushButton);
    impedanceInnerInfLayout->addWidget(nTerminalImpedanceLabel);

    impedanceLayout->addLayout(impedanceInnerSupLayout);
    impedanceLayout->addLayout(impedanceInnerInfLayout);

    checkBoxesLayout->addWidget(BIASCheckBox);

    configLayout->addLayout(impedanceLayout);
    configLayout->addLayout(checkBoxesLayout);

    externalLayout->addWidget(&channelNameLabel);
    externalLayout->addLayout(configLayout);

    setFixedWidth(500);

    connect(pTerminalImpedancePushButton, SIGNAL(pressed()), this, SLOT(pTerminalImpedancePushButtonPressed()));
    connect(pTerminalImpedancePushButton, SIGNAL(released()), this, SLOT(pTerminalImpedancePushButtonReleased()));
    connect(nTerminalImpedancePushButton, SIGNAL(pressed()), this, SLOT(nTerminalImpedancePushButtonPressed()));
    connect(nTerminalImpedancePushButton, SIGNAL(released()), this, SLOT(nTerminalImpedancePushButtonReleased()));
    connect(BIASCheckBox, SIGNAL(toggled(bool)), this, SLOT(BIASCheckBoxToggled(bool)));
}

ChannelLayoutAdvanced::~ChannelLayoutAdvanced()
{
    delete pTerminalImpedancePushButton;
    delete nTerminalImpedancePushButton;
    delete pTerminalImpedanceLabel;
    delete nTerminalImpedanceLabel;

    delete impedanceInnerSupLayout;
    delete impedanceInnerInfLayout;

    delete impedanceLayout;
    delete BIASCheckBox;

    delete checkBoxesLayout;

    delete configLayout;

    delete externalLayout;
}

void ChannelLayoutAdvanced::setChannelNumber(int number)
{
    channelNumber = number;

    if (number < 0)
    {
        pTerminalImpedancePushButton->setVisible(false);
        pTerminalImpedanceLabel->setVisible(false);
        nTerminalImpedancePushButton->setVisible(false);
        nTerminalImpedanceLabel->setVisible(false);

        impedanceInnerSupLayout->addSpacing(320);
        impedanceInnerInfLayout->addSpacing(320);
    }

    else
    {
        pTerminalImpedancePushButton->setVisible(true);
        pTerminalImpedanceLabel->setVisible(true);
        nTerminalImpedancePushButton->setVisible(true);
        nTerminalImpedanceLabel->setVisible(true);
    }
}

bool ChannelLayoutAdvanced::isConnectedToBIAS()
{
    return BIASCheckBox->isChecked();
}

void ChannelLayoutAdvanced::updateImpedanceValue(int channelNumber, System::ChannelTerminal terminal, double value)
{
    if (channelNumber == this->channelNumber)
    {
        switch (terminal)
        {
        case System::P_Terminal:
            pTerminalImpedanceLabel->setText(QString::number(value) + " [Ohm]");
            break;
        case System::N_Terminal:
            nTerminalImpedanceLabel->setText(QString::number(value) + " [Ohm]");
            break;
        default:
            break;
        }
    }
}

void ChannelLayoutAdvanced::setConnectedToBIAS(bool set)
{
    BIASCheckBox->setChecked(set);
}

void ChannelLayoutAdvanced::pTerminalImpedancePushButtonPressed()
{
    pTerminalImpedanceLabel->setText("Calculating...");

    emit startCheckingImpedanceRequested(channelNumber, System::P_Terminal);
}

void ChannelLayoutAdvanced::pTerminalImpedancePushButtonReleased()
{
    pTerminalImpedanceLabel->clear();

    emit stopCheckingImpedanceRequested();
}

void ChannelLayoutAdvanced::nTerminalImpedancePushButtonPressed()
{
    nTerminalImpedanceLabel->setText("Calculating...");

    emit startCheckingImpedanceRequested(channelNumber, System::N_Terminal);
}

void ChannelLayoutAdvanced::nTerminalImpedancePushButtonReleased()
{
    nTerminalImpedanceLabel->clear();

    emit stopCheckingImpedanceRequested();
}

void ChannelLayoutAdvanced::BIASCheckBoxToggled(bool status)
{
    emit connectToBIASToggled(channelNumber, status);
}
