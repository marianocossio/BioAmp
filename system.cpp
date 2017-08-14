#include "system.h"

System::System(QObject *parent) : QObject(parent)
{
    interface = new InterfaceQt;
    acquisitionServer = new AcquisitionServerQt;
    dataConditioner = new DataConditionerStd;

    bufferSize = 256;

    connect(acquisitionServer, SIGNAL(dataReceived(unsigned char)), dataConditioner, SLOT(newByte(unsigned char)));
    connect(dataConditioner, SIGNAL(dataReady(DataSet*)), this, SLOT(receiveData(DataSet*)));
}

System::~System()
{
    acquisitionServer->stopPort();

    delete interface;
    delete acquisitionServer;
    delete dataConditioner;
}

void System::run()
{
    acquisitionServer->setBaudRate(115200);
    acquisitionServer->startPort("/dev/tnt0");
    interface->show();
}

void System::receiveData(DataSet *data)
{
    if (buffer.size() >= bufferSize)
    {
//        for (unsigned int index = 0; index < buffer.size(); index++)
//            delete buffer[index];

        buffer.clear();
    }

    buffer.push_back(new DataSetStd(data));

    interface->displayData(buffer[buffer.size() - 1]);
}
