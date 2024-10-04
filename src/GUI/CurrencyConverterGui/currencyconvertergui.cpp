#include <QGuiApplication>
#include <QQuickStyle>
#include "currencyconvertergui.h"
#include "translator.h"

CurrencyConverterGui::CurrencyConverterGui() {}

bool CurrencyConverterGui::init(QQmlApplicationEngine *engine)
{
    Translator translator(engine);

    translator.setLanguage("ru");

    #ifdef Q_OS_MACOS
        m_os_style = "macOS";
    #else
        m_os_style = "iOS";
    #endif

    QQuickStyle::setStyle(m_os_style);

    engine->addImportPath(":/");

    engine->load("qrc:/CurrencyConverterModules/Main.qml");

    if(engine->rootObjects().isEmpty())
        return false;

    return true;
}
