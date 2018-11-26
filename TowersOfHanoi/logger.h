#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class Logger : public QObject
{
    Q_OBJECT
private:
    QList<QString> logs;

    void AppendLog(const QString &message);
public:
    QList<QString> get() {return logs;}
    Logger();

    void info(const QString &message);
    void clear();

    bool saveToFile(const QString &filePath);
signals:
    void logsChanged(const QString &message);
    void logsClear();
};

#endif // LOGGER_H
