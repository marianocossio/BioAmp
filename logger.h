#ifndef LOGGER_H
#define LOGGER_H

#include <QDate>
#include <QTime>

#include <fstream>
#include <string>

using namespace std;

class Logger
{
public:
    Logger();

    void setFile(string file);
    void open(ios_base::openmode mode = ios::app);
    void close();
    void logStart();
    void logPause();
    void logStop();
    void logRestart();
    void logCommand(string command);
    void logResponse(QByteArray response);
    void logError(string error);

    bool is_open();

private:
    string localFileName;

    ofstream localFile;
};

#endif // LOGGER_H
