#include "currencyonexchangemodel.h"
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CurrencyOnExchangeModel::CurrencyOnExchangeModel(QObject *parent)
    : QAbstractListModel {parent}
{
    m_currencies = {
                    {840, "USD"}, {980, "UAH"}, {978, "EUR"}, {826, "GBP"}, {392, "JPY"}, {756, "CHF"},
                    {156, "CNY"}, {784, "AED"}, {971, "AFN"}, {973, "AOA"}, {944, "AZN"}, {975, "BGN"}, {108, "BIF"},
                    {986, "BRL"}, {933, "BYN"}, {124, "CAD"}, {976, "CDF"}, {152, "CLP"}, {170, "COP"}, {188, "CRC"},
                    {192, "CUP"}, {203, "CZK"}, {262, "DJF"}, {208, "DKK"}, {818, "EGP"}, {230, "ETB"}, {981, "GEL"},
                    {936, "GHS"}, {270, "GMD"}, {324, "GNF"}, {344, "HKD"}, {191, "HRK"}, {348, "HUF"}, {360, "IDR"},
                    {376, "ILS"}, {356, "INR"}, {368, "IQD"}, {352, "ISK"}, {400, "JOD"}, {404, "KES"}, {417, "KGS"},
                    {116, "KHR"}, {410, "KRW"}, {414, "KWD"}, {398, "KZT"}, {418, "LAK"}, {422, "LBP"}, {144, "LKR"},
                    {434, "LYD"}, {504, "MAD"}, {498, "MDL"}, {969, "MGA"}, {807, "MKD"}, {496, "MNT"}, {480, "MUR"},
                    {454, "MWK"}, {484, "MXN"}, {458, "MYR"}, {943, "MZN"}, {516, "NAD"}, {566, "NGN"}, {558, "NIO"},
                    {578, "NOK"}, {524, "NPR"}, {554, "NZD"}, {512, "OMR"}, {604, "PEN"}, {608, "PHP"}, {586, "PKR"},
                    {985, "PLN"}, {600, "PYG"}, {634, "QAR"}, {946, "RON"}, {941, "RSD"}, {682, "SAR"}, {690, "SCR"},
                    {938, "SDG"}, {752, "SEK"}, {702, "SGD"}, {694, "SLL"}, {706, "SOS"}, {968, "SRD"}, {748, "SZL"},
                    {764, "THB"}, {972, "TJS"}, {788, "TND"}, {949, "TRY"}, {901, "TWD"}, {834, "TZS"}, {800, "UGX"},
                    {858, "UYU"}, {860, "UZS"}, {704, "VND"}, {950, "XAF"}, {952, "XOF"}, {886, "YER"}, {710, "ZAR"}
                   };

}

int CurrencyOnExchangeModel::rowCount(const QModelIndex &parent) const
{
    return m_currencies_on_exchange.count();
}

QVariant CurrencyOnExchangeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role < CurrencyOnExchangeCode)
        return {};

    const int rowIndex = index.row();

    switch (role)
    {
        case CurrencyOnExchangeCode:
            return m_currencies_on_exchange.at(rowIndex).currency_code;

        case CurrencyOnExchangeValue:
        {
           // qDebug() << m_currencies_on_exchange.at(rowIndex).currency_value;
            return m_currencies_on_exchange.at(rowIndex).currency_value;
        }
        default:
            break;
    }

    return {};
}

QHash<int, QByteArray> CurrencyOnExchangeModel::roleNames() const
{
    m_roles[CurrencyOnExchangeCode]  = "currency_code";
    m_roles[CurrencyOnExchangeValue] = "currency_value";

    return m_roles;
}

void CurrencyOnExchangeModel::fetchCurrencyData()
{
    qDebug() << "Fetching data ...";
    return;
}

void CurrencyOnExchangeModel::parseReply(const QByteArray &reply)
{
    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(reply, &parseError);

    if(parseError.error != QJsonParseError::NoError)
    {
        qDebug() << parseError.errorString();
    }
    else
    {
        QList<int> savedCurrencyA;
        for (const auto & object: document.array().toVariantList())
        {
            CurrencyOnExchange currencyOnExchange;
            currencyOnExchange.currency_code = object.toJsonValue()["currencyCodeB"].toInt();
            currencyOnExchange.currency_value = m_currencies[currencyOnExchange.currency_code];

            if(!savedCurrencyA.contains(currencyOnExchange.currency_code))
            {
                savedCurrencyA.push_back(currencyOnExchange.currency_code);
                beginResetModel();
                m_currencies_on_exchange.push_back(currencyOnExchange);
                endResetModel();
            }
        }
    }
}
