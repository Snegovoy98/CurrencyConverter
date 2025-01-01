#ifndef HISTORYEXCHANGESMODEL_H
#define HISTORYEXCHANGESMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QDateTime>
#include "../Database/public/dbworker.h"

class HistoryExchangesModel : public QAbstractListModel
{
    Q_OBJECT

    enum Roles
    {
        CURRENCY_ON_EXCHANGE_TITLE,
        VALUE_PER_UNIT,
        CURRENCY_TO_EXCHANGE_TITLE,
        EXCHANGED_SUM,
        EXCHANGE_DATE
    };

    struct HistoryExchagesData
    {
        QString m_currency_on_exchange_title;
        double m_value_per_unit;
        QString m_currency_to_exchange_title;
        double m_exchanged_sum;
        QString m_exchange_date;
    };

public:
    explicit HistoryExchangesModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE void saveHistory(const QString &currencyOnExchageTitle,
                                                    const double &valuePerUnit,
                                                    const QString &currencyToExchageTitle,
                                                    const double &exchangedSum);

public slots:
    void fetchExchangesHistory();

private:
    DBWorker *m_db_worker = nullptr;
    inline static QHash<int, QByteArray> m_roles;
    QList<HistoryExchagesData> m_data_list;
};

#endif // HISTORYEXCHANGESMODEL_H
