#ifndef CHANNELLAYOUT_H
#define CHANNELLAYOUT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>

/**
 * @brief Graphic class to be used in a QWidget. It provides all the basic configuration fields for a channel.
 *
 */
class ChannelLayout : public QWidget
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
     *   ChannelLayout *channel1;
     *
     *   channelsConfigurationBoxLayout = new QVBoxLayout(this);
     *   channel1 = new ChannelLayout("<u>Channel " + QString::number(1) + "</u>");
     *
     *   channel1->setChannelNumber(0);                  // First Channel.
     *   channel1->activateTestMode(false);
     *   channel1->setGain(24);                          // Sets the Gain ComboBox to display 24. Triggers channelGainChanged(int channel, int gain) signal.
     *
     *   channelsConfigurationBoxLayout->addWidget(channel1);
     * \endcode
     *
     * @param displayedText The text to be displayed as a title for the channel. Could be the channel name.
     * @param parent The QWidget that contains this object.
     */
    explicit ChannelLayout(QString displayedText, QWidget *parent = 0);
    /**
     * @brief Class destructor. You should call delete on this object before you delete the parent (or containing) Qwidget.
     *
     */
    ~ChannelLayout();

    /**
     * @brief Sets the channel number for the current channel. This is needed for several control logic algorithms within the
     * class, so you should call this method if possible.
     *
     * @param number The identification number of the channel, in case you have more than one channel. Defaults to 0.
     */
    void setChannelNumber(int number);
    /**
     * @brief Returns true if the channel is activated, otherwise returns false. This is from a graphic point of view;
     * you should add the proper logic to ensure that the channel is actually activated when you activate the graphic representation of it.
     *
     * See also select(bool status), channelSelected(int channel, bool status).
     *
     * @return bool
     */
    bool isActivated();
    /**
     * @brief Returns true if the channel is connected to a Test Signal, otherwise returns false. This is from a graphic
     * point of view; you should add the proper logic to ensure that the channel is actually connected to a Test Signal
     * when you set the graphic representation of it as connected.
     *
     * See also connectToTestSignal(bool connect), toTestSignalToggled(int channel, bool status).
     *
     * @return bool
     */
    bool isConnectedToTestSignal();
    /**
     * @brief Returns true if the channel is connected to Signal Reference, otherwise returns false. This is from a graphic point of
     * view; you should add the proper logic to ensure that the channel is actually connected to Signal Reference when you set the
     * graphic representation of it as connected.
     *
     * See also setBipolarConfiguration(bool set), bipolarConfigurationToggled(int channel, bool status).
     *
     * @return bool
     */
    bool isBipolarModeActivated();
    /**
     * @brief Returns the value of channel gain. This is from a graphic point of view; you should add the proper logic to
     * ensure that the channel has this gain value actually set, when you set the graphic representation of it.
     *
     * See also setGain(int gain), channelGainChanged(int channel, int gain).
     *
     * @return int Channel gain. Expected values: 1, 2, 4, 6, 8, 16, 24.
     */
    int channelGain();
    /**
     * @brief This method should only be called when you have a generic ChannelLayout that commands the behaviour of several
     * actual channels, and thus does not represent a channel itself.
     *
     * Use example:
     * \code{.cpp}
     *   QVBoxLayout *channelsConfigurationBoxLayout;
     *   ChannelLayout *channel1;
     *
     *   channelsConfigurationBoxLayout = new QVBoxLayout(this);
     *   channel1 = new ChannelLayout("<u>Channel " + QString::number(1) + "</u>");
     *
     *   channel1->setChannelNumber(0);                  // First Channel, used as configuration for all channels.
     *                                                   // The setChannelNumber(int number) method can be ignored in this case, as the channel number defaults to 0.
     *
     *   channel1->activateTestMode(false);
     *
     *   channel1->toggleVoidGain(true);                 // Sets the Gain ComboBox to display no text.
     *   channel1->toggleVoidGain(false);                // Sets the Gain ComboBox to display "1".
     *
     *   channel1->setGain(24);                          // Sets the Gain ComboBox to display 24.
     *                                                   // Triggers channelGainChanged(int channel, int gain) signal with gain = 24.
     *
     *   channelsConfigurationBoxLayout->addWidget(channel1);
     * \endcode
     *
     * @param voidGain Set true if the ChannelLayout should not display any Gain value. Otherwise set false.
     */
    void toggleVoidGain(bool voidGain);

signals:
    /**
     * @brief This signal is emitted when the "Activate Channel" CheckBox is toggled, or when select(bool status) is called.
     *
     * See also select(bool status), isActivated().
     *
     * @param channel Holds the channel that was activated/deactivated (\b this channel).
     * @param status Holds the new channel status.
     */
    void channelSelected(int channel, bool status);
    /**
     * @brief This signal is emitted when the "Gain" ComboBox has its value changed, or when setGain(int gain) is called.
     *
     * See also setGain(int gain), channelGain().
     *
     * @param channel Holds the channel that had its gain modified (this channel).
     * @param gain Holds the new gain value. Expected values: 1, 2, 4, 6, 8, 16, 24.
     */
    void channelGainChanged(int channel, int gain);
    /**
     * @brief This signal is emitted when the "Connect to test signal" CheckBox is toggled, or when connectToTestSignal(bool connect)
     * is called.
     *
     * See also connectToTestSignal(bool connect), isConnectedToTestSignal().
     *
     * @param channel Holds the channel connected/disconnected to Test Signal (\b this channel).
     * @param status Holds the new connection status for the channel.
     */
    void toTestSignalToggled(int channel, bool status);
    /**
     * @brief This signal is emitted when the "Bipolar Configuration" CheckBox is toggled, or when setBipolarConfiguration(bool set)
     * is called. (i.e. when the channel is connected/disconnected to  Signal Reference)
     *
     * See also setBipolarConfiguration(bool set), isBipolarModeActivated().
     *
     * @param channel Holds the channel connected/disconnected to Signal Reference (\b this channel).
     * @param status Holds the new connection status for the channel.
     */
    void bipolarConfigurationToggled(int channel, bool status);

public slots:
    /**
     * @brief If \a status is true, sets the channel as Activated. Otherwise, sets the channel to Deactivated. Triggers
     * channelSelected(int channel, bool status) SIGNAL. This is from a graphic point of view; you should add the proper logic to ensure
     * that the channel is actually activated when you set the graphic representation of it.
     * This SLOT can be used as is, or connected to a SIGNAL that also has one \b bool parameter.
     *
     * See also channelSelected(int channel, bool status), isActivated().
     *
     * @param status Receives the new status for the channel.
     */
    void select(bool status);
    /**
     * @brief Sets the gain value displayed in the "Gain" ComboBox to \a gain. Triggers channelGainChanged(int channel, int gain) SIGNAL.
     * This is from a graphic point of view; you should add the proper logic to ensure that the channel gain is actually changed
     * when you set the graphic representation of it. This SLOT can be used as is, or connected to a SIGNAL that also has
     * one \b int parameter.
     *
     * See also channelGainChanged(int channel, int gain), channelGain(), toggleVoidGain(bool voidGain).
     *
     * @param gain Receives the new value for the "Gain" ComboBox. Expected values: 1, 2, 4, 6, 8, 16, 24.
     */
    void setGain(int gain);
    /**
     * @brief If \a activate is true, enables the connection of the channel to Test Signal. Otherwise, disables the connection.
     * This SLOT can be used as is, or connected to a SIGNAL that also has one \b bool parameter.
     *
     * @param activate Receives the new status for de "Connect to test signal" CheckBox \b enable parameter.
     */
    void activateTestMode(bool activate);
    /**
     * @brief If \a connect is true, sets the channel as connected to Test Signal. Otherwise, sets the channel to disconnected from
     * Test Signal. Triggers toTestSignalToggled(int channel, bool status) SIGNAL. This is from a graphic point of view; you should
     * add the proper logic to ensure that the channel is actually connected to Test Signal when you set the graphic representation of it
     * as connected. This SLOT can be used as is, or connected to a SIGNAL that also has one \b bool parameter.
     *
     * See also toTestSignalToggled(int channel, bool status), isConnectedToTestSignal().
     *
     * @param connect Receives the new status for de "Connect to test signal" CheckBox.
     */
    void connectToTestSignal(bool connect);
    /**
     * @brief If \a set is true, sets the channel as connected to Signal Reference ("Bipolar Configuration" CheckBox). Otherwise, sets the channel
     * to disconnected from Signal Reference. Triggers bipolarConfigurationToggled(int channel, bool status) SIGNAL. This is from a graphic point of
     * view; you should add the proper logic to ensure that the channel is actually connected to Signal Reference when you set the graphic representation
     * of it as connected. This SLOT can be used as is, or connected to a SIGNAL that also has one \b bool parameter.
     *
     * See also bipolarConfigurationToggled(int channel, bool status), isBipolarModeActivated().
     *
     * @param set Receives the new status for the "Bipolar Configuration" CheckBox.
     */
    void setBipolarConfiguration(bool set);

private:
    QHBoxLayout *configLayout; /** Layout containing Labels and CheckBoxes. */
    QVBoxLayout *externalLayout; /** Most external Layout, containing configuration Layout and Channel Name. */
    QLabel channelNameLabel, channelGainLabel; /** Descriptive Shown Labels. */
    QComboBox *channelGainCombobox; /** Gain Selection ComboBox. */
    QCheckBox *channelSelectedCheckbox, *channelToTestCheckBox, *bipolarConfigurationCheckBox; /** CheckBoxes. */

    bool testMode; /** Holds whether the channel is connected to Test Signal or not, to handle the corresponding CheckBox when activated/deactivated. */
    int channelNumber; /** Holds Channel Number. */

private slots:
    /**
     * @brief This is a private SLOT. You should not use it. Whenever called it emits the channelSelected(int channel, bool status) SIGNAL.
     *
     * @param status It receives from a proper SIGNAL the new selection status.
     */
    void selectCheckboxToggled(bool status);
    /**
     * @brief This is a private SLOT. You should not use it. Whenever called it emits the channelGainChanged(int channel, int gain) SIGNAL.
     *
     * @param gain It receives from a proper SIGNAL the new gain for the channel.
     */
    void gainComboboxChanged(QString gain);
    /**
     * @brief This is a private SLOT. You should not use it. Whenever called it emits the
     * toTestSignalToggled(int channel, bool status) SIGNAL.
     *
     * @param status It receives from a proper SIGNAL the new "Connected to test signal" status.
     */
    void toTestCheckboxToggled(bool status);
    /**
     * @brief This is a private SLOT. You should not use it. Whenever called it emits the
     * bipolarConfigurationToggled(int channel, bool status) SIGNAL.
     *
     * @param status It receives from a proper SIGNAL the new "Bipolar Configuration" status.
     */
    void bipolarConfigurationCheckBoxToggled(bool status);
};

#endif // CHANNELLAYOUT_H
