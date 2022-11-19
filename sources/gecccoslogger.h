#ifndef GECCCOSLOGGER_H
#define GECCCOSLOGGER_H
#include <QFile>
#include <QObject>


class GecccosLogger
{
    bool debugEnabled;
    bool errorEnabled;
    bool infoEnabled;
    QFile logFile;

public:
    GecccosLogger(QString logfile, QString logLevel);
    GecccosLogger();
    void logErrorMessage(QString message);
    void logInfoMessage(QString message);
    void logDebugMessage(QString message);

private:
    QString getTimeStamp();

    void logMessage(QString message, QString logLevel);


};

#endif // GECCCOSLOGGER_H
