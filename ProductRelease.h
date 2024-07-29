// ProductRelease.h
// Rev. 2 - 17/07/24 Updated string objects to be char arrays, moved selectProductRelease functionality to ScenarioControl.h
// Rev. 1 - 03/07/24 Original by D.O.J.J Software Development

//*******************************************************//
// This module is designed to perform any operations for anything related to Product Releases
// It hides the implementation of any operations to other files and stores
// any data related to Product Releases in order to perform disk operations on the
// corresponding file storing Product Releases. Encapsulated in the ProductRelease class
// is the product's name, the Release ID and the date of release, as well as any operations
// that can be performed on the data, as well as a overloaded << operator.
// Other operations on general Product Releases are elsewhere in the file all with the goal
// of increasing cohesion in the program
//*******************************************************//

#ifndef PRODUCTRELEASE_H
#define PRODUCTRELEASE_H

#include <cstring>
#include <fstream>
#include "BinaryFileIOHelper.h"

using namespace std;

//*******************************************************//

class ProductRelease 
{
public:
    // Constructor
    ProductRelease();

    // Parameterized Constructor
    ProductRelease(char *name, char *id, char *date);

    // Destructor
    ~ProductRelease();

    // Getters
    void getProductName(char *str);
    void getProductID(char *str);
    void getReleaseDate(char *str);

    // Setters
    void setProductName(const char *theProductName);
    void setProductID(const char *theProductID);
    void setReleaseDate(const char *theReleaseDate);

private:
    char productName[11];
    char productID[9];
    char releaseDate[11];
};
// This class models a Product Release in the customer company
// This class also contains getters and setters for the attributes
// in order to set attributes or compare attributes in operations
// There is also an overloaded << operator
// The default constructor should set all attributes to a blank string

//*******************************************************//

class ProductReleaseFile : public BinaryFileIOHelper<ProductRelease>
{

public:
    ProductReleaseFile();
    ProductRelease findProductRelease(char *releaseIDKey);
    bool openProductReleaseFile();
    bool closeProductReleaseFile();
    bool createProductRelease(ProductRelease &aProductRelease);
    bool seekToBeginningOfFile();
    bool getNextProductRelease(ProductRelease &productReleaseObj);

private:
    bool writeProductRelease(ProductRelease productReleaseObj);
};
// This class deals with any reading or writing to disk for Product Releases
// You can search for a specific ProductRelease on disk by searching with a releaseID
// writeProductRelease writes a product release to disk appending it to the end of the file
// the open and close ProductReleaseFile functions open and close the file we are reading or writing to
// Meanwhile getNextProductRelease gets the next product release from disk

//*******************************************************//

ProductReleaseFile strtRelease();
// Initalizes any required classes, files, operations to perform any scenarios regarding product releases

//*******************************************************//

int createProductRelease(ProductRelease productReleaseToAdd);
// createProductRelease is a function which takes a ProductRelease object that is passed to it
// as a function argument which is the specific ProductRelease to add to the file
// it returns 0 if successful and -1 if there is an error
// It is expected that all attributes of a Product Release including the product name, ID and date are filled
// The function puts the Product Release on disk then returns whether successful or not
// The product release should be valid and the ProductRelease File should have room for a new Product Release

//*******************************************************//

int closeRelease(ProductReleaseFile &itemFile);
// closeRelease frees up all memory, closes any open files, and prepares the module to shutdown
// the function returns 0 if successful and -1 if any errors occur

//*******************************************************//

#endif