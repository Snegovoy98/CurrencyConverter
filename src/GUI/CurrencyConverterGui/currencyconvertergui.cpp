#include "currencyconvertergui.h"
#include <QGuiApplication>
#include <QQuickStyle>
#include <QQmlContext>
#include "../private/models/currencyonexchangemodel.h"
#include "../private/models/currencytoexchangemodel.h"

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

    m_service_manager = new ServiceManager();

    engine->rootContext()->setContextProperty("translator", m_translator.get());
    engine->rootContext()->setContextProperty("serviceManager", m_service_manager.get());

    qmlRegisterType<CurrencyOnExchangeModel>("com.preobrazhenskyi.currency_on_exchange_model", 1, 0, "CurrencyOnExchangeModel");
    qmlRegisterType<CurrencyToExchangeModel>("com.preobrazhenskyi.currency_to_exchange_model", 1, 0, "CurrencyToExchangeModel");

    engine->load("qrc:/CurrencyConverterModules/Main.qml");

    if(engine->rootObjects().isEmpty())
        return false;

    return true;
}
