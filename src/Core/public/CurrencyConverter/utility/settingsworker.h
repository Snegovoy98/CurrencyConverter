#ifndef SETTINGSWORKER_H
#define SETTINGSWORKER_H

#include <QObject>
#include "../Database/public/dbworker.h"

class SettingsWorker : public QObject
{
    Q_OBJECT
public:
    explicit SettingsWorker(QObject *parent = nullptr);

    Q_INVOKABLE void saveSettings(const QString &key, const QVariant &value);

private:
    DBWorker *m_db_worker;
};

#endif // SETTINGSWORKER_H
