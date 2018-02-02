#include <iostream>
#include <vector>

using namespace std;
#ifndef ITEM_H
#define ITEM_H

// Define item 
class Item {
    // Description: Defines an item  
    // Objects :
    //   char* description 
    public:
        // Public variables
        // Item's object constructor, includes description of item
        Item(char const*);
        // Returns the description of the item
        char* getDescription();
        // Prints the description of the item
	    int printItem();
    private:
        // Member variables
        char* description;
} ; 

#endif
