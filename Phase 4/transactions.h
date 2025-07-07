#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>

class transactions {
public:
    transactions();
    transactions(const std::string& id, const std::string& sales_person_id, const std::string& order_number);
    
    // Getters
    std::string getid() const;
    std::string getsalespersonid() const;
    std::string getordernumber() const;

private:
    std::string id;
    std::string sales_person_id;
    std::string order_number;
};

#endif