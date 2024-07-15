// ChangeItem.h
// Rev. 1 - 03/07/24 Original by D.O.J.J Software Development

//*******************************************************//
// This module is designed to manage everything to do with Change Items within a system while
// encapsulating the properties (change ID, product name, anticipated release, description, status
// and priority) of the ChangeItem class.
//*******************************************************//

#ifndef CHANGE_ITEM
#define CHANGE_ITEM

#include <cstring>
#include <fstream>
using namespace std;

//*******************************************************//

class ChangeItem
{
public:
    // Default Constructor
    ChangeItem()
        : changeID(0), productName("\0"), anticipatedRelease("\0"),
          description("\0"), state("\0"), priority(0) {}

    // Constructor
    ChangeItem(const char *name, const char *rID, const char *desc, const char *state, int prio);

    // Manually add a change id (for testing purposes)
    ChangeItem(int cID, const char *name, const char *rID, const char *desc, const char *state, int prio);

    // Getters
    int getChangeID();
    void getProductName(char *str);
    void getReleaseID(char *str);
    void getDescription(char *str);
    void getStatus(char *str);
    int getPriority();

    // Setters
    void setProductName(const char *name);
    void setReleaseID(const char *id);
    void setDescription(const char *desc);
    void setStatus(const char *st);
    void setPriority(int prio);

private:
    int changeID;
    char productName[11]; // 1 extra character for null-terminating char
    char anticipatedRelease[9];
    char description[31];
    char state[11];
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
    // Constructor
    ChangeItemFile() {}

    ChangeItem findChangeItem(int id);
    bool seekToBeginningOfFile();
    bool getNextChangeItem(ChangeItem &changeItemObj);
    void createChangeItem(ChangeItem &aChangeItem);
    void updateChangeItem(ChangeItem &aChangeItem);
    void searchChangeItem(int changeId);

    bool openChangeItemFile();
    bool closeChangeItemFile();

private:
    fstream fileStream;
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