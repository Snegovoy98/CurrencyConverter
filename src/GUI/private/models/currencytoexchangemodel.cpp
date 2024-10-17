#include "currencytoexchangemodel.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CurrencyToExchangeModel::CurrencyToExchangeModel(QObject *parent)
    : QAbstractListModel{parent}
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

int CurrencyToExchangeModel::rowCount(const QModelIndex &parent) const
{
    return m_currencies_to_exchange.count();
}

QVariant CurrencyToExchangeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role < CurrencyToExchangeValue)
        return {};

    const int indexRow = index.row();

    switch (role)
    {
        case CurrencyToExchangeValue:
            return m_currencies_to_exchange.at(indexRow).currency_to_exchange_value;

        case Date:
            return m_currencies_to_exchange.at(indexRow).date;

        case CrossRate:
            return m_currencies_to_exchange.at(indexRow).rate_cross;
        default:
            break;
    }


    return {};
}

QHash<int, QByteArray> CurrencyToExchangeModel::roleNames() const
{
    m_roles[CurrencyToExchangeValue] = "currency_value";
    m_roles[Date] = "date";
    m_roles[CrossRate] = "cross_rate";

    return m_roles;
}

void CurrencyToExchangeModel::fetchCurrencyData()
{
    qDebug() << "Fetching data ...";
    return;
}

void CurrencyToExchangeModel::parseReply(const QByteArray &reply)
{
    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(reply, &parseError);

    if(parseError.error != QJsonParseError::NoError)
    {
        qDebug() << parseError.errorString();
    }
    else
    {
        QString currencyValue;
        for (const auto &object: document.array().toVariantList())
        {
            currencyValue = m_currencies[object.toJsonValue()["currencyCodeA"].toInt()];
            if(currencyValue != "")
            {
                CurrencyToExchangeData currencyToExchangeData;
                currencyToExchangeData.currency_on_exchange_code  = object.toJsonValue()["currencyCodeB"].toInt();
                currencyToExchangeData.currency_to_exchange_value  = currencyValue;
                currencyToExchangeData.date       = object.toJsonValue()["date"].toString();
                currencyToExchangeData.rate_cross = object.toJsonValue()["rateCross"].toDouble();
                beginResetModel();
                m_currencies_to_exchange.push_back(currencyToExchangeData);
                endResetModel();
            }
        }
    }
}
