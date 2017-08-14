#include "datasetstd.h"

DataSetStd::DataSetStd(DataSet *parent) : DataSet(parent)
{    
    int _channels = 8;
    int _flags = 6;

    dataSet.resize(_channels);
    activeChannels.resize(_channels);
    flags.resize(_flags);

    if (parent == 0)
    {
        dataOrder = -1;

        activateAllChannels();
    }

    else
    {
        for (unsigned int dataSetIndex = 0; dataSetIndex < dataSet.size(); dataSetIndex++)
            dataSet[dataSetIndex] = parent->channelData(dataSetIndex);

        for (unsigned int activeChannelsIndex = 0; activeChannelsIndex < activeChannels.size(); activeChannelsIndex++)
            activeChannels[activeChannelsIndex] = parent->channelIsActive(activeChannelsIndex);

        for (unsigned int flagsIndex = 0; flagsIndex < flags.size(); flagsIndex++)
            flags[flagsIndex] = parent->flag(flagsIndex);

        dataOrder = parent->getDataOrder();
    }
}

DataSetStd::~DataSetStd()
{

}

void DataSetStd::setDataOrder(int order)
{
    dataOrder = order;
}

int DataSetStd::getDataOrder()
{
    return dataOrder;
}

void DataSetStd::activateChannel(int channel)
{
    activeChannels[channel] = true;
}

void DataSetStd::deactivateChannel(int channel)
{
    activeChannels[channel] = false;
}

void DataSetStd::activateAllChannels()
{
    for (unsigned int index = 0; index < activeChannels.size(); index++)
        activeChannels[index] = true;
}

void DataSetStd::deactivateAllChannels()
{
    for (unsigned int index = 0; index < activeChannels.size(); index++)
        activeChannels[index] = false;
}

int &DataSetStd::channelData(int channel)
{
    return dataSet[channel];
}

bool DataSetStd::channelIsActive(int channel)
{
    return activeChannels[channel];
}

int DataSetStd::numberOfActiveChannels()
{
    return activeChannels.size();
}

void DataSetStd::clearData()
{
    for (unsigned int index = 0; index < dataSet.size(); index++)
        dataSet[index] = 0;

    for (unsigned int index = 0; index < flags.size(); index++)
        flags[index] = 0;

    dataOrder = -1;
}

int &DataSetStd::flag(int flagNumber)
{
    return flags[flagNumber];
}
