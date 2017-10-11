#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include <QSerialPort>
#include <QSerialPortInfo>

#include <QByteArray>
#include <QList>

/**
 * @brief
 *
 */
class ServerThread : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    ServerThread(QObject *parent = 0);
    /**
     * @brief
     *
     */
    ~ServerThread();

    /**
     * @brief
     *
     * @param portName
     * @return bool
     */
    bool startPort(QString portName);
    /**
     * @brief
     *
     */
    void stopPort();
    /**
     * @brief
     *
     * @return bool
     */
    bool portIsActive();
    /**
     * @brief
     *
     * @param data
     */
    void write(QByteArray data);

    /**
     * @brief
     *
     * @return QList<QString>
     */
    QList<QString> availablePorts();

signals:
    /**
     * @brief
     *
     * @param data
     */
    void dataReceived(QByteArray data);
    /**
     * @brief
     *
     */
    void portOpened();
    /**
     * @brief
     *
     */
    void portClosed();
    /**
     * @brief
     *
     */
    void connectionError();

public slots:
    /**
     * @brief
     *
     * @param baudRate
     */
    void setBaudRate(long baudRate);

protected:
    /**
     * @brief
     *
     */
    void run() override;

private:
    QMutex mutex; /**< TODO: describe */
    QWaitCondition condition; /**< TODO: describe */

    QSerialPort portBioAmp; /**< TODO: describe */

    bool abort; /**< TODO: describe */
    long baudRate; /**< TODO: describe */
    int connectionAttempts; /**< TODO: describe */

private slots:
    /**
     * @brief
     *
     */
    void readData();
    /**
     * @brief
     *
     */
    void errorOccurredReceived();
};

#endif // SERVERTHREAD_H
