#include "messageshower.h"

MessageShower::MessageShower(QObject *parent)
    : QObject{parent}
{}

QString MessageShower::getMessage() const
{
    return m_message;
}

void MessageShower::setMessage(const QString &newMessage)
{
    if (m_message == newMessage)
        return;
    m_message = newMessage;
    emit messageChanged();
}
