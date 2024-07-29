// UI.cpp
// Rev. 2 - 16/07/24 Filled in function calls for each submenu
// Rev. 1 - 03/07/24 Original by D.O.J.J Software Development

//*******************************************************//

#include <iostream>
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
                break;
            default:
                cout << "Bad input detected, please try again" << endl;
                break;
        }
    } while (selection != 0);
}

//*******************************************************//

int displayMainMenu()
{
    cout << endl;
    cout << "+++++++ Main Menu +++++++" << endl;
    cout << "1) Products" << endl;
    cout << "2) Change Items" << endl;
    cout << "3) Change Requests" << endl;
    cout << "4) Reports" << endl; 
    cout << "0) Exit the Program" << endl;

    int selection;
    cin >> selection;
    cout << endl;
    return selection;
}

// Extra function to display the main menu, keeping the switch statement uncluttered

//*******************************************************//

void productSubMenu()
{
    cout << "+++++++ Products +++++++" << endl;
    cout << "1) Add a Product" << endl;
    cout << "2) Add a Prodcut Release" << endl;
    cout << "0) Return to the Main Menu" << endl;

    int selection;
    cin >> selection;
    switch (selection){
        case 1:
            addProduct();
            break;
        case 2:
            addProductRelease();
            break;
        case 0:
            //back to main menu as chosen
            break;
        default:
            cout << "Bad input detected, returning to main menu" << endl;
            break;
    }
}

// Extra function to display and allow the user to select the product functionality

//*******************************************************//

void changeItemSubMenu()
{
    cout << "+++++++ Change Items +++++++" << endl;
    cout << "1) Add a Change Item" << endl;
    cout << "2) Query a Change Item" << endl;
    cout << "3) Update a Change Item" << endl;
    cout << "0) Return to Main Menu" << endl;

    int selection;
    cin >> selection;
    switch (selection){
        case 1:
            addChangeItem();
            break;
        case 2: 
            queryChangeItems();
            break;
        case 3:
            modifyChangeItem();
            break;
        case 0:
            //return to main menu
            break;
        default:
            cout << "Bad input detected, returning to main menu" << endl;
            break;
    }
}

// Extra function to display and allow the user to select the change item functionality

//*******************************************************//

void changeReqSubMenu()
{
    cout << "+++++++ Change Reqeuests +++++++" << endl;
    cout << "1) Add a Request" << endl;
    cout << "0) Return to Main Menu" << endl;

    int selection;
    cin >> selection;
    switch (selection){
        case 1:
            addChangeReq();
            break;
        case 0:
            //back to main menu
            break;
        default:
            cout << "Bad input detected, returning to main menu" << endl;
            break;
    }
}

// Extra function to allow the user to display and select the change request functionality

//*******************************************************//

void reportSubMenu()
{
    cout << "+++++++ Reports +++++++" << endl;
    cout << "1) List Change Items that are not implemented for a Product";
    cout << "2) List customers/staff to be notified for an implemented change" << endl;
    cout << "0) Return to the Main Menu" << endl;

    int selection;
    cin >> selection;
    switch (selection)
    {
        case 1:
            listChangeItemsReport();
            break;
        case 2:
            listCustomersStaffReport();
            break;
        case 0:
            //back to main menu
            break;
        default:
            cout << "Bad input detected, returning to main menu" << endl;
            break;
    }
}

// Extra function to display and allow the user to select the report functionality