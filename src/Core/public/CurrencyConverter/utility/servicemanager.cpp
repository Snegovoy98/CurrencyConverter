#include "servicemanager.h"
#include <QEventLoop>

ServiceManager::ServiceManager(QObject *parent)
    : QObject{parent}
{
    m_manager = new QNetworkAccessManager();
}

void ServiceManager::get(const QString &url, const QHash<QString, QVariant> &params)
{
    QNetworkRequest m_request;
    QString urlWithParams = url;
    int paramsCounter = 0;

    for (const auto &[key, value]: params.asKeyValueRange())
    {
        ++paramsCounter;

        if(value != "")
        {
            urlWithParams += key + "=" + value.toString();
        }
        else
        {
            urlWithParams += key;
        }

        if(paramsCounter != params.size())
        {
            urlWithParams += "&";
        }
    }

    m_request.setUrl(QUrl(url));
    m_reply = m_manager->get(m_request);

    QEventLoop loop;
    connect(m_reply.get(), &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray resultValues = m_reply->readAll();

    if(!resultValues.isEmpty())
    {
        emit replyGetted(resultValues);
    }

    m_reply->deleteLater();
}

void ServiceManager::post(const QString &url, const QByteArray &data)
{
    QNetworkRequest m_request;
    m_request.setUrl(QUrl(url));
    m_reply = m_manager->post(m_request, data);

    QEventLoop loop;
    loop.exec();
    connect(m_reply.get(), &QNetworkReply::finished, &loop, &QEventLoop::quit);

    QByteArray resultValues = m_reply->readAll();

    if(!resultValues.isEmpty())
    {
        emit replyGetted(resultValues);
    }

    m_reply->deleteLater();
}

