//! [toggleVoidGain]
  QVBoxLayout *channelsConfigurationBoxLayout;
  ChannelLayout *channel1;

  channelsConfigurationBoxLayout = new QVBoxLayout(this);
  channel1 = new ChannelLayout("<u>Channel " + QString::number(1) + "</u>"));

  channel1->setChannelNumber(0);                  // First Channel.
  channel1->activateTestMode(false);
  channel1->toggleVoidGain(true);                 // Sets the Gain ComboBox to display no text.
  channel1->toggleVoidGain(false);                // Sets the Gain ComboBox to display "1".
  channel1->setGain(24);                          // Sets the Gain ComboBox to display 24. Triggers channelGainChanged(int channel, int gain) signal.

  channelsConfigurationBoxLayout->addWidget(channel1);
//! [toggleVoidGain]
