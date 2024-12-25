#include "translator.h"
#include <QGuiApplication>
#include <QDir>

Translator::Translator(QQmlEngine *engine, QObject *parent)
    : QObject{parent}
{
    m_engine = engine;
    m_translator.reset(new QTranslator(this));
    m_db_worker = DBWorker::makeDB();
    const QString languageCode = loadSavedLanguage();

    if(languageCode != "")
    {
        setLanguage(languageCode);
    }
}

void Translator::setLanguage(const QString &languageCode)
{
    if(m_translator->load(QString("translations_%1").arg(languageCode).toLatin1(), ":/"))
    {
        if(qApp->installTranslator(m_translator.get()))
        {
            m_engine->retranslate();
        }
    }
    else
    {
       QString error = "Translation file not found!";
       qDebug() << error;
       emit errorChanged(error);
    }
}

 const QString Translator::loadSavedLanguage()
{
    QString languageCode = m_db_worker->getSettingBySettingName("language").toString();
    return languageCode;
}
