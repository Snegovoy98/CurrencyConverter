#include "dbconnection.h"
#include <QSqlError>
#include <QFile>
#include <QStandardPaths>
#include <QDir>

DBConnection::DBConnection(QSqlDatabase * database, QObject *parent)
    : QObject{parent}
{
    this->database = database;
    configureDatabase();
}

void DBConnection::configureDatabase()
{
    if(!this->database->isValid())
    {
        this->database = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));

        if(!database->isValid())
        {
            qFatal("Cannot add database: %s", qPrintable(database->lastError().text()));
        }
    }

    const QDir dbLocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    if(!dbLocation.mkpath("."))
    {
        qFatal("Failed create writable directory at %s", qPrintable(dbLocation.absolutePath()));
    }

    filename = dbLocation.absolutePath() + "/convertions_db.sqlite3";
    database->setDatabaseName(filename);
}

DBConnection *DBConnection::GetInstance(QSqlDatabase *database)
{
    if(dbConnection == nullptr) {
        dbConnection = new DBConnection(database);
    }

    return dbConnection;
}

DBConnection::~DBConnection()
{
    delete database;
}

void DBConnection::run()
{
   bool isOpen =  database->open();

   if(!isOpen)
   {
       qFatal("Cannot open database: %s", qPrintable(database->lastError().text()));
       QFile::remove(filename);
   }
}
