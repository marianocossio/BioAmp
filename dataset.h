#ifndef DATASET_H
#define DATASET_H

#include <vector>

#include <dataset.h>

using namespace std;

class DataSet
{
public:
    DataSet(DataSet *parent = 0);
    virtual ~DataSet();

    virtual void setDataOrder(int order);
    virtual int getDataOrder();

    virtual void activateChannel(int channel);
    virtual void deactivateChannel(int channel);
    virtual void activateAllChannels();
    virtual void deactivateAllChannels();

    virtual int &channelData(int channel);

    virtual bool channelIsActive(int channel);
    virtual int numberOfActiveChannels();

    virtual void clearData();

    virtual int &flag(int flagNumber);

    enum {
        DataSet_8 = 8,
        DataSet_16 = 16
    };

private:
    vector<int> dataSet;
    vector<bool> activeChannels;
    vector<int> flags;
    int dataOrder;
};

#endif // DATASET_H
