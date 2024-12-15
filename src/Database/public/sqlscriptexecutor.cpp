#include "sqlscriptexecutor.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

SQLScriptExecutor::SQLScriptExecutor(QObject *parent)
    : QObject{parent}
{
    readScript(":/sql_scripts/tables_creation.sql");
}

void SQLScriptExecutor::createTables()
{
    if(m_script == "")
    {
        qWarning() << "Script is an empty execution not possible!";
        return;
    }

    {
        QSqlDatabase database = QSqlDatabase::cloneDatabase("mainConnection", "tableCreationConnection");
        database.open();
        QSqlQuery query(database);
        QStringList statements = m_script.split(";", Qt::SkipEmptyParts);

        for (const QString &statement : statements)
        {
            QString trimmedStatement = statement.trimmed();
            if(trimmedStatement.isEmpty())
            {
                continue;
            }

            if(!query.exec(trimmedStatement))
            {
                qDebug() << "Failed to execute statement:" << query.lastError().text();
                return;
            }
        }
    }
    QSqlDatabase::removeDatabase("tableCreationConnection");
}

void SQLScriptExecutor::readScript(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open SQL script file: " << file.errorString();
        return;
    }

    QTextStream in(&file);
    m_script = in.readAll();
}
