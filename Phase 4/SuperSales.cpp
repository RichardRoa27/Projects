#include "SuperSales.h"

SuperSales::SuperSales(const std::string& position,const std::string& employee_name, const std::string& id, const std::string& managerId)
    : Sales(position,employee_name, id, managerId) {}

double SuperSales::getCommission() const {
    return 0.065 * getGrossSales();
}
