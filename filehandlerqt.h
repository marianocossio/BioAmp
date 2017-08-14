#ifndef FILEHANDLERQT_H
#define FILEHANDLERQT_H

#include <QFile>

#include "filehandler.h"

class FileHandlerQt : public FileHandler
{
    Q_OBJECT

public:
    FileHandlerQt();
    virtual ~FileHandlerQt();

signals:

public slots:
};

#endif // FILEHANDLERQT_H
