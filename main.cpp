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
           QCoreApplication::translate("main", "Create token for email:password pair"));
    parser.addOption(createTokenOption);

    QCommandLineOption detectOption(QStringList() << "d" << "detect",
           QCoreApplication::translate("main", "Detect faces on specified image"), "-d");
    parser.addOption(detectOption);

    // Process the actual command line arguments given by the user
    parser.process(a);

    //const QStringList args = parser.positionalArguments();
    // source is args.at(0), destination is args.at(1)

    bool createToken    = parser.isSet(createTokenOption);
    bool detect         = parser.isSet(detectOption);

    TevianExchanger test;

    QFile credentials("credentials.txt");
    if(!credentials.open(QIODevice::ReadOnly))
    {
        cout << "Credentials file not found!" << endl;
    }


    if(createToken)
    {
        test.doLogin("https://backend.facecloud.tevian.ru/api/v1/login","sergeishk@gmail.com", "teviantest");
        a.exit();
    }

    if(detect)
    {
        QString imagePath = parser.value(detectOption);

        QFile credentials("credentials.txt");
        credentials.open(QIODevice::ReadOnly);
        QString token = credentials.readAll();
        credentials.close();


        test.detect("https://backend.facecloud.tevian.ru/api/v1/detect?demographics=true",imagePath, token);

    }
    return a.exec();
}
