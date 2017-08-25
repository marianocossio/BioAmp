#include "dataset.h"

DataSet::DataSet(DataSet *parent)
{
    if (parent == 0)
    {
        int _channels = 8;
        int _flags = 6;

        dataSet.resize(_channels);
        activeChannels.resize(_channels);
        flags.resize(_flags);

        activateAllChannels();
    }

    else
        *this = *parent;
}

DataSet::~DataSet()
{

}

void DataSet::setDataOrder(int order)
{
    dataOrder = order;
}

int DataSet::getDataOrder()
{
    return dataOrder;
}

void DataSet::activateChannel(int channel)
{
    activeChannels[channel] = true;
}

void DataSet::deactivateChannel(int channel)
{
    activeChannels[channel] = false;
}

void DataSet::activateAllChannels()
{
    for (unsigned int index = 0; index < activeChannels.size(); index++)
        activeChannels[index] = true;
}

void DataSet::deactivateAllChannels()
{
    for (unsigned int index = 0; index < activeChannels.size(); index++)
        activeChannels[index] = false;
}

int &DataSet::channelData(int channel)
{
    return dataSet[channel];
}

bool DataSet::channelIsActive(int channel)
{
    return activeChannels[channel];
}

int DataSet::numberOfActiveChannels()
{
    int _nOAC = 0;

    for (unsigned int index = 0; index < activeChannels.size(); index++)
        if (activeChannels[index])
            _nOAC++;

    return _nOAC;
}

void DataSet::clearData()
{
    for (unsigned int index = 0; index < dataSet.size(); index++)
        dataSet[index] = 0;

    for (unsigned int index = 0; index < flags.size(); index++)
        flags[index] = 0;

    dataOrder = -1;
}

int &DataSet::flag(int flagNumber)
{
    return flags[flagNumber];
}
