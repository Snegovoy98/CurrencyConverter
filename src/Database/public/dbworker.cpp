#include "dbworker.h"
#include <QDateTime>
#include <QSqlError>
#include <QSqlDatabase>
#include <QThread>

DBWorker::DBWorker(QObject *parent)
    : QObject{parent}
{
    QSqlDatabase historyConnection = QSqlDatabase::cloneDatabase("mainConnection", "historyConnection");
    historyConnection.open();
    m_query.reset(new QSqlQuery(historyConnection));
}

DBWorker* DBWorker::makeDB()
{
    if(m_db_worker == nullptr)
        m_db_worker = new DBWorker();

    return m_db_worker;
}

void DBWorker::saveSettings(const QMap<QString, QVariant> &parameters)
{
    m_query->prepare("INSERT INTO settings(setting_name, setting_value) VALUES(:setting_name, :setting_value)");

    for(const auto &[key, value] : parameters.asKeyValueRange())
    {
        m_query->bindValue(":setting_name", key);
        m_query->bindValue(":setting_value", value);
        if(!m_query->exec())
            emit errorHappened(m_query->lastError().text());
    }
}

const QVariant& DBWorker::getSettingBySettingName(const QString &settingName)
{
    m_query->prepare("SELECT * FROM settings WHERE setting_name = :setting_name");
    m_query->bindValue(":setting_name", settingName);

    if(!m_query->exec())
        emit errorHappened(m_query->lastError().text());

    while (m_query->next())
    {
       m_setting = m_query->value(settingName);
    }

    return m_setting;
}

void DBWorker::saveHistoryOfExchanges(const QString &currencyOnExchageTitle,
                                                            const double &valuePerUnit,
                                                            const QString &currencyToExchageTitle,
                                                            const double &exchangedSum)
{
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
}

const QSqlQuery *DBWorker::getHistoryOfExchanges()
{
    m_query->prepare("SELECT * FROM exchange_history");

    if(!m_query->exec())
    {
         emit errorHappened(m_query->lastError().text());
    }

    return m_query.get();
}


