// UI.cpp
// Rev. 1 - 03/07/24 Original by D.O.J.J Software Development

//*******************************************************//

#include <iostream>
#include "UI.h"
using namespace std;

//*******************************************************//

//function headers (so that u mainMenuLoop can actualy run the functions)
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
                //insert message about bad input
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
            //add product function from scenario control (nothing for now as the function is not actaully made yet)
            break;
        case 2:
            //add product release function
            break;
        case 0:
            //back to main menu
            break;
        default:
            //have message informing them of bad input
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
            //add change item function
            break;
        case 2: 
            //query a change item function
            break;
        case 3:
            //update a change item function
            break;
        case 0:
            //return to main menu
            break;
        default:
            //inform user of bad input
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
            //add a request function
            break;
        case 0:
            //back to main menu
            break;
        default:
            //inform user of bad input
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
            // unimplemented change items func
            break;
        case 2:
            // customer/staff notified function
            break;
        case 0:
            //back to main menu
            break;
        default:
            //inform user of bad input
            break;
    }
}

// Extra function to display and allow the user to select the report functionality