#include <QGuiApplication>
#include "currencyconvertergui.h"
#include "translator.h"

CurrencyConverterGui::CurrencyConverterGui() {}

bool CurrencyConverterGui::init(QQmlApplicationEngine *engine)
{
    Translator translator(engine);

    translator.setLanguage("ru");

    engine->load("qrc:/CurrencyConverterModules/Main.qml");

    if(engine->rootObjects().isEmpty())
        return false;

    return true;
}
