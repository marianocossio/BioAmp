#ifndef DATACONDITIONER_H
#define DATACONDITIONER_H

#include <QObject>
#include <QTimer>

#include <string>

#include "dataset.h"

using namespace std;

/**
 * @brief
 *
 */
class DataConditioner : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit DataConditioner(QObject *parent = 0);
    /**
     * @brief
     *
     */
    virtual ~DataConditioner();

    /**
     * @brief
     *
     * @param
     */
    void getResponse(bool get);

signals:
    /**
     * @brief
     *
     * @param data
     */
    void dataReady(DataSet data);
    /**
     * @brief
     *
     * @param resp
     */
    void responseReceived(QByteArray resp);
    /**
     * @brief
     *
     */
    void connectionError();

public slots:
    /**
     * @brief
     *
     * @param byte
     */
    virtual void newBytes(QByteArray byte);

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

protected:

private:
    int byteNumber; /**< TODO: describe */

    bool responseExpected; /**< TODO: describe */

    QByteArray response; /**< TODO: describe */
    QTimer timer;

    DataSet conditionedData; /**< TODO: describe */

private slots:
    void timerOverflow();
};

#endif // DATACONDITIONER_H
