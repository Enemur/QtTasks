#ifndef FEISTELNETWORK_H
#define FEISTELNETWORK_H

#include "des_permutations.h"
#include <functional>

template<typename BlockType, typename SubBlockType, typename KeyType>
class FeistelNetwork
{
private:
    std::function<SubBlockType(SubBlockType, KeyType)> _f;
public:
    FeistelNetwork(std::function<SubBlockType(SubBlockType, KeyType)> f)
        :_f(f) {}

    BlockType encrypt(BlockType block, KeyType* keys, int countRounds) const
    {
        SubBlockType L = block >> 32;
        SubBlockType R = block;

        for(int i = 0; i < countRounds; i++)
        {
            auto tmp = R;
            R = L ^ _f(R, keys[i]);
            L = tmp;
        }

        return (BlockType(L) << 32) | BlockType(R);
    }

    BlockType decrypt(BlockType block, KeyType* keys, int countRounds) const
    {
        SubBlockType L = block >> 32;
        SubBlockType R = block;

        for(int i = countRounds - 1; i >= 0; i--)
        {
            auto tmp = L;
            L = R ^ _f(L, keys[i]);
            R = tmp;
        }

        return (BlockType(L) << 32) | BlockType(R);
    }
};

#endif // FEISTELNETWORK_H
