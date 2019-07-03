#ifndef TEVIANEXHANGER_H
#define TEVIANEXHANGER_H

#include <QObject>
#include <iostream>
#include <jsonparser.h>
#include <QCoreApplication>
#include "../../DLL/teviandll.h"

using namespace std;

class TevianExchanger : public QObject
{
    Q_OBJECT

    ///Экземпляр для обмена данными с сервером
    TevianDLL tev;

    ///Название последнего обработанного файла
    QString lastFile;

    ///URL для распознавания
    QString detectUrl;

    ///JWT токен
    QString token;

    ///Список изображения для обработки
    QStringList images;

    ///Состояние обмена
    bool status;
signals:
    void requestDone();

public:
    ///Конструктор
    TevianExchanger();

    ///Обработчик сигнала об ошибке запроса
    void requestError(QString errorMessage);

    ///Обработчик сигнала об успешном логине
    void loginSuccess(QByteArray jsonData);

    ///Обработчик сигнала об успешном распознавании
    void detectSuccess(QByteArray rawJSON);

    ///Метод выполняющий login с заданными параметрами
    void doLogin(QString url, QString email, QString password);

    ///Метод выполняющий распознавание заданного списка изображений
    void detect(QString url, QStringList imagePaths, QString token);

    ///Метод выполняющий обработку следующего изображения из списка
    void processNextImage();

    ///Метод выдачи состояния запроса
    bool getStatus();
};

#endif // TEVIANEXHANGER_H

