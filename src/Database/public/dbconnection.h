#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QObject>
#include <QRunnable>
#include <QSqlDatabase>
#include "sqlscriptexecutor.h"
#include <QScopedPointer>

/*!
 * @brief The DBConnection class - uses for connection to SQLiteDB
 */
class DBConnection : public QObject, public QRunnable
{
    Q_OBJECT
public:
    DBConnection(const DBConnection &other) = delete;
    void operator=(const DBConnection &) = delete;
    /*!
     * @brief getInstance - create and return one instance of DBConnection class.
     * @param database - current database connection.
     * @return - instance of DBConnection class.
     */
    static DBConnection *getInstance(QSqlDatabase * database);
    ~DBConnection();
    /*!
     * @brief  - open connection to database
     */
    void run();
signals:
    void dbOpened();
 private:
     explicit DBConnection(QSqlDatabase * database, QObject *parent = nullptr);
     /*!
      * @brief configureDatabase - configure database paramters.
      */
    void configureDatabase();
    static inline DBConnection *m_db_connection = nullptr;
    QSqlDatabase * m_database = nullptr;
    static inline QString m_filename;
    QScopedPointer<SQLScriptExecutor> m_executor;
};

#endif // DBCONNECTION_H
