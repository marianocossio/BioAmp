#ifndef ACQUISITIONSERVER_H
#define ACQUISITIONSERVER_H

#include <QObject>

#include "serverthread.h"
#include "dataconditioner.h"

using namespace std;

/**
 * @brief Provides basic functionality to access serial ports.
 * You can start and stop the port, and write to it. Whenever a DataSet object is received an digested, the dataReady(DataSet) signal will be emitted.
 *
 */
class AcquisitionServer : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Class Constructor. Usually no QObject *parent is needed. You can provide a parent if you want the object to be associated to some QObject, but do not expect to create an AquisitionServer object from another AquisitionServer object with this constructor.
     * This method is inherited from QObject.
     *
     * @param parent
     */
    explicit AcquisitionServer(QObject *parent = 0);
    /**
     * @brief Class Destructor.
     *
     */
    virtual ~AcquisitionServer();

    /**
     * @brief Starts the port addressed by portName. Returns true if successful, otherwise returns false.
     *
     * @param portName
     * @return bool
     */
    virtual bool startPort(QString portName);
    /**
     * @brief Closes the port.
     *
     */
    virtual void stopPort();
    /**
     * @brief Returns true is the port is active and running (receiving data, or ready to receive). Otherwise returns false.
     *
     * @return bool
     */
    virtual bool portIsActive();
    /**
     * @brief Writes provided data to the port. As for now, this method has no ways of reporting errors.
     *
     * @param data
     */
    virtual void write(QByteArray data);

    /**
     * @brief Lists all the currently available Serial Ports.
     *
     * @return QList<QString> A list containing all the availabe Serial Port addresses. You could use one of these directly as the parameter for startPort(QString portName).
     */
    virtual QList<QString> availablePorts();

signals:
    /**
     * @brief This signal is emitted whenever a DataSet data is received and digested. You should not use this method in any other ways.
     *
     * @param data Holds the value of the recently generated DataSet. You should use this with a proper SLOT that also receives a DataSet, and there you can use it.
     */
    void dataReady(DataSet data);
    /**
     * @brief Signal emitted when the port is opened (starts receiving data, or is ready to receive).
     *
     */
    void portOpened();
    /**
     * @brief Signal emitted when the port is closed.
     *
     */
    void portClosed();
    /**
     * @brief This signal is emitted when a response is received. This happens after you send a "?" QByteArray through write(QByteArray data).
     * In order for it to work properly, you should use "using namespace std;" at the beginning of your header file. With Qt version 5.8.0, this does not work with std::string.
     *
     * @param reponse Holds the response received from the port. You should use this with a proper SLOT that also receives a QByteArray, and there you can use it.
     */
    void responseReceived(QByteArray reponse);
    /**
     * @brief Signal emitted when the port connection is lost.
     *
     */
    void portConnectionError();

public slots:
    /**
     * @brief Sets the baudrate that the port will use to communicate. Its default value is 115200, so you do not need to call this method if you will use this baudrate.
     *
     * @param baudRate
     */
    virtual void setBaudRate(long baudRate);

    /**
     * @brief Activates the specified channel, sending the proper commmand to the port.
     *
     * @param channel Expected values: 0 to 15.
     */
    virtual void activateChannel(int channel);
    /**
     * @brief Deactivates the specified channel, sending the proper commmand to the port.
     *
     * @param channel Expected values: 0 to 15.
     */
    virtual void deactivateChannel(int channel);
    /**
     * @brief Activates all the available channels, sending the proper commands to the port.
     *
     */
    virtual void activateAllChannels();
    /**
     * @brief Deactivates all the available channels, sending the proper commands to the port.
     *
     */
    virtual void deactivateAllChannels();

protected:

private:
    ServerThread thread; /** Separate thread running the port. */
    DataConditioner dataConditioner; /** Object specialiced in receiving raw bytes and digesting them to DataSet. */

private slots:
    /**
     * @brief This is a private SLOT. You should not use it. Whenever called it emits the dataReady(DataSet data) SIGNAL.
     *
     * @param data It receives from a proper SIGNAL the DataSet to be emitted.
     */
    virtual void dataReadySignalReceived(DataSet data);
    /**
     * @brief This is a private SLOT. You should not use it. Whenever called it emits the portOpened() SIGNAL.
     *
     */
    virtual void portOpenedSignalReceived();
    /**
     * @brief This is a private SLOT. You should not use it. Whenever called it emits the portClosed() SIGNAL.
     *
     */
    virtual void portClosedSignalReceived();
    /**
     * @brief This is a private SLOT. You should not use it. Whenever called it emits the responseReceived(string reponse) SIGNAL.
     *
     * @param response It receives from a proper SIGNAL the std::string to be emitted.
     */
    virtual void responseSignalReceived(QByteArray response);
    /**
     * @brief This is a private SLOT. You should not use it. Whenever called it emits the portConnectionLost() SIGNAL.
     *
     */
    virtual void connectionErrorSignalReceived();
};

#endif // ACQUISITIONSERVER_H
