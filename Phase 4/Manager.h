#ifndef MANAGER_H
#define MANAGER_H

#include "Supervisor.h"

class Manager : public Supervisor {
public:
    Manager(const std::string& position,const std::string& employee_name, const std::string& id = "", const std::string& managerId = "");
    double getCommission() const override;
};

#endif
