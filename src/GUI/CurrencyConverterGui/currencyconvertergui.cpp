#include "currencyconvertergui.h"

CurrencyConverterGui::CurrencyConverterGui() {}

bool CurrencyConverterGui::init(QQmlApplicationEngine *engine)
{
    engine->load("qrc:/CurrencyConverterModules/Main.qml");

    if(engine->rootObjects().isEmpty())
        return false;

    return true;
}
