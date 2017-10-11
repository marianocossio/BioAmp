#ifndef FILTER_H
#define FILTER_H

#include <QObject>

#include <deque>

#include "dataset.h"

/**
 * @brief
 *
 */
class Filter : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit Filter(QObject *parent = 0);
    /**
     * @brief
     *
     * @param parent
     */
    virtual vector < double > filter(deque < DataSet > &signal, int channel) = 0;
    /**
     * @brief
     *
     */
    virtual ~Filter();

signals:

public slots:
};

#endif // FILTER_H
