#include <iostream>
#include "Room.h"
#include <cstring>

using namespace std;

Room::Room(char const* newid, char const* newdescription) {
    // sets room id/name
    id = new char[strlen(newid)];
    strcpy(id, newid);

    // sets room description
    description = new char[strlen(newdescription)];
    strcpy(description, newdescription);
    
    // Create exits, initially pointing to this room
    exit['N']=this;
    exit['E']=this;
    exit['W']=this;
    exit['S']=this;
}

int Room::setDescription(char const* description) {
    // set room description
    return 0;
}

char* Room::getDescription() {
    // Returns room description
    return description;
}

char* Room::getID() {
    // Returns room id/name
    return id;
}
char* Room::printExits() {
    // Prints all exits from this room
    // If the exit is defined as this room, that means that it
    // was never defined as a different room, so it should not be
    // printed
    if (this != exit['N']) {
        cout << "To the north is " << exit['N']->getID() << ".\n";
    }
    if (this != exit['E']) {
        cout << "To the east is " << exit['E']->getID() << ".\n";
    }
    if (this != exit['W']) {
        cout << "To the west is " << exit['W']->getID() << ".\n";
    }
    if (this != exit['S']) {
        cout << "To the south is " << exit['S']->getID() << ".\n";
    }
}

int Room::createExit(Room* room, char direction) {
    // Defines an exit as a room pointer
    exit[direction] = room;
    return 0;
}

Item* Room::getSelectedItem(int n){
    // Returns an item pointer based on its position
    // in the room's Items vector
    Item* selectedItem = Items[n];
    return selectedItem;
}

vector<Item*> Room::getItems() {
    // Use: when the room's entire vector of items is needed
    // Returns the room's vector of items
    return Items;
}
int Room::addItem(Item* newItem) {
    // Adds a new item pointer to the room's vector of items
    Items.push_back(newItem);
    return 0;
}

int Room::removeItem(Item* selected) {
    // Removes an Item from the room's vector using
    // it's position in the vector
    // 'worked' is to show whether there is an item 
    // in the selected position in the vector
    bool worked = false;
    // Goes through vector of items until the selected item is found
    for( int i = 0; i < Items.size(); i++){
       if (Items[i] == selected){
           // Removes selected item from the vector
           Items.erase(Items.begin()+i);
           worked = true;
       }
    }
    if (worked == true){
    return 1;
    }
    // An item was not found in the selected position in the vector
    else{
    return 0;
    }    
}

int Room::printRoom(){
    // Prints the room's description
    cout << this->getDescription() << endl;
    return 0;
}

int Room::printItems(){
    // Prints all the items in the room's vector of items    
    // Checks if there are items in the room
    if (Items.size() > 0){
        cout << "On the ground you see... \n";
        // Go through Items vector
        for( int i = 0; i < Items.size(); i++){
            cout << (i+1) << ". "
                // Print the description of the item 
                 << Items[i]->getDescription() << endl;
        }
    }
    else {
        cout << "There's nothing here.\n";
    }
    return 0;
}

Room* Room::getExit(char direction){
    // Returns room pointer based on direction of exit
    return exit[direction];
}

bool Room::hasItem(Item* item){
    // Checks if the room contains a certain item
    bool hasItem = false;
    for (int i = 0; i < Items.size(); i++){
        if (Items[i] == item){
            hasItem = true;
        }
    }
    return hasItem;
}
