// ChangeItem.cpp
// Rev. 1 - 15/07/24 Original by D.O.J.J Software Development

//*******************************************************//
// This module implements the ChangeItem class and the ChangeItemFile class,
// that was designed in the ChangeItem.h header file. It provides functionality
// to create, read, update, and search for ChangeItem records stored in a binary file.
//*******************************************************//

#include "ChangeItem.h"
#include "BinaryFileIOHelper.h"
#include <iostream>
#include <iomanip>
using namespace std;

//*******************************************************//

int next_id()
{
  int id = 0;

  if (ifstream("changeId.txt") >> id)
    id += 1;

  ofstream("changeId.txt") << id;
  return id;
}
// Function to generate the next change ID

//*******************************************************//

ChangeItem::ChangeItem(const char *name, const char *rID, const char *desc, const char *state, int prio)
    : priority(prio)
{
  changeID = next_id();
  setProductName(name);
  setReleaseID(rID);
  setDescription(desc);
  setStatus(state);
}

//*******************************************************//

ChangeItem::ChangeItem(int cID, const char *name, const char *rID, const char *desc, const char *state, int prio)
    : changeID(cID), priority(prio)
{
  setProductName(name);
  setReleaseID(rID);
  setDescription(desc);
  setStatus(state);
}

//*******************************************************//

int ChangeItem::getChangeID()
{
  return changeID;
}

//*******************************************************//

void ChangeItem::getProductName(char *str)
{
  strncpy(str, productName, sizeof(productName));
  str[sizeof(productName) - 1] = '\0';
}
// Pass in a char buffer of size 11

//*******************************************************//

void ChangeItem::getReleaseID(char *str)
{
  strncpy(str, anticipatedRelease, sizeof(anticipatedRelease));
  str[sizeof(anticipatedRelease) - 1] = '\0';
}
// Pass in a char buffer of size 9

//*******************************************************//

void ChangeItem::getDescription(char *str)
{
  strncpy(str, description, sizeof(description));
  str[sizeof(description) - 1] = '\0';
}
// Pass in a char buffer of size 31

//*******************************************************//

void ChangeItem::getStatus(char *str)
{
  strncpy(str, state, sizeof(state));
  str[sizeof(state) - 1] = '\0';
}
// Pass in a char buffer of size 11

//*******************************************************//

int ChangeItem::getPriority()
{
  return priority;
}

//*******************************************************//

void ChangeItem::setProductName(const char *name)
{
  strncpy(productName, name, sizeof(productName));
  productName[sizeof(productName) - 1] = '\0';
}

//*******************************************************//

void ChangeItem::setReleaseID(const char *id)
{
  strncpy(anticipatedRelease, id, sizeof(anticipatedRelease));
  anticipatedRelease[sizeof(anticipatedRelease) - 1] = '\0';
}

//*******************************************************//

void ChangeItem::setDescription(const char *desc)
{
  strncpy(description, desc, sizeof(description));
  description[sizeof(description) - 1] = '\0';
}

//*******************************************************//

void ChangeItem::setStatus(const char *st)
{
  strncpy(state, st, sizeof(state));
  state[sizeof(state) - 1] = '\0';
}

//*******************************************************//

void ChangeItem::setPriority(int prio)
{
  priority = prio;
}

//*******************************************************//

ChangeItemFile::ChangeItemFile()
{
  openChangeItemFile();
}

//*******************************************************//

bool ChangeItemFile::findChangeItem(int id, ChangeItem &item)
{
  if (!seekToBeginningOfFile())
  {
    cerr << "Unable to find change item (cant seek to beginning)" << endl;
    return false;
  }

  ChangeItem buf;
  streampos pos;
  while (!file.eof())
  {
    getNextChangeItem(buf);
    if (buf.getChangeID() == id)
    {
      item = buf;
      return true;
    }
  }

  return false;
}

//*******************************************************//

bool ChangeItemFile::seekToBeginningOfFile()
{
  if (!file.is_open())
  {
    cerr << "File is not open" << endl;
    return false;
  }

  file.clear();
  file.seekg(0);

  return file.good(); // Returns true if the seek was successful
}

//*******************************************************//

bool ChangeItemFile::getNextChangeItem(ChangeItem &changeItemObj)
{
  return Read(changeItemObj);
}

//*******************************************************//

bool ChangeItemFile::createChangeItem(ChangeItem &aChangeItem)
{
  return Write(aChangeItem);
}

//*******************************************************//

bool ChangeItemFile::updateChangeItem(ChangeItem &oldChangeItem, ChangeItem &newChangeItem)
{
  if (!seekToBeginningOfFile())
  {
    cerr << "Unable to update change item" << endl;
    return false;
  }

  ChangeItem buf;
  streampos pos;
  while (!file.eof())
  {
    getNextChangeItem(buf);
    if (buf.getChangeID() == oldChangeItem.getChangeID())
    {
      // Get current read position and calculate the write position
      pos = file.tellg() - (streampos)sizeof(ChangeItem);

      // Reset flags for file
      closeChangeItemFile();
      openChangeItemFileForModify();

      // Seek to position to overwrite
      file.seekg(pos, file.beg);

      if (Write(newChangeItem))
      {
        closeChangeItemFile();
        openChangeItemFile();
        return true;
      }
      else
      {
        cerr << "Error writing change item" << endl;
        closeChangeItemFile();
        openChangeItemFile();
        return false;
      }
    }
  }

  cerr << "Change item not found" << endl;
  return false;
}

//*******************************************************//

void ChangeItemFile::searchChangeItem(int changeId)
{
  ChangeItem buf;
  if (!findChangeItem(changeId, buf))
    cout << "Item does not exist" << endl;
  else
  {
    // Prepare to display the ChangeItem details
    char productName[11];
    char anticipatedRelease[9];
    char description[31];
    char state[11];

    buf.getProductName(productName);
    buf.getReleaseID(anticipatedRelease);
    buf.getDescription(description);
    buf.getStatus(state);

    // Display the header
    cout << "\n";
    cout << "Selected Change Item in " << productName << ":\n";
    cout << setw(12) << "Change ID" <<
            setw(32) << "Description" <<
            setw(12) << "Status" <<
            setw(10) << "Priority" <<
            setw(12) << "Release ID" << endl;

    // Display the details
    cout << setw(12)<< buf.getChangeID() <<
            setw(32) << description <<
            setw(12) << state <<
            setw(10) << buf.getPriority() <<
            setw(12) << anticipatedRelease << endl;
  }
}

//*******************************************************//

bool ChangeItemFile::openChangeItemFile()
{
  file.open("ChangeItems.data", ios::in | ios::out | ios::binary | ios::app);
  if (!file.is_open())
  {
    cerr << "Error opening file" << endl;
    return false;
  }
  return true;
}

//*******************************************************//

bool ChangeItemFile::openChangeItemFileForModify()
{
  file.open("ChangeItems.data", ios::in | ios::out | ios::binary);
  if (!file.is_open())
  {
    cerr << "Error opening file" << endl;
    return false;
  }
  return true;
}

//*******************************************************//

bool ChangeItemFile::closeChangeItemFile()
{
  if (!file.is_open())
  {
    cerr << "File not open" << endl;
    return false;
  }

  file.close();
  return true;
}

bool ChangeItemFile::writeChangeItem(ChangeItem changeItemObj)
{
  return Write(changeItemObj);
}

//*******************************************************//

ChangeItemFile strtItem()
{
  return ChangeItemFile();
}

bool closeItem(ChangeItemFile &itemFile)
{
  return itemFile.closeChangeItemFile();
}

//*******************************************************//