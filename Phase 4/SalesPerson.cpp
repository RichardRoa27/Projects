#include "SalesPerson.h"

SalesPerson::SalesPerson(const std::string& position, const std::string& employee_name, const std::string& id, const std::string& managerId)
    : position(position), employee_name(employee_name), salesPersonID(id), managerID(managerId), grossSales(0.0), totalSales(0.0) {}

SalesPerson::~SalesPerson() {}

std::string SalesPerson::getEmployee_name() const {
    return employee_name;
}

std::string SalesPerson::getPosition() const {
    return position;
}

void SalesPerson::setGrossSales(double sales) {
    grossSales = sales;
}

double SalesPerson::getGrossSales() const {
    return grossSales;
}

void SalesPerson::addToTotalSales(double sales) {
    totalSales += sales;
}

double SalesPerson::getTotalSales() const {
    return totalSales;
}

std::string SalesPerson::getSalesPersonID() const {
    return salesPersonID;
}

std::string SalesPerson::getManagerID() const {
    return managerID;
}

void SalesPerson::addSubordinate(SalesPerson* subordinate) {
    subordinates.push_back(subordinate);
}

// Summing sales of direct subordinates
double SalesPerson::getSubordinateSales() const {
    double total = 0;
    for (const auto& sub : subordinates) {
        total += sub->getGrossSales();
    }
    return total;
}

// Summing sales of all subordinates, recursively
double SalesPerson::getTotalSubordinateSales() const {
    double total = getSubordinateSales();
    for (const auto& sub : subordinates) {
        total += sub->getTotalSubordinateSales();  // Recursive call to handle deeper levels
    }
    return total;
}