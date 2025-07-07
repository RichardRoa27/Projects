#include "Order.h"


Order::Order(){
    
    }
        
    Order::Order(const std::string& order_number, const std::string& date, const std::string& quantity, const std::string& amount_paid)
    : order_number(order_number), date(date),quantity(quantity), amount_paid(amount_paid) {
    // Constructor with parameters to set member variables.
    }
    
    std::string Order::getorder_number() const {
        return order_number;
    }
    
    std::string Order::getdate() const {
        return date;
    }
    
    std::string Order::getquantity() const {
        return quantity;
    }
    
    std::string Order::getamount_paid() const {
        return amount_paid;
    }