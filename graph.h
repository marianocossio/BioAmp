#ifndef GRAPH_H
#define GRAPH_H

#include <QOpenGLWidget>
#include <QVector>

#include "dataset.h"

class Graph : public QOpenGLWidget
{
    Q_OBJECT
public:
    Graph(QWidget *parent = 0);

    void addData(DataSet data);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QVector<DataSet> localSignals;
};

#endif // GRAPH_H
