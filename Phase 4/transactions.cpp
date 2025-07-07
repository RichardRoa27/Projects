#include "transactions.h"

transactions::transactions() {}

transactions::transactions(const std::string& id, const std::string& sales_person_id, const std::string& order_number)
    : id(id), sales_person_id(sales_person_id), order_number(order_number) {}

std::string transactions::getid() const {
    return id;
}

std::string transactions::getsalespersonid() const {
    return sales_person_id;
}

std::string transactions::getordernumber() const {
    return order_number;
}