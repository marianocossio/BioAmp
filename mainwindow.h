#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCloseEvent>
#include <QResizeEvent>

#include <QCheckBox>
#include <QGroupBox>
#include <QActionGroup>

#include <QFile>

#include <QDialog>

#include "system.h"
#include "channellayout.h"
#include "channellayoutadvanced.h"
#include "connectionlostdialog.h"
#include "waitforclosedialog.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~MainWindow();

public slots:
    /**
     * @brief
     *
     * @param event
     */
    void closeEvent(QCloseEvent *event);
    /**
     * @brief
     *
     * @param event
     */
    void resizeEvent(QResizeEvent *event);

protected:

private:
    Ui::MainWindow *ui; /**< TODO: describe */

    QVector<ChannelLayout*> channelsCheckBoxes; /**< TODO: describe */
    QVector<ChannelLayoutAdvanced*> channelsAdvancedCheckBoxes; /**< TODO: describe */

    QWidget *channelsConfigurationBox, *channelsAdvancedConfigurationBox; /**< TODO: describe */
    QVBoxLayout *channelsConfigurationBoxLayout, *channelsAdvancedConfigurationBoxLayout; /**< TODO: describe */

    QActionGroup *availablePorts, *operationModes;//, *baudRates; /**< TODO: describe */

    System system; /**< TODO: describe */

    QWidget *guideImageDialog; /**< TODO: describe */
    QLabel *guideImageLabel; /**< TODO: describe */

    ConnectionLostDialog *connectionLostDialog; /**< TODO: describe */
    WaitForCloseDialog *waitForCloseDialog; /**< TODO: describe */

    bool allChannelsModificationEnabled; /**< TODO: describe */
    bool closeRequested; /**< TODO: describe */
    int baudrate; /**< TODO: describe */

#if defined(Q_OS_LINUX)
    QTimer searchPortTicker;
#endif

private slots:
    /**
     * @brief
     *
     * @param operationMode
     */
    void toggleCascadeMode(QAction *operationMode);
    /**
     * @brief
     *
     * @param selectedPort
     */
    void selectPort(QAction *selectedPort);
    /*
    void selectBaudRate(QAction *selectedBaudRate);
    */
    void selectSampleRate(QString sampleRate);
    void selectTestSignal(int testSignal);
    void connectionError();
    void updatePorts();
    void updatePortsFromMenu();
    void closeWindow();

    /**
     * @brief
     *
     * @param channel
     * @param activated
     */
    void activateChannel(int channel, bool activated);
    /**
     * @brief
     *
     * @param channel
     * @param gain
     */
    void setChannelGain(int channel, int gain);
    /**
     * @brief
     *
     * @param channel
     * @param status
     */
    void toTestSignalToggled(int channel, bool status);
    /**
     * @brief
     *
     * @param channel
     * @param status
     */
    void bipolarConfigurationToggled(int channel, bool status);
    /**
     * @brief
     *
     * @param channel
     * @param status
     */
    void BIASToggled(int channel, bool status);

    /**
     * @brief
     *
     * @param disregarded
     * @param status
     */
    void selectAllChannels(int disregarded, bool status);
    /**
     * @brief
     *
     * @param disregarded
     * @param gain
     */
    void changeAllChannelsGain(int disregarded, int gain);
    /**
     * @brief
     *
     * @param disregarded
     * @param status
     */
    void connectAllChannelsToTest(int disregarded, bool status);
    /**
     * @brief
     *
     * @param disregarded
     * @param status
     */
    void setAllChannelsBipolarConfiguration(int disregarded, bool status);
    /**
     * @brief
     *
     * @param disregarded
     * @param status
     */
    void connectAllChannelsToBIAS(int disregarded, bool status);

    /**
     * @brief
     *
     */
    void on_connectButton_clicked();
    /**
     * @brief
     *
     */
    void on_actionConnection_Guide_triggered();
};

#endif // MAINWINDOW_H
