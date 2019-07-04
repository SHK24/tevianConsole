#include <QFile>
#include <QObject>
#include <QLibrary>
#include <iostream>
#include <QCoreApplication>
#include "tevianexchanger.h"
#include <QCommandLineParser>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ///-----------------------------------Создание опций для параметров командной строки---------------------------------------
    QCommandLineParser parser;
    parser.setApplicationDescription("TevianBackEnd CLI");
    parser.addHelpOption();

    QCommandLineOption createTokenOption(QStringList() << "c" << "createToken",
           QCoreApplication::translate("main", "Create token for email:password pair"), "-c");
    parser.addOption(createTokenOption);

    QCommandLineOption detectOption(QStringList() << "d" << "detect",
           QCoreApplication::translate("main", "Detect faces on specified image"), "-d");
    parser.addOption(detectOption);
    ///------------------------------------------------------------------------------------------------------------------------

    ///Определение параметров с которыми было запущено приложение
    parser.process(a);

    ///Детектирование опции создания токена
    bool createToken    = parser.isSet(createTokenOption);

    ///Детектирование опции распознавания
    bool detect         = parser.isSet(detectOption);

    ///Если ни один параметр не был определен - закончить выполнение
    if((!createToken) && (!detect))
    {
        cout<< "No parameters detected!" << endl;
        a.exit();
    }

    ///Создание экземпляра для обмена с backend сервером
    TevianExchanger test;

    ///Если была установлена опция создания токена
    if(createToken)
    {
        ///Разделение входной строки по символу ":"
        QStringList creds = parser.value(createTokenOption).split(':');

        ///Завершить выполнение если длина данных для авторизации меньше 2
        if(creds.count() < 2)
        {
            cout << "Login data is not full!" <<endl;
            return 2;
        }

        ///выполнение запроса
        test.doLogin("https://backend.facecloud.tevian.ru/api/v1/login",creds[0], creds[1]);
    }

    if(detect)
    {
        ///Разделение входной строки по символу ";" - список изображений для обработки
        QStringList imagePaths = parser.value(detectOption).split(';');

        ///Чтение токена из файла - завершение программы при неудачном чтении
        QFile credentials("credentials.txt");
        if(!credentials.open(QIODevice::ReadOnly))
        {
            cout<<"Credentials file not found"<<endl;
            a.exit();
        }
        else
        {
            ///Выполнение запроса на распознавание в случае удачного чтения токена
            QString token = credentials.readAll();

            if(token == "")
            {
                cout<<"JWT is empty"<<endl;
                return 3;
            }

            credentials.close();

            test.detect("https://backend.facecloud.tevian.ru/api/v1/detect?demographics=true",imagePaths, token);
        }
    }

    while(!test.getStatus())
    {
        a.processEvents();
    }

    a.exit();
}
