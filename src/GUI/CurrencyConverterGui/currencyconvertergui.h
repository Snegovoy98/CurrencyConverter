#ifndef CURRENCYCONVERTERGUI_H
#define CURRENCYCONVERTERGUI_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QScopedPointer>
#include "translator.h"
#include "../../Core/public/CurrencyConverter/utility/settingsworker.h"
#include "../../Core/public/CurrencyConverter/utility/messageshower.h"

class CurrencyConverterGui
{
public:
    CurrencyConverterGui();

    bool init(QQmlApplicationEngine *engine);

private:
    QString m_os_style;
    QScopedPointer<Translator> m_translator;
    QScopedPointer<SettingsWorker> m_settings_worker;
    QScopedPointer<MessageShower> m_message_shower;
};

#endif // CURRENCYCONVERTERGUI_H
