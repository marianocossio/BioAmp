#ifndef ACQUISITIONSERVERQT_H
#define ACQUISITIONSERVERQT_H

#include "acquisitionserver.h"
#include "serverthread.h"

class AcquisitionServerQt : public AcquisitionServer
{
    Q_OBJECT

public:
    AcquisitionServerQt();
    virtual ~AcquisitionServerQt();

    virtual bool startPort(QString portName);
    virtual void stopPort();
    virtual void write(QByteArray data);

signals:
    void dataReceived(unsigned char data);
    void portOpened();
    void portClosed();

public slots:
    virtual void setBaudRate(long baudRate);

protected:

private:
    ServerThread thread;

private slots:
    void dataReceivedSignalReceived(unsigned char data);
    void portOpenedSignalReceived();
    void portClosedSignalReceived();
};

#endif // ACQUISITIONSERVERQT_H
