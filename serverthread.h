#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include <QSerialPort>

#include <QByteArray>

class ServerThread : public QThread
{
    Q_OBJECT

public:
    ServerThread(QObject *parent = 0);
    ~ServerThread();

    bool startPort(QString portName);
    void stopPort();
    void write(QByteArray data);

signals:
    void dataReceived(unsigned char data);
    void portOpened();
    void portClosed();

public slots:
    void setBaudRate(long baudRate);

protected:
    void run() override;

private:
    QMutex mutex;
    QWaitCondition condition;

    QSerialPort portBioAmp;

    bool abort;
    long baudRate;
};

#endif // SERVERTHREAD_H
