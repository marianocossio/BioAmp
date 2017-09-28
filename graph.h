#ifndef GRAPH_H
#define GRAPH_H

#include <QOpenGLWidget>
#include <QPainter>

#include <QKeyEvent>

#include <QVector>

#include "dataset.h"

#define PI 3.1415926536
#define SIGNAL_EXCURSION 5
#define SIGNAL_MAX_VALUE 0x7FFFFF

class Graph : public QOpenGLWidget
{
    Q_OBJECT
public:
    Graph(QWidget *parent = 0);
    ~Graph();

    void addData(DataSet data);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyReleaseEvent(QKeyEvent *event);

private:
    QVector<DataSet> localSignals;
    QVector<QColor> colors;

    void drawChannelNumbers();

    int numberOfActiveChannels;
    bool viewChannelNames;
};

#endif // GRAPH_H
