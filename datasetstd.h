#ifndef DATASETSTD_H
#define DATASETSTD_H

#include <vector>

#include <dataset.h>

using namespace std;

class DataSetStd : public DataSet
{
public:
    DataSetStd(DataSet *parent = 0);
    virtual ~DataSetStd();

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

private:
    vector<int> dataSet;
    vector<bool> activeChannels;
    vector<int> flags;
    int dataOrder;
};

#endif // DATASETSTD_H
