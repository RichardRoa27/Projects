#include "Sales.h"

Sales::Sales(const std::string& position,const std::string& employee_name, const std::string& id, const std::string& managerId)
    : SalesPerson(position,employee_name, id, managerId) {}

double Sales::getCommission() const {
    return 0.05 * getGrossSales();
}
