// Product.h
// Rev. 2 - 17/07/24 Updated string objects to be char arrays, moved selectProduct functionality to ScenarioControl.h
// Rev. 1 - 03/07/24 Original by D.O.J.J Software Development

//*******************************************************//
// This module is designed to perform any operations for anything related to Products.
// It hides the implementation of how it does any of the operations to the other files
// and also stores any data relating to Products with the ability to perform disk operations
// to the respective data file storing Products. Encapsulated in the Product class is just the
// name of the product and any operations that can alter the data are also included inside the class
// while all operations on products are elsewhere in the file. All of this is to improve cohesion in the program.
//*******************************************************//

#ifndef PRODUCT_H
#define PRODUCT_H

#include <cstring>
#include <fstream>
#include "BinaryFileIOHelper.h"

using namespace std;

//*******************************************************//

class Product 
{
public:
    // Constructor
    Product();

    // Parameterized Constructor
    Product(const char *name);

    // Destructor
    ~Product();

    // Getter
    void getName(char *str);

    // Setter
    void setName(const char *theName);

private:
    char productName[11];
};
// This class models a Product in the customer company
// The class contains getters and setters in order to set the name of a product when creating one
// and also has a getter for comparisons, while also having a << operator overloaded
// the default constructor should set the name to an empty string

//*******************************************************//

class ProductFile : public BinaryFileIOHelper<Product>
{

public:
    ProductFile();
    Product findProduct(char *searchName);
    bool openProductFile();
    bool closeProductFile();
    bool seekToBeginningOfFile();
    bool getNextProduct(Product &productObj);
    bool createProduct(Product &aProduct);

private:
    bool writeProduct(Product productObj);
};
// This class deals with any reading or writing from disk for all Product Class objects
// You can find a specific product by using its search key which is a string
// the writeProduct function writes the product to disk and appends to the end of the file
// openProductFile and closeProductFile open and close the respective file storing Products
// getNextProduct gets the next product from disk

//*******************************************************//

ProductFile strtProduct();
// Initalizes any required classes, files, operations to perform any scenarios regarding products

//*******************************************************//

int createProduct(Product productToAdd);
// createProduct is a function which takes a product object that is passed to it as a function argument
// The function returns 0 for a successful operation, and -1 if there is an error
// It is expected to have all attributes of a product filled which is the name
// The function puts the product on disk and then returns, if the process is successful
// The product should be valid and the Product File should have room for a new Product

//*******************************************************//

int closeProduct(ProductFile &itemFile);
// closeProduct frees up all memory, closes any open files, and prepares the module for shutdown
// the function returns 0 if successful and -1 for a failure of any sort

//*******************************************************//

#endif