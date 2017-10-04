#ifndef CHANNELLAYOUTADVANCED_H
#define CHANNELLAYOUTADVANCED_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>

#include "system.h"

class ChannelLayoutAdvanced : public QWidget
{
    Q_OBJECT
public:
    explicit ChannelLayoutAdvanced(QString displayedText, QWidget *parent = 0);
    ~ChannelLayoutAdvanced();

    void setChannelNumber(int number);
    bool isConnectedToBIAS();

signals:
    void startCheckingImpedanceRequested(int channel, System::ChannelTerminal terminal);
    void stopCheckingImpedanceRequested();
    void connectToBIASToggled(int channel, bool status);

public slots:
    void updateImpedanceValue(int channelNumber, System::ChannelTerminal terminal, double value);
    void setConnectedToBIAS(bool set);

private:
    QHBoxLayout *configLayout, *impedanceInnerSupLayout, *impedanceInnerInfLayout, *checkBoxesLayout;
    QVBoxLayout *externalLayout, *impedanceLayout;
    QPushButton *pTerminalImpedancePushButton, *nTerminalImpedancePushButton;
    QLabel channelNameLabel, *pTerminalValueOfImpedanceLabel, *nTerminalValueOfImpedanceLabel, *pTerminalImpedanceLabel, *nTerminalImpedanceLabel;
    QCheckBox *BIASCheckBox;

    int channelNumber;
    bool checkingImpedance;

private slots:
    void pTerminalImpedancePushButtonClicked();
    void nTerminalImpedancePushButtonClicked();
    void BIASCheckBoxToggled(bool status);
};

#endif // CHANNELLAYOUTADVANCED_H
