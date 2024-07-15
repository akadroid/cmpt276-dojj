// UnitTestMain.cpp
// Rev. 1 - 03/07/24 Original by D.O.J.J Software Development

//*******************************************************//
// This module is designed to test the creation and retrieval of ChangeItem objects
// within the system.
// The testCreatingChangeItem function calls createChangeItem to save
// a Change Item to the disk, and then retrieves it from disk using a ChangeItemFile object.
// It will then compare the retrieved object with another object with expected results.
// The testUpdatingChangeItem function will first create a new ChangeItem object,
// then modify it, and then call the updateChangeItem function to save it to disk.
// The program will notify the user of failed test cases.
//*******************************************************//

#include <iostream>
#include <cstring>
#include "ChangeItem.h"

using namespace std;
void assertChangeItem(string testName, ChangeItem &expected, ChangeItem &actual);

//*******************************************************//

// Name of test: Testing createChangeItem
// Type: Functional Test
// Preconditions: change item file is empty
// Steps: run the program
// Expected results: Program says "Creating change item passed."
void testCreatingChangeItem()
{
  ChangeItemFile file;

  // Create new Change Item (saves to disk)
  ChangeItem item("Test Product", "V1", "Not working", "none", 5);
  file.createChangeItem(item);

  // Get Change Item from disk
  ChangeItem createdChangeItem = file.findChangeItem(1);

  // Test the Change Item
  ChangeItem expectedChangeItem(1, "Test Product", "V1", "Not working", "none", 5);
  assertChangeItem("Creating change item", expectedChangeItem, createdChangeItem);
}

//*******************************************************//

// Name of test: Testing updateChangeItem
// Type: Functional Test
// Preconditions: change item file has one record already, that record having change ID of 1
// Steps: run the program
// Expected results: Program says "Updating change item passed."
void testUpdatingChangeItem()
{
  ChangeItemFile file;

  // Create new Change Item (saves to disk)
  ChangeItem item("Test Product", "V2", "Crashes", "none", 1);
  file.createChangeItem(item);

  // Update new Change Item (reads, then saves to disk)
  ChangeItem item2 = file.findChangeItem(1);
  item2.setStatus("Assessed");
  file.updateChangeItem(item2);

  // Get updated Change Item from disk
  ChangeItem createdChangeItem = file.findChangeItem(2);

  // Test the updated Change Item
  ChangeItem testChangeItem(2, "Test Product", "V2", "Crashes", "Assessed", 1);
  assertChangeItem("Updating change item", createdChangeItem, testChangeItem);
}

//*******************************************************//

int main()
{
  testCreatingChangeItem();
  testUpdatingChangeItem();
}

//*******************************************************//

void assertChangeItem(string testName, ChangeItem &expected, ChangeItem &actual)
{
  bool pass = true;

  if (actual.getChangeID() != expected.getChangeID())
  {
    std::cout << testName << " failed. Change ID mismatch. Expected: " << expected.getChangeID() << ", Actual: " << actual.getChangeID() << std::endl;
    pass = false;
  }

  char actualProductName[11];
  char expectedProductName[11];
  actual.getProductName(actualProductName);
  expected.getProductName(expectedProductName);

  if (strcmp(actualProductName, expectedProductName) != 0)
  {
    cout << testName << " failed. Product Name mismatch. Expected: " << expectedProductName << ", Actual: " << actualProductName << std::endl;
    pass = false;
  }

  char actualReleaseID[9];
  char expectedReleaseID[9];
  actual.getReleaseID(actualReleaseID);
  expected.getReleaseID(expectedReleaseID);

  if (strcmp(actualReleaseID, expectedReleaseID) != 0)
  {
    cout << testName << " failed: Release ID mismatch. Expected: " << expectedReleaseID << ", Actual: " << actualReleaseID << std::endl;
    pass = false;
  }

  char actualDescription[31];
  char expectedDescription[31];
  actual.getDescription(actualDescription);
  expected.getDescription(expectedDescription);

  if (strcmp(actualDescription, expectedDescription) != 0)
  {
    cout << testName << " failed: Description mismatch. Expected: " << expectedDescription << ", Actual: " << actualDescription << std::endl;
    pass = false;
  }

  char actualState[11];
  char expectedState[11];
  actual.getStatus(actualState);
  expected.getStatus(expectedDescription);

  if (strcmp(actualState, expectedState) != 0)
  {
    cout << testName << " failed: Status mismatch. Expected: " << expectedState << ", Actual: " << actualState << std::endl;
    pass = false;
  }

  if (actual.getPriority() != expected.getPriority())
  {
    std::cout << testName << " failed: Priority mismatch. Expected: " << expected.getPriority() << ", Actual: " << actual.getPriority() << std::endl;
    pass = false;
  }

  if (pass)
  {
    cout << testName << " passed." << endl;
  }
}

//*******************************************************//