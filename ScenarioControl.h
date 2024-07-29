// ScenarioControl.h
// Rev. 2 - 16/07/24 Added implementation of the functions to ScenarioControl.cpp
// Rev. 1 - 03/07/24 Original by D.O.J.J Software Development

//*******************************************************//
// This module is designed to manage the collection of information for each function parameter.
// The ui.h file will lead the user through a menu, which they will then run one of these functions
// which will deal with collecting the necessary input information required to run the intended 
// function in any of the other modules.
//*******************************************************// 

#ifndef SCENARIO_CONTROL_H
#define SCENARIO_CONTROL_H
#include <string.h>
#include "ChangeItem.h"
#include "ChangeRequest.h"
#include "Customer.h"
#include "Product.h"
#include "ProductRelease.h"

//*******************************************************//

void strtControl();
// Initialize all other modules that must be initialzied such as running the start up funciton 
// for each module.

//*******************************************************//

void closeControl();
// Deals with the closing the program and all other modules.

//*******************************************************//

void addChangeReq();
// This function will be called by the UI to do all the gathering for the information needed to run
// another function in the ChangeRequest.h module being createChangeRequest().

//*******************************************************//

void addProduct();
// This function will be called by the UI to gather all the information needed to run the
// createProduct() function found in the Product.h module

//*******************************************************//

void addProductRelease();
// This function will be called by the UI to gather all the information needed to run the 
// createProductRelease() function found in the ProductRelease.h module

//*******************************************************//

void addChangeItem();
// This function will be called by the UI to gather all the information needed to run the 
// createChangeItem() function found in the ChangeItem.h module

//*******************************************************//

void modifyChangeItem();
// This function will be called by the UI to gather all the information needed to run the 
// updateChangeItem() function found in the ChangeItem.h module

//*******************************************************//

void queryChangeItems();
// This function will be called by the UI to gather all the information needed to run the 
// searchChangeItem() function found in the ChangeItem.h module

//*******************************************************//

void listChangeItemsReport();
// This function will be called by the UI and will run selectProduct() in the Product.h module 
// which will then go thorugh the change item file and print out each change for a product
// that has not been implemented

//*******************************************************//

void listCustomersStaffReport();
// This function will be called bt the UI will gatehr all the information needed to locate and 
// display all customers associated with a specific ChangeItem.

#endif