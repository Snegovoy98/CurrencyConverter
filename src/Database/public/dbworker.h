#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QSqlQuery>
#include <QScopedPointer>
#include <QJsonDocument>
#include <QSemaphore>

class DBWorker : public QObject
{
    Q_OBJECT
public:
    static DBWorker* makeDB();
    ~DBWorker();
    DBWorker(const DBWorker &other) = delete;
    void operator=(const DBWorker &other) = delete;
    void saveSettings(const QString &settingName, const QVariant &settingValue);
    const QVariant& getSettingBySettingName(const QString &settingName);
    void loadCurrenciesToDB(const QJsonDocument &document);
    void clearCurrencies();
    void saveHistoryOfExchanges(const QString &currencyOnExchageTitle,
                                                const double &valuePerUnit,
                                                const QString &currencyToExchageTitle,
                                                const double &exchangedSum);
    const QSqlQuery* getHistoryOfExchanges();
    const QSqlQuery* getCurrenciesOnExchange();
    const QSqlQuery* getCurrenciesToExchangeByOnExchangeCode(const int & onExchangeCode);

signals:
    void errorHappened(const QString &errorMessage);
    void historySaved();

private:
    bool isSettingExists(const QString &settingName);
    explicit DBWorker(QObject *parent = nullptr);
    QScopedPointer<QSqlQuery>m_query;
    QScopedPointer<QSemaphore> m_semaphore;
    QVariant m_setting;
    inline static DBWorker* m_db_worker = nullptr;
    const QString m_db_connection_name;
    const int m_max_threads;
    inline static int connectionsCount = 0;
};

#endif // DBWORKER_H
