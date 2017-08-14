#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayData(DataSet *data)
{
    ui->graph->addData(data);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->graph->move(10, 10);
    ui->graph->resize(width() - 20, height() - 20);
}
