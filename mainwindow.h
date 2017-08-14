#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QResizeEvent>

#include "dataset.h"
#include "graph.h"

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
    void displayData(DataSet *data);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
