#ifndef SALES_H
#define SALES_H

#include "SalesPerson.h"

class Sales : public SalesPerson {
public:
    Sales(const std::string& position,const std::string& employee_name, const std::string& id = "", const std::string& managerId = "");
    double getCommission() const override;
};

#endif // SALES_H
