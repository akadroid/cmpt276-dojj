// ScenarioControl.cpp
// Rev. 1 - 17/07/2024 Original by D.O.J.J Software Development

//*******************************************************//

#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#include "ScenarioControl.h"
using namespace std;

#define MAX_NAME_SIZE 31 // accounts for the null character
#define MAX_PHONE_NUM_SIZE 11
#define MAX_EMAIL_SIZE 24
#define MAX_PRODUCT_NAME_SIZE 11
#define MAX_RELEASEID_SIZE 9
#define MAX_DATE_SIZE 11
#define MAX_DESCRIPTION_SIZE 31
#define MAX_STATUS_SIZE 11
#define WIDTH 30

// global variables 
ProductFile productFile;
CustomerFile customerFile;
ChangeItemFile changeItemFile;
ChangeRequestFile changeRequestFile;
ProductReleaseFile productReleaseFile;

// function header for select product/change item
void selectProduct(char *productName);
void selectChangeItem(char* product, int &chngID);

//*******************************************************//

bool formatMismatchError()
{   
    string choice; // great class for dealing with bad inputs
    while(true)
    {
        cout << "Data was not entered due to a formatting mismatch." << endl;
        cout << "Press Y to try again, or 0 to return to the main menu." << endl;
        getline(cin, choice);
        if (choice == "Y") { return true; } 
        else if (choice == "0") { return false; }
        else { cout << "Please select an appropriate option from the menu" << endl; }
    } 
}
// This function serves as the UI when there is a format mismatch determined by the user.
// The function will ask whether the user would like to try again or not to which the user will choose.
// Returns True if the Y (yes) is entered, False if 0 (no) is entered 

//*******************************************************//

bool is_number(const std::string& s) 
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
// https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
// Helper function to find if the string is a number or not

//*******************************************************//

// Startup functions that need to be called
void strtControl()
{
    productFile = strtProduct();
    customerFile = strtCustomer();
    changeItemFile = strtItem();
    changeRequestFile = strtChangeReq();
    productReleaseFile = strtRelease();
}

//*******************************************************//

// Shutdown functions that need to be called
void closeControl()
{
    closeProduct(productFile);
    stopCustomer(customerFile);
    closeItem(changeItemFile);
    closeChangeReq(changeRequestFile);
    closeRelease(productReleaseFile);
}

//*******************************************************//

// Scenario when user wants to add a Change Request, get required data
// and perform required operations to add a change request
void addChangeReq()
{
    string temp; //put things into string before the char array to ensure proper lenght
    char name[MAX_NAME_SIZE];
    char phoneNum[MAX_PHONE_NUM_SIZE];
    char email[MAX_EMAIL_SIZE];
    char productName[MAX_PRODUCT_NAME_SIZE];
    char releaseID[MAX_RELEASEID_SIZE];
    char date[MAX_DATE_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
    int changeID;
    int priority;

    // get name
    do
    {
        cout << "Enter the customer name: (Max 30 Char.)" << endl;
        getline(cin, temp); // move into a string first

        if (temp.size() > MAX_NAME_SIZE-1)
        {
            if (formatMismatchError() == false) return; // return to main menu
        }
    } while(temp.size() > MAX_NAME_SIZE-1);
    
    strcpy(name, temp.c_str()); // move into name once size agrees


    // get number
    bool validNum = false;
    do{
        cout << "Enter the phone number:" << endl;
        getline(cin, temp);

        if (temp.size() != MAX_PHONE_NUM_SIZE - 1) // must be 10 characters
        { 
            if (formatMismatchError() == false) return;
        }
        else
        {
            bool validDigits = true;
            for (char c : temp) //check if its 10 valid characters
            {
                if (!isdigit(c))
                {   
                    validDigits = false; // change for if we break out of the for loop
                    if(formatMismatchError() == false) return;
                    break; // if they want to retry, break out 
                }
            }
            if (validDigits) validNum = true; //
        }
    } while (!validNum);


    // get email
    do
    {
        cout << "Enter the email address: (Max 24 Char.)" << endl;
        getline(cin, temp);

        if (temp.size() > MAX_EMAIL_SIZE)
        {
            if (formatMismatchError() == false) return;
        }
    } while (temp.size() > MAX_EMAIL_SIZE);

    strcpy(email, temp.c_str());

    // add or dont add customer. 
    char choice;
    cout << "Do you want to add the customer to the system (Y/N)" << endl;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Customer customer(name, email, phoneNum);

    switch (choice)
    {
        case 'Y':
            customerFile.createCustomer(customer);
            cout << "The customer is successfully added to the system!" << endl;
            break;
        case 'N':
            cout << "The customer is not added to the system" << endl;
            break;
        default:
            cout << "Bad input detected, the customer is not added." << endl;
    }

    // select the product
    selectProduct(productName);
    if (productName[0] == '\0') return; //product not selected return and end function here

    // select the change item for the product
    selectChangeItem(productName, changeID);
    if(changeID == -1)
    {   
        cout << "Enter the description of the request" << endl;
        cin.getline(description, MAX_DESCRIPTION_SIZE);
        cout << "Enter the Priority of the request" << endl;
        cin >> priority;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
        ChangeRequest toAdd(changeID, releaseID, name, date);
        //the method to write to file is private and therefore unaccessable, but we add file here
    }

}

//*******************************************************//

// Scenario when user wants to add a Product, get required data
// and perform required operation to add a product
void addProduct()
{
    cout << "What is the name of the Product? (Max 10 Char.)" << endl;
    char productName[MAX_PRODUCT_NAME_SIZE];
    cin.getline(productName, MAX_PRODUCT_NAME_SIZE);

    cout << "Would you like to confirm adding WordEdit as a product? (Y/N)" << endl;
    char choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Product toAdd(productName); // create temporary product

    switch (choice)
    {
    case 'Y':
        createProduct(toAdd);
        cout << "The product has been added successfully." << endl;
        break;
    case 'N':
        cout << "The product was not added" << endl;
    default:
        cout << "Bad output detected, product was not added" << endl;
        break;
    }
}

//*******************************************************//

// Scenario when user wants to add a Product Release, get required data
// and perform required operation to add a product release
void addProductRelease()
{
    char productName[MAX_PRODUCT_NAME_SIZE];
    char releaseID[MAX_RELEASEID_SIZE];
    char releaseDate[MAX_DATE_SIZE];

    selectProduct(productName);
    if (productName[0] == '\0') return; // no product was selected therefore exit function

    cout << "What is the Release ID for this product (Max 8 Char.)" << endl;
    cin.getline(releaseID, MAX_RELEASEID_SIZE);
    
    cout << "What is the Release Date? (In form: YYYY-MM-DD)" << endl;
    cin.getline(releaseDate, MAX_DATE_SIZE);

    cout << "Would you like to confirm adding a Product Release with ID" << releaseID << "with Release Date"
        << releaseDate << "for WordEdit? (Y/N)" << endl;
    char choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ProductRelease productRelease(productName, releaseID, releaseDate);

    switch (choice)
    {
        case 'Y':
            createProductRelease(productRelease);
            cout << "The product has been added successfully." << endl;
            break;
        case 'N':
            cout << "The product release was not added." << endl;
            break;
        default:
            cout << "Bad output detected, product was not added" << endl;
            break;
    }
}

//*******************************************************//

// Scenario when user wants to add a Change Item, get required data
// and perform required operation to add a change item
void addChangeItem()
{
    char productName[MAX_PRODUCT_NAME_SIZE];
    char releaseID[MAX_RELEASEID_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
    char status[MAX_STATUS_SIZE];
    int priority;

    selectProduct(productName);
    if (productName[0] == '\0') return; // no product selected

    cout << "What is the Release ID? (Max 8 Char.)" << endl;
    cin.getline(releaseID, MAX_RELEASEID_SIZE);
    
    cout << "Write a description of the Change Item. (Max 30 Char.)" << endl;
    cin.getline(description, MAX_DESCRIPTION_SIZE);

    cout << "Status? (Reported, Assessed, Cancelled, In Progress, Done)" << endl;
    cin.getline(status, MAX_STATUS_SIZE);
    
    cout << "Priority? (1 to 5, with 5 being the highest priority)" << endl;
    cin >> priority;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ChangeItem toAdd(productName, releaseID, description, status, priority);

    cout << "Would you like to confirm adding this Change Item to the product WordEdit (Y/N):" << endl;
    cout << "Change ID" << setw(WIDTH) << "Description" << setw(WIDTH) << "Status" 
            << setw(WIDTH) << "Priority" << setw(WIDTH) << "Release ID" << endl;
     cout << toAdd.getChangeID() << left << setw(WIDTH) << description << setw(WIDTH) << status
            << setw(WIDTH) << priority << setw(WIDTH) << releaseID << endl;
    

    char choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice)
    {
        case 'Y':
            changeItemFile.createChangeItem(toAdd);
            cout << "The Change Item has been added successfully." << endl;
            break;
        case 'N':
            cout << "The Change Item was not added." << endl;
            break;
        default:
            cout << "Bad output detected, product was not added" << endl;
            break;
    }
}

//*******************************************************//

// Scenario when user chooses they want to modify a change item,
// find the change item in the respective file and perform the changes
// needed
void modifyChangeItem()
{
    char productName[MAX_PRODUCT_NAME_SIZE];
    char releaseID[MAX_RELEASEID_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
    char status[MAX_STATUS_SIZE];
    int priority;
    int changeID;
    ChangeItem changeItem;
    

    selectProduct(productName);
    if (productName[0] == '\0') return; // no product selected

    selectChangeItem(productName, changeID);
    if (changeID == -1) return; //did not select a change item

    //obtain changeitem first
    while(changeItem.getChangeID() != changeID)
    {
        changeItemFile.seekToBeginningOfFile();
        changeItemFile.getNextChangeItem(changeItem);
    }

    //update values
    changeItem.getDescription(description);
    changeItem.getStatus(status);
    priority = changeItem.getPriority();
    changeItem.getReleaseID(releaseID);


    cout << "Select the attribute you would like to edit for the Change Item in " << productName << endl;
    cout << "+++++" << endl;
    cout << "Change ID" << setw(WIDTH) << "Description" << setw(WIDTH) << "Status" 
            << setw(WIDTH) << "Priority" << setw(WIDTH) << "Release ID" << endl;
    cout << changeID << setw(WIDTH) << description << setw(WIDTH) << status 
            << setw(WIDTH) << priority << setw(WIDTH) << releaseID << endl;

    cout << "+++++" << endl;
    cout << "+++++" << endl;
    cout << "1) Edit Description" << endl;
    cout << "2) Edit Status" << endl;
    cout << "3) Edit Priority" << endl;
    cout << "4) Edit Release ID" << endl;
    cout << "0) Main Menu" << endl;
    cout << "+++++";

    int choice;
    char choice2;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (choice)
    {
        case 1:
        {
            cout << "Enter the new description for this Change Item:" << endl;
            cin.getline(description, MAX_DESCRIPTION_SIZE);
            cout << "Are you sure you want to change the description to" << description << " ? (Y/N)" << endl;
            cin >> choice2;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            ChangeItem updatedChangeItem(productName, releaseID, description, status, priority);
            switch (choice2)
            {
                case 'Y':
                    changeItemFile.updateChangeItem(changeItem, updatedChangeItem); // update on file
                    cout << "The Change Item has been successfully updated" << endl; 
                    break;
                case 'N':
                    cout << "The Change Item was not updated" << endl;
                    break;
                default:
                    cout << "Bad input detected, no change was made" << endl;
            }
            break;
        }    
        case 2:
        {
            cout << "Enter the new status for this Change Item:" << endl;
            cin.getline(status, MAX_STATUS_SIZE);
            cout << "Are you sure you want to change the status to" << status << " ? (Y/N)" << endl;
            cin >> choice2;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            ChangeItem updatedChangeItem(productName, releaseID, description, status, priority);
            switch (choice2)
            {
                case 'Y':
                    changeItemFile.updateChangeItem(changeItem, updatedChangeItem); // update on file
                    cout << "The Change Item has been successfully updated" << endl; 
                    break;
                case 'N':
                    cout << "The Change Item was not updated" << endl;
                    break;
                default:
                    cout << "Bad input detected, no change was made" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "Enter the new priority for this Change Item:" << endl;
            cin >> priority;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Are you sure you want to change the priority to" << priority << " ? (Y/N)" << endl;
            cin >> choice2;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            ChangeItem updatedChangeItem(productName, releaseID, description, status, priority);
            switch (choice2)
            {
                case 'Y':
                    changeItemFile.updateChangeItem(changeItem, updatedChangeItem); // update on file
                    cout << "The Change Item has been successfully updated" << endl; 
                    break;
                case 'N':
                    cout << "The Change Item was not updated" << endl;
                    break;
                default:
                    cout << "Bad input detected, no change was made" << endl;
            }
            break;
        }
        case 4:
        {
            cout << "Enter the new Release ID for this Change Item:" << endl;
            cin.getline(releaseID, MAX_RELEASEID_SIZE);
            cout << "Are you sure you want to change the Release ID to" << releaseID << " ? (Y/N)" << endl;
            cin >> choice2;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            ChangeItem updatedChangeItem(productName, releaseID, description, status, priority);
            switch (choice2)
            {
                case 'Y':
                    changeItemFile.updateChangeItem(changeItem, updatedChangeItem); // update on file
                    cout << "The Change Item has been successfully updated" << endl; 
                    break;
                case 'N':
                    cout << "The Change Item was not updated" << endl;
                    break;
                default:
                    cout << "Bad input detected, no change was made" << endl;
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Bad input detected, returning to menu" << endl;
    }
}

//*******************************************************//
// Scenario when user wants to search for a ChangeItem, get required information
// and perform required operation with a linear search of the binary file
void queryChangeItems()
{
    char productName[MAX_PRODUCT_NAME_SIZE];
    int changeID;
    ChangeItem changeItem;
    
    selectProduct(productName);
    if (productName[0] == '\0') return; // no product selected

    selectChangeItem(productName, changeID);
    if (changeID == -1) return; //did not select a change item

    changeItemFile.searchChangeItem(changeID); // the current implementation of searchChangeItem still has ui
}

//*******************************************************//

// Scenario when user wants a report for a list of change items for a product release
// Perform needed operations to obtain and print this report
void listChangeItemsReport()
{
    char productName[MAX_PRODUCT_NAME_SIZE];
    char releaseID[MAX_RELEASEID_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
    char status[MAX_STATUS_SIZE];
    int priority = 0;
    int changeID = 0;
    int counter = 0;
    ChangeItem changeItem;
    

    selectProduct(productName);
    if (productName[0] == '\0') return; // no product selected

    bool exit = false;
    changeItemFile.seekToBeginningOfFile();
    while (!exit)
    {
        cout << "List of Change Items for " << productName << " to implement:" << endl;
        cout << "+++++" << endl;
        cout << "   Change ID" << left << setw(WIDTH) << "Description" << setw(WIDTH) << "Status" 
            << setw(WIDTH) << "Priority" << setw(WIDTH) << "Anticipated Release" << endl;
        for (int i=0; i < 20;)
        {
            if (!changeItemFile.getNextChangeItem(changeItem)) break; // get next change item, but if read fails then break
            char currentProduct[MAX_PRODUCT_NAME_SIZE];
            char currentStatus[MAX_STATUS_SIZE];
            changeItem.getProductName(currentProduct);
            changeItem.getStatus(currentStatus);
            if (productName == currentProduct && currentStatus != "Done" && currentStatus != "Cancelled")
            {
                i++;
                changeID = changeItem.getChangeID();
                changeItem.getDescription(description);
                changeItem.getStatus(status);
                changeItem.getReleaseID(releaseID);
                priority = changeItem.getPriority();
                cout << i << ") " << changeID << setw(WIDTH) << description << setw(WIDTH) << status 
                    << setw(WIDTH) << priority << setw(WIDTH) << releaseID << endl;
            }
        }
        cout << "+++++" << endl;
        cout << "Press P for the previous 20 Products" << endl;
        cout << "Press N for the next 20 Products" << endl;
        cout << "Press 0 to Return" << endl;
        cout << "+++++" << endl;

        string choice;
        if (is_number(choice))
        {
            int number = stoi(choice);
            if (1 <= number  && number <= 20)
            {
                counter -= number;
                changeItemFile.seekToBeginningOfFile();
                for (int i=0; i<counter; i++)
                {
                    changeItemFile.getNextChangeItem(changeItem);
                }
                exit = true;
            }
            else if (number == 0){
                exit = true;
            }
            cout << "Number input goes beyond the range, try again" << endl;
        }
        else if (choice == "P" || choice == "p")
        {
            changeItemFile.seekToBeginningOfFile();
            counter -= 20;
            for(int i=0; i < counter ; i++) { changeItemFile.getNextChangeItem(changeItem); }
        }
        else if (choice == "N" || choice == "n")
        {
            // dont do anything
        }
        else
        {
            cout << "Bad input detected, no Change Item will be selected" << endl;
            break;
        }
    }
}

//*******************************************************//

// Scenario when user wants a report for a list of customers associated with a change request
// Perform needed operations to obtain and print this report
void listCustomersStaffReport()
{
    char productName[MAX_PRODUCT_NAME_SIZE];
    char customerName[MAX_NAME_SIZE];
    int changeID;
    int counter;
    ChangeRequest changeRequest;
    Customer toFind;

    selectProduct(productName);
    if (productName[0] == '\0') return; // no product selected

    selectChangeItem(productName, changeID);
    if (changeID == -1) return; //did not select a change item

    bool exit = false;
    changeRequestFile.seekToBeginningOfFile();
    while (!exit)
    {
        cout << "List of Customers/Staff to inform about implemented change:" << endl;
        cout << "+++++" << endl;
        cout << "Name" << setw(WIDTH) << "Email" << setw(WIDTH) << "Phone Number" << endl;
        for (int i=0; i < 20;){
            if (!changeRequestFile.getNextChangeRequest(changeRequest)) break; //get the next item, if eof then stop and break out of the loop
            int currentChangeID = changeRequest.getRequestID(); //naming conflict but this is the change id
            if (changeID == currentChangeID)
            {
                i++;
                
                changeRequest.getCustomerName(customerName);
                toFind.setCustomerName(customerName); // the find customer only needs the first name on the object
                customerFile.findCustomer(customerName, toFind);
                cout << customerName; 
            }
            
        }
        cout << "+++++" << endl;
        cout << "+++++" << endl;
        cout << "Press P for the previous 20 Products" << endl;
        cout << "Press N for the next 20 Products" << endl;
        cout << "Press 0 to Return" << endl;
        cout << "+++++" << endl;

        string choice;

        getline(cin, choice);

        if (is_number(choice)) //decisions on what to do based on choice
        {
            int number = stoi(choice);
            if (1 <= number  && number <= 20)
            {
                counter -= number;
                changeRequestFile.seekToBeginningOfFile();
                for (int i=0; i<counter; i++)
                {
                    changeRequestFile.getNextChangeRequest(changeRequest);
                }
                exit = true;
            }
            else if (number == 0){
                exit = true;
            }

            cout << "Number input goes beyond the range, try again" << endl;
        }
        else if (choice == "P" || choice == "p")
        {
            changeRequestFile.seekToBeginningOfFile();
            counter -= 20;
            for(int i=0; i < counter ; i++) { changeRequestFile.getNextChangeRequest(changeRequest); }
        }
        else if (choice == "N" || choice == "n")
        {
            // dont do anything
        }
        else
        {
            cout << "Bad input detected, no Change Item will be selected" << endl;
            break;
        }
    }
}

//*******************************************************//

void selectProduct(char* productName)
{
    if (!productFile.seekToBeginningOfFile()) //seek first
    {
        cerr << "Unable to find product (cant seek to beginning)" << endl;
    }
    
    int counter = 0; //file line position
    bool exit = false;
    string choice;
    char prodName[MAX_PRODUCT_NAME_SIZE];
    Product product;

    while (!exit)
    {
        cout << "Select the Product you want to look at" << endl;
        cout << "+++++" << endl;
        cout << "Product:" << endl;
        for (int i=0; i < 20; i++){
            if (!productFile.getNextProduct(product)) break;
            counter++;
            product.getName(prodName);
            cout << i++ << ") " << prodName << endl;
        }
        cout << "+++++" << endl;
        cout << "+++++" << endl;
        cout << "Press P for the previous 20 Products" << endl;
        cout << "Press N for the next 20 Products" << endl;
        cout << "Press 0 to Return" << endl;
        cout << "+++++" << endl;

        getline(cin, choice);

        if (is_number(choice))
        {
            int number = stoi(choice);
            if (1 <= number  && number <= 20)
            {
                counter -= number;
                productFile.seekToBeginningOfFile();
                for (int i=0; i<counter; i++)
                {
                    productFile.getNextProduct(product);
                }
                product.getName(productName);
                exit = true;
            }
            else if (number == 0){
                productName[0] = '\0'; //set as basically blank c string
                exit = true;
            }

            cout << "Number input goes beyond the range, try again" << endl;
        }
        else if (choice == "P" || choice == "p")
        {
            productFile.seekToBeginningOfFile();
            counter -= 20;
            for(int i=0; i < counter ; i++) { productFile.getNextProduct(product); }
        }
        else if (choice == "N" || choice == "n")
        {
            //do nothing and let the loop run again
        }
        else
        {
            cout << "Bad input detected, no product selected" << endl;
            productName[0] = '\0';
            break;
        }
    }
}

//This function looks to provide the user interface options when selecting we have to select a product

//*******************************************************//

void selectChangeItem(char* product, int &chngID)
{
    if (!changeItemFile.seekToBeginningOfFile()) //seek first
    {
        cerr << "Unable to find product (cant seek to beginning)" << endl;
    }
    
    int counter = 0; //file line position
    bool exit = false;
    string choice;
    char prodName[MAX_PRODUCT_NAME_SIZE];
    ChangeItem changeItem;
    char description[MAX_DESCRIPTION_SIZE];
    char status[MAX_STATUS_SIZE];
    char antiRelease[MAX_RELEASEID_SIZE];
    int changeID;
    int prio;
    

    while (!exit)
    {
        cout << "Given below are existing change items for" << product << endl;
        cout << "+++++" << endl;
        cout << "   Change ID" << left << setw(WIDTH) << "Description" << setw(WIDTH) << "Status" 
            << setw(WIDTH) << "Priority" << setw(WIDTH) << "Anticipated Release" << endl;
        for (int i=0; i < 20;){
            if (!changeItemFile.getNextChangeItem(changeItem)) break; //get the next item, if eof then stop and break out of the loop
            changeItem.getProductName(prodName);
            if (prodName == product)
            {
                i++;
                changeID = changeItem.getChangeID();
                changeItem.getDescription(description);
                changeItem.getStatus(status);
                changeItem.getReleaseID(antiRelease);
                prio = changeItem.getPriority();
                cout << i << ") " << changeID << setw(WIDTH) << description << setw(WIDTH) << status 
                    << setw(WIDTH) << prio << setw(WIDTH) << antiRelease << endl;
            }
            
        }
        cout << "+++++" << endl;
        cout << "+++++" << endl;
        cout << "Press P for the previous 20 Products" << endl;
        cout << "Press N for the next 20 Products" << endl;
        cout << "Press 0 to Return" << endl;
        cout << "+++++" << endl;

        getline(cin, choice);

        if (is_number(choice)) //decisions on what to do based on choice
        {
            int number = stoi(choice);
            if (1 <= number  && number <= 20)
            {
                counter -= number;
                changeItemFile.seekToBeginningOfFile();
                for (int i=0; i<counter; i++)
                {
                    changeItemFile.getNextChangeItem(changeItem);
                }
                changeID = changeItem.getChangeID(); //when selecting the right one replace the chngID
                exit = true;
            }
            else if (number == 0){
                changeID = -1; //if none was selected, put -1 to let user know
                exit = true;
            }

            cout << "Number input goes beyond the range, try again" << endl;
        }
        else if (choice == "P" || choice == "p")
        {
            changeItemFile.seekToBeginningOfFile();
            counter -= 20;
            for(int i=0; i < counter ; i++) { changeItemFile.getNextChangeItem(changeItem); }
        }
        else if (choice == "N" || choice == "n")
        {
            // dont do anything
        }
        else
        {
            cout << "Bad input detected, no Change Item will be selected" << endl;
            chngID = -1;
            break;
        }
    }
}

// This function prodives the user interface for when we select a change item