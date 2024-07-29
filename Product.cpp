// Product.cpp
// Rev. 1 - 17/07/24 Original by D.O.J.J Software Development

//*******************************************************//
// This module implements the operations associated with Products by
// including fixed length binary file operations included in the ProductFile class, and
// these file operations include reading, writing, and searching.
// The binary file search uses a linear search method which is one tradeoff
// for its simple implementation. Secondly all data related to products are
// encapsulated in a Product class with different constructors, setters and getters
// for operations on such data where some data privacy is traded off for easier implementation
// i.e. setters allow outside functions to directly change Product data, but it is easier to
// change or set data to needed values.
//*******************************************************//

#include "Product.h"
#include "BinaryFileIOHelper.h"
#include <iostream>
using namespace std;

//*******************************************************//

// Default Constructor, initalizes all char arrays to empty strings
Product::Product() 
{
    setName("\0");
}

//*******************************************************//

// Parameterized Constructor, initalizes the char arrays to the function argument
Product::Product(const char *name) 
{
    setName(name);
}

//*******************************************************//

// Destructor
Product::~Product()
{
}

//*******************************************************//

// Getter for the Product Name, uses strncpy to set a function argument char array
// to the product name
void Product::getName(char *str) 
{  
    // Copy the char array from the appropriate data member to the function argument char array
    unsigned int length = sizeof(productName);
    strncpy(str, productName, length);
}

//*******************************************************//

// Setter for the Product Name, uses strncpy to set the name data value to
// the char array of the function argument
void Product::setName(const char *theName)
{
    // Copy the char array from the function argument to appropriate data member
    strncpy(productName, theName, sizeof(productName));
    productName[sizeof(productName) - 1] = '\0';
}

//*******************************************************//

// Creates and opens a product file object
ProductFile::ProductFile()
{
  openProductFile();
}

//*******************************************************//

// Searches for a product in a file with a search key and returns that product if found
// Implemented using a while loop to look through the associated data file until a product is found
// or the end of the file is reached
Product ProductFile::findProduct(char *searchName)
{
    // emptyProduct to be returned if no product is found
    Product emptyProduct = Product();

    // If we cannot find the start of the file throw an error
    if (!seekToBeginningOfFile())
    {
        cerr << "Unable to find product (cant seek to beginning)" << endl;
        return emptyProduct;
    }

    // Initalize local variables for the search
    Product buf;
    streampos pos;
    char compareString[11] = "";

    // While loop for the entire file until we reach the end of the file,
    // or the product we are searching for is found
    // Incremented per item in the binary record file
    while (!file.eof())
    {
        // Get the next Product from the file and compare its name
        // If the names match return the Product we found
        getNextProduct(buf);
        buf.getName(compareString);
        if (strcmp(compareString,searchName) == 0)
        {
            seekToBeginningOfFile();
            return buf;
        }
    }

    // If no match is found return an empty Product
    seekToBeginningOfFile();
    return emptyProduct;
}

//*******************************************************//

// Resets the product we are looking at in the file to the product at the front using the seekg function
// Returns a boolean for success or failure
bool ProductFile::seekToBeginningOfFile() 
{
    // If there is no file open throw an error
    if (!file.is_open())
    {
        cerr << "File is not open" << endl;
        return false;
    }

    // Otherwise seek back to the start of the file and return
    file.clear();
    file.seekg(0);
    
    return file.good(); // Returns true if the seek was successful
}

//*******************************************************//

// Reads the next product from the data file, uses the read function from BinaryFileIOHelper.h
// Returns a boolean for success or failure
bool ProductFile::getNextProduct(Product &productObj)
{
  return Read(productObj);
}

//*******************************************************//

// Writes a product to the data file, uses the write function from BinaryFileIOHelper.h
// Returns a boolean for success or failure
bool ProductFile::createProduct(Product &aProduct)
{
  return Write(aProduct);
}

//*******************************************************//

// Opens the file storing all of the binary fixed-length records holding Products
// Returns a boolean for success or failure
bool ProductFile::openProductFile() 
{
    // If the file failed to open report an error, otherwise return true
    file.open("Product.data", ios::in | ios::out | ios::binary | ios::app);
    if (!file.is_open())
    {
    cerr << "Error opening file" << endl;
    return false;
    }
    return true;
}

//*******************************************************//

// Closes the file storing all of the binary fixed-length records holding Products
// Returns a boolean for success or failure
bool ProductFile::closeProductFile()
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

// Writes the next product to the data file, uses the write function from BinaryFileIOHelper.h
// Returns a boolean for success or failure
bool ProductFile::writeProduct(Product productObj) 
{
  return Write(productObj);
}

//*******************************************************//

// Startup function which opens the fixed-length binary file storing Products
ProductFile strtProduct() 
{
    return ProductFile();
}

// Function which inserts a product into the fixed-length binary file record
// Uses both Product and ProductFile class operations, and checks for exceptions
// about duplicates or a failed insertion
int createProduct(Product productToAdd, ProductFile &theFile) {
    // Adds the Product to the end of the fixed-length binary record file

    // Initalize local char arrays to check exceptions, and initalize return variable
    char searchkey[11] = "";
    char searchresult[11] = "";
    int insertionresult = 1;

    // Check to see if the product we are adding already exists
    // by searching for it with a Product object
    // Using local variables to perform this search
    productToAdd.getName(searchkey);
    Product searchProduct = Product();
    searchProduct = theFile.findProduct(searchkey);
    searchProduct.getName(searchresult);

    // If the product is a duplicate return a failed insertion
    if (strcmp(searchresult, searchkey) == 0) {
        return 0;
    }

    // Insert the product and return wether the insertion was successful or not

    insertionresult = theFile.createProduct(productToAdd);
    return insertionresult;
}

//*******************************************************//

// Shutdown function, which closes the fixed-length binary record file
int closeProduct(ProductFile &itemFile)
{
    return itemFile.closeProductFile();
}

//*******************************************************//