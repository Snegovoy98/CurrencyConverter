#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QObject>
#include <QRunnable>
#include <QSqlDatabase>

class DBConnection : public QObject, public QRunnable
{
    Q_OBJECT
public:
    DBConnection(const DBConnection &other) = delete;
    void operator=(const DBConnection &) = delete;
    static DBConnection *GetInstance(QSqlDatabase * database);
    ~DBConnection();
    void run();
signals:

 private:
     explicit DBConnection(QSqlDatabase * database, QObject *parent = nullptr);
     void configureDatabase();
    static inline DBConnection *dbConnection = nullptr;
     QSqlDatabase * database = nullptr;
    static inline QString filename;
};

#endif // DBCONNECTION_H
