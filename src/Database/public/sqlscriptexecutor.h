#ifndef SQLSCRIPTEXECUTOR_H
#define SQLSCRIPTEXECUTOR_H

#include <QObject>

class SQLScriptExecutor : public QObject
{
    Q_OBJECT
public:
    explicit SQLScriptExecutor(QObject *parent = nullptr);

public slots:
        void createTables();

private:
    void readScript(const QString &filePath);
    QString m_script;
};

#endif // SQLSCRIPTEXECUTOR_H
