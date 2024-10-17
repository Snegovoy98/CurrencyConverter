#ifndef CURRENCYTOEXCHANGEMODEL_H
#define CURRENCYTOEXCHANGEMODEL_H

#include <QAbstractListModel>
#include "../../../Interfaces/public/ICurrencyModel.h"

class CurrencyToExchangeModel : public QAbstractListModel, public ICurrencyModel
{
    Q_OBJECT

    enum Roles {
        CurrencyToExchangeValue = Qt::UserRole + 1,
        Date,
        CrossRate
    };

    struct CurrencyToExchangeData
    {
        int currency_on_exchange_code;
        QString currency_to_exchange_value;
        QString date;
        double rate_cross;
    };

public:
    explicit CurrencyToExchangeModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    void fetchCurrencyData();

public slots:
    void parseReply(const QByteArray &reply);

private:
    static inline QHash<int, QByteArray> m_roles;
    QList<CurrencyToExchangeData> m_currencies_to_exchange;
    QMap<int, QString> m_currencies;
};

#endif // CURRENCYTOEXCHANGEMODEL_H
