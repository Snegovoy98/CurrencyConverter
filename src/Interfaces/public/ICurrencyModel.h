#ifndef ICURRENCYMODEL_H
#define ICURRENCYMODEL_H
#include <QObject>

class ICurrencyModel {
public:
    virtual void fetchCurrencyData() = 0;
    virtual void fetchCurrencyData(const int &currencyCode) = 0;
};

#endif // ICURRENCYMODEL_H
