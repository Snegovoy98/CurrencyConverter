#include "translator.h"
#include <QGuiApplication>
#include <QDir>

Translator::Translator(QQmlEngine *engine, QObject *parent)
    : QObject{parent}
{
    m_engine = engine;
    m_translator = new QTranslator(this);
}

void Translator::setLanguage(const QString &languageCode)
{
    if(m_translator->load(QString("translations_%1").arg(languageCode).toLatin1(), ":/"))
    {
        if(qApp->installTranslator(m_translator))
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
