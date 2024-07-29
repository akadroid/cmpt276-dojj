// Customer.cpp
// Rev. 1 - 16/07/24 Original by D.O.J.J Software Development

//********************************************************************************************************//
// This module implements the Customer class and the CustomerFile class,
// that was designed in the Customer.h header file. It provides functionality
// to create, read, write  for Customer records stored in a binary file.
//the binary file search uses a linar search method is one tradeoff 
//as it is easier access and understandable due to less amount of code 
// using binary file storage which minimises storage and makes it effcient for large data .
// we used encapsulation to hide sensitive data from user by declaring class variables as private.
//the getter function is used to retrieve the variable value.
// the setter function is used to set the variable value.
//************************************************************************************************************//

#include "Customer.h"
#include "BinaryFileIOHelper.h"
#include <iostream>
using namespace std;

//**********************************************************************************************************/

Customer::Customer(const char* Custname, const char* EmailAdd, const char* Phonenum)
{
        setCustomerName(Custname);
        setPhoneNumber(Phonenum);
        setEmailAddress(EmailAdd);
}

//***********************************************************************************************************/
// Getter for customer name using strncpy to set argument as char array.
// pass in char buffer of size 31 for customer name .

void Customer::getCustomerName(char *str)
{
  strncpy(str, customerName, sizeof(customerName));
  str[sizeof(customerName) - 1] = '\0';
}

//***********************************************************************************************************/
// Getter for phone number using strncpy to set argument as char array.
// pass in char buffer of size 12 for phone number 

void Customer::getPhoneNumber(char *str)
{
  strncpy(str, phoneNumber, sizeof(phoneNumber));
  str[sizeof(phoneNumber) - 1] = '\0';
}

//***************************************************************************************************************/
// Getter for email address using strncpy to set argument as char array.
// pass in char buffer of size 25 for email address

void Customer::getEmailAddress(char *str)
{
  strncpy(str, emailAddress, sizeof(emailAddress));
  str[sizeof(emailAddress) - 1] = '\0';
}

//****************************************************************************************************************/
// setter for customer name uses strncpy to set name value to char array

void Customer::setCustomerName(const char *name)
{
  strncpy(customerName, name, sizeof(customerName));
  customerName[sizeof(customerName) - 1] = '\0';
}

//******************************************************************************************************************/
// setter for phone number uses strncpy to set name value to char array

void Customer::setPhoneNumber(const char *number)
{
  strncpy(phoneNumber, number, sizeof(phoneNumber));
  phoneNumber[sizeof(phoneNumber) - 1] = '\0';
}

//*******************************************************************************************************************/
// setter for email address uses strncpy to set name value to char array

void Customer::setEmailAddress(const char *email)
{
  strncpy(emailAddress, email, sizeof(emailAddress));
  emailAddress[sizeof(emailAddress) - 1] = '\0';
}

//********************************************************************************************************************/
//opens the customer file object

CustomerFile::CustomerFile()
{
  openCustomerFile();
}

//*********************************************************************************************************************/
//searches for the customer in the file and returns the customer if found.
//while loop is used to look through the entire list of customers untill found.
// or it reaches the end of the file.

bool CustomerFile::findCustomer(char *customerName, Customer &name)
{
  // if we are unable to start the file, throw an error
  if (!seekToBeginningOfFile())
  {
    cerr << "Unable to update customer (cant seek to beginning)" << endl;
    return false;
  }
// variable associated with the search
  Customer buf;
  streampos pos;
  //while look is used for the search untill we find the customer or reach end
  //increment per customer in binary record file
  while (!file.eof())
  {
    // get the next customer in search
    getNextCustomer(buf);
    char fileCustomerName[31] = "";
    buf.getCustomerName(fileCustomerName);
    //if the name matches return the customer
    if (strcmp(fileCustomerName, customerName) == 0)
    {
      name = buf;
      return true;
    }
  }
// if no mach found, return false (no customer)
  return false;
}

//****************************************************************************************************************/
// Resets the customer we are looking at in the file to the customer at the front using the seekg function
// Returns a boolean for success or failure

bool CustomerFile::seekToBeginningOfFile()
{
  // if there is no file, throw an error
  if (!file.is_open())
  {
    cerr << "File is not open" << endl;
    return false;
  }
  file.seekg(0);
  return file.good();  // Returns true if the seek was successful
}

//****************************************************************************************************************/
// Writes a customer to the data file, uses the write function from BinaryFileIOHelper.h
// Returns a boolean for success or failure

bool CustomerFile::createCustomer(Customer &adCustomer)
{
  return Write(adCustomer);
}

//*********************************************************************************************************************/
// Reads the next customer from the data file, uses the read function from BinaryFileIOHelper.h
// Returns a boolean for success or failure

bool CustomerFile::getNextCustomer(Customer &customerObj)
{
  return Read(customerObj);
}

//***********************************************************************************************************************/
// Opens the file storing all of the binary fixed-length records holding customers
// Returns a boolean for success or failure

bool CustomerFile::openCustomerFile()
{
  // if opening a file shows error, return false
  file.open("Customer.data", ios::in | ios::out | ios::binary | ios::app);
  if (!file.is_open())
  {
    cerr << "Error opening file" << endl;
    return false;
  }
  // if file opens, return true
  return true;
}

//***************************************************************************************************************************/
// Closes the file storing all of the binary fixed-length records holding customers
// Returns a boolean for success or failure

bool CustomerFile::closeCustomerFile()
{
  // if no file is opened, return false
  if (!file.is_open())
  {
    cerr << "File not open" << endl;
    return false;
  }
  // customerFile.close();
  file.close();
  
  return true;
}

//*******************************************************************************************************************************/
// Writes the next customer to the data file, uses the write function from BinaryFileIOHelper.h
// Returns a boolean for success or failure

bool CustomerFile::writeCustomer(Customer customerObj)
{
  return Write(customerObj);
}

//***************************************************************************************************************************/
// startup function when we open the binary file storing customers

CustomerFile strtCustomer()
{
  // CustomerFile.open("customer.txt", fstream::in | fstream::out | std::ios::app);
  return CustomerFile();
}

//*************************************************** *********************************************************************/
// it is a shutdown function, which closes the file containing customers

bool stopCustomer(CustomerFile &custFile)
{
  return custFile.closeCustomerFile();
}
