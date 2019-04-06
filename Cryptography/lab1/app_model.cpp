#include "app_model.h"

AppModel::AppModel()
    :_key(""),
     _isEncrypting(true),
     _encryptingAlgorithm(EncryptingAlgorithms::RC4),    
     _cryptoModels()
{
    _cryptoModels[EncryptingAlgorithms::RC4] = new RC4Model();
    _cryptoModels[EncryptingAlgorithms::Vernam] = new VernamModel();
    _cryptoModels[EncryptingAlgorithms::DES] = new DESModel();
}

void AppModel::setAlgorithm(EncryptingAlgorithms encryptingAlgorithm)
{
    _encryptingAlgorithm = encryptingAlgorithm;
}

void AppModel::setDESMode(DESMode mode)
{
    if (_cryptoModels.contains(EncryptingAlgorithms::DES))
        ((DESModel*)_cryptoModels[EncryptingAlgorithms::DES])->setMode(mode);
}

void AppModel::setDESInitialVector(const QString &initialVector)
{
    if (_cryptoModels.contains(EncryptingAlgorithms::DES))
        ((DESModel*)_cryptoModels[EncryptingAlgorithms::DES])->setInitialVector(initialVector);
}

void AppModel::setKey(const QString &key)
{
    _key = key;
    
    auto altgorithms = _cryptoModels.keys();
    for (auto &algorithm: altgorithms)
        _cryptoModels[algorithm]->setKey(key);
}

void AppModel::setEncrypt(bool isEncrypt)
{
    _isEncrypting = isEncrypt;
}

bool AppModel::isEncrypting() const
{
    return _isEncrypting;
}

void AppModel::processFile(const QString &openFilePath, const QString &saveFilePath)
{
    if (_cryptoModels.contains(_encryptingAlgorithm))
    {
        auto cryptoModel = _cryptoModels[_encryptingAlgorithm];

        if (_isEncrypting)
            cryptoModel->encrypt(openFilePath, saveFilePath);
        else
            cryptoModel->decrypt(openFilePath, saveFilePath);
    }
    else
        throw std::runtime_error("Not overload algorithm");
}

QString AppModel::getKey() const
{
    return _key;
}

EncryptingAlgorithms AppModel::getAlgorithm() const
{
    return _encryptingAlgorithm;
}

AppModel::~AppModel()
{    
    auto keys = _cryptoModels.keys();
    for (auto key: keys)
        delete _cryptoModels[key];
}
