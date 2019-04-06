#include "my_algorithm.h"

MyAlgorithm::MyAlgorithm()
{

}

void MyAlgorithm::setKey(const QString &key)
{
    auto sArray = key;
    auto permutation = sArray.split(",").toVector();

    if (permutation.size() != 4)
        throw std::runtime_error("Array size != 4");

    for(auto val : permutation)
        _permutations.append(val.toUInt());
}

uint64_t MyAlgorithm::encryptBlock(uint64_t block)
{
    return SUFFLE_BITS(block, DesPermutations::InitialPermutation);
}

uint64_t MyAlgorithm::decryptBlock(uint64_t block)
{
    return SUFFLE_BITS(block, DesPermutations::reverseInitialPermutation);
}

QVector<uint64_t> MyAlgorithm::readFile(const QString &fileName, bool isEncrypting) const
{

    auto openFileName = fileName.toStdString();

    std::ifstream inFile(openFileName, std::ios::in | std::ios::binary | std::ifstream::ate);

    if (!inFile.is_open())
        throw std::runtime_error("Error opening input file");

    uint64_t fileSize = inFile.tellg();
    inFile.seekg(std::ios_base::beg);
    uint64_t countBlocks = fileSize / sizeof (uint64_t);

    auto incorrectFile = ((fileSize % sizeof (uint64_t) != 0)) && !isEncrypting;
    if (incorrectFile)
        throw std::runtime_error("Incorrect file");

    QVector<uint64_t> blocks;
    uint64_t inData;
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

void MyAlgorithm::writeFile(const QString &fileName, const QVector<uint64_t> &blocks, bool isEncrypting) const
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

uint64_t MyAlgorithm::shuffleBits(uint64_t block, const uint8_t *permatation, int countPermutations)
{
    uint64_t newBlock = 0;

    for(auto i = 0; i < countPermutations; i++)
    {
        auto newBit = (block >> (permatation[i] - 1)) & 1;
        newBlock |= (newBit << i);
    }

    return newBlock;
}

void MyAlgorithm::encrypt(const QString &openFilePath, const QString &saveFilePath)
{
    auto blocks = readFile(openFilePath, true);
    for(auto & block: blocks)
        block = encryptBlock(block);
    writeFile(saveFilePath, blocks, true);
}

void MyAlgorithm::decrypt(const QString &openFilePath, const QString &saveFilePath)
{
    auto blocks = readFile(openFilePath, false);
    for(auto & block: blocks)
        block = decryptBlock(block);
    writeFile(saveFilePath, blocks, false);
}
