#include "currencyconvertergui.h"
#include <QGuiApplication>
#include <QQuickStyle>
#include <QQmlContext>
#include "../private/models/currencyonexchangemodel.h"
#include "../private/models/currencytoexchangemodel.h"
#include "../private/models/historyexchangesmodel.h"

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

    engine->addImportPath("qrc:/");

    m_service_manager = new ServiceManager();

    engine->rootContext()->setContextProperty("translator", m_translator.get());
    engine->rootContext()->setContextProperty("serviceManager", m_service_manager.get());

    qmlRegisterType<CurrencyOnExchangeModel>("com.preobrazhenskyi.currency_on_exchange_model", 1, 0, "CurrencyOnExchangeModel");
    qmlRegisterType<CurrencyToExchangeModel>("com.preobrazhenskyi.currency_to_exchange_model", 1, 0, "CurrencyToExchangeModel");
    qmlRegisterType<HistoryExchangesModel>("com.preobrazhenskyi.history_exchanges_model", 1, 0, "HistoryExchangesModel");
    qmlRegisterSingletonType(QUrl(QStringLiteral("qrc:/CurrencyConverterModules/Common/Constants.qml")), "com.preobrazhenskyi.Constants", 1, 0, "Constants");
    qmlRegisterSingletonType(QUrl(QStringLiteral("qrc:/CurrencyConverterModules/Common/Theme.qml")), "com.preobrazhenskyi.Theme", 1, 0, "Theme");

    const QUrl url("qrc:/CurrencyConverterModules/Main.qml");
    engine->load(url);

    if(engine->rootObjects().isEmpty())
        return false;

    return true;
}
