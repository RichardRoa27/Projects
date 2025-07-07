#include "Supervisor.h"

Supervisor::Supervisor(const std::string& position,const std::string& employee_name, const std::string& id, const std::string& managerId)
    : SuperSales(position,employee_name, id, managerId) {}

double Supervisor::getCommission() const {
    return (0.065 * getGrossSales()) +  (getTotalSales()*0.03) ;
}