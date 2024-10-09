#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
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

    app.setFont(QFont(QFontDatabase::families().at(8)));

    CurrencyConverterGui currencyConverterGui;

    currencyConverterGui.init(&engine);

    return app.exec();
}
