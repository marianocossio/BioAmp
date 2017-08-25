#include "graph.h"

Graph::Graph(QWidget *parent) : QOpenGLWidget(parent)
{
    // setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
}

void Graph::addData(DataSet data)
{
    if (localSignals.size() >= width())
        localSignals.clear();

    localSignals.push_back(data);

    update();
}

void Graph::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Graph::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0f, width() * 1.0f, 0.0f, 50.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graph::paintGL()
{
    if (localSignals.size() > 1)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        int activeChannels = localSignals[localSignals.size() - 1].numberOfActiveChannels();
        int currentChannel = 0;

        glClear(GL_DEPTH_BUFFER_BIT);

        glPushMatrix();

        glBegin(GL_LINES);

        glColor3f(0.0f, 1.0f, 0.0f);

        for (int channelIndex = 0; channelIndex < 8; channelIndex++)
            if (localSignals[localSignals.size() - 1].channelIsActive(channelIndex))
            {
                for (int signalIndex = 0; signalIndex < (localSignals.size() - 1); signalIndex++)
                {
                    glVertex3f(signalIndex * 1.0f,
                               (localSignals[signalIndex].channelData(channelIndex) / ((0x7FFFFF) / 10.0f)) + (50.0f / (activeChannels * 2.0f)) + (50.0f / (activeChannels * 1.0f)) * (currentChannel * 1.0f),
                               0.0f);
                    glVertex3f((signalIndex + 1) * 1.0f,
                               (localSignals[signalIndex + 1].channelData(channelIndex) / ((0x7FFFFF) / 10.0f)) + (50.0f / (activeChannels * 2.0f)) + (50.0f / (activeChannels * 1.0f)) * (currentChannel * 1.0f),
                               0.0f);
                }

                currentChannel++;
            }

        glEnd();

        glPopMatrix();

        glFlush();
    }
}
