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
#include <string>
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
  ChangeItem item = file.findChangeItem(1);
  string status = "Assessed";
  item.setStatus(status);
  file.updateChangeItem(item);

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

  if (actual.getProductName() != expected.getProductName())
  {
    std::cout << testName << " failed. Product Name mismatch. Expected: " << expected.getProductName() << ", Actual: " << actual.getProductName() << std::endl;
    pass = false;
  }

  if (actual.getReleaseID() != expected.getReleaseID())
  {
    std::cout << testName << " failed: Release ID mismatch. Expected: " << expected.getReleaseID() << ", Actual: " << actual.getReleaseID() << std::endl;
    pass = false;
  }

  if (actual.getDescription() != expected.getDescription())
  {
    std::cout << testName << " failed: Description mismatch. Expected: " << expected.getDescription() << ", Actual: " << actual.getDescription() << std::endl;
    pass = false;
  }

  if (actual.getStatus() != expected.getStatus())
  {
    std::cout << testName << " failed: Status mismatch. Expected: " << expected.getStatus() << ", Actual: " << actual.getStatus() << std::endl;
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