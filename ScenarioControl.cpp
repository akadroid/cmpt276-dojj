// ScenarioControl.cpp
// Rev. 3 - (Add date) Fixed many glaring issues within the code such as error handling and general incorrect algorithms
// Rev. 2 - 16/07/24 Added implementation of the functions to ScenarioControl.cpp


//editing notes: addchangeitem is almost finished, just work on the end part, fix select product and we should be good for the most part
//*******************************************************//

#include <iostream>
#include <cstring>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#include "ScenarioControl.h"
using namespace std;

// Each macro also accounts for the new-line character
#define MAX_NAME_SIZE 31
#define MAX_PHONE_NUM_SIZE 11
#define MAX_EMAIL_SIZE 24
#define MAX_PRODUCT_NAME_SIZE 11
#define MAX_RELEASEID_SIZE 9
#define MAX_DATE_SIZE 11
#define MAX_DESCRIPTION_SIZE 31
#define MAX_STATUS_SIZE 11
#define WIDTH 30

//*******************************************************//

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

bool is_number(const string& s) 
{
    return !s.empty() && find_if(s.begin(), s.end(), [](unsigned char c){ return !isdigit(c); }) == s.end();
}
// https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
// Helper function to find if the string is a number or not

//*******************************************************//

void strtControl()
{
    productFile = strtProduct();
    customerFile = strtCustomer();
    changeItemFile = strtItem();
    changeRequestFile = strtChangeReq();
    productReleaseFile = strtRelease();
}

//*******************************************************//

void closeControl()
{
    closeProduct(productFile);
    stopCustomer(customerFile);
    closeItem(changeItemFile);
    closeChangeReq(changeRequestFile);
    closeRelease(productReleaseFile);
}

//*******************************************************//

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

        if (temp.size() != MAX_PHONE_NUM_SIZE - 1) // check that it must be 10 characters
        { 
            if (formatMismatchError() == false) return;
        }
        else // now check if the 10 digit string a number
        {
            if(is_number(temp)) { validNum = true; }
            else { if(!formatMismatchError()) return; }
        }
    } while (!validNum);

    strcpy(phoneNum, temp.c_str()); // move phone number over


    // get email
    do
    {
        cout << "Enter the email address: (Max 24 Char.)" << endl;
        getline(cin, temp);

        if (temp.size() > MAX_EMAIL_SIZE)
        {
            if (!formatMismatchError()) return;
        }
    } while (temp.size() > MAX_EMAIL_SIZE);

    strcpy(email, temp.c_str());


    // add or dont add customer. 
    char choice;
    bool exitCustomer = false;
    do
    {
        cout << "Do you want to add the customer to the system (Y/N)" << endl;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 'Y': {
                Customer customer(name, email, phoneNum);
                if (!customerFile.findCustomer(name, customer))
                {
                    if(customerFile.createCustomer(customer))
                    {
                        cout << "The customer is successfully added to the system!" << endl;
                        exitCustomer = true;
                    }
                    else
                    {
                        cout << "Failed to add customer to the system." << endl;
                        return;
                    }
                }
                else
                {
                    cout << "The user already exists. Continuing.." << endl;
                    exitCustomer = true;
                }
                break;
            }
            case 'N': {
                cout << "The customer is not added to the system" << endl;
                return; // just exit the option at this point
            }
            default: {
                if (!formatMismatchError()) return;
                break;
            }
        }
    } while(exitCustomer);

    // select the product
    selectProduct(productName);
    if (productName[0] == '\0') return; //product not selected return and end function here

    // select the change item for the product
    selectChangeItem(productName, changeID);

    if(changeID == -1) //if the user does not select a change item, attempt to create one
    {   
        // enter description
        do
        {
            cout << "Enter the description of the request:" << endl;
            getline(cin, temp);
            if (temp.size() > MAX_DESCRIPTION_SIZE)
            {
                if (!formatMismatchError()) return;
            }
        } while(temp.size() > MAX_DESCRIPTION_SIZE);

        strcpy(description, temp.c_str());
        
        // enter priority
        bool exitPrio = false;
        do
        {
            cout << "Enter the Priority of the request:" << endl;
            cin >> priority;

            if(cin.fail() || priority < 1 || priority > 5)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (!formatMismatchError()) return;
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                exitPrio = true;
            }   
        } while(exitPrio);

        // Confirmation and Printing
        bool exitConf = false;
        do
        {
            cout << "Confirm the above change request (Y/N)" << endl;
            char choice2;
            cin >> choice2;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice)
            {
                case 'Y': {
                    ChangeItem toAddChItem(productName, releaseID, description, "Reported", priority);
                    changeID = toAddChItem.getChangeID();
                    if (changeItemFile.createChangeItem(toAddChItem))
                    {
                        cout << "The change ID for the change item is assigned as" 
                            << changeID << "and the status is reported" << endl; //hard code because its default

                        ChangeRequest toAddChReq(changeID, releaseID, name, date);
                        if (changeRequestFile.createChangeRequest(toAddChReq))
                        {
                            cout << "The request that is assigned to " << changeID
                                << " has been sent out to the system." << endl;
                            exitConf = true;
                        }
                        else
                        {
                            cout << "Failed to add change request to file, aborting operation.." << endl;
                            return;
                        }
                    }
                    else
                    {
                        cout << "Failed to add change item to file, aborting operation.." << endl;
                        return;
                    }  
                    break;
                }
                case 'N': {
                    cout << "The change request was not added, returning to main menu.." << endl;
                    return;
                }
                default: {
                    if (!formatMismatchError()) return;
                    break;
                }
            }
        } while (exitConf);
    }
    else // in this case, a change item is selected and thus we can simply 
    {
        ChangeRequest toAddChReq(changeID, releaseID, name, date);
        if(changeRequestFile.createChangeRequest(toAddChReq))
        {
            cout << "The change ID for the request is " << changeID << "." << endl;
            cout << "The request that is assigned to " << changeID 
                << " has been sent to the system." << endl;
        }
        else
        {
            cout << "Failed to add change request to the system, aborting operation.." << endl;
        }
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

    cout << "Would you like to confirm adding " << productName << " as a product? (Y/N)" << endl;
    char choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Product toAdd(productName); // create temporary product

    switch (choice)
    {
    case 'Y':
        if(createProduct(toAdd, productFile) != 0) {
            cout << "The product has been added successfully." << endl;
        } else {
            cout << "Duplicate product detected. The product was not added." << endl;
        }
        break;
    case 'N':
        cout << "The product was not added" << endl;
        break;
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

    productFile.seekToBeginningOfFile();
    selectProduct(productName);
    if (productName[0] == '\0') return; // no product was selected therefore exit function

    cout << "What is the Release ID for this product (Max 8 Char.)" << endl;
    cin.getline(releaseID, MAX_RELEASEID_SIZE);
    
    cout << "What is the Release Date? (In form: YYYY-MM-DD)" << endl;
    cin.getline(releaseDate, MAX_DATE_SIZE);

    cout << "Would you like to confirm adding a Product Release with ID " << releaseID << " with Release Date "
        << releaseDate << " for " << productName << "? (Y/N)" << endl;
    char choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ProductRelease productRelease(productName, releaseID, releaseDate);

    switch (choice)
    {
        case 'Y':
            if(createProductRelease(productRelease, productReleaseFile) != 0) {
                cout << "The product has been added successfully." << endl;
            } else {
                cout << "Duplicate product release detected. The product release was not added." << endl;
            }
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

    cout << "Would you like to confirm adding this Change Item to the product " << productName << " (Y/N):" << endl;
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

void listChangeItemsReport()
{
    char productName[MAX_PRODUCT_NAME_SIZE];
    char releaseID[MAX_RELEASEID_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
    char status[MAX_STATUS_SIZE];
    int priority = 0;
    int changeID = 0;
    unsigned int counter = 0;
    ChangeItem changeItem;
    string choice;
    

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
        for (unsigned int i=0; i < 20;)
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

        getline(cin, choice);

        if (is_number(choice))
        {
            int number = stoi(choice);
            if (number == 0){ exit = true; }
            else
            {
                cout << "Number input goes beyond the range, try again" << endl;
            }  
        }
        else if (choice == "P" || choice == "p")
        {
            changeItemFile.seekToBeginningOfFile();

            if (counter <= 20) { counter = 0; }
            else
            {
                counter -= 20;
                for(unsigned int i=0; i < counter ; i++) { changeItemFile.getNextChangeItem(changeItem); }
            }
            
        }
        else if (choice == "N" || choice == "n")
        {
            // dont do anything
        }
        else
        {
            if (!formatMismatchError()) exit = true;
        }
    }
}

//*******************************************************//

void listCustomersStaffReport()
{
    char productName[MAX_PRODUCT_NAME_SIZE];
    char customerName[MAX_NAME_SIZE];
    int changeID;
    unsigned int counter;
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
        for (unsigned int i=0; i < 20;){
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
            if (number == 0){ exit = true; }
            else
            {
                cout << "Number input goes beyond the range, try again" << endl;
            }
        }
        else if (choice == "P" || choice == "p")
        {
            changeRequestFile.seekToBeginningOfFile();

            if (counter <= 20) { counter = 0; }
            else
            {
                counter -= 20;
                for(int i=0; i < counter ; i++) { changeRequestFile.getNextChangeRequest(changeRequest); }
            }
        }
            
        else if (choice == "N" || choice == "n")
        {
            // dont do anything
        }
        else
        {
            if (!formatMismatchError()) exit = true;
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
    Product tmp;

    while (!exit)
    {
        cout << "Select the Product you want to look at" << endl;
        cout << "+++++" << endl;
        cout << "Product:" << endl;
        for (int i=0; i < 20; i++){
            if (!productFile.getNextProduct(product)) break;
            counter++;
            product.getName(prodName);
            cout << counter << ") " << prodName << endl;
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
            if (1 <= number && number <= counter)
            {
                // counter -= number;
                productFile.seekToBeginningOfFile();
                for (int i=0; i < number; i++)
                {
                    productFile.getNextProduct(tmp);
                }
                tmp.getName(productName);
                exit = true;
            }
            else if (number == 0){
                productName[0] = '\0'; //set as basically blank c string
                exit = true;
            } else {
                cout << "Number input goes beyond the range, try again" << endl;
                productFile.seekToBeginningOfFile();
                counter = 0;
            }
        }
        else if (choice == "P" || choice == "p")
        {
            productFile.seekToBeginningOfFile();
            counter -= counter;
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


//This function looks to provide the user interface options when selecting we have to select a product

//*******************************************************//

void selectChangeItem(char* product, int &chngID)
{
    if (!changeItemFile.seekToBeginningOfFile()) //seek first
    {
        cerr << "Unable to find change item (cant seek to beginning)" << endl;
    }
    
    unsigned int counter = 0; //file line position
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
        for (unsigned int i=0; i < 20;){
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
            if (1 <= number && number <= 20)
            {
                counter = (counter/20) * 20 + number;
                changeItemFile.seekToBeginningOfFile();
                for (unsigned int i=0; i<counter; i++)
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

            if (counter <= 20) { counter = 0; }
            else
            {
                counter -= 20;
                for(unsigned int i=0; i < counter ; i++) { changeItemFile.getNextChangeItem(changeItem); }
            }
        }
        else if (choice == "N" || choice == "n")
        {
            // dont do anything
        }
        else
        {
            if (!formatMismatchError()){
                chngID = -1;
                exit = true;
            }
        }
    }
}

// This function prodives the user interface for when we select a change item