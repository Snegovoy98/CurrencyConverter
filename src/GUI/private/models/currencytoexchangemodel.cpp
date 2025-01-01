#include "currencytoexchangemodel.h"
#include <QSqlQuery>

CurrencyToExchangeModel::CurrencyToExchangeModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_db_worker = DBWorker::makeDB();
}

int CurrencyToExchangeModel::rowCount(const QModelIndex &parent) const
{
    return m_currencies_to_exchange.count();
}

QVariant CurrencyToExchangeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role < CurrencyToExchangeTitle)
        return {};

    const int indexRow = index.row();

    switch (role)
    {
        case CurrencyToExchangeTitle:
            return m_currencies_to_exchange.at(indexRow).currency_to_exchange_title;
        case CrossRate:
            return m_currencies_to_exchange.at(indexRow).rate_cross;
        default:
            break;
    }

    return {};
}

QHash<int, QByteArray> CurrencyToExchangeModel::roleNames() const
{
    m_roles[CurrencyToExchangeTitle] = "currency_title";
    m_roles[CrossRate] = "cross_rate";

    return m_roles;
}

void CurrencyToExchangeModel::fetchCurrencyData(const int &currencyCode)
{
    QSqlQuery *query = const_cast<QSqlQuery*>(m_db_worker->getCurrenciesToExchangeByOnExchangeCode(currencyCode));

    m_currencies_to_exchange.clear();
    while(query->next())
    {
        CurrencyToExchangeData currencyToExchangeData;
        currencyToExchangeData.currency_to_exchange_title = query->value("currency_title").toString();
        currencyToExchangeData.rate_cross = query->value("rate_cross").toDouble();
        beginResetModel();
        m_currencies_to_exchange.push_back(currencyToExchangeData);
        endResetModel();
    }
}
