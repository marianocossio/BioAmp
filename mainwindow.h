#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCloseEvent>

#include <QCheckBox>
#include <QVBoxLayout>
#include <QActionGroup>

#include "system.h"

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

protected:

private:
    Ui::MainWindow *ui;

    QVector<QCheckBox*> channelsCheckBoxes;
    QByteArray activateChannelsCommands, deactivateChannelsCommands;

    QActionGroup *availablePorts, *operationModes;

    System system;

private slots:
    void configureChannels();
    void toggleCascadeMode(QAction *operationMode);
    void selectPort(QAction *selectedPort);
};

#endif // MAINWINDOW_H
