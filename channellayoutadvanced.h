#ifndef CHANNELLAYOUTADVANCED_H
#define CHANNELLAYOUTADVANCED_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>

#include "system.h"

/**
 * @brief
 *
 */
class ChannelLayoutAdvanced : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Class constructor. It receives the text to be displayed as a title.
     * This method is inherited from QWidget.
     *
     * A basic configuration example could be:
     * \code{.cpp}
     *   QVBoxLayout *channelsConfigurationBoxLayout;
     *   ChannelLayoutAdvanced *channel1;
     *
     *   channelsConfigurationBoxLayout = new QVBoxLayout(this);
     *   channel1 = new ChannelLayout("<u>Channel " + QString::number(1) + "</u>");
     *
     *   channel1->setChannelNumber(0);                  // First Channel.
     *
     *   channelsConfigurationBoxLayout->addWidget(channel1);
     * \endcode
     *
     * @param displayedText The text to be displayed as a title for the channel. Could be the channel name.
     * @param parent The QWidget that contains this object.
     */
    explicit ChannelLayoutAdvanced(QString displayedText, QWidget *parent = 0);
    /**
     * @brief Class destructor. You should call delete on this object before you delete the parent (or containing) Qwidget.
     *
     */
    ~ChannelLayoutAdvanced();

    /**
     * @brief Sets the channel number for the current channel. This is needed for several control logic algorithms within the
     * class, so you should call this method if possible.
     *
     * @param number The identification number of the channel, in case you have more than one channel. Defaults to 0.
     */
    void setChannelNumber(int number);
    /**
     * @brief Returns true if the channel is connected to BIAS, otherwise returns false. This is from a graphic point of
     * view; you should add the proper logic to ensure that the channel is actually connected to BIAS when you set the
     * graphic representation of it as connected.
     *
     * See also setConnectedToBIAS(bool set), connectToBIASToggled(int channel, bool status)
     *
     * @return bool
     */
    bool isConnectedToBIAS();

signals:
    /**
     * @brief This signal is emitted when the
     *
     * @param channel
     * @param terminal
     */
    void startCheckingImpedanceRequested(int channel, System::ChannelTerminal terminal);
    /**
     * @brief
     *
     */
    void stopCheckingImpedanceRequested();
    /**
     * @brief
     *
     * @param channel
     * @param status
     */
    void connectToBIASToggled(int channel, bool status);

public slots:
    /**
     * @brief
     *
     * @param channelNumber
     * @param terminal
     * @param value
     */
    void updateImpedanceValue(int channelNumber, System::ChannelTerminal terminal, double value);
    /**
     * @brief
     *
     * @param set
     */
    void setConnectedToBIAS(bool set);

private:
    QHBoxLayout *configLayout, *impedanceInnerSupLayout, *impedanceInnerInfLayout, *checkBoxesLayout; /**< TODO: describe */
    QVBoxLayout *externalLayout, *impedanceLayout; /**< TODO: describe */
    QPushButton *pTerminalImpedancePushButton, *nTerminalImpedancePushButton; /**< TODO: describe */
    QLabel channelNameLabel, *pTerminalValueOfImpedanceLabel, *nTerminalValueOfImpedanceLabel, *pTerminalImpedanceLabel, *nTerminalImpedanceLabel; /**< TODO: describe */
    QCheckBox *BIASCheckBox; /**< TODO: describe */

    int channelNumber; /**< TODO: describe */
    bool checkingImpedance; /**< TODO: describe */

private slots:
    /**
     * @brief
     *
     */
    void pTerminalImpedancePushButtonClicked();
    /**
     * @brief
     *
     */
    void nTerminalImpedancePushButtonClicked();
    /**
     * @brief
     *
     * @param status
     */
    void BIASCheckBoxToggled(bool status);
};

#endif // CHANNELLAYOUTADVANCED_H
