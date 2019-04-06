#ifndef APPMODEL_H
#define APPMODEL_H

#include "qobject.h"
#include "encrypting_algorithm.h"
#include "des_model.h"
#include "encrypting_algorithm.h"
#include "rc4_model.h"
#include "vernam_model.h"
#include "base_cryptomodel.h"

class AppModel: public QObject
{
    Q_OBJECT
private:
    bool _isEncrypting;
    EncryptingAlgorithms _encryptingAlgorithm;
    QString _key;
    
    QMap<EncryptingAlgorithms, BaseCryptoModel*> _cryptoModels;
public:
    AppModel();

    EncryptingAlgorithms getAlgorithm() const;
    QString getKey() const;
    bool isEncrypting() const;
    
    void processFile(const QString& openFilePath, const QString& saveFilePath);

    void setKey(const QString& key);
    void setEncrypt(bool isEncrypt);
    void setAlgorithm(EncryptingAlgorithms encryptingAlgorithm);
    
    void setDESMode(DESMode mode);
    void setDESInitialVector(const QString& initialVector);

    ~AppModel();
};

#endif // APPMODEL_H
