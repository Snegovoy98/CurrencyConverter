#ifndef CURRENCYTOEXCHANGEMODEL_H
#define CURRENCYTOEXCHANGEMODEL_H

#include <QAbstractListModel>
#include "../Database/public/dbworker.h"

class CurrencyToExchangeModel : public QAbstractListModel
{
    Q_OBJECT

    enum Roles {
        CurrencyToExchangeTitle = Qt::UserRole + 1,
        CrossRate
    };

    struct CurrencyToExchangeData
    {
        QString currency_to_exchange_title;
        double rate_cross;
    };

public:
    explicit CurrencyToExchangeModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    /*!
     * @brief fetchCurrencyData -  this method fetch data from the database.
     * @param currencyCode - currency_on_exchange_code
     */
    Q_INVOKABLE void fetchCurrencyData(const int &currencyCode);

private:
    DBWorker *m_db_worker = nullptr;
    static inline QHash<int, QByteArray> m_roles;
    QList<CurrencyToExchangeData> m_currencies_to_exchange;
};

#endif // CURRENCYTOEXCHANGEMODEL_H
