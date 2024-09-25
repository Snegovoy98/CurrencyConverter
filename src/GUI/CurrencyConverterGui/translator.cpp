#include "translator.h"

Translator::Translator(QQmlEngine *engine, QObject *parent)
    : QObject{parent}
{
    m_engine = engine;
    m_translator = new QTranslator(this);
}

void Translator::setLanguage(const QString &lanugageCode)
{
    if(m_translator->load(QString("translations_%1").arg(lanugageCode).toLatin1(), ":/"))
    {
       m_engine->retranslate();
    }
    else
    {
       QString error = "Translation file not found!";
       qDebug() << error;
       emit errorChanged(error);
    }
}
