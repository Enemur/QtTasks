#ifndef DES_MODEL_H
#define DES_MODEL_H

#include "des.h"
#include "base_cryptomodel.h"
#include "des_mode.h"
#include "fstream"
#include "cstring"
#include "qmap.h"
#include "functional"

class DESModel: public BaseCryptoModel
{
    Q_OBJECT
private:
    DESMode _mode;
    Des _des;
    QString _key;

    Des::BLOCK_TYPE _c0;

    QMap<DESMode, std::function<QVector<Des::BLOCK_TYPE>(QVector<Des::BLOCK_TYPE>, bool isEncrypt)>> _mods;
private:
    QVector<Des::BLOCK_TYPE> readFile(const QString& fileName, bool isEncrypting) const;
    void writeFile(const QString& fileName, const QVector<Des::BLOCK_TYPE>& blocks, bool isEncrypting) const;

    QVector<Des::BLOCK_TYPE> ecb(QVector<Des::BLOCK_TYPE> blocks, bool isEncrypt);
    QVector<Des::BLOCK_TYPE> cbc(QVector<Des::BLOCK_TYPE> blocks, bool isEncrypt);
    QVector<Des::BLOCK_TYPE> cfb(QVector<Des::BLOCK_TYPE> blocks, bool isEncrypt);
    QVector<Des::BLOCK_TYPE> ofb(QVector<Des::BLOCK_TYPE> blocks, bool isEncrypt);
public:
    DESModel();

    void setMode(DESMode mode);

    void setKey(const QString& key);
    void setInitialVector(const QString& vector);


    void encrypt(const QString& openFilePath, const QString& saveFilePath);
    void decrypt(const QString& openFilePath, const QString& saveFilePath);
};

#endif // DES_MODEL_H
