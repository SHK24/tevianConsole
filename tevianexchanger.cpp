#include "tevianexchanger.h"


TevianExchanger::TevianExchanger(QCoreApplication * app)
{
    connect(&tev, &TevianDLL::loginSuccess,  this, &TevianExchanger::loginSuccess);
    connect(&tev, &TevianDLL::requestError,  this, &TevianExchanger::requestError);
    connect(&tev, &TevianDLL::detectSuccess, this, &TevianExchanger::detectSuccess);

    this->app = app;
}

void TevianExchanger::requestError(QString errorMessage)
{
    cout <<errorMessage.toUtf8().data() << endl;
}

void TevianExchanger::loginSuccess(QString token)
{
    cout<<"---------Login result------"<<endl;
    cout<<"Login is OK! Your JWT token has been storaged in credentials.txt" << endl;
    QFile credentials("credentials.txt");

    if(!credentials.open(QIODevice::WriteOnly))
    {
        cout<<"Can't create credentials file!"<<endl;
        return;
    }

    credentials.write(token.toUtf8());
    credentials.close();

    app->exit();
}

void TevianExchanger::detectSuccess(QByteArray rawJSON)
{
    cout<<"->"<<lastFile.toUtf8().data()<<endl;
    cout<<rawJSON.data()<<endl;

    if(images.count() > 0)
    {
        images.pop_front();

        processNextImage();
    }
    else {
        cout<<"All images has been processed" << endl;
        app->exit();
    }
}

void TevianExchanger::doLogin(QString url, QString email, QString password)
{
    tev.doLogin(url, email, password);
}

void TevianExchanger::processNextImage()
{
    if(images.count() > 0)
    {
        if(!QFile(images[0]).open(QIODevice::ReadOnly))
        {
            cout<<"Image "<<images[0].toUtf8().data()<<" not found"<<endl;

            images.pop_front();
            processNextImage();

            return;
        }
        tev.detect(detectUrl, images[0], token);
        lastFile = images[0];
    }
}

void TevianExchanger::detect(QString url, QStringList imagePaths, QString token)
{
    if(imagePaths.count() == 0)
    {
        cout << "Images list is empty" << endl;
        return;
    }
    detectUrl = url;
    images = imagePaths;
    this->token = token;
    processNextImage();
}
