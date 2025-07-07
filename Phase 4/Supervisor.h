
#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "SuperSales.h"

class Supervisor : public SuperSales {
public:
    Supervisor(const std::string& position,const std::string& employee_name, const std::string& id = "", const std::string& managerId = "");
    double getCommission() const override;
};

#endif
