#include "vernam_model.h"

VernamModel::VernamModel()
{

}

void VernamModel::setKey(const QString &key)
{
    _key = key;
}

void VernamModel::encrypt(const QString& openFilePath, const QString& saveFilePath)
{
    begin(openFilePath, saveFilePath, _key);
}

void VernamModel::decrypt(const QString& openFilePath, const QString& saveFilePath)
{
    begin(openFilePath, saveFilePath, _key);
}

char VernamModel::getChar(const std::string& key)
{
    if (_i == key.length())
        _i = 0;
    return key[_i++];+
}

void VernamModel::begin(const QString& openFilePath, const QString& saveFilePath, const QString& key)
{
    if (key == "")
        throw std::runtime_error("Incorrect key");
    _i = 0;

    auto openFileName = openFilePath.toStdString();
    auto saveFileName = saveFilePath.toStdString();
    
    std::ifstream inFile(openFileName, std::ios::in | std::ios::binary);
    std::ofstream outFile(saveFileName, std::ios::out | std::ios::binary);

    auto stdKey = key.toStdString();

    int8_t inData, outData;
    while (inFile.read((char*)&inData, sizeof (inData)))
    {
        outData = inData ^ getChar(stdKey);
        outFile.write((char*)&outData, sizeof (outData));
    }

    if (!inFile.is_open())
        throw std::runtime_error("Error opening input file");
    if (!outFile.is_open())
        throw std::runtime_error("Error opening output file");

    inFile.close();
    outFile.close();
}
