
#ifndef SUPERSALES_H
#define SUPERSALES_H

#include "Sales.h"

class SuperSales : public Sales {
public:
    SuperSales(const std::string& position,const std:: string& employe_name, const std::string& id = "", const std::string& managerId = "");
    double getCommission() const override;
};

#endif
