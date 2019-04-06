#include "crypto_model.h"

CryptoModel::CryptoModel()
    :_a(0),
     _k(0),
     _i(0),
     _j(0),
     _m(0)
{

}

void CryptoModel::setA(uint32_t a)
{
    _a = a;
    updatedAll();
}

void CryptoModel::updatedAll()
{
    emit updatedA();
    emit updatedIAndJ();
    emit updatedK();
    emit updatedM();
    emit updateLen();
}

void CryptoModel::setK(uint32_t k)
{
    _k = k;
    emit updatedK();
}

void CryptoModel::setI(uint32_t i)
{
    _i = i;
    emit updatedIAndJ();
}

void CryptoModel::setJ(uint32_t j)
{
    _j = j;
    emit updatedIAndJ();
}

void CryptoModel::setM(uint32_t m)
{
    _m = m;
    emit updatedM();
}

void CryptoModel::setLen(uint32_t len)
{
    _len = len;
    emit updateLen();
}

void CryptoModel::setArray(const QVector<unsigned> array)
{
    _array = array;
    emit updateArray();
}

QString CryptoModel::getBinary() const
{
    QString value;
    if (_a != 0)
        for(int i = int(log(_a)/log(2)); i >= 0; i--)
            value.append(int(_a >> i & 1) + '0');
    else
        value.append('0');
    return value;
}

short CryptoModel::getBit() const
{
    return _a >> _k & 1;
}

uint32_t CryptoModel::updateBit() const
{
    if (_a >> _k & 1)
        return unsetBit(_a, _k);
    else
        return setBit(_a, _k);
}

uint32_t CryptoModel::unsetBit(u_int32_t a, uint32_t k) const
{
    return a & (~(1 << k));
}

u_int32_t CryptoModel::setBit(u_int32_t a, uint32_t k) const
{
    return a | (1 << k);
}

uint32_t CryptoModel::swapBits() const
{
    uint32_t iBitMask = ~(1 << _i);
    uint32_t jBitMask = ~(1 << _j);

    uint32_t bitMask = iBitMask & jBitMask;

    uint32_t iBit = (_a >> _i) & 1;
    uint32_t jBit = (_a >> _j) & 1;

    return (_a & bitMask) | (iBit << _j) | (jBit << _i);
}

uint32_t CryptoModel::clearBits() const
{
    return _a & ((~0ul) << _m);
}

uint32_t CryptoModel::pasteBitsTogether()
{
    uint32_t left = ((_a << (32 - _len)) >> (32 - _i)) << _i;
    uint32_t right = _a & ((~uint32_t(0)) >> (32 - _i));
    return (left | right);
}

uint32_t CryptoModel::getMiddle()
{
    return ((_a >> _i) & ((~uint32_t(0)) >> (32 - _len + _i + _i)));
}

uint32_t CryptoModel::  getPermutations()
{
    if (_array.size() != 4)
        throw std::runtime_error("Array size != 4");


    auto byteSize = sizeof(char) * 8;
    auto byteMask = (1ul << byteSize) - 1ul;
    uint32_t result = 0;

    for (auto index : _array) {
        result = (result << byteSize) | ((_a >> (index * byteSize)) & byteMask);
    }

    return result;
}

uint64_t CryptoModel::maxDivPow2()
{
    return _a & -_a;
}

uint64_t CryptoModel::findP()
{
    if (_a == 0) {
          throw std::runtime_error("X == 0");
      }

      uint64_t p = 0;
      uint64_t _2_p = 1;

      while ((_2_p < _a) && (_2_p * 2 > _2_p)) {
          _2_p *= 2;

          if (_2_p >= _a) {
              return p;
          }

          p++;
      }

      return p;
}

uint64_t CryptoModel::allXor()
{
    uint64_t i = 0;
    auto tmp = _a;

       while (tmp) {
           i = i ^ (tmp & 1);
           tmp = tmp >> 1;
       }

       return i;
}

uint64_t CryptoModel::leftShift()
{
     return (_a << _k) | (_a >> (32 - _k));
}

uint64_t CryptoModel::rightShift()
{
    return (_a >> _k) | (_a << (32 - _k));
}
