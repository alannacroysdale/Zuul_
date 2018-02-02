#include <iostream>
#include <vector>
#include "Item.h"
#include "Room.h"

using namespace std;
#ifndef PLAYER_H
#define PLAYER_H

class Player {
    //Description:  Defines a player which has a description and items 
    // class*    : Pointer to item. Only one item in a room
    // char      : description

    public:
        // Public variables
        Player();

        // Functions to manipulate items

        // Removes an item from the player's vector of items
        int removeItem(Item*);
        
        // Adds an item to the player's vector of items
        int addItem(Item*);
       

        // Functions to print stuff
        
        // Prints all the items in the player's vector of items
        int printInventory();
        
        // Prints one item from the player's vector of items
        int printItem(int);
        

        // Functions for checking inventory
        
        // Returns the player's vector of items
        vector<Item*> getPlayerItems();
        
        // Returns one item from the player's vector of items
        Item* getSelectedItem(int);
        
        // Checks if player's inventory contains a certain item
        bool hasItem(Item*);
        
    private:
        // Member variables
        
        // Player's inventory, a vector of item pointers
        vector<Item*> Items;
};
#endif
