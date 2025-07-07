#ifndef ORDER_H
#define ORDER_H


#include <string>
using namespace std;

class Order{
    
    public:

    Order();
    Order(const std::string& order_number,const std::string& date,
    const std::string& quantity,const std::string& amount_paid);
    
    //getters
    std::string getorder_number() const;
    std::string getdate() const;
    std::string getquantity() const;
    std::string getamount_paid() const;


    string toString(); 
    private:
    
    std::string order_number;
    std::string date;
    std::string quantity;
    std::string amount_paid;
    
};


#endif