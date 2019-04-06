#ifndef BASECRYPTOMODEL_H
#define BASECRYPTOMODEL_H

#include "QObject"

class BaseCryptoModel: public QObject
{
    Q_OBJECT
public:
    virtual void setKey(const QString& key) = 0;
    virtual void encrypt(const QString& openFilePath, const QString& saveFilePath) = 0;
    virtual void decrypt(const QString& openFilePath, const QString& saveFilePath) = 0;
};

#endif // BASECRYPTOMODEL_H
