#ifndef MESSAGESHOWER_H
#define MESSAGESHOWER_H

#include <QObject>

class MessageShower : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ getMessage WRITE setMessage NOTIFY messageChanged FINAL)
public:
    explicit MessageShower(QObject *parent = nullptr);

    QString getMessage() const;
public slots:
    void setMessage(const QString &newMessage);

signals:
    void messageChanged();
private:
    QString m_message;
};

#endif // MESSAGESHOWER_H
