#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCloseEvent>
#include <QResizeEvent>

#include <QCheckBox>
#include <QGroupBox>
#include <QActionGroup>

#include "system.h"
#include "channellayout.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);

protected:

private:
    Ui::MainWindow *ui;

    QVector<ChannelLayout*> channelsCheckBoxes;

    QWidget *channelsConfigurationBox;
    QVBoxLayout *channelsConfigurationBoxLayout;

    QActionGroup *availablePorts, *operationModes, *baudRates;

    System system;

    bool allChannelsModificationEnabled;

private slots:
    void toggleCascadeMode(QAction *operationMode);
    void selectPort(QAction *selectedPort);
    void selectBaudRate(QAction *selectedBaudRate);
    void selectSampleRate(QString sampleRate);
    void selectTestSignal(int testSignal);

    void activateChannel(int channel, bool activated);
    void setChannelGain(int channel, int gain);
    void toTestSignalToggled(int channel, bool status);

    void selectAllChannels(int disregarded, bool status);
    void changeAllChannelsGain(int disregarded, int gain);
    void connectAllChannelsToTest(int disregarded, bool status);

};

#endif // MAINWINDOW_H
