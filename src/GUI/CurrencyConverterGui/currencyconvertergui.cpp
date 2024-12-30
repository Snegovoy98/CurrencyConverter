#include "currencyconvertergui.h"
#include <QGuiApplication>
#include <QQuickStyle>
#include <QQmlContext>
#include <QObject>
#include "../private/models/currencyonexchangemodel.h"
#include "../private/models/currencytoexchangemodel.h"
#include "../private/models/historyexchangesmodel.h"

CurrencyConverterGui::CurrencyConverterGui() {}

bool CurrencyConverterGui::init(QQmlApplicationEngine *engine)
{

    m_translator.reset(new Translator(engine));
    m_settings_worker.reset(new SettingsWorker());
    m_message_shower.reset(new MessageShower());

    QObject::connect(m_translator.get(), &Translator::errorChanged, m_message_shower.get(), &MessageShower::setMessage);

    #ifdef Q_OS_MACOS
        m_os_style = "macOS";
    #else
        m_os_style = "iOS";
    #endif

    QQuickStyle::setStyle(m_os_style);

    engine->addImportPath("qrc:/");

    const QString languageCode = m_translator->loadSavedLanguage();

    if(languageCode != "")
        m_translator->setLanguage(languageCode);

    engine->rootContext()->setContextProperty("translator", m_translator.get());
    engine->rootContext()->setContextProperty("settingsWorker", m_settings_worker.get());
    engine->rootContext()->setContextProperty("messageShower", m_message_shower.get());

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
