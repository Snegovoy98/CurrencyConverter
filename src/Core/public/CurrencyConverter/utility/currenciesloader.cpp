#include "currenciesloader.h"
#include <QtConcurrent/QtConcurrent>
#include <QJsonDocument>

CurrenciesLoader::CurrenciesLoader(QObject *parent)
    : QObject{parent}
{
    m_manager.reset(new ServiceManager());
    m_db_worker = DBWorker::makeDB();
    connect(m_manager.get(), &ServiceManager::replyGetted, this, &CurrenciesLoader::loadCurrencies);

    int lastActiviy = m_db_worker->getSettingBySettingName("last_activity").toInt();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDateTime dateTimeTwoHourLater = QDateTime::fromSecsSinceEpoch(lastActiviy).addSecs(7200);

    if(currentDateTime > dateTimeTwoHourLater)
    {
        m_manager->get("https://api.monobank.ua/bank/currency");
    }
}

void CurrenciesLoader::saveLastActivity()
{
    QFuture<void> future = QtConcurrent::run([this]()
    {
        int lastActivity = QDateTime::currentSecsSinceEpoch();
        this->m_db_worker->saveSettings("last_activity", lastActivity);
    });
}

void CurrenciesLoader::loadCurrencies(const QByteArray &reply)
{
    QFuture<void> future = QtConcurrent::run([reply, this]()
    {
        this->m_db_worker->clearCurrencies();
        QJsonParseError parseError;
        QJsonDocument document = QJsonDocument::fromJson(reply);

        if(parseError.error == QJsonParseError::NoError)
        {
            this->m_db_worker->loadCurrenciesToDB(document);
        }
    });
}
