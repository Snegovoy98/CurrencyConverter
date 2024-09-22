#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QTranslator>
#include <QPointer>
#include <QQmlEngine>

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(QQmlEngine *engine, QObject *parent = nullptr);

    Q_INVOKABLE void setLanguage(const QString &lanugageCode);
signals:
    void errorChanged(const QString &error);

private:
    QQmlEngine *m_engine = nullptr;
    QPointer<QTranslator> m_translator;
};

#endif // TRANSLATOR_H
