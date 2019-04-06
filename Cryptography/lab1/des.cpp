    #include "des.h"

Des::Des()
    :_feistelNetwork(FeistelNetwork<BLOCK_TYPE, SUB_BLOCK_TYPE, KEY_TYPE>(std::bind(&Des::f, this, std::placeholders::_1, std::placeholders::_2)))
{

}

void Des::setKey(KEY_TYPE key)
{
    initKeys(key);
}

void Des::initKeys(KEY_TYPE key)
{
    key = SUFFLE_BITS(key, DesPermutations::InitialPermatationKey);

    SUB_BLOCK_TYPE c0 = key;
    SUB_BLOCK_TYPE d0 = key >> 28;

    for(int i = 0; i < KEYS_COUNT; i++)
    {
        auto shearNumber = DesPermutations::pCircleTable[i];

        c0 = ((c0 << shearNumber) & (268435455)) | ((c0 >> (28 - shearNumber)));
        d0 = ((d0 << shearNumber) & (268435455)) | ((d0 >> (28 - shearNumber)));

        BLOCK_TYPE s_i = c0 | (BLOCK_TYPE(d0) << 28);

        _keys[i] = SUFFLE_BITS(s_i, DesPermutations::keyTable);
    }
}

Des::SUB_BLOCK_TYPE Des::f(Des::SUB_BLOCK_TYPE subBlock, Des::KEY_TYPE key)
{
    BLOCK_TYPE block = SUFFLE_BITS(subBlock, DesPermutations::FunctionE);

    block ^= key;

    static BLOCK_TYPE mask6 = 63;
    static BLOCK_TYPE mask4 = 15;
    BLOCK_TYPE res = 0;

    for(int i = 0; i < DesPermutations::S_BLOCKS_COUNT; i++)
    {
        BLOCK_TYPE tmp = block & mask6;
        block >>= 6;

        auto line = (tmp & 1) | (((tmp >> 5) & 1) << 1);
        auto column = (tmp >> 1) & mask4;

        auto sValue = BLOCK_TYPE(DesPermutations::S[i][line * 16 + column]);

        res = res | (sValue << (4 * i));
    }

    return SUFFLE_BITS(res, DesPermutations::P);
}

Des::BLOCK_TYPE Des::shuffleBits(BLOCK_TYPE block, const uint8_t* permatation, int countPermutations) const
{
    BLOCK_TYPE newBlock = 0;

    for(auto i = 0; i < countPermutations; i++)
    {
        auto newBit = (block >> (permatation[i] - 1)) & 1;
        newBlock |= (newBit << i);
    }

    return newBlock;
}

Des::BLOCK_TYPE Des::encrypt(Des::BLOCK_TYPE block)
{
    block = SUFFLE_BITS(block, DesPermutations::InitialPermutation);
    block = _feistelNetwork.encrypt(block, _keys, KEYS_COUNT);
    return SUFFLE_BITS(block, DesPermutations::reverseInitialPermutation);
}

Des::BLOCK_TYPE Des::decrypt(Des::BLOCK_TYPE block)
{
    block = SUFFLE_BITS(block, DesPermutations::InitialPermutation);
    block = _feistelNetwork.decrypt(block, _keys, KEYS_COUNT);
    return SUFFLE_BITS(block, DesPermutations::reverseInitialPermutation);
}
