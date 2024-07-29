// ChangeRequest.h
// Rev. 2 - 17/07/24 Changed strings to char arrays, other general improvements
// Rev. 1 - 03/07/24 Original by D.O.J.J Software Development

//*****************************************************************************************************************//
// This module is designed to manage the change requests made by customers or department 
// encapsulating the properties (change ID , customer name, reported release, date) of the change request class.
//*********************************************************************************************************************8//

#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H
#include <string>
#include <fstream>
#include <cstring>
#include "BinaryFileIOHelper.h"

using namespace std;

// change request is class that will add change request according to customer demand.
class ChangeRequest{
    public: 
        // Default Constructor
    ChangeRequest()
        : requestID(0),customerName(""), reportedRelease(""), date("") {}

    // Constructor
    ChangeRequest(const int rID, const char *release, const char *name,
               const char *date); 

        //getters
        int getRequestID();
        void getCustomerName(char *str);
        void getReportedRelease(char *str);
        void getDate(char *str);

        //setters
        void setCustomerName(const char *name);
        void setReportedRelease(const char *release);
        void setDate(const char *aDate);

    private: 
        char customerName[31];
        int requestID;
        char reportedRelease[9];
        char date[11];
};

//****************************************************************** */
//  This class models a ChangeRequest entity.
// It contains getters and setters to access 
//and modify the properties of the ChangeRequest object.
//the constructer will generate change ID and reported release.
//the customer will enter his/her details and puts in a request.

//*********************************************************************//
class ChangeRequestFile : public BinaryFileIOHelper<ChangeRequest>
{
private:
    fstream file;
    bool writeChangeRequest(ChangeRequest changeRequestObj);

public:

    ChangeRequestFile();
    bool findChangeRequest(int id, ChangeRequest &request);
    bool seekToBeginningOfFile();
    bool createChangeRequest(ChangeRequest &adChangeRequest); 
    bool getNextChangeRequest(ChangeRequest &changeRequestObj);

    bool openChangeRequestFile();
    bool closeChangeRequestFile();
};

//******************************************************************************** */
 // This class handles the reading and writing of ChangeRequest objects to and from a file.
// You can find a specific ChangeRequest through the findChangeRequest function by giving it a Change Id
// Use writeChangeItem to write the ChangeItem object to disk. It will append the object at the end of the file.
// Use createChangeItem to add and save a given ChangeRequest object to changeRequests.txt.
// Use updateChangeItem to save a given updated/modified Changerequest object to changeRequests.txt
//***************************************************************************************/

ChangeRequestFile strtChangeReq(); 
bool closeChangeReq(ChangeRequestFile &requestFile);

//***************************************************************** ****************************/
// createChangeRequest function takes the requests from the customer.
//it allows customer to enteer the request and gets a reported release and change id.
//strtChangeReq function takes up charge to set the change request module to get started 
//to take user input and start the system.
//closeChangeReq function activates when the system shut down and all the modules are set off.
//******************************************************************************************************88 */

#endif
