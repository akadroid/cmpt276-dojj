// ChangeRequest.cpp
// Rev. 1 - 16/07/24 Original by D.O.J.J Software Development

//***************************************************************************************************//
// This module implements the Change request class and the ChangeRequestFile class,
// that was designed in the ChangeRequest.h header file. It provides functionality
// to create, read, write for Change request records stored in a binary file.
//the binary file search uses a linar search method is one tradeoff 
//as it is easier access and understandable due to less amount of code 
//using binary file storage which minimises storage and makes it effcient for large data .
// we used encapsulation to hide sensitive data from user by declaring class variables as private.
//the getter function is used to retrieve the variable value.
// the setter function is used to set the variable value.
//******************************************************************************************************//

#include "ChangeRequest.h"
#include "BinaryFileIOHelper.h"
#include <iostream>
using namespace std;

//******************************************************************************************************/
// Function to generate the next request ID
static int next_RequestID()
{
  // initiate the id to 0 
  int id = 0;
// using if statement to check if the input id exists in the file 
  if (ifstream("requestId.txt") >> id)
  // increatment by 1 to get new id 
    id += 1;
// writes the data to the file 
  ofstream("requestId.txt") << id;
  return id;
}

/********************************************************************************************************/

ChangeRequest::ChangeRequest(const int rID, const char *release, const char *name,
               const char *date) : requestID(rID)
{
    setCustomerName(name);
    setReportedRelease(release);
    setDate(date);
}

//********************************************************************************************************/
// getter for phone number using int to set the retuen the request id

int ChangeRequest::getRequestID()
{
  return requestID;
}

//************************************************************************************************************/
// getter for customer name using strncpy to set argument as char array.
// pass in char buffer of size 31 for customer name .

void ChangeRequest::getCustomerName(char *str)
{
  strncpy(str, customerName, sizeof(customerName));
  str[sizeof(customerName) - 1] = '\0';
}

//*************************************************************************************************************/
// getter for reported release using strncpy to set argument as char array.
// pass in char buffer of size 9 for reported release
 
void ChangeRequest::getReportedRelease(char *str)
{
  strncpy(str, reportedRelease, sizeof(reportedRelease));
  str[sizeof(reportedRelease) - 1] = '\0';
}

//*************************************************************************************************************/
// getter for date using strncpy to set argument as char array.
// pass in char buffer of size 11 for date .

void ChangeRequest::getDate(char *str)
{
  strncpy(str, date, sizeof(date));
  str[sizeof(date) - 1] = '\0';
}

//*************************************************************************************************************/
// setter for customer name uses strncpy to set name value to char array

void ChangeRequest::setCustomerName(const char *name)
{
  strncpy(customerName, name, sizeof(customerName));
  customerName[sizeof(customerName) - 1] = '\0';
}

//**************************************************************************************************************/
// setter for reported release uses strncpy to set name value to char array

void ChangeRequest::setReportedRelease(const char *release)
{
  strncpy(reportedRelease, release, sizeof(reportedRelease));
  reportedRelease[sizeof(reportedRelease) - 1] = '\0';
}

//****************************************************************************************************************/
// setter for date uses strncpy to set name value to char array

void ChangeRequest::setDate(const char *aDate)
{
  strncpy(date, aDate, sizeof(date));
  date[sizeof(date) - 1] = '\0';
}

//*****************************************************************************************************************/
//opens the change request file object

ChangeRequestFile::ChangeRequestFile()
{
  openChangeRequestFile();
}

//****************************************************************************************************************/
//searches for the change request in the file and returns the change request if found.
//while loop is used to look through the entire list of change request untill found.
// or it reaches the end of the file.

bool ChangeRequestFile::findChangeRequest(int id, ChangeRequest &request)
{
   // if we are unable to start the file, throw an error
  if (!seekToBeginningOfFile())
  {
    cerr << "Unable to update change request (cant seek to beginning)" << endl;
    return false;
  }
// variable associated with the search
  ChangeRequest buf;
  streampos pos;
  // while look is used for the search untill we find the change request or reach end
  // increment per change request in binary record file
  while (!file.eof())
  {
    // get the next change request in search
    getNextChangeRequest(buf);
    // if the name matches return the change request
    if (buf.getRequestID() == id)
    {
      request = buf;
      return true;
    }
  }
// if no mach found, return false (no change request)
  return false;
}

//********************************************************************************************************************/
// Resets the change request we are looking at in the file to the change request at the front using the seekg function
// Returns a boolean for success or failure

bool ChangeRequestFile::seekToBeginningOfFile()
{
    // if there is no file, throw an error
  if (!file.is_open())
  {
    cerr << "File is not open" << endl;
    return false;
  }

  file.clear();
  file.seekg(0);
  
  return file.good(); // Returns true if the seek was successful
}

//************************************************************************************************************/
// Reads the next change request from the data file, uses the read function from BinaryFileIOHelper.h
// Returns a boolean for success or failure

bool ChangeRequestFile::getNextChangeRequest(ChangeRequest &changeRequestObj)
{
  return Read(changeRequestObj);
}

//*****************************************************************************************************/
// Writes a change request to the data file, uses the write function from BinaryFileIOHelper.h
// Returns a boolean for success or failure

bool ChangeRequestFile::createChangeRequest(ChangeRequest &adChangeRequest)
{
  return Write(adChangeRequest);
}

//**************************************************************************************************************/
// Opens the file storing all of the binary fixed-length records holding change request
// Returns a boolean for success or failure

bool ChangeRequestFile::openChangeRequestFile()
{
  // if opening a file shows error, return false
  file.open("ChangeRequest.data", ios::in | ios::out | ios::binary | ios::app);
  if (!file.is_open())
  {
    cerr << "Error opening file" << endl;
    return false;
  }
  // if file opens, return true
  return true;
}

//*****************************************************************************************************************/
// Closes the file storing all of the binary fixed-length records holding change requests
// Returns a boolean for success or failure

bool ChangeRequestFile::closeChangeRequestFile()
{
 // if no file is opened, return false
  if (!file.is_open())
  {
    cerr << "File not open" << endl;
    return false;
  }
// changeRequestFile.close();
  file.close();
  return true;
}

//**********************************************************************************************************************/
// Writes the next change request to the data file, uses the write function from BinaryFileIOHelper.h
// Returns a boolean for success or failure

bool ChangeRequestFile::writeChangeRequest(ChangeRequest changeRequestObj)
{
  return Write(changeRequestObj);
}

//********************************************************************************************************************/
// startup function when we open the binary file storing change requests

ChangeRequestFile strtChangeReq()
{
  // ChangeRequestFile.open("changeRequest.txt", fstream::in | fstream::out | std::ios::app);
  return ChangeRequestFile();
}

//******************************************************************************************************************/
// it is a shutdown function, which closes the file containing change requests

bool closeChangeReq(ChangeRequestFile &requestFile)
{
  return requestFile.closeChangeRequestFile();
}
