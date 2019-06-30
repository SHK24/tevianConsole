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
    QCoreApplication * app;

public:
    TevianExchanger(QCoreApplication * app);
    void requestError(QString errorMessage);
    void loginSuccess(QString token);
    void detectSuccess(QByteArray rawJSON);

    void doLogin(QString url, QString email, QString password);               //Выполнить login
    void detect(QString url, QString imagePath, QString token);               //Выполнить распознавание
};

#endif // TEVIANEXHANGER_H

