#include "logger.h"

void Logger::AppendLog(const QString &message)
{
    logs.push_back(message);
    emit logsChanged(message);
}

Logger::Logger()
    :logs(QList<QString>())
{

}

void Logger::info(const QString &message)
{
    AppendLog(message);
}

void Logger::clear()
{
    logs.clear();
    emit logsClear();
}

bool Logger::saveToFile(const QString &filePath)
{
    QFile writter(filePath);

    if (writter.open(QIODevice::ReadWrite))
    {
        QTextStream stream( &writter );
        for(auto message : logs)
            stream << message << endl;
    }

    writter.close();
    return true;
}
