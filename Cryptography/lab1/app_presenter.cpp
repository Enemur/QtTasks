#include "app_presenter.h"

AppPresenter::AppPresenter(UiElements uiElements)
    :_uiElements(uiElements),
    _model(new AppModel()),
    _cryptoModel(new CryptoModel()),
    _dirModel()
{
    setConnections();

    _dirModel.setRootPath("");
    _uiElements.treeView->setModel(&_dirModel);
    _uiElements.treeView->setRootIndex(_dirModel.index(""));
}

void AppPresenter::setConnections()
{
    connect(_cryptoModel, &CryptoModel::updatedA, this, &AppPresenter::onAChanged);
    connect(_cryptoModel, &CryptoModel::updatedK, this, &AppPresenter::onKChanged);
    connect(_cryptoModel, &CryptoModel::updatedIAndJ, this, &AppPresenter::onIAndJChanged);
    connect(_cryptoModel, &CryptoModel::updatedM, this, &AppPresenter::onMChanged);
    connect(_cryptoModel, &CryptoModel::updateLen, this, &AppPresenter::onLenChanged);
    connect(_cryptoModel, &CryptoModel::updateArray, this, &AppPresenter::onArrayChanged);
}

bool AppPresenter::checkInput(const QString &text) const
{
    bool isNumber;
    auto value = text.toUInt(&isNumber);
    if (!isNumber)
        return false;

    return value <= MAX_VALUE;
}

void AppPresenter::changeColorOfTextEdit(QLineEdit* textEdit, Qt::GlobalColor color) const
{
    QPalette palette;
    palette.setColor(QPalette::Text, color);
    textEdit->setPalette(palette);
}

void AppPresenter::error(const QString &message) const
{
    QMessageBox box;
    box.setWindowTitle("Error");
    box.setText(message);
    box.exec();
}

void AppPresenter::setA()
{
    auto isCurrectValue = checkInput(_uiElements.valueOfA->text());
    changeColorOfTextEdit(_uiElements.valueOfA, (isCurrectValue) ? (Qt::black) : (Qt::red));

    if (!isCurrectValue)
        return;

    auto a = _uiElements.valueOfA->text().toUInt();
    _cryptoModel->setA(a);
}

void AppPresenter::setK()
{
    auto isCurrectValue = checkInput(_uiElements.valueOfK->text());
    changeColorOfTextEdit(_uiElements.valueOfK, (isCurrectValue) ? (Qt::black) : (Qt::red));

    if (!isCurrectValue)
        return;

    auto k = _uiElements.valueOfK->text().toUInt();
    _cryptoModel->setK(k);
}

void AppPresenter::setI()
{
    auto isCurrectValue = checkInput(_uiElements.valueOfI->text());
    changeColorOfTextEdit(_uiElements.valueOfI, (isCurrectValue) ? (Qt::black) : (Qt::red));

    if (!isCurrectValue)
        return;

    auto i = _uiElements.valueOfI->text().toUInt();
    _cryptoModel->setI(i);
}

void AppPresenter::setJ()
{
    auto isCurrectValue = checkInput(_uiElements.valueOfJ->text());
    changeColorOfTextEdit(_uiElements.valueOfJ, (isCurrectValue) ? (Qt::black) : (Qt::red));

    if (!isCurrectValue)
        return;

    auto j = _uiElements.valueOfJ->text().toUInt();
    _cryptoModel->setJ(j);
}

void AppPresenter::setM()
{
    auto isCurrectValue = checkInput(_uiElements.valueOfM->text());
    changeColorOfTextEdit(_uiElements.valueOfM, (isCurrectValue) ? (Qt::black) : (Qt::red));

    if (!isCurrectValue)
        return;

    auto m = _uiElements.valueOfM->text().toUInt();
    _cryptoModel->setM(m);
}

void AppPresenter::setLen()
{
    auto len = _uiElements.lenLE->text().toUInt();
    _cryptoModel->setLen(len);
}

void AppPresenter::setArray()
{
    try
    {
        auto sArray = _uiElements.per->text();
        auto permutation = sArray.split(",").toVector();
        QVector<unsigned> per;
        for(auto val : permutation)
            per.append(val.toUInt());
        _cryptoModel->setArray(per);
    } catch(std::exception &err)
    {
        error(err.what());
    }
}

void AppPresenter::onAChanged()
{
    auto binary = _cryptoModel->getBinary();

    auto maxPow = _cryptoModel->maxDivPow2();
    auto p = _cryptoModel->findP();
    auto XOR = _cryptoModel->allXor();
    auto leftShift = _cryptoModel->leftShift();
    auto rightShift = _cryptoModel->rightShift();

    _uiElements.viewBinary->setText(binary);

    _uiElements.leftShiftLE->setText(QString::number(leftShift));
    _uiElements.rightShiftLE->setText(QString::number(rightShift));

    _uiElements.maxPowLE->setText(QString::number(maxPow));
    _uiElements.pLE->setText(QString::number(p));
    _uiElements.xorLE->setText(QString::number(XOR));
}

void AppPresenter::onKChanged()
{
    auto bit = _cryptoModel->getBit();
    auto newA = _cryptoModel->updateBit();

    auto leftShift = _cryptoModel->leftShift();
    auto rightShift = _cryptoModel->rightShift();

    _uiElements.viewBit->setText(QString::number(bit));
    _uiElements.viewUpdatedBit->setText(QString::number(newA));

    _uiElements.leftShiftLE->setText(QString::number(leftShift));
    _uiElements.rightShiftLE->setText(QString::number(rightShift));
}

void AppPresenter::onIAndJChanged()
{
    auto newA = _cryptoModel->swapBits();

    _uiElements.viewSwapBits->setText(QString::number(newA));

    auto glueBits = _cryptoModel->pasteBitsTogether();
    auto middleBits = _cryptoModel->getMiddle();

    _uiElements.glueBits->setText(QString::number(glueBits));
    _uiElements.middleBits->setText(QString::number(middleBits));
}

void AppPresenter::onMChanged()
{
    auto newA = _cryptoModel->clearBits();

    _uiElements.viewResetBits->setText(QString::number(newA));
}

void AppPresenter::onLenChanged()
{
    auto glueBits = _cryptoModel->pasteBitsTogether();
    auto middleBits = _cryptoModel->getMiddle();

    _uiElements.glueBits->setText(QString::number(glueBits));
    _uiElements.middleBits->setText(QString::number(middleBits));
}

void AppPresenter::onArrayChanged()
{
    try
    {
        auto value = _cryptoModel->getPermutations();

        _uiElements.resPer->setText(QString::number(value));
    } catch(std::exception &err)
    {
        error(err.what());
    }
}

void AppPresenter::setAlgorithm(EncryptingAlgorithms encryptingAlgorithm)
{
    _model->setAlgorithm(encryptingAlgorithm);
    if (encryptingAlgorithm == EncryptingAlgorithms::DES)
        _uiElements.gbDES->setEnabled(true);
    else
        _uiElements.gbDES->setEnabled(false);
}

void AppPresenter::setKey(const QString &key)
{
    _model->setKey(key);
}

void AppPresenter::onFileSelected(const QModelIndex &index)
{
    auto openFilePath = _dirModel.filePath(index);

    auto key = _model->getKey();

    if (key.length() == 0)
    {
        error("Set secret key");
        return;
    }


    QFileInfo fileInfo(openFilePath);
    auto isFile = fileInfo.isFile();

    try
    {
        if (isFile)
        {
            auto saveFilePath = QFileDialog::getSaveFileName(_uiElements.window,
                                                             "Get save file");
            if (saveFilePath == "")
            {
                error("Incorect save file name");
                return;
            }
            
            _model->processFile(openFilePath, saveFilePath);
        }
    }
    catch(std::exception& ex)
    {
        error(ex.what());
    }
}

void AppPresenter::setEncrypt(bool isEncrypt)
{
    _model->setEncrypt(isEncrypt);
}

void AppPresenter::setDesMode(DESMode mode)
{
    _model->setDESMode(mode);
}

void AppPresenter::setInitialVector(const QString &vector)
{
    _model->setDESInitialVector(vector);
}

AppPresenter::~AppPresenter()
{
    delete _model;
    delete _cryptoModel;
}
