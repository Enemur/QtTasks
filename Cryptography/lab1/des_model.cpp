#include "des_model.h"

DESModel::DESModel()
    :_des(),
     _mods(),
     _mode(DESMode::ECB),
     _c0(3256346)
{
    _mods.insert(DESMode::ECB, std::bind(&DESModel::ecb, this, std::placeholders::_1, std::placeholders::_2));
    _mods.insert(DESMode::CBC, std::bind(&DESModel::cbc, this, std::placeholders::_1, std::placeholders::_2));
    _mods.insert(DESMode::CFB, std::bind(&DESModel::cfb, this, std::placeholders::_1, std::placeholders::_2));
    _mods.insert(DESMode::OFB, std::bind(&DESModel::ofb, this, std::placeholders::_1, std::placeholders::_2));
}

void DESModel::setMode(DESMode mode)
{
    _mode = mode;
}

QVector<Des::BLOCK_TYPE> DESModel::readFile(const QString &fileName, bool isEncrypting) const
{
    auto openFileName = fileName.toStdString();

    std::ifstream inFile(openFileName, std::ios::in | std::ios::binary | std::ifstream::ate);

    if (!inFile.is_open())
        throw std::runtime_error("Error opening input file");

    uint64_t fileSize = inFile.tellg();
    inFile.seekg(std::ios_base::beg);
    uint64_t countBlocks = fileSize / sizeof (Des::BLOCK_TYPE);

    auto incorrectFile = ((fileSize % sizeof (Des::BLOCK_TYPE) != 0)) && !isEncrypting;
    if (incorrectFile)
        throw std::runtime_error("Incorrect file");

    QVector<Des::BLOCK_TYPE> blocks;
    Des::BLOCK_TYPE inData;
    uint64_t countReadedBlocks = 0;

    while (inFile.read((char*)&inData, sizeof (inData)))
    {
        blocks.append(inData);
        countReadedBlocks++;

        inData = 0;
    }

    if (isEncrypting)
    {
        uint64_t countLastReadedBytes = inFile.gcount();
        inData |= ((8 - countLastReadedBytes) << 56);

        blocks.append(inData);

        if (countLastReadedBytes == 8)
            blocks.append(countLastReadedBytes);
    }
    else if (!isEncrypting && inData != 0)
        blocks.append(inData);

    return blocks;
}

void DESModel::writeFile(const QString &fileName, const QVector<Des::BLOCK_TYPE> &blocks, bool isEncrypting) const
{
    auto writeFileName = fileName.toStdString();

    std::ofstream outFile(writeFileName, std::ios::out | std::ios::binary);

    if (!outFile.is_open())
        throw std::runtime_error("Error opening output file");

    for(int i = 0; i < blocks.size(); i++)
    {
        uint64_t data = blocks[i];

        if (i == blocks.size() - 1 && !isEncrypting)
        {
            auto countBytes = 8 - (data >> 56);
            outFile.write((char*)&data, countBytes);
        }
        else
            outFile.write((char*)&data, sizeof(data));
    }
}

void DESModel::setKey(const QString &key)
{
    Des::KEY_TYPE tmpKey[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    auto size = (key.size() > 8) ? (8) : (key.size());

    auto stdKey = key.toStdString();
    for(int i = 0; i < size; i++)
        tmpKey[i] = stdKey[i] - '0';

    _key = key;

    Des::KEY_TYPE desKey = 0;
    std::memcpy(&desKey, tmpKey, 8);
    _des.setKey(desKey);
}

void DESModel::setInitialVector(const QString &vector)
{

}

void DESModel::encrypt(const QString& openFilePath, const QString& saveFilePath)
{
    if (_key == "")
        throw std::runtime_error("Incorrect key");

    auto blocks = readFile(openFilePath, true);
    if (_mods.contains(_mode))
    {
        blocks = _mods[_mode](blocks, true);
        writeFile(saveFilePath, blocks, true);
    }
    else throw std::runtime_error("DES mode method didn't implemented");
}

void DESModel::decrypt(const QString& openFilePath, const QString& saveFilePath)
{
    if (_key == "")
        throw std::runtime_error("Incorrect key");

    auto blocks = readFile(openFilePath, false);
    if (_mods.contains(_mode))
    {
        blocks = _mods[_mode](blocks, false);
        writeFile(saveFilePath, blocks, false);
    }
    else throw std::runtime_error("DES mode method didn't implemented");
}

QVector<Des::BLOCK_TYPE> DESModel::ecb(QVector<Des::BLOCK_TYPE> blocks, bool isEncrypt)
{
    for(auto& block : blocks)
        block = (isEncrypt) ? (_des.encrypt(block)) : (_des.decrypt(block));
    return blocks;
}

QVector<Des::BLOCK_TYPE> DESModel::cbc(QVector<Des::BLOCK_TYPE> blocks, bool isEncrypt)
{
    auto c = _c0;

    for(auto& block : blocks)
    {
        if (isEncrypt)
        {
            auto newBlock = c ^ block;
            block = c = _des.encrypt(newBlock);
        }
        else
        {
            auto decryptBlock = _des.decrypt(block);
            auto newC = block;
            block = c ^ decryptBlock;
            c = newC;
        }
    }
    return blocks;
}

QVector<Des::BLOCK_TYPE> DESModel::cfb(QVector<Des::BLOCK_TYPE> blocks, bool isEncrypt)
{

    auto c = _c0;

    for(auto& block : blocks)
    {
        auto newC = _des.encrypt(c);
        if (isEncrypt)
        {
            block = block ^ newC;
            c = block;
        }
        else
        {
            c = block;
            block ^= newC;
        }
    }
    return blocks;
}

QVector<Des::BLOCK_TYPE> DESModel::ofb(QVector<Des::BLOCK_TYPE> blocks, bool isEncrypt)
{
    auto c = _c0;
    for(auto& block : blocks)
    {
        auto newC = _des.encrypt(c);
        block = block ^ newC;
        c = newC;
    }
    return blocks;
}
