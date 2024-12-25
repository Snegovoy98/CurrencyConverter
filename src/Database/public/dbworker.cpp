#include "dbworker.h"
#include <QDateTime>
#include <QSqlError>
#include <QSqlDatabase>
#include <QJsonArray>
#include <QJsonObject>

DBWorker::DBWorker(QObject *parent)
    : QObject{parent}, m_db_connection_name{"dbConnection"}, m_max_threads{8}
{
    ++connectionsCount;
    QString number = QString::number(connectionsCount);
    QSqlDatabase dbConnection = QSqlDatabase::cloneDatabase("mainConnection", m_db_connection_name + number);
    dbConnection.open();
    m_query.reset(new QSqlQuery(dbConnection));
    m_semaphore.reset(new QSemaphore(m_max_threads));
}

DBWorker* DBWorker::makeDB()
{
    if(m_db_worker == nullptr)
        m_db_worker = new DBWorker();

    return m_db_worker;
}

DBWorker::~DBWorker()
{
    --connectionsCount;
    QSqlDatabase::removeDatabase(m_db_connection_name);
    delete m_db_worker;
}

void DBWorker::saveSettings(const QString &settingName, const QVariant &settingValue)
{
    m_semaphore->acquire();
    if(isSettingExists(settingName))
    {
        m_query->prepare("UPDATE settings SET setting_value = :setting_value WHERE setting_name = :setting_name");
    } else {
        m_query->prepare("INSERT INTO settings(setting_name, setting_value) VALUES(:setting_name, :setting_value)");
    }

    m_query->bindValue(":setting_name", settingName);
    m_query->bindValue(":setting_value", settingValue);

    if(!m_query->exec())
        emit errorHappened(m_query->lastError().text());
    m_semaphore->release();
}

const QVariant& DBWorker::getSettingBySettingName(const QString &settingName)
{
    m_semaphore->acquire();
    m_query->prepare("SELECT setting_value FROM settings WHERE setting_name = :setting_name");
    m_query->bindValue(":setting_name", settingName);

    if(!m_query->exec())
        emit errorHappened(m_query->lastError().text());

    while (m_query->next())
    {
       m_setting = m_query->value("setting_value");
    }

    return m_setting;
    m_semaphore->release();
}

void DBWorker::loadCurrenciesToDB(const QJsonDocument &document)
{
    m_semaphore->acquire();
    ++connectionsCount;
    QString number = QString::number(connectionsCount);
    {
        QSqlDatabase dbConnection = QSqlDatabase::cloneDatabase("mainConnection", m_db_connection_name + number);
         dbConnection.open();
        QSqlQuery query(dbConnection);
        query.prepare("INSERT INTO currencies(currency_on_exchange_code, currency_to_exchange_code, exchange_date,  rate_cross) "
                                   "VALUES(:currency_on_exchange_code, :currency_to_exchange_code, :exchange_date, :rate_cross)");
        int currencyCodeB;
        int currencyCodeA;
        int exchangeDate;
        double rateCross;

        for (const auto &object : document.array().toVariantList())
        {
            currencyCodeB = object.toJsonObject()["currencyCodeB"].toInt();
            currencyCodeA = object.toJsonObject()["currencyCodeA"].toInt();
            exchangeDate = object.toJsonObject()["date"].toInt();
            rateCross = object.toJsonObject()["rateCross"].toDouble();
            query.bindValue(":currency_on_exchange_code",  currencyCodeB);
            query.bindValue(":currency_to_exchange_code", currencyCodeA);
            query.bindValue(":exchange_date", exchangeDate);
            query.bindValue(":rate_cross",  rateCross);

            if(!query.exec())
            {
                emit errorHappened(query.lastError().text());
            }
        }
    }
    QSqlDatabase::removeDatabase(m_db_connection_name + number);
    --connectionsCount;
    m_semaphore->release();
}

void DBWorker::clearCurrencies()
{
    m_semaphore->acquire();
    ++connectionsCount;
    QString number = QString::number(connectionsCount);
    {
        QSqlDatabase dbConnection = QSqlDatabase::cloneDatabase("mainConnection", m_db_connection_name + number);
        dbConnection.open();
        QSqlQuery query(dbConnection);
        query.prepare("DELETE FROM currencies");

        if(!query.exec())
        {
            emit errorHappened(query.lastError().text());
        }
    }
    m_semaphore->release();
}

void DBWorker::saveHistoryOfExchanges(const QString &currencyOnExchageTitle,
                                                            const double &valuePerUnit,
                                                            const QString &currencyToExchageTitle,
                                                            const double &exchangedSum)
{
    m_semaphore->acquire();
    int exchangeDateTime  = QDateTime::currentSecsSinceEpoch();
    m_query->prepare("INSERT INTO exchange_history (currency_on_exchange_title, value_per_unit, currency_to_exchange_title,  exchanged_sum, exchange_date)"
                               "VALUES(:currency_on_exchange_title, :value_per_unit, :currency_to_exchange_title, :exchanged_sum,  :exchange_date)");
    m_query->bindValue(":currency_on_exchange_title", currencyOnExchageTitle);
    m_query->bindValue(":value_per_unit", valuePerUnit);
    m_query->bindValue(":currency_to_exchange_title", currencyToExchageTitle);
    m_query->bindValue(":exchanged_sum", exchangedSum);
    m_query->bindValue(":exchange_date", exchangeDateTime);

    if(!m_query->exec())
    {
        emit errorHappened(m_query->lastError().text());
    }
    else
    {
        emit historySaved();
    }

    m_semaphore->release();
}

const QSqlQuery *DBWorker::getHistoryOfExchanges()
{
    m_semaphore->acquire();
    m_query->prepare("SELECT * FROM exchange_history");

    if(!m_query->exec())
    {
         emit errorHappened(m_query->lastError().text());
    }

    return m_query.get();
    m_semaphore->release();
}

const QSqlQuery *DBWorker::getCurrenciesOnExchange()
{
    m_semaphore->acquire();
    m_query->prepare("SELECT DISTINCT ci.currency_title as currency_title, c.currency_on_exchange_code as currency_code "
                                "FROM currencies AS c "
                               "JOIN currencies_info AS ci ON ci.currency_code = c.currency_on_exchange_code");

    if(!m_query->exec())
    {
        emit errorHappened(m_query->lastError().text());
    }

    return m_query.get();
    m_semaphore->release();
}

const QSqlQuery *DBWorker::getCurrenciesToExchangeByOnExchangeCode(const int &onExchangeCode)
{
    m_semaphore->acquire();
    m_query->prepare("SELECT DISTINCT ci.currency_title, c.rate_cross FROM currencies AS c "
                               "JOIN currencies_info AS ci ON ci.currency_code = c.currency_to_exchange_code "
                               "WHERE c.currency_on_exchange_code = :currency_on_exchange_code");
    m_query->bindValue(":currency_on_exchange_code", onExchangeCode);

    if(!m_query->exec())
    {
        emit errorHappened(m_query->lastError().text());
    }

    m_semaphore->release();
    return m_query.get();
}

bool DBWorker::isSettingExists(const QString &settingName)
{
    m_semaphore->acquire();
    m_query->prepare("SELECT setting_name FROM settings WHERE setting_name = :setting_name");
    m_query->bindValue(":setting_name", settingName);

    if(!m_query->exec())
    {
        emit errorHappened(m_query->lastError().text());
    }

    m_semaphore->release();
    return m_query->first();
}


