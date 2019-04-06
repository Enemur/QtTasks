#ifndef MY_ALGORITHM_H
#define MY_ALGORITHM_H

#include "base_cryptomodel.h"
#include "des_permutations.h"
#include "fstream"
#define SUFFLE_BITS(block, table) shuffleBits(block, table, sizeof(table) / sizeof(table[0]))

class MyAlgorithm : public BaseCryptoModel
{
private:
    QVector<uint8_t> _permutations;
private:
    QVector<uint64_t> readFile(const QString& fileName, bool isEncrypting) const;
    void writeFile(const QString& fileName, const QVector<uint64_t>& blocks, bool isEncrypting) const;

    uint64_t shuffleBits(uint64_t block, const uint8_t* permatation, int countPermutations);
public:
    MyAlgorithm();

    uint64_t encryptBlock(uint64_t block);
    uint64_t decryptBlock(uint64_t block);

    void setKey(const QString& key);
    void encrypt(const QString& openFilePath, const QString& saveFilePath);
    void decrypt(const QString& openFilePath, const QString& saveFilePath);
};

#endif // MY_ALGORITHM_H
