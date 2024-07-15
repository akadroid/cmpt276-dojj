// ChangeItem.h
// Rev. 1 - 03/07/24 Original by D.O.J.J Software Development

//*******************************************************//
// This module is designed to manage everything to do with Change Items within a system while
// encapsulating the properties (change ID, product name, anticipated release, description, status
// and priority) of the ChangeItem class.
//*******************************************************//

#ifndef CHANGE_ITEM
#define CHANGE_ITEM

#include <string>
#include <fstream>
using namespace std;

//*******************************************************//

enum class State
{
    REPORTED,
    ASSESSED,
    IN_PROGRESS,
    CANCELLED,
    DONE
};

class ChangeItem
{
public:
    // Default Constructor
    ChangeItem()
        : changeID(0), productName(""), anticipatedRelease(""),
          description(""), state(State::REPORTED), priority(0) {}

    // Constructor
    ChangeItem(const string &name, const string &rID, const string &desc, const string &st,
               const int &prio);

    // Manually add a change id (for testing purposes)
    ChangeItem(const int &cID, const string &name, const string &rID, const string &desc, const string &st,
               const int &prio);

    // Getters
    int getChangeID();
    void getProductName(char *str);
    void getReleaseID(char *str);
    void getDescription(char *str);
    void getStatus(char *str); // returns a string of the status
    int getPriority();

    // Setters
    void setProductName(char *name);
    void setReleaseID(char *release_id);
    void setDescription(char *description);
    void setStatus(State state);
    void setPriority(int priority);

private:
    int changeID;
    char productName[30];       // Example size, adjust as needed
    char anticipatedRelease[8]; // Example size, adjust as needed
    char description[30];       // Example size, adjust as needed
    State state;
    int priority;
};
// This class models a ChangeItem entity.
// It contains getters and setters to access and modify the properties of the ChangeItem object.
// The constructor will automatically generate a change ID.
// The change ID is auto-incrementing and will be stored in the file "changeID.txt"

//*******************************************************//

class ChangeItemFile
{
public:
    ChangeItem findChangeItem(int id);
    bool seekToBeginningOfFile();
    bool getNextChangeItem(ChangeItem &changeItemObj);
    void createChangeItem(ChangeItem &aChangeItem);
    void updateChangeItem(ChangeItem &aChangeItem);
    void searchChangeItem(int changeId);

    bool openChangeItemFile();
    bool closeChangeItemFile();

private:
    fstream file;
    bool writeChangeItem(ChangeItem changeItemObj);
};
// This class handles the reading and writing of ChangeItem objects to and from a file.
// You can find a specific ChangeItem through the findChangeItem function by giving it a Change Id
// Use writeChangeItem to write the ChangeItem object to disk. It will append the object at the end of the file.
// Use createChangeItem to add and save a given ChangeItem object to changeitems.txt.
// It will open the file first, and then close when finished
// Use updateChangeItem to save a given updated/modified ChangeItem object to changeitems.txt
// searchChangeItem will search using a changeId and then display information about a Change Item
// Example:
// Selected Change Item in Sierra2:
//  Change ID    Description      Status     Priority    Release ID
//  2            Crash option 4   Assessed   5           AA2345X2

//*******************************************************//

ChangeItemFile strtItem();
// Initialize reading and writing of the change items. If changeitems.txt does not exist, it will be created.

//*******************************************************//

bool closeItem(ChangeItemFile &itemFile);
// Close the change item file

//*******************************************************//

#endif