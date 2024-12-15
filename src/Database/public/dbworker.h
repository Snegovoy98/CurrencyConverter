#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QSqlQuery>
#include <QScopedPointer>

class DBWorker : public QObject
{
    Q_OBJECT
public:
    static DBWorker* makeDB();
    void saveSettings(const QMap<QString, QVariant> &parameters);
   const QVariant& getSettingBySettingName(const QString &settingName);

    void saveHistoryOfExchanges(const QString &currencyOnExchageTitle,
                                                const double &valuePerUnit,
                                                const QString &currencyToExchageTitle,
                                                const double &exchangedSum);
   const QSqlQuery* getHistoryOfExchanges();

signals:
    void errorHappened(const QString &errorMessage);
    void historySaved();

private:
    explicit DBWorker(QObject *parent = nullptr);
    QScopedPointer<QSqlQuery>m_query;
    QVariant m_setting;
    inline static DBWorker* m_db_worker = nullptr;
};

#endif // DBWORKER_H
