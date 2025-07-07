#include "Customer.h"

    Customer::Customer(){
    
    }
        
    Customer::Customer(const std::string& id,const std::string& Password, const std::string& FirstName, const std::string& LastName,
    const std::string& address, const std::string& city,
    const std::string& state, const std::string& ZipCode)
    : id(id),Password(Password), FirstName(FirstName), LastName(LastName), address(address),
    city(city), state(state), ZipCode(ZipCode) {
    // Constructor with parameters to set member variables.
    }
    
    std::string Customer::getid() const {
        return id;
    }
    std::string Customer::getPassword() const {
        return Password;
    }
    
    
    std::string Customer::getFirstName() const {
        return FirstName;
    }
    
    std::string Customer::getLastName() const {
        return LastName;
    }
    
    std::string Customer::getaddress() const {
        return address;
    }
    
    std::string Customer::getcity() const {
        return city;
    }
    void Customer::setPassword(const string& newPassword) {
    Password = newPassword;
    }
    std::string Customer::getstate() const {
        return state;
    
    }
    std::string Customer::getZipCode() const {
        return ZipCode;
    }
