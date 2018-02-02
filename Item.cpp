#include <iostream>
#include "Item.h"
#include <cstring>

using namespace std;

// Item constructor
Item::Item(char const* newdescription) {
    // Defines description
    description = new char[strlen(newdescription)];
    strcpy(description, newdescription);
}

char* Item::getDescription() {
    return description;
}

int Item::printItem() {
    // Prints the description of this Item object
    cout << this->getDescription() << endl;
}

