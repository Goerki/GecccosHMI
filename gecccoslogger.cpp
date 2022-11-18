#include "gecccoslogger.h"
#include "QDateTime"
#include <QObject>
#include <QFile>

GecccosLogger::GecccosLogger(QString logfilePath, QString logLevel)
{
    QFile logFile(logfilePath);
    debugEnabled = logLevel.toLower().contains("DEBUG");
    infoEnabled = logLevel.toLower().contains("INFO");
    errorEnabled = logLevel.toLower().contains("ERROR");

}
GecccosLogger::GecccosLogger()
{
    QFile logFile("");
    debugEnabled = false;
    infoEnabled = false;
    errorEnabled = false;

}
void GecccosLogger::logErrorMessage(QString message){
    if (errorEnabled) {
        logMessage(message, "ERROR");
    }

}

void GecccosLogger::logInfoMessage(QString message) {
    if (infoEnabled) {
        logMessage(message, "INFO");
    }

}

void GecccosLogger::logDebugMessage(QString message){
    if (debugEnabled) {
        logMessage(message, "DEBUG");
    }

}

void GecccosLogger::logMessage(QString message, QString logLevel) {
    QString line = getTimeStamp();
    line.append(" " + logLevel + ":");
    line.append(message);
    if (logFile.open(QIODevice::ReadWrite)){
        QTextStream stream(&logFile);
        stream << line << "\n";
    }

}

QString GecccosLogger::getTimeStamp(){

QDateTime current = QDateTime::currentDateTime();
return current.toString();
}

