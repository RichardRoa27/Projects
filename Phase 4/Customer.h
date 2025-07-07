
#ifndef CUSTOMER_H
#define CUSTOMER_H


#include <string>
using namespace std;

class Customer{
public:

    Customer();
    Customer(const std::string& id,const std::string& Password,const std::string& FirstName,const std::string& 
    LastName,const std::string& address, const std::string& city,
    const std::string& state, const std::string& ZipCode);
    
    //getters
    std::string getid() const;
    std::string getPassword() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getaddress() const;
    std::string getcity() const;
    std::string getstate() const;
    std::string getZipCode() const;

    void setPassword(const string& newPassword);

    string toString(); 

private:
    
    std::string id;
    std::string Password;
    std::string FirstName;
    std::string LastName;
    std::string address;
    std::string city;
    std::string state;
    std::string ZipCode;
    
    
    
};

#endif

