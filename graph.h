#ifndef GRAPH_H
#define GRAPH_H

#include <QOpenGLWidget>
#include <QPainter>

#include <QKeyEvent>
#include <QWheelEvent>

#include <QVector>

#include "dataset.h"

#define PI 3.1415926536
#define SIGNAL_EXCURSION 5
#define SIGNAL_MAX_VALUE 0x7FFFFF

/**
 * @brief
 *
 */
class Graph : public QOpenGLWidget
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     * @param parent
     */
    Graph(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~Graph();

    /**
     * @brief
     *
     * @param data
     */
    void addData(DataSet data);

protected:
    /**
     * @brief
     *
     */
    void initializeGL();
    /**
     * @brief
     *
     * @param w
     * @param h
     */
    void resizeGL(int w, int h);
    /**
     * @brief
     *
     */
    void paintGL();

    /**
     * @brief
     *
     * @param event
     */
    void keyReleaseEvent(QKeyEvent *event);
    /**
     * @brief
     *
     * @param event
     */
    void wheelEvent(QWheelEvent *event);

private:
    QVector<DataSet> localSignals; /**< TODO: describe */
    QVector<QColor> colors; /**< TODO: describe */

    /**
     * @brief
     *
     */
    void drawChannelNumbers();

    int numberOfActiveChannels; /**< TODO: describe */
    int graphicZoom; /**< TODO: describe */
    bool viewChannelNames; /**< TODO: describe */
};

#endif // GRAPH_H
