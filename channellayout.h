#ifndef CHANNELLAYOUT_H
#define CHANNELLAYOUT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>

class ChannelLayout : public QWidget
{
    Q_OBJECT
public:
    explicit ChannelLayout(QString displayedText, QWidget *parent = 0);
    ~ChannelLayout();

    void setChannelNumber(int number);
    bool isActivated();
    bool isConnectedToTestSignal();
    bool isBipolarModeActivated();
    int channelGain();
    void toggleVoidGain(bool voidGain);

signals:
    void channelSelected(int channel, bool status);
    void channelGainChanged(int channel, int gain);
    void toTestSignalToggled(int channel, bool status);
    void bipolarConfigurationToggled(int channel, bool status);

public slots:
    void select(bool status);
    void setGain(int gain);
    void activateTestMode(bool activate);
    void connectToTestSignal(bool connect);
    void setBipolarConfiguration(bool set);

private:
    QHBoxLayout *configLayout;
    QVBoxLayout *externalLayout;
    QLabel channelNameLabel, channelGainLabel;
    QComboBox *channelGainCombobox;
    QCheckBox *channelSelectedCheckbox, *channelToTestCheckBox, *bipolarConfigurationCheckBox;

    bool testMode;
    int channelNumber;

private slots:
    void selectCheckboxToggled(bool status);
    void gainComboboxChanged(QString gain);
    void toTestCheckboxToggled(bool status);
    void bipolarConfigurationCheckBoxToggled(bool status);
};

#endif // CHANNELLAYOUT_H
