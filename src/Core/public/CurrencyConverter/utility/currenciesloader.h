#ifndef CURRENCIESLOADER_H
#define CURRENCIESLOADER_H

#include <QObject>
#include <QScopedPointer>
#include "servicemanager.h"
#include "../Database/public/dbworker.h"

class CurrenciesLoader : public QObject
{
    Q_OBJECT
public:
    explicit CurrenciesLoader(QObject *parent = nullptr);


public slots:
    void saveLastActivity();

private slots:
       void loadCurrencies(const QByteArray & reply);

private:
    QScopedPointer<ServiceManager> m_manager;
    DBWorker * m_db_worker;
};

#endif // CURRENCIESLOADER_H
