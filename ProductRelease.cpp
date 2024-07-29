// ProductRelease.cpp
// Rev. 1 - 17/07/24 Original by D.O.J.J Software Development

//*******************************************************//
// This file is the implementation of the operations as outlined in
// ProductRelease.h. Broader implementation detailed associated with
// Product Releases can be found there. This file implements fixed-length binary
// file operations for Product Releases using a linear search method, and appends
// product releases on addition. All data related to product releases are
// encapsulated in the ProductRelease class alongside constructors, destructors,
// setters and getters for operations on ProductRelease data, and there is
// a small tradeoff as using setters reduces the privacy of the class data, in
// turn for an easier implementation
//*******************************************************//

#include "ProductRelease.h"
#include "BinaryFileIOHelper.h"
#include <iostream>
using namespace std;

//*******************************************************//

// Default Constructor, initalizes all char arrays to empty strings
ProductRelease::ProductRelease()
{
    setProductName("\0");
    setProductID("\0");
    setReleaseDate("\0");
}

//*******************************************************//

// Parameterized Constructor, initalizes the char arrays to the function arguments
ProductRelease::ProductRelease(char *name, char *id, char *date)
{
    setProductName(name);
    setProductID(id);
    setReleaseDate(date);
}

//*******************************************************//

// Destructor
ProductRelease::~ProductRelease()
{
}

//*******************************************************//

// Getter for the Product Name, uses strncpy to set a function argument char array
// to the product name
void ProductRelease::getProductName(char *str)
{
    // Copy the char array from the appropriate data member to the function argument char array
    unsigned int length = sizeof(productName);
    strncpy(str, productName, length);
}

//*******************************************************//

// Getter for the ReleaseID, uses strncpy to set a function argument char array
// to the releaseID data value
void ProductRelease::getProductID(char *str)
{
    // Copy the char array from the appropriate data member to the function argument char array
    unsigned int length = sizeof(productID);
    strncpy(str, productID, length);
}

//*******************************************************//

// Getter for the Release Date, uses strncpy to set a function argument char array
// to the releaseDate data value
void ProductRelease::getReleaseDate(char *str)
{
    // Copy the char array from the appropriate data member to the function argument char array
    unsigned int length = sizeof(releaseDate);
    strncpy(str, releaseDate, length);
}

//*******************************************************//

// Setter for the Product Name, uses strncpy to set the product name data value to
// the char array of the function argument
void ProductRelease::setProductName(const char *theProductName)
{
    // Copy the char array from the function argument to appropriate data member
    strncpy(productName, theProductName, sizeof(productName));
    productName[sizeof(productName) - 1] = '\0';
}

//*******************************************************//

// Setter for the Release ID, uses strncpy to set the release ID data value to
// the char array of the function argument
void ProductRelease::setProductID(const char *theProductID)
{
    // Copy the char array from the function argument to appropriate data member
    strncpy(productID, theProductID, sizeof(productID));
    productID[sizeof(productID) - 1] = '\0';
}

//*******************************************************//

// Setter for the Release Date, uses strncpy to set the releaseDate data value to
// the char array of the function argument
void ProductRelease::setReleaseDate(const char *theReleaseDate)
{
    // Copy the char array from the function argument to appropriate data member
    strncpy(releaseDate, theReleaseDate, sizeof(releaseDate));
    releaseDate[sizeof(releaseDate) - 1] = '\0';
}

//*******************************************************//

// Creates and opens a product release file object
ProductReleaseFile::ProductReleaseFile()
{
    openProductReleaseFile();
}

//*******************************************************//

// Searches for a product release in a file with a search key and returns that product release if found
// Implemented using a while loop to look through the associated data file until a product release is found
// or the end of the file is reached
ProductRelease ProductReleaseFile::findProductRelease(char *releaseIDKey)
{
    // emptyProduct to be returned if no product is found
    ProductRelease emptyRelease = ProductRelease();

    // If we cannot find the start of the file throw an error
    if (!seekToBeginningOfFile())
    {
    cerr << "Unable to find product release (cant seek to beginning)" << endl;
    return emptyRelease;
    }

    // Initalize local variables for the search
    ProductRelease buf;
    streampos pos;
    char compareString[9] = "";

    // While loop for the entire file until we reach the end of the file
    // or the product release we are searching for is found
    // Incremented per item in the binary record file
    while (!file.eof())
    {
        // Get the next Product Release from the file and compare its releaseID
        // If the ReleaseIDs match return the Product Release we found
        getNextProductRelease(buf);
        buf.getProductID(compareString);
        if (strcmp(compareString,releaseIDKey) == 0)
        {
            return buf;
        }
    }

    // If no match is found return an empty Product Release
    return emptyRelease;
}

//*******************************************************//

// Resets the product release we are looking at in the file to the product release at the front 
// using the seekg function, Returns a boolean for success or failure
bool ProductReleaseFile::seekToBeginningOfFile()
{
    // If there is no file open throw an error
    if (!file.is_open())
    {
    cerr << "File is not open" << endl;
    return false;
    }

    // Otherwise seek back to the start of the file and return
    file.seekg(0);
    return file.good(); // Returns true if the seek was successful
}

//*******************************************************//

// Reads the next product release from the data file, uses the read function from BinaryFileIOHelper.h
// Returns a boolean for success or failure
bool ProductReleaseFile::getNextProductRelease(ProductRelease &productReleaseObj)
{
    return Read(productReleaseObj);
}

//*******************************************************//

// Writes a product release to the data file, uses the write function from BinaryFileIOHelper.h
// Returns a boolean for success or failure
bool ProductReleaseFile::createProductRelease(ProductRelease &aProductRelease)
{
    return Write(aProductRelease);
}

//*******************************************************//

// Opens the file storing all of the binary fixed-length records holding Product Releases
// Returns a boolean for success or failure
bool ProductReleaseFile::openProductReleaseFile()
{
    // If the file failed to open report an error, otherwise return true
    file.open("ProductRelease.data", ios::in | ios::out | ios::binary | ios::app);
    if (!file.is_open())
    {
    cerr << "Error opening file" << endl;
    return false;
    }
    return true;
}

//*******************************************************//

// Closes the file storing all of the binary fixed-length records holding Product Releases
// Returns a boolean for success or failure
bool ProductReleaseFile::closeProductReleaseFile()
{
    // If no file is open throw an exception
    if (!file.is_open())
    {
        cerr << "File not open" << endl;
        return false;
    }

    // Otherwise close the file and return true
    file.close();
    return true;
}

//*******************************************************//

// Writes a product release to the data file, uses the write function from BinaryFileIOHelper.h
// Returns a boolean for success or failure
bool ProductReleaseFile::writeProductRelease(ProductRelease productReleaseObj) 
{
    return Write(productReleaseObj);
}

//*******************************************************//

// Startup function which opens the fixed-length binary file storing Product Releases
ProductReleaseFile strtRelease()
{
    return ProductReleaseFile();
}

//*******************************************************//

// Function which inserts a product release into the fixed-length binary file record
// Uses both ProductRelease and ProductFile class operations, and checks for exceptions
// about duplicates or a failed insertion
int createProductRelease(ProductRelease productReleaseToAdd)
{
    // Adds the Product to the end of the fixed-length binary record file

    // Initalize local char arrays to check exceptions, and initalize return variable
    char searchkey[9] = "";
    char searchresult[9] = "";
    bool insertionresult = 1;

    // Check to see if the product we are adding already exists
    // by searching for it with a ProductRelease object
    // Initalize some local variables to assist with this search
    productReleaseToAdd.getProductName(searchkey);
    ProductRelease searchProduct = ProductRelease();
    ProductReleaseFile theFile = ProductReleaseFile();
    searchProduct = theFile.findProductRelease(searchkey);
    searchProduct.getProductName(searchresult);

    // If the product is a duplicate return a failed insertion
    if (strcmp(searchresult, searchkey) == 0) {
        return 0;
    }

    // Insert the product and return wether the insertion was successful or not
    insertionresult = createProductRelease(productReleaseToAdd);
    return insertionresult;
}

//*******************************************************//

// Shutdown function, which closes the fixed-length binary record file
int closeRelease(ProductReleaseFile &itemFile)
{
    return itemFile.closeProductReleaseFile();
}

//*******************************************************//