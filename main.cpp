// main.cpp
// Rev. 3 - 31/07/24 commented out startControl as it does not actaully do anything
// Rev. 2 - 17/07/24 Renamed main menu loop to activateUI
// Rev. 1 - 03/07/24 Original by D.O.J.J Software Development

//*******************************************************//

#include <iostream>
#include "ScenarioControl.h"
#include "UI.h"
using namespace std;

//*******************************************************//

int main()
{
    //strtControl();
    activateUI();
    closeControl();
    return 0;
}

//*******************************************************//

// Coding Conventions:
// Top of file include file name and revision history from newest to oldest.
// File naming format: FileName.cpp/FileName.h
// Sepearte each section with //***...***// where the total length is 60.
// Character limit per line is 100 (excluding comments though try to keep it for comments too).
// After the name and revision section, sepereate and add an explanation of the module.
// Seperate again for each function. 
// In header file under the function header/class explain the purpose and what it does.
// Naming: ClassExample, functionExample, variableExample, MACRO_EXAMPLE/CONSTANT_EXAMPLE. 
// All indentations are 4 spaces, '{' goes on the next line, for else if and else put them on a seperate line (so below '}').
// Space things so '=' is surrounded by spaces and thers a space after each comma.