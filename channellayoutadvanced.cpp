#include "channellayoutadvanced.h"

ChannelLayoutAdvanced::ChannelLayoutAdvanced(QString displayedText, QWidget *parent) : QWidget(parent)
{
    externalLayout = new QVBoxLayout(this);
    configLayout = new QHBoxLayout();
    checkBoxesLayout = new QHBoxLayout();
    impedanceLayout = new QVBoxLayout();
    impedanceInnerSupLayout = new QHBoxLayout();
    impedanceInnerInfLayout = new QHBoxLayout();

    pTerminalImpedancePushButton = new QPushButton("Start");
    nTerminalImpedancePushButton = new QPushButton("Start");
    pTerminalImpedanceLabel = new QLabel("Check P-Terminal Impedance");
    nTerminalImpedanceLabel = new QLabel("Check N-Terminal Impedance");
    pTerminalValueOfImpedanceLabel = new QLabel();
    nTerminalValueOfImpedanceLabel = new QLabel();

    checkingImpedance = false;

    BIASCheckBox = new QCheckBox("Connect to BIAS");

    channelNameLabel.setText(displayedText);

    BIASCheckBox->setChecked(true);

    pTerminalImpedanceLabel->setFixedWidth(200);
    nTerminalImpedanceLabel->setFixedWidth(200);
    pTerminalImpedancePushButton->setFixedWidth(50);
    nTerminalImpedancePushButton->setFixedWidth(50);
    pTerminalValueOfImpedanceLabel->setFixedWidth(110);
    nTerminalValueOfImpedanceLabel->setFixedWidth(110);
    BIASCheckBox->setFixedWidth(150);

    impedanceInnerSupLayout->addWidget(pTerminalImpedanceLabel);
    impedanceInnerSupLayout->addWidget(pTerminalImpedancePushButton);
    impedanceInnerSupLayout->addWidget(pTerminalValueOfImpedanceLabel);
    impedanceInnerInfLayout->addWidget(nTerminalImpedanceLabel);
    impedanceInnerInfLayout->addWidget(nTerminalImpedancePushButton);
    impedanceInnerInfLayout->addWidget(nTerminalValueOfImpedanceLabel);

    impedanceLayout->addLayout(impedanceInnerSupLayout);
    impedanceLayout->addLayout(impedanceInnerInfLayout);

    checkBoxesLayout->addWidget(BIASCheckBox);

    configLayout->addLayout(impedanceLayout);
    configLayout->addLayout(checkBoxesLayout);

    externalLayout->addWidget(&channelNameLabel);
    externalLayout->addLayout(configLayout);

    setFixedWidth(600);

    connect(pTerminalImpedancePushButton, SIGNAL(pressed()), this, SLOT(pTerminalImpedancePushButtonClicked()));
    connect(nTerminalImpedancePushButton, SIGNAL(pressed()), this, SLOT(nTerminalImpedancePushButtonClicked()));
    connect(BIASCheckBox, SIGNAL(toggled(bool)), this, SLOT(BIASCheckBoxToggled(bool)));
}

ChannelLayoutAdvanced::~ChannelLayoutAdvanced()
{
    delete pTerminalImpedancePushButton;
    delete nTerminalImpedancePushButton;
    delete pTerminalImpedanceLabel;
    delete nTerminalImpedanceLabel;
    delete pTerminalValueOfImpedanceLabel;
    delete nTerminalValueOfImpedanceLabel;

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
        pTerminalImpedanceLabel->setVisible(false);
        pTerminalImpedancePushButton->setVisible(false);
        pTerminalValueOfImpedanceLabel->setVisible(false);
        nTerminalImpedanceLabel->setVisible(false);
        nTerminalImpedancePushButton->setVisible(false);
        nTerminalValueOfImpedanceLabel->setVisible(false);

        impedanceInnerSupLayout->addSpacing(395);
        impedanceInnerInfLayout->addSpacing(395);
    }

    else
    {
        pTerminalImpedanceLabel->setVisible(true);
        pTerminalImpedancePushButton->setVisible(true);
        pTerminalValueOfImpedanceLabel->setVisible(true);
        nTerminalImpedanceLabel->setVisible(true);
        nTerminalImpedancePushButton->setVisible(true);
        nTerminalValueOfImpedanceLabel->setVisible(true);
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
            pTerminalValueOfImpedanceLabel->setText(QString::number((int) value) + " [Ohm]");
            break;
        case System::N_Terminal:
            nTerminalValueOfImpedanceLabel->setText(QString::number((int) value) + " [Ohm]");
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

void ChannelLayoutAdvanced::pTerminalImpedancePushButtonClicked()
{
    if(!checkingImpedance)
    {
        pTerminalValueOfImpedanceLabel->setText("Calculating...");

        pTerminalImpedancePushButton->setText("Stop");

        nTerminalImpedancePushButton->setEnabled(false);

        checkingImpedance = true;

        emit startCheckingImpedanceRequested(channelNumber, System::P_Terminal);
    }
    else
    {
        pTerminalValueOfImpedanceLabel->clear();

        pTerminalImpedancePushButton->setText("Start");

        nTerminalImpedancePushButton->setEnabled(true);

        checkingImpedance = false;

        emit stopCheckingImpedanceRequested();
    }
}

void ChannelLayoutAdvanced::nTerminalImpedancePushButtonClicked()
{
    if(!checkingImpedance)
    {
        nTerminalValueOfImpedanceLabel->setText("Calculating...");

        nTerminalImpedancePushButton->setText("Stop");

        pTerminalImpedancePushButton->setEnabled(false);

        checkingImpedance = true;

        emit startCheckingImpedanceRequested(channelNumber, System::N_Terminal);
    }
    else
    {
        nTerminalValueOfImpedanceLabel->clear();

        nTerminalImpedancePushButton->setText("Start");

        pTerminalImpedancePushButton->setEnabled(true);

        checkingImpedance = false;

        emit stopCheckingImpedanceRequested();
    }
}

void ChannelLayoutAdvanced::BIASCheckBoxToggled(bool status)
{
    emit connectToBIASToggled(channelNumber, status);
}
