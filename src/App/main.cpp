#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include "CurrencyConverterGui/currencyconvertergui.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    CurrencyConverterGui currencyConverterGui;

    currencyConverterGui.init(&engine);

   return app.exec();
}
