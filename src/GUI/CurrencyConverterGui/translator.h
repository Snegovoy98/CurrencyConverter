#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QTranslator>
#include <QScopedPointer>
#include <QQmlEngine>
#include "../Database/public/dbworker.h"

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(QQmlEngine *engine, QObject *parent = nullptr);

    Q_INVOKABLE void setLanguage(const QString &lanugageCode);
signals:
    void errorChanged(const QString &error);

private:
    const QString loadSavedLanguage();
    QQmlEngine *m_engine = nullptr;
    QScopedPointer<QTranslator> m_translator;
    DBWorker *m_db_worker;
};

#endif // TRANSLATOR_H
