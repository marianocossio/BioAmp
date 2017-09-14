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
    int channelGain();
    void toggleVoidGain(bool voidGain);

signals:
    void channelSelected(int channel, bool status);
    void channelGainChanged(int channel, int gain);
    void toTestSignalToggled(int channel, bool status);

public slots:
    void select(bool status);
    void setGain(int gain);
    void activateTestMode(bool activate);
    void connectToTestSignal(bool connect);

private:
    QHBoxLayout *configLayout;
    QVBoxLayout *externalLayout;
    QLabel channelNameLabel, channelGainLabel;
    QComboBox *channelGainCombobox;
    QCheckBox *channelSelectedCheckbox, *channelToTestCheckBox;

    bool testMode;
    int channelNumber;

private slots:
    void selectCheckboxToggled(bool status);
    void gainComboboxChanged(QString gain);
    void toTestCheckboxToggled(bool status);
};

#endif // CHANNELLAYOUT_H
