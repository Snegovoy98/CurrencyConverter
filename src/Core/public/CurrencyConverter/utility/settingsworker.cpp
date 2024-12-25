#include "settingsworker.h"
#include <QtConcurrent/QtConcurrent>

SettingsWorker::SettingsWorker(QObject *parent)
    : QObject{parent}
{
    m_db_worker = DBWorker::makeDB();
}

void SettingsWorker::saveSettings(const QString &key, const QVariant &value)
{
    QFuture<void> future = QtConcurrent::run([key, value, this]() {
        m_db_worker->saveSettings(key, value);
    });
}
