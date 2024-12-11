#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QSqlDatabase>
#include <QThreadPool>
#include "CurrencyConverterGui/currencyconvertergui.h"
#include "../Database/public/dbconnection.h"

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

    QSqlDatabase database = QSqlDatabase::database();
    DBConnection *connection = DBConnection::GetInstance(&database);

    QThreadPool pool = QThreadPool::globalInstance();
    pool.start(connection);

    CurrencyConverterGui currencyConverterGui;

    currencyConverterGui.init(&engine);

    return app.exec();
}
