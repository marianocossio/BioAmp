#include "logger.h"

Logger::Logger()
{

}

void Logger::setFile(string file)
{
    localFileName = file;
}

void Logger::open(ios_base::openmode mode)
{
    localFile.open(localFileName.c_str(), mode);
}

void Logger::close()
{
    localFile.close();
}

void Logger::logStart()
{
    localFile.open(localFileName.c_str());

    localFile << "<style> center {text-align:center;}</style>" << endl;

    localFile << "<h1><font face=\"verdana, arial, helvetica\">BioAmp 1.0 Log <small><font color=\"grey\">"
            << QDate::currentDate().year()
            << QDate::currentDate().month();

    if (QDate::currentDate().day() < 10)
        localFile << "0";

    localFile << QDate::currentDate().day()
            << "-";

    if (QTime::currentTime().hour() < 10)
        localFile << "0";

    localFile << QTime::currentTime().hour() << ":";

    if (QTime::currentTime().minute() < 10)
        localFile << "0";

    localFile << QTime::currentTime().minute() << ":";

    if (QTime::currentTime().second() < 10)
        localFile << "0";

    localFile << QTime::currentTime().second() << "</font></small></font></h1>" << endl << "<hr>" << endl;

    /* ----------------------------------------------------------------------------------------------------------------------- */

    localFile << "<h5>" << endl;

    localFile << "  <table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">" << endl;
    localFile << "    <tr>" << endl;
    localFile << "      <td width=\"240\">" << endl;
    localFile << "        <font size=2 face=\"verdana, arial, helvetica\"><b>Start</b></font>" << endl;
    localFile << "      </td>" << endl;
    localFile << "      <td width=\"120\">" << endl;
    localFile << "        <font size=1 color=\"grey\">";

    if (QTime::currentTime().hour() < 10)
        localFile << "0";

    localFile << QTime::currentTime().hour() << ":";

    if (QTime::currentTime().minute() < 10)
        localFile << "0";

    localFile << QTime::currentTime().minute() << ":";

    if (QTime::currentTime().second() < 10)
        localFile << "0";

    localFile << QTime::currentTime().second() << ".";

    if (QTime::currentTime().msec() < 100)
        localFile << "0";

    if (QTime::currentTime().msec() < 10)
        localFile << "00";

    localFile << QTime::currentTime().msec();

    localFile << "</font>" << endl;
    localFile << "      </td>" << endl;
    localFile << "    </tr>" << endl;
    localFile << "  </table>" << endl;
    localFile << "</h5>" << endl;

    localFile.close();
}

void Logger::logPause()
{
    if (!localFile.is_open())
        localFile.open(localFileName.c_str(), ios::app);

    localFile << "<h5>" << endl;

    localFile << "  <table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">" << endl;
    localFile << "    <tr>" << endl;
    localFile << "      <td width=\"240\">" << endl;
    localFile << "        <font size=2 face=\"verdana, arial, helvetica\"><b>Pause</b></font>" << endl;
    localFile << "      </td>" << endl;
    localFile << "      <td width=\"120\">" << endl;
    localFile << "        <font size=1 color=\"grey\">";

    if (QTime::currentTime().hour() < 10)
        localFile << "0";

    localFile << QTime::currentTime().hour() << ":";

    if (QTime::currentTime().minute() < 10)
        localFile << "0";

    localFile << QTime::currentTime().minute() << ":";

    if (QTime::currentTime().second() < 10)
        localFile << "0";

    localFile << QTime::currentTime().second() << ".";

    if (QTime::currentTime().msec() < 100)
        localFile << "0";

    if (QTime::currentTime().msec() < 10)
        localFile << "00";

    localFile << QTime::currentTime().msec();

    localFile << "</font>" << endl;
    localFile << "      </td>" << endl;
    localFile << "    </tr>" << endl;
    localFile << "  </table>" << endl;
    localFile << "</h5>" << endl;

    localFile.close();
}

void Logger::logStop()
{
    if (!localFile.is_open())
        localFile.open(localFileName.c_str(), ios::app);

    localFile << "<h5>" << endl;

    localFile << "  <table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">" << endl;
    localFile << "    <tr>" << endl;
    localFile << "      <td width=\"240\">" << endl;
    localFile << "        <font size=2 face=\"verdana, arial, helvetica\"><b>Stop</b></font>" << endl;
    localFile << "      </td>" << endl;
    localFile << "      <td width=\"120\">" << endl;
    localFile << "        <font size=1 color=\"grey\">";

    if (QTime::currentTime().hour() < 10)
        localFile << "0";

    localFile << QTime::currentTime().hour() << ":";

    if (QTime::currentTime().minute() < 10)
        localFile << "0";

    localFile << QTime::currentTime().minute() << ":";

    if (QTime::currentTime().second() < 10)
        localFile << "0";

    localFile << QTime::currentTime().second() << ".";

    if (QTime::currentTime().msec() < 100)
        localFile << "0";

    if (QTime::currentTime().msec() < 10)
        localFile << "00";

    localFile << QTime::currentTime().msec();

    localFile << "</font>" << endl;
    localFile << "      </td>" << endl;
    localFile << "    </tr>" << endl;
    localFile << "  </table>" << endl;
    localFile << "</h5>" << endl;

    localFile.close();
}

void Logger::logRestart()
{
    if (!localFile.is_open())
        localFile.open(localFileName.c_str(), ios::app);

    localFile << "<h5>" << endl;

    localFile << "  <table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">" << endl;
    localFile << "    <tr>" << endl;
    localFile << "      <td width=\"240\">" << endl;
    localFile << "        <font size=2 face=\"verdana, arial, helvetica\"><b>Restart</b></font>" << endl;
    localFile << "      </td>" << endl;
    localFile << "      <td width=\"120\">" << endl;
    localFile << "        <font size=1 color=\"grey\">";

    if (QTime::currentTime().hour() < 10)
        localFile << "0";

    localFile << QTime::currentTime().hour() << ":";

    if (QTime::currentTime().minute() < 10)
        localFile << "0";

    localFile << QTime::currentTime().minute() << ":";

    if (QTime::currentTime().second() < 10)
        localFile << "0";

    localFile << QTime::currentTime().second() << ".";

    if (QTime::currentTime().msec() < 100)
        localFile << "0";

    if (QTime::currentTime().msec() < 10)
        localFile << "00";

    localFile << QTime::currentTime().msec();

    localFile << "</font>" << endl;
    localFile << "      </td>" << endl;
    localFile << "    </tr>" << endl;
    localFile << "  </table>" << endl;
    localFile << "</h5>" << endl;

    localFile.close();
}

void Logger::logCommand(string command)
{
    if (!localFile.is_open())
        localFile.open(localFileName.c_str(), ios::app);

    localFile << "<table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">" << endl;
    localFile << "  <tr>" << endl;
    localFile << "    <td width=\"120\">" << endl;
    localFile << "      <font size=2 face=\"verdana, arial, helvetica\"><b>Command Sent</b></font>" << endl;
    localFile << "    </td>" << endl;
    localFile << "    <td width=\"120\">" << endl;

    localFile << "      <font size=2 color=\"#009933\">" << command << "</font>" << endl;

    localFile << "    </td>" << endl;
    localFile << "    <td width=\"120\">" << endl;
    localFile << "      <font size=1 color=\"grey\">";

    if (QTime::currentTime().hour() < 10)
        localFile << "0";

    localFile << QTime::currentTime().hour() << ":";

    if (QTime::currentTime().minute() < 10)
        localFile << "0";

    localFile << QTime::currentTime().minute() << ":";

    if (QTime::currentTime().second() < 10)
        localFile << "0";

    localFile << QTime::currentTime().second() << ".";

    if (QTime::currentTime().msec() < 100)
        localFile << "0";

    if (QTime::currentTime().msec() < 10)
        localFile << "00";

    localFile << QTime::currentTime().msec();

    localFile << "</font>" << endl;
    localFile << "    </td>" << endl;
    localFile << "  </tr>" << endl;
    localFile << "</table>" << endl;
}

void Logger::logResponse(QByteArray response)
{
    ofstream configFile("config.conf");

    QList<QByteArray> list = response.split(',');

    list[list.size() - 1].truncate(list[list.size() - 1].indexOf('$'));

    if (!localFile.is_open())
        localFile.open(localFileName.c_str(), ios::app);

    localFile << "</br>" << endl;

    localFile << "<table width=\"400\" cellspacing=\"1\" cellpadding=\"10\" border=\"0\" bgcolor=\"#165480\">" << endl;
    localFile << "  <tr>" << endl;
    localFile << "    <td bgcolor=\"#5FA6D7\">" << endl;
    localFile << "      <font size=2 face=\"verdana, arial, helvetica\">" << endl;

    localFile << "        <b>Response Received</b> at ";

    if (QTime::currentTime().hour() < 10)
        localFile << "0";

    localFile << QTime::currentTime().hour() << ":";

    if (QTime::currentTime().minute() < 10)
        localFile << "0";

    localFile << QTime::currentTime().minute() << ":";

    if (QTime::currentTime().second() < 10)
        localFile << "0";

    localFile << QTime::currentTime().second() << ".";

    if (QTime::currentTime().msec() < 100)
        localFile << "0";

    if (QTime::currentTime().msec() < 10)
        localFile << "00";

    localFile << QTime::currentTime().msec() << endl;

    localFile << "      </font>" << endl;
    localFile << "    </td>" << endl;
    localFile << "  </tr>" << endl;
    localFile << "  <tr>" << endl;
    localFile << "    <td bgcolor=\"#ffffcc\">" << endl;
    localFile << "      <font face=\"verdana, arial, helvetica\" size=1>" << endl;

    // ?

    localFile << "        <table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">" << endl;
    localFile << "          <tr>" << endl;
    localFile << "            <td width=\"100\">" << endl;
    localFile << "              <font face=\"verdana, arial, helvetica\" size=1>" << endl;
    localFile << "                " << list[0].mid(0, 2).toStdString() << endl;
    localFile << "              </font>" << endl;
    localFile << "            </td>" << endl;
    localFile << "          </tr>" << endl;
    localFile << "        </table>" << endl;

    localFile << "        </br>" << endl;

    //  Board ADS Registers

    localFile << "        <table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">" << endl;
    localFile << "          <tr>" << endl;
    localFile << "            <td width=\"100\">" << endl;
    localFile << "              <font face=\"verdana, arial, helvetica\" size=1>" << endl;
    localFile << "                <u>" << list[0].mid(3, 19).toStdString() << "</u>" << endl;
    localFile << "              </font>" << endl;
    localFile << "            </td>" << endl;
    localFile << "          </tr>" << endl;
    localFile << "        </table>" << endl;

    //  ADS_ID

    localFile << "        <table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">" << endl;
    localFile << "          <tr>" << endl;
    localFile << "            <td width=\"100\">" << endl;
    localFile << "              <font face=\"verdana, arial, helvetica\" size=1>" << endl;
    localFile << "                " << list[0].mid(24, 7).toStdString() << endl;
    localFile << "              </font>" << endl;
    localFile << "            </td>" << endl;
    localFile << "            <td width=\"100\">" << endl;
    localFile << "              <font face=\"verdana, arial, helvetica\" size=1 color=\"#165480\">" << endl;
    localFile << "                0x" << list[0].mid(list[0].indexOf(':') + 2).toHex().toUpper().toStdString() << endl;
    localFile << "              </font>" << endl;
    localFile << "            </td>" << endl;
    localFile << "          </tr>" << endl;
    localFile << "        </table>" << endl;

    configFile << list[0].mid(list[0].indexOf(':') + 2).toStdString();

    for (int stringIndex = 1; stringIndex < list.size(); stringIndex++)
    {
        localFile << "        <table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">" << endl;
        localFile << "          <tr>" << endl;
        localFile << "            <td width=\"100\">" << endl;
        localFile << "              <font face=\"verdana, arial, helvetica\" size=1>" << endl;
        localFile << "                " << list[stringIndex].mid(0, list[stringIndex].indexOf(':') + 1).toStdString() << endl;
        localFile << "              </font>" << endl;
        localFile << "            </td>" << endl;
        localFile << "            <td width=\"100\">" << endl;
        localFile << "              <font face=\"verdana, arial, helvetica\" size=1 color=\"#165480\">" << endl;
        localFile << "                0x" << list[stringIndex].mid(list[stringIndex].indexOf(':') + 2).toHex().toUpper().toStdString() << endl;
        localFile << "              </font>" << endl;
        localFile << "            </td>" << endl;
        localFile << "          </tr>" << endl;
        localFile << "        </table>" << endl;

        configFile << endl << list[stringIndex].mid(list[stringIndex].indexOf(':') + 2).toStdString();
    }

    localFile << "        </br>" << endl;

    localFile << "        $$$" << endl;

    localFile << "      </font>" << endl;
    localFile << "    </td>" << endl;
    localFile << "  </tr>" << endl;
    localFile << "</table>" << endl;

    localFile << "</br>" << endl;

    localFile.close();
    configFile.close();
}

void Logger::logError(string error)
{
    localFile << "<h5>" << endl;

    localFile << "  <table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">" << endl;
    localFile << "    <tr>" << endl;
    localFile << "      <td width=\"240\">" << endl;
    localFile << "        <font size=2 face=\"verdana, arial, helvetica\" color=\"red\"><b>" << error << "</b></font>" << endl;
    localFile << "      </td>" << endl;
    localFile << "      <td width=\"120\">" << endl;
    localFile << "        <font size=1 color=\"grey\">" << endl;

    if (QTime::currentTime().hour() < 10)
        localFile << "0";

    localFile << QTime::currentTime().hour() << ":";

    if (QTime::currentTime().minute() < 10)
        localFile << "0";

    localFile << QTime::currentTime().minute() << ":";

    if (QTime::currentTime().second() < 10)
        localFile << "0";

    localFile << QTime::currentTime().second() << ".";

    if (QTime::currentTime().msec() < 100)
        localFile << "0";

    if (QTime::currentTime().msec() < 10)
        localFile << "00";

    localFile << QTime::currentTime().msec();

    localFile << "</font>" << endl;
    localFile << "      </td>" << endl;
    localFile << "    </tr>" << endl;
    localFile << "  </table>" << endl;
    localFile << "</h5>" << endl;

    localFile.close();
}

bool Logger::is_open()
{
    return localFile.is_open();
}
