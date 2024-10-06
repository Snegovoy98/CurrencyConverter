#include "currencyconvertergui.h"
#include <QGuiApplication>
#include <QQuickStyle>
#include <QQmlContext>

CurrencyConverterGui::CurrencyConverterGui() {}

bool CurrencyConverterGui::init(QQmlApplicationEngine *engine)
{
    m_translator = new Translator(engine);

    #ifdef Q_OS_MACOS
        m_os_style = "macOS";
    #else
        m_os_style = "iOS";
    #endif

    QQuickStyle::setStyle(m_os_style);

    engine->addImportPath(":/");

    engine->rootContext()->setContextProperty("translator", m_translator.get());

    engine->load("qrc:/CurrencyConverterModules/Main.qml");

    if(engine->rootObjects().isEmpty())
        return false;

    return true;
}
