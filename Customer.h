// Customer.h
// Rev. 2 - 17/07/24 Updated strings to be char arrays, included BinaryFileIOHelper
// Rev. 1 - 03/07/24 Original by D.O.J.J Software Development

//*******************************************************//
// This module is designed to manage the creation of customer in the system
// encapsulating the properties (customer name , phone number, email address) of the customer class.
//*******************************************************//

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <cstring>
#include "BinaryFileIOHelper.h"
using namespace std;

//***********************************************************************/

//customer class adds the customer to the system
class Customer{

public:
    // Default Constructor
    Customer()
        : customerName(""),phoneNumber("0"), emailAddress("") {}

    // Parametrized Constructor
    Customer(const char *Custname, const char *EmailAdd, const char *Phonenum); 

    // Getters
    void getCustomerName(char *str);
    void getPhoneNumber(char *str);
    void getEmailAddress(char *str);

    // Setters
    void setCustomerName(const char *name);
    void setPhoneNumber(const char *number);
    void setEmailAddress(const char *email);

private:
    char customerName[31];
    char phoneNumber[12];
    char emailAddress[25];
};

//  This class models a Customer entity.
// It contains getters and setters to access 
//and modify the properties of the Customer object.
//the constructer will get customer name, phone number and email address.
//the customer will enter his/her details then forward with their request.

//*******************************************************//

class CustomerFile : public BinaryFileIOHelper<Customer>
{
private:
    fstream file;
    bool writeCustomer(Customer customerObj);
public:

    CustomerFile();
    Customer findCustomer(char *customerName);
    bool seekToBeginningOfFile();
    bool getNextCustomer(Customer &customerObj);
    bool createCustomer(Customer &adCustomer);
  

    bool openCustomerFile();
    bool closeCustomerFile();
};

//******************************************************************************** */
 // This class handles the reading and writing of Customer objects to and from a file.
// You can find a specific Customer through the findCustomer function by giving it customer name.
// Use writeCustomer to write the customer object to disk. It will append the object at the end of the file.
// Use createCustomer to add and save a given Customer object to customer.txt.
///***************************************************************************************/


CustomerFile strtCustomer(); // starts the customer module
int createCustomer(Customer customerToAdd, CustomerFile &File);
// createCustomer is a function which takes a Customer object that is passed to it as a function argument
// The function returns 0 for a successful operation, and -1 if there is an error
// It is expected to have all attributes of a customer filled which is the name, phone number, email address
// The function puts the Customer on disk and then returns, if the process is successful
// The Customer should be valid and the Customer File should have room for a new Customer

//*******************************************************//
bool stopCustomer(CustomerFile &custFile); // stops the customer module


#endif