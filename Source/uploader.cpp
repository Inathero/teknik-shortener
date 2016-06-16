#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QClipboard>
#include <QApplication>
#include <QUrlQuery>
#include "uploader.h"

#define SHORTEN_API_POINT "https://api.teknik.io/v1/Shorten"



Uploader::Uploader(const QString & apiKey, QObject * parent): QObject(parent), m_apiKey(apiKey)
{
    m_manager = new QNetworkAccessManager(this);

    connect(m_manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(requestFinished(QNetworkReply *)));
}

void Uploader::getShortenURL(const QString dataStream)
{
    qDebug() << "Uploader::uploadFileFromData";
    gettingURL = true;

    QNetworkRequest request(QUrl(SHORTEN_API_POINT));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray postData;
    QUrlQuery params;
    params.addQueryItem("url",QUrl::toPercentEncoding(dataStream));

    postData = params.query(QUrl::FullyEncoded).toUtf8();


    reply = m_manager->post(request, postData);

}
void Uploader::requestFinished(QNetworkReply* reply)
{
    QString response = reply->readAll();
 gettingURL = false;
    qDebug() << response;

    QJsonParseError a;
    QJsonDocument sd = QJsonDocument::fromJson(response.toUtf8(), &a);
    QJsonObject docObject = sd.object();

    docObject = docObject.take("result").toObject();
    QString imageLink = docObject.value("shortUrl").toString();

    QClipboard *clip = QApplication::clipboard();
    clip->setText(imageLink);

}
