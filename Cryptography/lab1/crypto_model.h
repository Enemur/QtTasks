#ifndef CRYPTO_MODEL_H
#define CRYPTO_MODEL_H

#include "QObject"
#include "cmath"
#include "QVector"

class CryptoModel: public QObject
{
    Q_OBJECT
private:
    uint32_t _a;
    uint32_t _k;
    uint32_t _i;
    uint32_t _j;
    uint32_t _m;
    uint32_t _len;
    QVector<unsigned> _array;
private:
    uint32_t setBit(u_int32_t a, unsigned k) const;
    uint32_t unsetBit(u_int32_t a, unsigned k) const;
    
    void updatedAll();
public:
    CryptoModel();
    
    void setA(uint32_t a);
    void setK(uint32_t k);
    void setI(uint32_t i);
    void setJ(uint32_t j);
    void setM(uint32_t m);
    void setLen(uint32_t len);
    void setArray(const QVector<unsigned> array);

    QString getBinary() const;
    short getBit() const;
    uint32_t updateBit() const;

    uint32_t swapBits() const;
    uint32_t clearBits() const;
    uint32_t pasteBitsTogether();
    uint32_t getMiddle();
    uint32_t getPermutations();
    uint64_t maxDivPow2();
    uint64_t findP();
    uint64_t allXor();
    uint64_t leftShift();
    uint64_t rightShift();
signals:
    void updatedA();
    void updatedK();
    void updatedIAndJ();
    void updatedM();
    void updateLen();
    void updateArray();
};

#endif // CRYPTO_MODEL_H
