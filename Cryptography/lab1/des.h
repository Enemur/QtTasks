#ifndef DES_H
#define DES_H

#include "qobject.h"
#include "des_permutations.h"
#include "feistel_network.h"

#define SUFFLE_BITS(block, table) shuffleBits(block, table, sizeof(table) / sizeof(table[0]))

class Des : public QObject
{
    Q_OBJECT
public:
    using BLOCK_TYPE = uint64_t;
    using SUB_BLOCK_TYPE = uint32_t;
    using KEY_TYPE = uint64_t;

    const static int KEYS_COUNT = 16;
private:
    KEY_TYPE _keys[KEYS_COUNT];

    const FeistelNetwork<BLOCK_TYPE, SUB_BLOCK_TYPE, KEY_TYPE> _feistelNetwork;
private:
    void initKeys(KEY_TYPE key);
    SUB_BLOCK_TYPE f(SUB_BLOCK_TYPE subBlock, KEY_TYPE key);
    BLOCK_TYPE shuffleBits(BLOCK_TYPE block, const uint8_t* permatation, int countPermutations) const;
public:
    Des();

    void setKey(KEY_TYPE key);

    BLOCK_TYPE encrypt(BLOCK_TYPE block);
    BLOCK_TYPE decrypt(BLOCK_TYPE block);
};

#endif // DES_H
