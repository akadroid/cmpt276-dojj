// UI.cpp
// Rev. 3 - 29/07/24 Fixed minor bugs, and exception handling
// Rev. 2 - 16/07/24 Filled in function calls for each submenu
// Rev. 1 - 03/07/24 Original by D.O.J.J Software Development

//*******************************************************//

#include <iostream>
#include <string>
#include <limits>
#include "UI.h"
using namespace std;

//*******************************************************//

// function headers (so that mainMenuLoop can actualy run the functions)
int displayMainMenu();
void productSubMenu();
void changeItemSubMenu();
void changeReqSubMenu();
void reportSubMenu();

void activateUI()
{
    int selection;

    do{
        selection = displayMainMenu();
        switch (selection){
            case 1:
                productSubMenu();
                break;
            case 2: 
                changeItemSubMenu();
                break;
            case 3:
                changeReqSubMenu();
                break;
            case 4:
                reportSubMenu();
                break;
            case 0:
                cout << "Thank you for using the Issue Tracking System." << endl;
                break;
            default:
                cout << "Please select an appropriate option from the menu." << endl;
                break;
        }
    } while (selection != 0);
}

//*******************************************************//

int displayMainMenu()
{
    int selection;
    string currentInput;

    cout << endl;
    cout << "+++++++ Main Menu +++++++" << endl;
    cout << "Select an Option Below (0 to 4):" << endl;
    cout << "1) Products" << endl;
    cout << "2) Change Items" << endl;
    cout << "3) Change Requests" << endl;
    cout << "4) Reports" << endl; 
    cout << "0) Exit the Program" << endl;

    cin >> currentInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
    if (currentInput == "1") 
    {
        selection = 1;
    }
    else if (currentInput == "2") 
    {
        selection = 2;
    }
    else if (currentInput == "3") 
    {
        selection = 3;
    }
    else if (currentInput == "4") 
    {
        selection = 4;
    }
    else if (currentInput == "0") 
    {
        selection = 0;
    }
    else 
    {
        selection = -1;
    }
    return selection;
}

// Extra function to display the main menu, keeping the switch statement uncluttered

//*******************************************************//

void productSubMenu()
{
    bool selectionStatus = 0;
    string currentSelection = "";
    int selection = -1;

    while (selectionStatus == 0)
    {
        cout << "+++++++ Products +++++++" << endl;
        cout << "Select an Option Below (0 to 2):" << endl;
        cout << "1) Add a Product" << endl;
        cout << "2) Add a Product Release" << endl;
        cout << "0) Return to the Main Menu" << endl;

        cin >> currentSelection;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (currentSelection == "1") 
        {
            selection = 1;
        }
        else if (currentSelection == "2")
        {
            selection = 2;
        }
        else if (currentSelection == "0")
        {
            selection = 0;
        }
        else
        {
            selection = -1;
        }

        switch (selection){
            case 1:
                addProduct();
                selectionStatus = 1;
                break;
            case 2:
                addProductRelease();
                selectionStatus = 1;
                break;
            case 0:
                //back to main menu as chosen
                selectionStatus = 1;
                break;
            default:
                cout << "Please select an appropriate option from the menu." << endl;
                break;
        }
    }
}

// Extra function to display and allow the user to select the product functionality

//*******************************************************//

void changeItemSubMenu()
{
    bool selectionStatus = 0;
    string currentSelection = "";
    int selection = -1;

    while (selectionStatus == 0)
    {
        cout << "+++++++ Change Items +++++++" << endl;
        cout << "Select an Option Below (0 to 3):" << endl;
        cout << "1) Add a Change Item" << endl;
        cout << "2) Query a Change Item" << endl;
        cout << "3) Update a Change Item" << endl;
        cout << "0) Return to the Main Menu" << endl;

        cin >> currentSelection;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (currentSelection == "1") 
        {
            selection = 1;
        }
        else if (currentSelection == "2")
        {
            selection = 2;
        }
        else if (currentSelection == "3")
        {
            selection = 3;
        }
        else if (currentSelection == "0")
        {
            selection = 0;
        }
        else
        {
            selection = -1;
        }

        switch (selection){
            case 1:
                addChangeItem();
                selectionStatus = 1;
                break;
            case 2: 
                queryChangeItems();
                selectionStatus = 1;
                break;
            case 3:
                modifyChangeItem();
                selectionStatus = 1;
                break;
            case 0:
                //return to main menu
                selectionStatus = 1;
                break;
            default:
                cout << "Please select an appropriate option from the menu." << endl;
                break;
        }
    }
}

// Extra function to display and allow the user to select the change item functionality

//*******************************************************//

void changeReqSubMenu()
{
    bool selectionStatus = 0;
    string currentSelection = "";
    int selection = -1;

    while (selectionStatus == 0)
    {

        cout << "+++++++ Change Requests +++++++" << endl;
        cout << "Select an Option Below (0 to 1):" << endl;
        cout << "1) Add a Request" << endl;
        cout << "0) Return to the Main Menu" << endl;

        cin >> currentSelection;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (currentSelection == "1") 
        {
            selection = 1;
        }
        else if (currentSelection == "0")
        {
            selection = 0;
        }
        else
        {
            selection = -1;
        }

        switch (selection){
            case 1:
                addChangeReq();
                selectionStatus = 1;
                break;
            case 0:
                //back to main menu
                selectionStatus = 1;
                break;
            default:
                cout << "Please select an appropriate option from the menu." << endl;
                break;
        }
    }
}

// Extra function to allow the user to display and select the change request functionality

//*******************************************************//

void reportSubMenu()
{
    bool selectionStatus = 0;
    string currentSelection = "";
    int selection = -1;

    while (selectionStatus == 0)
    {

        cout << "+++++++ Reports +++++++" << endl;
        cout << "Select an Option Below (0 to 2):" << endl;
        cout << "1) List Change Items that are not implemented for a Product" << endl;
        cout << "2) List customers/staff to be notified for an implemented change" << endl;
        cout << "0) Return to the Main Menu" << endl;

        cin >> currentSelection;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (currentSelection == "1") 
        {
            selection = 1;
        }
        else if (currentSelection == "2")
        {
            selection = 2;
        }
        else if (currentSelection == "0")
        {
            selection = 0;
        }
        else
        {
            selection = -1;
        }

        switch (selection)
        {
            case 1:
                listChangeItemsReport();
                selectionStatus = 1;
                break;
            case 2:
                listCustomersStaffReport();
                selectionStatus = 1;
                break;
            case 0:
                //back to main menu
                selectionStatus = 1;
                break;
            default:
                cout << "Please select an appropriate option from the menu." << endl;
                break;
        }
    }
}

// Extra function to display and allow the user to select the report functionality