#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <QObject>
#include <QPointer>
#include <QNetworkAccessManager>
#include <QNetworkReply>


/*!
 * @brief The ServiceManager class - uses for sending requests to the services.
 */
class ServiceManager : public QObject
{
    Q_OBJECT
public:
    explicit ServiceManager(QObject *parent = nullptr);

    /*!
     * @brief get    - method used for sending get requests to the service.
     * @param url    - link on which will be sending request.
     * @param params - params for formating full link.
     */
    void get(const QString &url, const QHash<QString, QVariant> &params);

    /*!
     * @brief post - method used for sending post requests to the service.
     * @param url  - link on which will be sending request.
     * @param data - params for formating full link.
     */
    void post(const QString &url, const QByteArray &data);

signals:
    /*!
     * @brief replyGetted - signal which emmited when reply was getted.
     * @param reply - data which was getted from a service.
     */
    void replyGetted(const QString &reply);

private:
    static inline QString m_access_token;
    QPointer<QNetworkReply> m_reply = nullptr;
    QPointer<QNetworkAccessManager> m_manager = nullptr;
};

#endif // SERVICEMANAGER_H
