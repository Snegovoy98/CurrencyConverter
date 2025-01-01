#include "currencyonexchangemodel.h"
#include <QSqlQuery>

CurrencyOnExchangeModel::CurrencyOnExchangeModel(QObject *parent)
    : QAbstractListModel {parent}
{
    m_db_worker = DBWorker::makeDB();
    fetchCurrencyData();
}

int CurrencyOnExchangeModel::rowCount(const QModelIndex &parent) const
{
    return m_currencies_on_exchange.count();
}

QVariant CurrencyOnExchangeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role < CurrencyOnExchangeCode)
        return {};

    const int rowIndex = index.row();

    switch (role)
    {
        case CurrencyOnExchangeCode:
            return m_currencies_on_exchange.at(rowIndex).currency_code;

        case CurrencyOnExchangeTitle:
        {
            return m_currencies_on_exchange.at(rowIndex).currency_title;
        }
        default:
            break;
    }

    return {};
}

QHash<int, QByteArray> CurrencyOnExchangeModel::roleNames() const
{
    m_roles[CurrencyOnExchangeCode]  = "currency_code";
    m_roles[CurrencyOnExchangeTitle]  = "currency_title";

    return m_roles;
}

void CurrencyOnExchangeModel::fetchCurrencyData()
{
    QSqlQuery *query = const_cast<QSqlQuery*>(m_db_worker->getCurrenciesOnExchange());

    m_currencies_on_exchange.clear();
    while(query->next())
    {
        CurrencyOnExchange currencyOnExchange;
        currencyOnExchange.currency_title  = query->value("currency_title").toString();
        currencyOnExchange.currency_code  = query->value("currency_code").toInt();
        beginResetModel();
        m_currencies_on_exchange.push_back(currencyOnExchange);
        endResetModel();
    }
}
