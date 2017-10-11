#ifndef DATASET_H
#define DATASET_H

#include <vector>

#include <dataset.h>

using namespace std;

/**
 * @brief
 *
 */
class DataSet
{
public:
    /**
     * @brief
     *
     */
    enum DataType{
        DataSet_8 = 8,
        DataSet_16 = 16
    };

    /**
     * @brief
     *
     * @param type
     * @param parent
     */
    DataSet(DataType type = DataSet_8, DataSet *parent = 0);
    /**
     * @brief
     *
     */
    virtual ~DataSet();

    /**
     * @brief
     *
     * @param order
     */
    virtual void setDataOrder(int order);
    /**
     * @brief
     *
     * @return int
     */
    virtual int getDataOrder();

    /**
     * @brief
     *
     * @param channel
     */
    virtual void activateChannel(int channel);
    /**
     * @brief
     *
     * @param channel
     */
    virtual void deactivateChannel(int channel);
    /**
     * @brief
     *
     */
    virtual void activateAllChannels();
    /**
     * @brief
     *
     */
    virtual void deactivateAllChannels();

    /**
     * @brief
     *
     * @param channel
     * @return int
     */
    virtual int &channelData(int channel);
    /**
     * @brief
     *
     * @param channel
     * @return int
     */
    virtual int &channelGain(int channel);

    /**
     * @brief
     *
     * @param channel
     * @return bool
     */
    virtual bool channelIsActive(int channel);
    /**
     * @brief
     *
     * @return int
     */
    virtual int numberOfActiveChannels();

    /**
     * @brief
     *
     */
    virtual void clearData();

    /**
     * @brief
     *
     * @param flagNumber
     * @return int
     */
    virtual int &flag(int flagNumber);

    /**
     * @brief
     *
     * @return DataType
     */
    DataType getDataType();

private:
    vector<int> dataSet; /**< TODO: describe */
    vector<bool> activeChannels; /**< TODO: describe */
    vector<int> flags; /**< TODO: describe */
    vector<int> channelGains; /**< TODO: describe */
    int dataOrder; /**< TODO: describe */
};

#endif // DATASET_H
