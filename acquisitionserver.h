#ifndef ACQUISITIONSERVER_H
#define ACQUISITIONSERVER_H

#include <QObject>

class AcquisitionServer : public QObject
{
    Q_OBJECT

public:
    explicit AcquisitionServer(QObject *parent = 0);
    virtual ~AcquisitionServer();

    virtual bool startPort(QString portName) = 0;
    virtual void stopPort() = 0;
    virtual void write(QByteArray data) = 0;

signals:
    void dataReceived(unsigned char data);
    void portOpened();
    void portClosed();

public slots:
    virtual void setBaudRate(long baudRate) = 0;

protected:

};

#endif // ACQUISITIONSERVER_H
