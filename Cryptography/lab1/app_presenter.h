#ifndef APPPRESENTER_H
#define APPPRESENTER_H

#include "app_model.h"
#include "ui_elements.h"
#include "QObject"
#include "cmath"
#include "QFileSystemModel"
#include "QString"
#include "crypto_model.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

class AppPresenter: public QObject
{
    Q_OBJECT
private:
    UiElements _uiElements;

    AppModel* _model;
    CryptoModel* _cryptoModel;
    QFileSystemModel _dirModel;
private:
    void setConnections();
    bool checkInput(const QString& text) const;
    void changeColorOfTextEdit(QLineEdit* textEdit, Qt::GlobalColor color) const;
    void error(const QString& message) const;
public:
    const static long MAX_VALUE = 4294967295;

    AppPresenter(UiElements uiElements);

    void setAlgorithm(EncryptingAlgorithms typeEncrypting);
    void setKey(const QString& key);

    ~AppPresenter();
public slots:
    void setA();
    void setK();
    void setI();
    void setJ();
    void setM();
    void setLen();
    void setArray();

    void onAChanged();
    void onKChanged();
    void onIAndJChanged();
    void onMChanged();
    void onLenChanged();
    void onArrayChanged();

    void onFileSelected(const QModelIndex &index);
    void setEncrypt(bool isEncrypt);
    void setDesMode(DESMode mode);
    void setInitialVector(const QString& vector);
};

#endif // APPPRESENTER_H
