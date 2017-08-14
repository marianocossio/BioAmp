#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>

class FileHandler : public QObject
{
    Q_OBJECT

public:
    explicit FileHandler(QObject *parent = 0);
    virtual ~FileHandler();

signals:

public slots:
};

#endif // FILEHANDLER_H
