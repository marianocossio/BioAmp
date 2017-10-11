#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QFile>

/**
 * @brief
 *
 */
class FileHandler : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit FileHandler(QObject *parent = 0);
    /**
     * @brief
     *
     */
    virtual ~FileHandler();

signals:

public slots:
};

#endif // FILEHANDLER_H
