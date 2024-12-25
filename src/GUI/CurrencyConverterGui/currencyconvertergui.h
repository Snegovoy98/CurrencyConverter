#ifndef CURRENCYCONVERTERGUI_H
#define CURRENCYCONVERTERGUI_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QScopedPointer>
#include "translator.h"
#include "../../Core/public/CurrencyConverter/utility/settingsworker.h"

class CurrencyConverterGui
{
public:
    CurrencyConverterGui();

    bool init(QQmlApplicationEngine *engine);

private:
    QString m_os_style;
    QScopedPointer<Translator> m_translator;
    QScopedPointer<SettingsWorker> m_settings_worker;
};

#endif // CURRENCYCONVERTERGUI_H
