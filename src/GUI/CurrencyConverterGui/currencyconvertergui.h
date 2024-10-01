#ifndef CURRENCYCONVERTERGUI_H
#define CURRENCYCONVERTERGUI_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>

class CurrencyConverterGui
{
public:
    CurrencyConverterGui();

    bool init(QQmlApplicationEngine *engine);

private:
    QString m_os_style;
};

#endif // CURRENCYCONVERTERGUI_H
