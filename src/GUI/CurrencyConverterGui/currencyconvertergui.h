#ifndef CURRENCYCONVERTERGUI_H
#define CURRENCYCONVERTERGUI_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QPointer>
#include "CurrencyConverter/utility/servicemanager.h"
#include "translator.h"

class CurrencyConverterGui
{
public:
    CurrencyConverterGui();

    bool init(QQmlApplicationEngine *engine);

private:
    QString m_os_style;
    QPointer<Translator> m_translator = nullptr;
    QPointer<ServiceManager> m_service_manager;
};

#endif // CURRENCYCONVERTERGUI_H
