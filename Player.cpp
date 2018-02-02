#include <iostream>
#include "Player.h"
#include <cstring>

using namespace std;

Player::Player() {
}

int Player::addItem(Item* newItem) {
    // Add a new item to player's vector of items
    Items.push_back(newItem);
    return 0;
}

vector<Item*> Player::getPlayerItems() {
    // Use: when the player's entire vector of items is needed
    // Returns the player's vector of items
    return Items;
}

int Player::printInventory(){ 
    // Prints all the items in the player's vector of items    
    cout << "Inventory:" << endl;
    // Checks if there are items in the inventory
    if (Items.size() > 0){
        // Go through Items vector
        for( int i = 0; i < Items.size(); i++){
            cout << (i+1) << ". "
                // Print the description of the item 
                 << Items[i]->getDescription() << endl;
        }
    }
    else {
        cout << "No items\n";
    }
    return 0;
}

int Player::printItem(int n){
    // Prints an item using the number of the element in the vector
    cout << Items[n]->getDescription();
    return 0;
}

int Player::removeItem(Item* selected){
    // Removes an Item from the player's vector using
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

Item* Player::getSelectedItem(int n){
    // Returns an item pointer based on its position 
    // in the player's Items vector
    Item* selectedItem = Items[n];
    return selectedItem;
}

bool Player::hasItem(Item* item){
    // Checks if the player has a certain item
    bool hasItem = false;
    for (int i = 0; i < Items.size(); i++){
        if (Items[i] == item){
            hasItem = true;
        }
    }
    return hasItem;
}
