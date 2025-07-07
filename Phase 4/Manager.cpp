#include "Manager.h"

Manager::Manager(const std::string& position,const std::string& employee_name, const std::string& id, const std::string& managerId)
    : Supervisor(position,employee_name, id, managerId) {}

double Manager::getCommission() const {
    return (0.065 * getGrossSales()) + (getTotalSales()*0.03)  ;
}