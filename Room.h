#include <map>
#include <iostream>
#include <vector>
#include "Item.h"

using namespace std;
#ifndef ROOM_H
#define ROOM_H

class Room {
    // Description:  Defines a room which has a description, items and exits
    // char      :  description
    // map       :  exit

    public:
        // Public variables
        // Room constructor 
        // Name of Room, Description of Room
        Room(char const*, char const*); 

        // Function to get description
        char* getDescription();
        
        // Function to set description
        int setDescription(char const*);

        // Function to return Room ID
        char* getID();


        // Functions to manipulate items

        // Removes item from the room's vector of items
        int removeItem(Item*);

        // Adds an item to the room's vector of items
        int addItem(Item*);
        

        // Functions to get
        
        // Returns the vector of the items in the room
        vector<Item*> getItems();
        
        // Returns one item from the room's vector of items
        Item* getSelectedItem(int);

        // Returns the room defined as an exit
        Room* getExit(char);

        // Checks if the room has an item
        bool hasItem(Item*);


        // Functions to manipulate exits
        
        // Defines an exit as a room pointer
        int createExit( Room* , char );


        // Print stuff
        int printRoom();
        int printRooms();
        char* printExits();
    	int printItems();
        
    private:
        // Member variables
        // exit map 
            // key    = N, E, W, or S
            // Room*  = Room that exit leads to
        std::map<char, Room*>  exit;

        // Description 
        char* description;

        // Room Id
        char* id;

        // Items in the room, a vector of item pointers
        vector<Item*> Items;
};

#endif
