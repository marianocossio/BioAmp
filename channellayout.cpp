#include "channellayout.h"

ChannelLayout::ChannelLayout(QString displayedText, QWidget *parent) : QWidget(parent)
{
    externalLayout = new QVBoxLayout(this);
    configLayout = new QHBoxLayout();
    channelGainCombobox = new QComboBox();
    channelSelectedCheckbox = new QCheckBox("Activate Channel");
    channelToTestCheckBox = new QCheckBox("Connect to test signal");
    bipolarConfigurationCheckBox = new QCheckBox("Bipolar Configuration");

    testMode = false;
    channelNumber = 0;

    channelNameLabel.setText(displayedText);
    channelGainLabel.setText("Gain");

    channelGainCombobox->addItem("1");
    channelGainCombobox->addItem("2");
    channelGainCombobox->addItem("4");
    channelGainCombobox->addItem("6");
    channelGainCombobox->addItem("8");
    channelGainCombobox->addItem("16");
    channelGainCombobox->addItem("24");

    channelSelectedCheckbox->setChecked(true);
    channelToTestCheckBox->setChecked(false);
    bipolarConfigurationCheckBox->setChecked(true);

    channelSelectedCheckbox->setFixedWidth(135);
    channelGainLabel.setFixedWidth(30);
    channelGainCombobox->setFixedWidth(60);
    channelToTestCheckBox->setFixedWidth(170);
    bipolarConfigurationCheckBox->setFixedWidth(170);

    configLayout->addWidget(channelSelectedCheckbox);
    configLayout->addSpacing(50);
    configLayout->addWidget(&channelGainLabel);
    configLayout->addWidget(channelGainCombobox);
    configLayout->addSpacing(50);
    configLayout->addWidget(channelToTestCheckBox);
    configLayout->addWidget(bipolarConfigurationCheckBox);

    externalLayout->addWidget(&channelNameLabel);
    externalLayout->addLayout(configLayout);

    setFixedWidth(820);

    connect(channelSelectedCheckbox, SIGNAL(toggled(bool)), this, SLOT(selectCheckboxToggled(bool)));
    connect(channelGainCombobox, SIGNAL(currentIndexChanged(QString)), this, SLOT(gainComboboxChanged(QString)));
    connect(channelToTestCheckBox, SIGNAL(toggled(bool)), this, SLOT(toTestCheckboxToggled(bool)));
    connect(bipolarConfigurationCheckBox, SIGNAL(toggled(bool)), this, SLOT(bipolarConfigurationCheckBoxToggled(bool)));
}

ChannelLayout::~ChannelLayout()
{
    delete channelToTestCheckBox;
    delete channelSelectedCheckbox;
    delete channelGainCombobox;
    delete configLayout;
    delete externalLayout;
}

void ChannelLayout::setChannelNumber(int number)
{
    channelNumber = number;
}

bool ChannelLayout::isActivated()
{
    return channelSelectedCheckbox->isChecked();
}

bool ChannelLayout::isConnectedToTestSignal()
{
    return channelToTestCheckBox->isChecked();
}

bool ChannelLayout::isBipolarModeActivated()
{
    return bipolarConfigurationCheckBox->isChecked();
}

int ChannelLayout::channelGain()
{
    return channelGainCombobox->currentText().toInt();
}

void ChannelLayout::toggleVoidGain(bool voidGain)
{
    if (!voidGain && (channelGainCombobox->itemText(0) == ""))
        channelGainCombobox->removeItem(0);

    if (voidGain && (channelGainCombobox->itemText(0) != ""))
    {
        channelGainCombobox->insertItem(0, "");
        channelGainCombobox->setCurrentIndex(0);
    }
}

void ChannelLayout::select(bool status)
{
    channelSelectedCheckbox->setChecked(status);
}

void ChannelLayout::setGain(int gain)
{
    switch (gain)
    {
    case 1:
        channelGainCombobox->setCurrentIndex(0);
        break;
    case 2:
        channelGainCombobox->setCurrentIndex(1);
        break;
    case 4:
        channelGainCombobox->setCurrentIndex(2);
        break;
    case 6:
        channelGainCombobox->setCurrentIndex(3);
        break;
    case 8:
        channelGainCombobox->setCurrentIndex(4);
        break;
    case 16:
        channelGainCombobox->setCurrentIndex(5);
        break;
    case 24:
        channelGainCombobox->setCurrentIndex(6);
        break;
    }
}

void ChannelLayout::activateTestMode(bool activate)
{
    if (isActivated())
        channelToTestCheckBox->setEnabled(activate);

    testMode = activate;
}

void ChannelLayout::connectToTestSignal(bool connect)
{
    channelToTestCheckBox->setChecked(connect);
}

void ChannelLayout::setBipolarConfiguration(bool set)
{
    bipolarConfigurationCheckBox->setChecked(set);
}

void ChannelLayout::selectCheckboxToggled(bool status)
{
    channelGainLabel.setEnabled(status);
    channelGainCombobox->setEnabled(status);
    if (testMode)
        channelToTestCheckBox->setEnabled(status);
    bipolarConfigurationCheckBox->setEnabled(status);

    emit channelSelected(channelNumber, status);
}

void ChannelLayout::gainComboboxChanged(QString gain)
{
    int _gain;

    if (gain == "1")
        _gain = 1;
    else if (gain == "2")
        _gain = 2;
    else if (gain == "4")
        _gain = 4;
    else if (gain == "6")
        _gain = 6;
    else if (gain == "8")
        _gain = 8;
    else if (gain == "16")
        _gain = 16;
    else
        _gain = 24;

    emit channelGainChanged(channelNumber, _gain);
}

void ChannelLayout::toTestCheckboxToggled(bool status)
{
    bipolarConfigurationCheckBox->setEnabled(!status);
    emit toTestSignalToggled(channelNumber, status);
}

void ChannelLayout::bipolarConfigurationCheckBoxToggled(bool status)
{
    emit bipolarConfigurationToggled(channelNumber, status);
}
