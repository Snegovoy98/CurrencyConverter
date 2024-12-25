#ifndef CURRENCYONEXCHANGEMODEL_H
#define CURRENCYONEXCHANGEMODEL_H

#include <QAbstractListModel>
#include <QPointer>
#include "../Database/public/dbworker.h"

/*!
 * @brief The CurrencyOnExchangeModel class - model which store currency data for exchange.
 */
class CurrencyOnExchangeModel : public QAbstractListModel
{
    Q_OBJECT

    enum Roles
    {
        CurrencyOnExchangeCode = Qt::UserRole + 1,
        CurrencyOnExchangeTitle
    };

    struct CurrencyOnExchange
    {
        int currency_code;
        QString currency_title;
    };

public:
   explicit CurrencyOnExchangeModel(QObject *parent = nullptr);

   int rowCount(const QModelIndex &parent) const override;
   QVariant data(const QModelIndex &index, int role) const override;
   QHash<int, QByteArray> roleNames() const override;

   /*!
    * @brief fetchCurrencyData - this method fetch data from the database.
    */
   void fetchCurrencyData();

private:
   DBWorker *m_db_worker = nullptr;
   static inline QHash<int, QByteArray> m_roles;
   QList<CurrencyOnExchange> m_currencies_on_exchange;
};

#endif // CURRENCYONEXCHANGEMODEL_H
