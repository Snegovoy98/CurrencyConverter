#include "dbconnection.h"
#include <QSqlError>
#include <QFile>
#include <QStandardPaths>
#include <QDir>

DBConnection::DBConnection(QSqlDatabase * database, QObject *parent)
    : QObject{parent}
{
    this->m_database = database;
    m_executor.reset(new SQLScriptExecutor());
    configureDatabase();
}

void DBConnection::configureDatabase()
{
    if(!this->m_database->isValid())
    {
        this->m_database = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "mainConnection"));

        if(!m_database->isValid())
        {
            qFatal("Cannot add database: %s", qPrintable(m_database->lastError().text()));
        }
    }

    const QDir dbLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    if(!dbLocation.mkpath("."))
    {
        qFatal("Failed create writable directory at %s", qPrintable(dbLocation.absolutePath()));
    }

    m_filename = dbLocation.absolutePath() + "/convertions_db.sqlite3";
    m_database->setDatabaseName(m_filename);
}

DBConnection *DBConnection::getInstance(QSqlDatabase *database)
{
    if(m_db_connection == nullptr) {
        m_db_connection = new DBConnection(database);
    }

    return m_db_connection;
}

DBConnection::~DBConnection()
{
    delete m_database;
}

void DBConnection::run()
{
   bool isOpen = m_database->open();

   if(!isOpen)
   {
       qFatal("Cannot open database: %s", qPrintable(m_database->lastError().text()));
       QFile::remove(m_filename);
   }

   m_executor->createTables();
}
