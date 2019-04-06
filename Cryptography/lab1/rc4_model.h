#ifndef RC4_MODEL_H
#define RC4_MODEL_H

#include "QObject"
#include "base_cryptomodel.h"
#include <fstream>

class RC4Model: public BaseCryptoModel
{
    Q_OBJECT
private:
    uint8_t _s[256];
    int _i;
    int _j;
    QString _key;
private:
    uint8_t kword();
    void initKey(const QString& key);

    void begin(const QString& openFilePath, const QString& saveFilePath, const QString& key);
public:
    RC4Model();

    void setKey(const QString& key);

    void encrypt(const QString& openFilePath, const QString& saveFilePath);
    void decrypt(const QString& openFilePath, const QString& saveFilePath);
};

#endif // RC4_MODEL_H
