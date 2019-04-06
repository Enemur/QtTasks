#ifndef UIELEMENTS_H
#define UIELEMENTS_H

#include "qmainwindow.h"
#include "QLineEdit"
#include <QGroupBox>
#include <QTreeView>
#include "QRadioButton"

struct UiElements
{
    QMainWindow* window;

    QLineEdit* valueOfA;
    QLineEdit* valueOfK;
    QLineEdit* valueOfI;
    QLineEdit* valueOfJ;
    QLineEdit* valueOfM;

    QLineEdit* lenLE;
    QLineEdit* glueBits;
    QLineEdit* middleBits;
    QLineEdit* resPer;
    QLineEdit* per;

    QLineEdit* viewBinary;
    QLineEdit* viewBit;
    QLineEdit* viewUpdatedBit;
    QLineEdit* viewSwapBits;
    QLineEdit* viewResetBits;

    QTreeView* treeView;

    QRadioButton* rbEncrypting;
    QRadioButton* rbDecrypting;

    QRadioButton* rbMyAlgorithm;
    QRadioButton* rbDES;
    QRadioButton* rbRC4;
    QRadioButton* rbVernam;

    QGroupBox* gbDES;

    QLineEdit* maxPowLE;
    QLineEdit* pLE;
    QLineEdit* xorLE;
    QLineEdit* leftShiftLE;
    QLineEdit* rightShiftLE;
};

#endif // UIELEMENTS_H
