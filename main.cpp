#include <QCoreApplication>
#include <QCommandLineParser>
#include <QLibrary>
#include <iostream>
#include <QObject>
#include <QFile>
#include "tevianexchanger.h"

using namespace std;

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("TevianBackEnd CLI");
    parser.addHelpOption();

    QCommandLineOption createTokenOption(QStringList() << "c" << "createToken",
           QCoreApplication::translate("main", "Create token for email:password pair"), "-c");
    parser.addOption(createTokenOption);

    QCommandLineOption detectOption(QStringList() << "d" << "detect",
           QCoreApplication::translate("main", "Detect faces on specified image"), "-d");
    parser.addOption(detectOption);

    parser.process(a);

    bool createToken    = parser.isSet(createTokenOption);
    bool detect         = parser.isSet(detectOption);

    TevianExchanger test(&a);

//    QFile credentials("credentials.txt");
//    if(!credentials.open(QIODevice::ReadOnly))
//    {
//        cout << "Credentials file not found!" << endl;
//    }

    if(createToken)
    {
        QStringList creds = parser.value(createTokenOption).split(':');

        if(creds.count() < 2)
        {
            cout << "Login data is not full!" <<endl;
            return 2;
        }

        test.doLogin("https://backend.facecloud.tevian.ru/api/v1/login",creds[0], creds[1]);
    }

    if(detect)
    {
        QStringList imagePaths = parser.value(detectOption).split(';');

        QFile credentials("credentials.txt");
        if(!credentials.open(QIODevice::ReadOnly))
        {
            cout<<"Credentials not found"<<endl;
            a.exit();
        }
        else
        {
            QString token = credentials.readAll();
            credentials.close();

            test.detect("https://backend.facecloud.tevian.ru/api/v1/detect?demographics=true",imagePaths, token);
        }
    }
    return a.exec();
}
