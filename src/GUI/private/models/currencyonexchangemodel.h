#ifndef CURRENCYONEXCHANGEMODEL_H
#define CURRENCYONEXCHANGEMODEL_H

#include <QAbstractListModel>
#include <QPointer>
#include "../../../Interfaces/public/ICurrencyModel.h"

/*!
 * @brief The CurrencyOnExchangeModel class - model which store currency data for exchange.
 */
class CurrencyOnExchangeModel : public QAbstractListModel, public ICurrencyModel
{
    Q_OBJECT

    enum Roles
    {
        CurrencyOnExchangeCode = Qt::UserRole + 1,
        CurrencyOnExchangeValue
    };

    struct CurrencyOnExchange
    {
        int currency_code;
        QString currency_value;
    };

public:
   explicit CurrencyOnExchangeModel(QObject *parent = nullptr);

   int rowCount(const QModelIndex &parent) const override;
   QVariant data(const QModelIndex &index, int role) const override;
   QHash<int, QByteArray> roleNames() const override;

   /*!
    * @brief fetchCurrencyData - this method fetch data from the service.
    */
   Q_INVOKABLE void fetchCurrencyData() override;

public slots:
   void parseReply(const QByteArray &reply) override;

private: 
   static inline QHash<int, QByteArray> m_roles;
   QList<CurrencyOnExchange> m_currencies_on_exchange;
   QMap<int, QString> m_currencies;
};

#endif // CURRENCYONEXCHANGEMODEL_H
