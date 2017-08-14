#ifndef DATASET_H
#define DATASET_H


class DataSet
{
public:
    DataSet(DataSet *parent = 0);
    virtual ~DataSet();

    virtual void setDataOrder(int order) = 0;
    virtual int getDataOrder() = 0;

    virtual void activateChannel(int channel) = 0;
    virtual void deactivateChannel(int channel) = 0;
    virtual void activateAllChannels() = 0;
    virtual void deactivateAllChannels() = 0;

    virtual int &channelData(int channel) = 0;

    virtual bool channelIsActive(int channel) = 0;
    virtual int numberOfActiveChannels() = 0;

    virtual void clearData() = 0;

    virtual int &flag(int flagNumber) = 0;
};

#endif // DATASET_H
