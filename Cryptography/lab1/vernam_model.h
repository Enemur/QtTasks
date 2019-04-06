#ifndef VERNAM_MODEL_H
#define VERNAM_MODEL_H

#include "QObject"
#include "base_cryptomodel.h"
#include <fstream>

class VernamModel: public BaseCryptoModel
{
    Q_OBJECT
private:
    int _i = 0;
    QString _key;
private:
    char getChar(const std::string& key);
    void begin(const QString& openFilePath, const QString& saveFilePath, const QString& key);
public:
    VernamModel();

    void setKey(const QString& key);

    void encrypt(const QString& openFilePath, const QString& saveFilePath);
    void decrypt(const QString& openFilePath, const QString& saveFilePath);
};

#endif // VERNAM_MODEL_H
