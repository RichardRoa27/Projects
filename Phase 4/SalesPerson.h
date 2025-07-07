#ifndef SALESPERSON_H
#define SALESPERSON_H

#include <vector>
#include <string>

class SalesPerson {

private:
    std::string position;
    std::string employee_name;
    std::string salesPersonID;
    std::string managerID;
    double grossSales;
    double totalSales;
    std::vector<SalesPerson*> subordinates;

public:
    SalesPerson(const std::string& position, const std::string& employee_name, const std::string& id, const std::string& managerId);
    virtual ~SalesPerson();

    std::string getEmployee_name() const;
    std::string getPosition() const;
    void setGrossSales(double sales);
    double getGrossSales() const;
    void addToTotalSales(double sales);
    double getTotalSales() const;
    std::string getSalesPersonID() const;
    std::string getManagerID() const;

    virtual double getCommission() const = 0;  // Pure virtual function

    void addSubordinate(SalesPerson* subordinate);
    double getSubordinateSales() const;  // Summing sales of direct subordinates
    double getTotalSubordinateSales() const;  // Summing sales of all subordinates (recursive)
};

#endif

