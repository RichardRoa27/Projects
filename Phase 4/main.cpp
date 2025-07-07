/*Group number: 4
Group members: Myriam Arbid, Ebaad Rehman, Richard Gipson, Richard Roa

This code is a driven menu program that will use files like orders, customers, transactions, and rainbow tribbles
and use them to help add customers, sell trembles and manage customers information. We implemented a commission function that will help 
us calculate each supervisor, manager, etc commission, while also printing out the sale Staff. For the last phase we went ahead and created 
a menu system where the Customer will have to input their loginID instead of name or Customer ID. In the menu they are allowed to 
change their password, review their order history, place an order, or sign out. We also introduce a way where we decrypt their 
Password when they are trying to login in or set up a new password where it gets encrypted and store it back to the customer.txt file. 

*/

#include <iostream>
#include <vector>
#include <fstream>
#include "Customer.h"
#include "transactions.h"
#include "Order.h"
#include "SuperSales.h"
#include "SalesPerson.h"
#include "Sales.h"
#include "Supervisor.h"
#include "Manager.h"
#include <sstream>
#include <iomanip>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<Customer> Customerdata(){  // Function to load customer data from file

    
    vector<Customer> Customer_data;
    ifstream file("customers.txt");
    
    if(!file){
        cerr<< "Error, unable to open customer.txt file "<<endl; // Error message if file does not open
        return Customer_data;
    }
    
    string line;
    
    while(getline(file, line)){
        stringstream ss(line);
        
        string id,Password,FirstName,LastName,address,city,state,ZipCode;
        

        if(getline(ss,id,';')&&
        getline(ss,Password,';')&&
        getline(ss,FirstName,';')&&
        getline(ss,LastName,';')&&
        getline(ss,address,';')&&
        getline(ss,city,';')&&
        getline(ss,state,';')&&
        getline(ss,ZipCode,';')) 
        {
        Customer customer(id,Password,FirstName,LastName,address,city,state,ZipCode); // Calling the constructor 
        Customer_data.push_back(customer); // Store customer data in vector
        }

        
    
    }
    file.close(); // Close file after reading
    return Customer_data;
}

void CreateNewCustomer(const vector<Customer> Customer_data ){ // Function to write customer data back to file
    ofstream file("customers.txt");
    
    if(!file){
        cerr<< "Error, unable to open customer.txt file "<<endl;
    }
    
    for (const Customer& customer:Customer_data){ 
        file<<customer.getid()<<";"
            <<customer.getPassword()<<";"
            <<customer.getFirstName()<<";"
            <<customer.getLastName()<<";"
            <<customer.getaddress()<<";"
            <<customer.getcity()<<";"
            <<customer.getstate()<<";"
            <<customer.getZipCode()<<endl;
    }
    file.close(); // Close file after writing
}

vector<Order> orderData(){ // Function to read order data from file
    vector<Order> Order_Data;
    ifstream file("orders.txt");
    if(!file){
        cerr<<"Error, unable to open orders.txt file "<<endl;
        return Order_Data;
    }
    
    
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        
        string order_number,date,quantity, amount_paid;
        if(getline(ss,order_number,';')&&
        getline(ss,date,';')&&
        getline(ss,quantity,';')&&
        getline(ss,amount_paid,';')) 
        {
        Order order(order_number,date,quantity, amount_paid);//calling the constructor
        Order_Data.push_back(order);
        }
    }
    file.close();
    return Order_Data;
}

  
vector<transactions> transactionData(){ // Function to read transaction data from file
    vector<transactions> transactions_data;
    ifstream file("transactions.txt");
    
    if(!file){
        cerr<< "Error, unable to open transactions.txt file "<<endl;
        return transactions_data;
    }
    
    string line;
    
    while(getline(file, line)){
        stringstream ss(line);
        
        string id,sales_person_id,order_number;
        if (getline(ss,id,';')&&
	    getline(ss,sales_person_id, ';')&&
            getline(ss,order_number,';')) 
        {
        transactions transactions(id,sales_person_id,order_number); // Calling the constructor 
        transactions_data.push_back(transactions);// pushes transaction ito the end of the vector
        }
    }
    file.close();
    return transactions_data;
}


vector<SalesPerson*> salesStaff(){
    vector<SalesPerson*> salesstaff;
    ifstream file("salesStaff.txt");
    
    if(!file){
        cerr<< "Error, unable to open salesStaff.txt file "<<endl;
        return salesstaff;
    }
    
    string line;
    string Position,Employee_name,SalespersonID,BossID,grossSaless;
    while(getline(file, line)){
        stringstream ss(line);
        
        
        string id,order_number;
        if(getline(ss,Position,';')&&
        getline(ss,Employee_name,';')&&
        getline(ss,SalespersonID,';')&&
        getline(ss,BossID,';'));
        
        
        
       
        if(Position== "Sales"){
            salesstaff.push_back(new Sales(Position,Employee_name,SalespersonID,BossID));
        }
        else if(Position== "SuperSales"){
           salesstaff.push_back(new SuperSales(Position,Employee_name,SalespersonID,BossID));
        }
        else if(Position== "Supervisor"){
          salesstaff.push_back(new Supervisor(Position,Employee_name,SalespersonID,BossID));
        }
        else if(Position== "Manager"){
          salesstaff.push_back(new Manager(Position,Employee_name,SalespersonID,BossID));
        }
        
    }
    file.close();
    
   
    
    return salesstaff;
    
    
}

vector<SalesPerson*> setCommission(vector<SalesPerson*>& salesStaff, vector<Order>& order, vector<transactions>& transactionsList) {
    for (SalesPerson* Sperson : salesStaff) {
        string salesPersonID = Sperson->getSalesPersonID();
        double personalSales = 0.0;

        for (const transactions& transaction : transactionsList) {
            if (transaction.getsalespersonid() == salesPersonID) {
                for (const Order& orders : order) {
                    if (orders.getorder_number() == transaction.getordernumber()) {
                        double saleAmount = stod(orders.getamount_paid());
                        personalSales += saleAmount;
                    }
                }
            }
        }
        
        Sperson->setGrossSales(personalSales);
    }

    for (SalesPerson* sperson : salesStaff) {
        if (sperson->getPosition() == "Supervisor") {
            Supervisor* supervisor = dynamic_cast<Supervisor*>(sperson);
            if (supervisor) {
                double teamSales = 0.0;
                for (SalesPerson* worker : salesStaff) {
                    if (worker->getManagerID() == supervisor->getSalesPersonID()) {
                        teamSales += worker->getGrossSales();
                    }
                }
                supervisor->addToTotalSales(teamSales);
            }
        }
    }

    for (SalesPerson* sperson : salesStaff) {
        if (sperson->getPosition() == "Manager") {
            Manager* manager = dynamic_cast<Manager*>(sperson);
            if (manager) {
                double totalSales = 0.0;
                for (SalesPerson* subordinate : salesStaff) {
                    if (subordinate->getManagerID() == manager->getSalesPersonID()) {
                        totalSales += subordinate->getGrossSales();
                        if (subordinate->getPosition() == "Supervisor") {
                            Supervisor* supervisor = dynamic_cast<Supervisor*>(subordinate);
                            if (supervisor) {
                                totalSales += supervisor->getTotalSales();
                            }
                        }
                    }
                }
                manager->addToTotalSales(totalSales);
            }
        }
    }

    for (SalesPerson* sperson : salesStaff) {
        if (sperson->getPosition() == "Sales") {
            Sales* salesperson = dynamic_cast<Sales*>(sperson);
            if (salesperson) {
                salesperson->getCommission();
            }
        } else if (sperson->getPosition() == "SuperSales") {
            SuperSales* supersales = dynamic_cast<SuperSales*>(sperson);
            if (supersales) {
                supersales->getCommission();
            }
        } else if (sperson->getPosition() == "Supervisor") {
            Supervisor* supervisor = dynamic_cast<Supervisor*>(sperson);
            if (supervisor) {
                supervisor->getCommission();
            }
        } else if (sperson->getPosition() == "Manager") {
            Manager* manager = dynamic_cast<Manager*>(sperson);
            if (manager) {
                manager->getCommission();
            }
        }
    }

    return salesStaff;

}

void SalesReport(const vector<SalesPerson*>& salesstaff) {
    cout<<left<<setw(25)<<"Name"<<setw(15)<<"Position"<<setw(15)<<"Commission"<<endl;
    for(const auto& Sperson:salesstaff){
        double Commission=Sperson->getCommission();
        cout<<left<<setw(25)<<Sperson->getEmployee_name()<<setw(15)<<Sperson->getPosition()
        <<"$"<<fixed<<right<< setprecision(2) << setfill(' ') <<setw(6)<<Commission<<endl;
    }
}

void ViewOrder(const vector<Order>& order, string orderId){ // Function to view info of a specific order
    bool found = false;
    for(const Order& order : order){
        if(order.getorder_number()==orderId){
            cout<<"Order Number: "<<order.getorder_number()<<endl;
            cout<<"Date: "<<order.getdate()<<endl;
            cout<<"Quantity: "<<order.getquantity()<<endl;
            cout<<"Amount Paid: $"<<order.getamount_paid()<<endl;
            found= true;
            
            break;            
        }
        
    }
    if(!found){
        cout<<"Sorry but "<<orderId<<" not found"<<endl;// displays if there are no orders found
    }
}

// Function to process a customer sale
void CustomerSale(vector<Order>& order, const vector<Customer>& customer_data, vector<transactions>& transactions_data, const vector<SalesPerson*>& Staff){
    bool found= false;
    
    int newQTY;
    double newAmountPaid;
    string newDate, customer_name,customerID,salespersonID;
    
    // ... existing code ...
    cout << "Please enter Sales Person ID: ";
    cin >> salespersonID;
    
    // Check if salesperson exists
    bool validSalesperson = false;
    for (const SalesPerson* sp : Staff) {
        if (sp->getSalesPersonID() == salespersonID) {
            validSalesperson = true;
            break;
        }
    }
    if (!validSalesperson) {
        cout << "Invalid Sales Person ID!" << endl;
        return;
    }
    // ... rest of the function ...

    cout<<"Please enter Customer ID: "<<endl;
    cin>> customerID; // Take user input for customer ID
    
    for (const Customer& customer : customer_data) {
        if (customer.getid() == customerID) {
            customer_name = customer.getFirstName() + " " + customer.getLastName();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Sorry, but customer was not found!\nPlease try again!" << endl;
        return;
    }
    cout<<"                       Menu                         "<<endl;
	cout<<"===================================================="<<endl;
	cout<<"||                                                ||"<<endl;
	cout<<"||    1 tribbles                          $9.50   ||"<<endl;
	cout<<"||                                                ||"<<endl;
	cout<<"||    2 tribbles                          $16.50  ||"<<endl;
	cout<<"||                                                ||"<<endl;
	cout<<"||    3 tribbles                          $25.88  ||"<<endl;
	cout<<"||                                                ||"<<endl;
	cout<<"||    4 tribbles                          $28.15  ||"<<endl;
	cout<<"||                                                ||"<<endl;
	cout<<"||    5 tribbles                          $30.00  ||"<<endl;
	cout<<"||                                                ||"<<endl; 
	cout<<"===================================================="<<endl;
    
    cout<<"Enter Quantity (1 to 5)"<<endl;
    cin>>newQTY;
    
    if(newQTY<1 || newQTY>5){
        cout<<"Sorry, Please enter a number between 1 through 5"<<endl;
        return;
    }
    
    switch(newQTY){ // Assign price based on quantity
        case 1:
            newAmountPaid =9.50;
            break;
        case 2:
            newAmountPaid =16.15;
            break;    
        case 3:
            newAmountPaid =25.88;
            break;
        case 4:
            newAmountPaid =28.15;
            break;
        case 5:
            newAmountPaid =30.00;
            break;
        default:
            break;
    }
    
    cout << "Customer Name: " << customer_name << endl;
    cout << "Quantity: " << newQTY << endl;
    cout << "Amount Paid: $" << newAmountPaid << endl;

    //Generate order ID
    srand(time(0));
    int newOrderID = rand() % 90000 + 100000;
    cout << "Order Id: "<<newOrderID<<endl;
    
    
    //Generate current time
    time_t  t=time(nullptr);
    tm* current_time = localtime(&t);
    ostringstream date;
    date<<put_time(current_time,"%d-%m-%y");
    newDate= date.str();
    cout<< "Sales Date: "<<newDate<<endl;


    // Create new order
    Order newOrder(to_string(newOrderID), newDate, to_string(newQTY), to_string(newAmountPaid));
    order.push_back(newOrder);

    // Create new transaction
    transactions newPurchase(customerID, salespersonID, to_string(newOrderID));
    transactions_data.push_back(newPurchase);

    // Open orders file and append the new order
    ofstream file1("orders.txt", ios::app);
    if (!file1) {
        cerr << "Error, unable to open orders.txt file" << endl;
    } else {
        file1 << setw(6) << setfill('0') << newOrderID << ";" << newDate << ";" << newQTY << ";" << fixed << setprecision(2) << newAmountPaid << endl;
        file1.close();
    }

    // Open transactions file and append the new transaction
    ofstream file2("transactions.txt", ios::app);
    if (!file2) {
        cerr << "Error, unable to open transactions.txt file" << endl;
    } else {
        file2 << customerID << ";" << salespersonID<<";" <<setw(6) << setfill('0') << newOrderID << endl;
        file2.close();
    }
}


void CustomerPortalSale(vector<Order>& order, const vector<Customer>& customer_data, vector<transactions>& transactions_data,const string& LoginID){
    bool found= false;
    
    int newQTY;
    double newAmountPaid;
    string newDate, customer_name,customerID=LoginID,salespersonID="000000";
    

    for (const Customer& customer : customer_data) {
        if (customer.getid() == customerID) {
            customer_name = customer.getFirstName() + " " + customer.getLastName();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Sorry, but customer was not found!\nPlease try again!" << endl;
        return;
    }
    cout<<"                       Menu                         "<<endl;
	cout<<"===================================================="<<endl;
	cout<<"||                                                ||"<<endl;
	cout<<"||    1 tribbles                          $9.50   ||"<<endl;
	cout<<"||                                                ||"<<endl;
	cout<<"||    2 tribbles                          $16.50  ||"<<endl;
	cout<<"||                                                ||"<<endl;
	cout<<"||    3 tribbles                          $25.88  ||"<<endl;
	cout<<"||                                                ||"<<endl;
	cout<<"||    4 tribbles                          $28.15  ||"<<endl;
	cout<<"||                                                ||"<<endl;
	cout<<"||    5 tribbles                          $30.00  ||"<<endl;
	cout<<"||                                                ||"<<endl; 
	cout<<"===================================================="<<endl;
    
    cout<<"Enter Quantity (1 to 5)"<<endl;
    cin>>newQTY;
    
    if(newQTY<1 || newQTY>5){
        cout<<"Sorry, Please enter a number between 1 through 5"<<endl;
        return;
    }
    
    switch(newQTY){ // Assign price based on quantity
        case 1:
            newAmountPaid =9.50;
            break;
        case 2:
            newAmountPaid =16.15;
            break;    
        case 3:
            newAmountPaid =25.88;
            break;
        case 4:
            newAmountPaid =28.15;
            break;
        case 5:
            newAmountPaid =30.00;
            break;
        default:
            break;
    }
    
    cout << "Customer Name: " << customer_name << endl;
    cout << "Quantity: " << newQTY << endl;
    cout << "Amount Paid: $" << newAmountPaid << endl;

    //Generate order ID
    srand(time(0));
    int newOrderID = rand() % 90000 + 100000;
    cout << "Order Id: "<<newOrderID<<endl;
    
    
    //Generate current time
    time_t  t=time(nullptr);
    tm* current_time = localtime(&t);
    ostringstream date;
    date<<put_time(current_time,"%d-%m-%y");
    newDate= date.str();
    cout<< "Sales Date: "<<newDate<<endl;


    // Create new order
    Order newOrder(to_string(newOrderID), newDate, to_string(newQTY), to_string(newAmountPaid));
    order.push_back(newOrder);

    // Create new transaction
    transactions newPurchase(customerID, salespersonID, to_string(newOrderID));
    transactions_data.push_back(newPurchase);

    // Open orders file and append the new order
    ofstream file1("orders.txt", ios::app);
    if (!file1) {
        cerr << "Error, unable to open orders.txt file" << endl;
    } else {
        file1 << setw(6) << setfill('0') << newOrderID << ";" << newDate << ";" << newQTY << ";" << fixed << setprecision(2) << newAmountPaid << endl;
        file1.close();
    }

    // Open transactions file and append the new transaction
    ofstream file2("transactions.txt", ios::app);
    if (!file2) {
        cerr << "Error, unable to open transactions.txt file" << endl;
    } else {
        file2 << customerID << ";" << salespersonID<<";" <<setw(6) << setfill('0') << newOrderID << endl;
        file2.close();
    }
}
queue<string> loadWaitingList() {
    queue<string> waitingList;
    ifstream file("rainbowList.txt");

    if (!file) {
        cerr << "Error, unable to open rainbowList.txt file" << endl;
        return waitingList;
    }

    string customerID;
    while (getline(file, customerID)) {
        waitingList.push(customerID);  // Use push
    }

    file.close();
    return waitingList;
}

void saveWaitingList(const queue<string>& waitingList, const string& filename) {
    ofstream file(filename);
    queue<string> temp = waitingList;  // Make a copy to iterate

    while (!temp.empty()) {
        file << temp.front() << endl;
        temp.pop();
    }
    file.close();
}

// Function to add a new customer ID to the waiting list queue
void addToWaitingList(queue<string>& waitingList, const vector<Customer>& customer_data) {
    string customerID;
    cout << "Enter Customer ID to add to the waiting list: ";
    cin >> customerID;
    string customer_name;
    bool found = false;
    for (const Customer& customer : customer_data) {
        if (customer.getid() == customerID) {
            customer_name = customer.getFirstName() + " " + customer.getLastName();
            found = true;
            waitingList.push(customerID);  // Use push() to add to queue
            break;
        }
    }

    if (!found) {
        cout << "Customer ID " << customerID << " not found in system!" << endl;
        return;
    }
    
    
    ofstream file("rainbowList.txt", ios::app);
    if (!file) {
        cerr << "Error, unable to open rainbowList.txt file" << endl;
        return;
    }

    file << customerID << endl;
    file.close();
    cout << customer_name << " has been added to the waiting list." << endl;
}
void sellRainbowTribble(queue<string>& waitingList, const vector<Customer>& customer_data, vector<Order>& order_data, vector<transactions>& transactions_data) {
    if (waitingList.empty()) {
        cout << "No customers in the waiting list!" << endl;
        return;
    }

    string customerID = waitingList.front();  // Get first in line
    waitingList.pop();  // Remove from list

    // Find customer details
    string customer_name;
    bool found = false;
    for (const Customer& customer : customer_data) {
        if (customer.getid() == customerID) {
            customer_name = customer.getFirstName() + " " + customer.getLastName();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Customer ID " << customerID << " not found in system!" << endl;
        return;
    }

    // Process Order
    srand(time(0));
    int newOrderID = rand() % 90000 + 100000;
    string todaysDate;
    stringstream ss;
    ss << setw(6) << setfill('0') << newOrderID;
    cout<<"Enter today's date:";
    cin>>todaysDate;
    

    Order newOrder(ss.str(), todaysDate, ";1;", "40.00");
    order_data.push_back(newOrder);

    // Add to Transactions (use existing transactions_data)
    transactions newTransaction(customerID,"", ss.str());
    transactions_data.push_back(newTransaction);

    // Update Files (orders.txt)
    ofstream orderFile("orders.txt", ios::app);
    if (!orderFile) {
        cerr << "Error, unable to open orders.txt file" << endl;
    } else {
        orderFile << ss.str() << todaysDate << endl;
        orderFile.close();
    }

    // Update Files (transactions.txt)
    ofstream transactionFile("transactions.txt", ios::app);
    if (!transactionFile) {
        cerr << "Error, unable to open transactions.txt file" << endl;
    } else {
        transactionFile << customerID << ";" << ss.str() << endl;
        transactionFile.close();
    }

    cout << "Rainbow Tribble sold to " << customer_name << "!" << endl;
    saveWaitingList(waitingList, "rainbowList.txt");
}
//function to encrypt the Password
string encryption(string& Password){
    const string charlist="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int offset = 3;
    const int char_size= charlist.length();
    string encrypt;
    //encrypt the password by looping the password and offseting the letter to get a different letter
    encrypt.reserve(Password.length());
    for(char character: Password){
        int ID=charlist.find(character);
        if(ID== string::npos){
            encrypt+=character;
        }
        else{
            int newID=(ID+offset)%char_size;
            encrypt+=charlist[newID];
            
        }
    }
    return encrypt;
}
//functio to changePassword
void changePassword(vector<Customer>& customers, const string& customerID) {

    cout << "====================\n";
    cout << "\nChange Password\n";
    cout << "====================\n";
    cout << "Enter your new password: ";
    string newPassword;
    cin >> newPassword;
    //uses the the newPassword and encrypts using the encrypt function
    string encryptedPassword = encryption(newPassword);

    bool customerFound = false;
    //locates the customer using their ID and tells them that their pass wod has being change
    for (Customer& customer : customers) {
        if (customer.getid() == customerID) {
            customerFound = true;
            customer.setPassword(encryptedPassword);
            cout << "Your password has been successfully changed!\n";
            break;
        }
    }
    //error if customer not found
    if (!customerFound) {
        cout << "Error: Customer not found.\n";
        return;
    }

    ofstream outFile("customers.txt");
    if (!outFile) {
        cerr << "Error: Unable to open customers.txt file.\n";
        return;
    }
    //gets the Customer information
    for (const Customer& customer : customers) {
        outFile << customer.getid() << ";" 
                << customer.getPassword() << ";" 
                << customer.getFirstName() << ";" 
                << customer.getLastName() << ";" 
                << customer.getaddress() << ";" 
                << customer.getcity() << ";" 
                << customer.getstate() << ";" 
                << customer.getZipCode() << endl;
    }

    outFile.close();
}


int main(){
    
    vector<Customer> Customer_data=Customerdata();
    vector<Order> order_data=orderData();
    vector<transactions> transactions_data=transactionData();
    vector<SalesPerson*> Staff=salesStaff();
    
    string last_name;
	int choice;
	bool found;
	bool hasOrder;
	bool id;
	do {

		cout<<"================================================================= "<<endl;
		cout<<"||                                                             || "<<endl;
		cout<<"||           Welcome to the Naperville Tribble Store           || "<<endl;
		cout<<"||                         Main Menu                           || "<<endl;
		cout<<"||                                                             || "<<endl;
        cout<<"================================================================= "<<endl;
        cout<<"||                                                             || "<<endl;
		cout<<"|| 1. Add a new customer                                       || "<<endl;
		cout<<"||                                                             || "<<endl;
		cout<<"|| 2. Display customer information via customer ID             || "<<endl;
		cout<<"||                                                             || "<<endl;
		cout<<"|| 3. Display customer information via Last Name               || "<<endl;
		cout<<"||                                                             || "<<endl;
		cout<<"|| 4. Make a purchase Quantity(1 to 5)                         || "<<endl;
		cout<<"||                                                             || "<<endl;
		cout<<"|| 5. Rainbow Tribble Menu                                     || "<<endl;
		cout<<"||                                                             || "<<endl;
		cout<<"|| 6. Print Sales Report                                       || "<<endl;
		cout<<"||                                                             || "<<endl;
		cout<<"|| 7. Login/SignUp                                             || "<<endl;
		cout<<"||                                                             || "<<endl;
		cout<<"|| 8. Exit                                                     || "<<endl;
		cout<<"||                                                             || "<<endl;
		cout<<"================================================================= "<<endl;



		cout << "Enter choice: ";
		cin>>choice;

		switch(choice)
		{
		case 1: { // Add a new customer

		    Customer newUser;
		    string newId,newPassword, newFirst, newLast, newAddress, newCity,newState, newZipCode,encrypt;
		    
		    srand(time(0)); // Generate a random 6-digit customer ID
		    int randomID= rand() %90000+100000;
		    stringstream ss;
		    ss<<setw(6)<<setfill('0')<<randomID;
		    newId=ss.str();
		    
		    
			cout<<"Welcome please insert the user information here: "<<endl;
			id=false;
			for(const Customer& customer:Customer_data){ // Check if the generated ID is already in use

			    if(customer.getid()==newId){
			        id=true;
			        cout<<"Sorry, This Customer ID is already in used!";
			        break;
			    }
			}
			if(!id){
			    cout<<"Enter Password: ";//create a encryption for the Password
			    cin>>newPassword;
			    encrypt = encryption(newPassword);
			    cout<<"Enter First Name: ";
			    cin>>newFirst;
			    cout<<"Enter Last Name: ";
			    cin>>newLast;
			    cout<<"Enter Address: ";
			    getline(cin>> ws, newAddress);
			    cout<<"Enter city: ";
			    getline(cin, newCity);
			    cout<<"Enter State: ";
			    getline(cin, newState);
			    cout<<"Enter ZipCode: ";
			    getline(cin, newZipCode);
			    
			    cout<<"Customer added!"<<endl;
			newUser= Customer(newId,encrypt,newFirst,newLast,newAddress,newCity,newState,newZipCode); 
			Customer_data.push_back(newUser); // Store customer data in vector
			
			CreateNewCustomer(Customer_data);
			}
			break;

		    }
		case 2: { // Search for a customer by ID and searches if the customers have any orders 
    	    found = false;
			string ID;
			cout<<"Please enter Customer ID: ";
			cin>>ID;
			
			cout<<"searching for "<<ID<<" ..."<<endl;
			for(const Customer& customer : Customer_data){ // Iterate through customer data to find a match
			    if (customer.getid() == ID){
			        cout<<"ID: "<<customer.getid()<<endl;
			        cout<<"First Name: "<<customer.getFirstName()<<endl;
			        cout<<"Last Name: "<<customer.getLastName()<<endl;
			        cout<<"Address: "<<customer.getaddress()<<endl;
			        cout<<"City: "<<customer.getcity()<<endl;
			        cout<<"State: "<<customer.getstate()<<endl;
			        cout<<"Zip Code: "<<customer.getZipCode()<<"\n"<<endl;
			        
			        found = true;
			        hasOrder= false;
			        
			        for(const transactions& transactions:transactions_data){ // Search for customer orders in transactions
			            if(transactions.getid()==customer.getid()){
			                for(const Order& order: order_data){
			                    if(order.getorder_number()==transactions.getordernumber()){
			                        cout<<"Order ID: "<<order.getorder_number()<<endl;
			                        cout<<"Date: "<<order.getdate()<<endl;
			                        cout<<"Quantity: "<<order.getquantity()<<endl;
			                        cout<<"Amount Paid: $"<<order.getamount_paid()<<"\n"<<endl;
			                        hasOrder= true;
            			            
			                    }
			                }
			            }
			        }
			        
			        if(!hasOrder){
			            cout<<"Sorry, but this customer does not have any orders!"<<endl;
			        }
			        
			    }
			    //break;
			}
			if(!found){
			    cout<<"Sorry but customer: "<<ID<<" is not in our system"<<endl;
			}
			
			break;
		}
		case 3: {//searches for customer by last name
			found = false;
			vector<Customer> similarNames;// a vector that holds custoemr with similiar last names
			cout<<"Please enter Customer Last Name: ";
			cin>>last_name;
			
			cout<<"searching for "<<last_name<<" ..."<<endl;
			for(const  Customer& customer: Customer_data){
			    if(customer.getLastName()==last_name){
			        similarNames.push_back(customer);//pushes the customer with the last naem to the vector
			    }
			}
			for(size_t i=0; i< similarNames.size();i++){//increases the size by the amount of customers with the same name and displays their basic information
			    cout<<i+1<<" ID: "<<similarNames[i].getid()<<"\n"
			    <<" First Name: "<<similarNames[i].getFirstName()<<"\n"
			    <<" Last Name: "<<similarNames[i].getLastName()<<"\n"
			    <<" Address: "<<similarNames[i].getaddress()<<"\n"
			    <<" City: "<<similarNames[i].getcity()<<"\n"
			    <<" State: "<<similarNames[i].getstate()<<"\n"
			    <<" ZipCode: "<<similarNames[i].getZipCode()<<"\n"<<endl;
			}
			
			int selection;
			cout<<"\n"<<"Which customer are you?"<<endl;
			cin>>selection;
			if(selection<1||selection> similarNames.size()){//error handler if the user select a number less than or greater then the actual customers in the vector
			    cout<<"Please enter a valid input!"<<endl;
			    break;
			}/* find any customer with similair last name and put them into a list 
			 where iif there is more of2 people with the same name then it will give an
			 option of what customer data you want to select*/
			Customer select=similarNames[selection-1];
			for(const Customer& customer : Customer_data){
			    if (customer.getLastName() == last_name){
			        cout<<"ID: "<<select.getid()<<endl;
			        cout<<"First Name: "<<select.getFirstName()<<endl;
			        cout<<"Last Name: "<<select.getLastName()<<endl;
			        cout<<"Address: "<<select.getaddress()<<endl;
			        cout<<"\n"<<endl;
			        
			        found = true;
			        cout<<"Order Data"<<"\n"<<endl;
			       
			        hasOrder= false;
			        
			        for(const transactions& transactions:transactions_data){//prints out the customer order history 
			            if(transactions.getid()==customer.getid()){
			                for(const Order& order: order_data){
			                    if(order.getorder_number()==transactions.getordernumber()){
			                        cout<<"Order ID: "<<order.getorder_number()<<endl;
			                        cout<<"Date: "<<order.getdate()<<endl;
			                        cout<<"Quantity: "<<order.getquantity()<<endl;
			                        cout<<"Amount Paid: $"<<order.getamount_paid()<<"\n"<<endl;
			                        hasOrder= true;
            			            
			                    }
			                }
			            }
			        }
			        
			        if(!hasOrder){//if the person does not have any orders then it will say no orders
			            cout<<"Sorry, but this customer does not have any orders!"<<endl;
			        }
			        break;
			    }
			    
			}
			if(!found){
			    cout<<"Sorry but customer: "<<last_name<<" is not in our system"<<endl;
			}
			
			break;
		}
			
		case 4:{
		    //create a customer sale
		    CustomerSale(order_data,Customer_data,transactions_data,Staff);
		    
		    break;
		}

		case 5:{
		    queue<string> waitingList = loadWaitingList();
    int subChoice;
    
    do {
        cout << "========== Rainbow Tribble Menu ==========" << endl;
        cout << "1. Add customer to waiting list" << endl;
        cout << "2. Sell Rainbow Tribble to next customer" << endl;
        cout << "3. Return to main menu" << endl;
        cout << "==========================================" << endl;
        cout << "Enter choice: ";
        cin >> subChoice;

        switch (subChoice) {
            case 1:
                //added to waitingList
                addToWaitingList(waitingList, Customer_data);
                break;
            case 2:
            //sell their Rainbow Tribble
                sellRainbowTribble(waitingList, Customer_data, order_data, transactions_data);
                break;
            case 3:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again!" << endl;
                }
            } while (subChoice != 3);
            
            break;		}


		

		case 6:{ // Exit the program
		     Staff = setCommission(Staff, order_data, transactions_data);
		     SalesReport(Staff);
		    break;
		}

		
		case 7: { // login
            bool custID = false;
            string LoginID, passwd, encrypt;
            int choice;
            cout << "=====================================" << endl;
            cout << "     Welcome to Customer Portal      " << endl;
            cout << "=====================================" << endl;
            cout << "     Please Enter your LoginID       " << endl;
            cout << "          '000000' to exit           " << endl;
            cout << "=====================================" << endl;
	    cout<<"Please Enter Login ID: "<<endl;
            cin >> LoginID;
        
            while (LoginID != "000000") {
                custID = false; // reset for each new login attempt
        
                for (const Customer& customer : Customer_data) {
                    if (customer.getid() == LoginID) {
                        custID = true;
                        cout << "Password: ";
                        cin >> passwd;
                        encrypt = encryption(passwd);// encrypt input password
                        if (customer.getPassword() == encrypt) {
                            cout << "Welcome, " << customer.getFirstName() <<" "<< customer.getLastName() << endl;
        
                            do {
                                cout << "========================================" << endl;
                                cout << "||                                    ||" << endl;
                                cout << "|| 1. Change password                 ||" << endl;
                                cout << "||                                    ||" << endl;
                                cout << "|| 2. Review order history            ||" << endl;
                                cout << "||                                    ||" << endl;
                                cout << "|| 3. Place an order                  ||" << endl;
                                cout << "||                                    ||" << endl;
                                cout << "|| 4. Sign out                        ||" << endl;
                                cout << "||                                    ||" << endl;
                                cout << "========================================" << endl;
        
                                cout << "Enter Choice: ";
                                cin >> choice;
        
                                switch (choice) {
                                    case 1: {
                                        //change the customer passsword
                                        changePassword(Customer_data, customer.getid());
					                    break;
                                    }
                                    case 2: {
                                        //bool to check if the person had previous orders
                                        hasOrder= false;
			        //gets customer order information
			        for(const transactions& transactions:transactions_data){ // Search for customer orders in transactions
			            if(transactions.getid()==customer.getid()){
			                for(const Order& order: order_data){
			                    if(order.getorder_number()==transactions.getordernumber()){
			                        cout<<"Order ID: "<<order.getorder_number()<<endl;
			                        cout<<"Date: "<<order.getdate()<<endl;
			                        cout<<"Quantity: "<<order.getquantity()<<endl;
			                        cout<<"Amount Paid: $"<<order.getamount_paid()<<"\n"<<endl;
			                        hasOrder= true;
            			            
			                    }
			                }
			            }
			        }
			        //error if customer has no order
			        if(!hasOrder){
			            cout<<"Sorry, but this customer does not have any orders!"<<endl;
			        }
                                        break;
                                    }
                                    case 3: {
                                        //makes a new new sales order
                                        CustomerPortalSale(order_data, Customer_data, transactions_data,LoginID);
                                        break;
                                    }
                                    case 4: {
                                        //customer sign out to main menu
                                        cout << "Signing out!" << endl;
                                        break;
                                    }
                                    default: {
                                        cout << "Please enter a correct choice" << endl;
                                    }
                                }
                            } while (choice != 4);
        
                            break; // break out of for-loop if login was successful
                        } else {
                            cout << "Wrong password! Please try again." << endl;
                            break;
                        }
                    }
                }
                //error if customer is not found
                if (!custID) {
                    cout << "Customer ID not found! Please try again." << endl;
                }
                //enures that the user enters a correct LoginID or '000000' to exit
                cout << "\nPlease Enter your LoginID ('000000' to exit): ";
                cin >> LoginID;
            }
        
            break;
        }
           
        case 8:{ // Exit the program
		    cout<<"                   Thank you have a nice day!                    "<<endl;
		    break;
		}
		
		default: {//default case if the user made a wrong input
			cout<<"Invalid choice, please try again"<<endl;
		}


		}
	} while(choice!=8);
	
	return 0;
}
