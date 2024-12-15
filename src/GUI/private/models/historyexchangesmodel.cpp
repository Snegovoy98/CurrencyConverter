#include "historyexchangesmodel.h"
#include <QtConcurrent/QtConcurrent>

HistoryExchangesModel::HistoryExchangesModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_db_worker = DBWorker::makeDB();
    connect(m_db_worker, &DBWorker::historySaved, this, &HistoryExchangesModel::fetchExchangesHistory);
}

int HistoryExchangesModel::rowCount(const QModelIndex &parent) const
{
    return m_data_list.count();
}

QVariant HistoryExchangesModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role < CURRENCY_ON_EXCHANGE_TITLE)
        return {};

    int rowIndex = index.row();

    switch(role)
    {
        case CURRENCY_ON_EXCHANGE_TITLE:
            return m_data_list.at(rowIndex).m_currency_on_exchange_title;
        case VALUE_PER_UNIT:
            return m_data_list.at(rowIndex).m_value_per_unit;
        case CURRENCY_TO_EXCHANGE_TITLE:
            return  m_data_list.at(rowIndex).m_currency_to_exchange_title;
        case EXCHANGED_SUM:
            return m_data_list.at(rowIndex).m_exchanged_sum;
        case EXCHANGE_DATE:
            return m_data_list.at(rowIndex).m_exchange_date;
    }

    return {};
}

QHash<int, QByteArray> HistoryExchangesModel::roleNames() const
{
      m_roles[CURRENCY_ON_EXCHANGE_TITLE] = "currency_on_exchange_title";
      m_roles[VALUE_PER_UNIT] = "value_per_unit";
      m_roles[CURRENCY_TO_EXCHANGE_TITLE] = "currency_to_exchange_title";
      m_roles[EXCHANGED_SUM] = "exchanged_sum";
      m_roles[EXCHANGE_DATE] = "exchange_date";

      return m_roles;
}

void HistoryExchangesModel::saveHistory(const QString &currencyOnExchageTitle,
                                                             const double &valuePerUnit,
                                                             const QString &currencyToExchageTitle,
                                                             const double &exchangedSum)
{
   QFuture<void> future = QtConcurrent::run(&DBWorker::saveHistoryOfExchanges,  m_db_worker, currencyOnExchageTitle,
                                                                valuePerUnit, currencyToExchageTitle, exchangedSum);
}

void HistoryExchangesModel::fetchExchangesHistory()
{
    QSqlQuery *historyOfExchanges = const_cast<QSqlQuery*>(m_db_worker->getHistoryOfExchanges());

    m_data_list.clear();
    while(historyOfExchanges->next())
    {
        HistoryExchagesData dataOfExchanges;
        dataOfExchanges.m_currency_on_exchange_title  = historyOfExchanges->value("currency_on_exchange_title").toString();
        dataOfExchanges.m_value_per_unit                    = historyOfExchanges->value("value_per_unit").toDouble();
        dataOfExchanges.m_currency_to_exchange_title   = historyOfExchanges->value("currency_to_exchange_title").toString();
        dataOfExchanges.m_exchanged_sum                   = historyOfExchanges->value("exchanged_sum").toDouble();
        dataOfExchanges.m_exchange_date                     =  historyOfExchanges->value("exchange_date").toDateTime();
        beginResetModel();
        m_data_list.append(dataOfExchanges);
        endResetModel();
    }
}
