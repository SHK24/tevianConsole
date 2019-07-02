#ifndef TEVIANEXHANGER_H
#define TEVIANEXHANGER_H

#include <QObject>
#include <iostream>
#include <QCoreApplication>
#include "../../DLL/teviandll.h"

using namespace std;

class TevianExchanger : public QObject
{
    Q_OBJECT

    TevianDLL tev;
    QString lastFile;
    QString detectUrl;
    QString token;
    QStringList images;
    bool status;
signals:
    void requestDone();

public:
    TevianExchanger(QCoreApplication * app);
    void requestError(QString errorMessage);
    void loginSuccess(QString token);
    void detectSuccess(QByteArray rawJSON);

    void doLogin(QString url, QString email, QString password);               //Выполнить login
    void detect(QString url, QStringList imagePaths, QString token);               //Выполнить распознавание
    void processNextImage();
    bool getStatus();
};

#endif // TEVIANEXHANGER_H

