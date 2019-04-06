#include "rc4_model.h"

RC4Model::RC4Model()
    :_i(0),
     _j(0),
     _key()
{
}

void RC4Model::setKey(const QString &key)
{
    _key = key;
}

void RC4Model::encrypt(const QString& openFilePath, const QString& saveFilePath)
{
    begin(openFilePath, saveFilePath, _key);
}

void RC4Model::decrypt(const QString& openFilePath, const QString& saveFilePath)
{
    begin(openFilePath, saveFilePath, _key);
}

uint8_t RC4Model::kword()
{
    _i = (_i + 1) % 256;
    _j = (_j + _s[_i]) % 256;

    auto tmp = _s[_i];
    _s[_i] = _s[_j];
    _s[_j] = tmp;

    char c = _s[(_s[_i] + _s[_j]) % 256];
    return c;
}

void RC4Model::initKey(const QString& key)
{
    auto tmpKey = key.toStdString();
    for (int i = 0; i < 256; i++)
        _s[i] = u_int8_t(i);

    for (int i = 0, j = 0; i < 256; i++)
    {
        j = (j + _s[i] + uint8_t(tmpKey[i % key.size()])) % 256;

        auto temp = _s[i];
        _s[i] = _s[j];
        _s[j] = temp;
    }

    _i = _j = 0;
}

void RC4Model::begin(const QString& openFilePath, const QString& saveFilePath, const QString& key)
{
    if (key == "")
        throw std::runtime_error("Incorrect key");

    auto openFileName = openFilePath.toStdString();
    auto saveFileName = saveFilePath.toStdString();
    
    std::ifstream inFile(openFileName, std::ios::in | std::ios::binary);
    std::ofstream outFile(saveFileName, std::ios::out | std::ios::binary);

    if (!inFile.is_open())
        throw std::runtime_error("Error opening input file");
    if (!outFile.is_open())
        throw std::runtime_error("Error opening output file");

    initKey(key);

    int8_t inData, outData;
    while (inFile.read((char*)&inData, sizeof (inData)))
    {
        outData = inData ^ kword();
        outFile.write((char*)&outData, sizeof (outData));
    }
    inFile.close();
    outFile.close();
}
