#include <iostream>
#include <string.h>
#include <vector>
#include "Room.h"
#include "Item.h"
#include "Player.h"


//Alanna Croysdale 2-1-18 Zuul
using namespace std;

// Print all room descriptions
void printRooms(vector<Room*>);

// function to create Rooms and Items, define Exits, 
// and put items in rooms
void createRooms(vector<Room*> &rooms, vector<Item*> &items);

// function for Player to pick up item
void pickUpItem(Room*, Player*, int);

// function for Player to drop item
void dropItem(Room*, Player*, int);

// function to switch rooms
void exitRoom(vector<Room*> rooms, Room* &currentRoom, char direction, bool worked);

int main()
{
    // Define a vector of Room pointers
    vector<Room*> rooms;
    
    // Define a vector of Item pointers
    vector<Item*> items;

    // Create Room objects and define their exits
    // Also creates Item objects and puts items in Room objects
    createRooms(rooms, items);
    
    // Create player objects
    Player* player = new Player();

    // Define the starting room
    // 0 is the desert island, the starting room
    Room* currentRoom = rooms[0];

    // Game continues until playing is false
    bool playing = true;

    // Used when exiting room. If exit is false, 
    // no exit was found in the requested direction 
    bool worked = false;

    // Used to figure out whether you still need
    // to check if player has won the game.
    // If won is true, there is no need to keep checking
    bool won =  false;

    // Player's input
    char input[2];

    // Used for room's exits, ex: 'N', 'E', 'W', 'S'
    char direction;

    // Used for the dropping and picking up selected 
    // item out of a vector in either
    // the player or the current room
    int selected;

    cout << "Press 'H' for help\nYou are in ";
    // Print the name of the current room
    cout << currentRoom->getID() << endl;
    cout << "You're not sure what the goal is, but danger lurks about. You'll have to kkeep moving until you have what you need to survive, then you'll figure out what to do next";
    
    // Start loop/game
    while (playing == true){
        // Print the description of the current Room:
        currentRoom->printRoom();
        // Print the exits defined in the current Room:
        currentRoom->printExits();
        cout << "\nWhat will you do?\n";

        // take player's input
        cin.get(input, 2);
        
        if ((input[0] == 'f') || (input[0] == 'F')){
            // Player 'finds' items
            // Print items in current room:
            currentRoom->printItems();
        }
        
        else if ((input[0] == 'i') || (input[0] == 'I')){
            // Player asks for 'inventory'
            // Print player's inventory
            player->printInventory();
        }
        
        else if ((input[0] == 'p') || (input[0] == 'P')){
            // Player asks to 'pick up' items
            // Check if there are items in the current room
            if (((currentRoom->getItems()).size()) > 0){
                // When items are displayed they are in a numbered list
                // The player is asked to pick a number from this list
                cout << "What would you like to pick up? ex: 1\n";
                cin >> selected;
                // Selected goes into a vector that starts with 0, but 
                // the items are displayed starting at 1, therefore, 1
                // must be subtracted from the variable. Now the value 
                // is the position of the selected item in the 
                // current room's vector of items
                selected -= 1;
                // Adds the item to the player's inventory and 
                // removes it from the room
                pickUpItem(currentRoom, player, selected);
            }
            // If there are no items in the current room
            else {
                cout << "There's nothing here!\n";
            }
        }
        
        else if ((input[0] == 'd') || (input[0] == 'D')){
            // Player asks to 'drop' items
            // Checks if the player has items in their inventory
            if (((player->getPlayerItems()).size()) > 0){
                cout << "What would you like to drop? ex: 1\n";
                cin >> selected;
                // Selected goes into a vector that starts with 0, but 
                // the items are displayed starting at 1, therefore, 1
                // must be subtracted from the variable. Now the value
                // is the position of the selected item in the 
                // player's vector of items
                selected -= 1;
                dropItem(currentRoom, player, selected);
            }
            // If the player doesn't have any items in their inventory
            else {
                cout << "Your inventory is empty!\n";
            }
        }

        else if ((input[0] == 'n') || (input[0] == 'N')){
            // Player asks to go to the room to the 'north'
            // Set requested direction to North
            direction = 'N';
            exitRoom(rooms, currentRoom, direction, worked);
        }
        
        else if ((input[0] == 'e') || (input[0] == 'E')){
            // Player asks to go to the room to the 'east'
            // Set requested direction to East
            direction = 'E';
            exitRoom(rooms, currentRoom, direction, worked);
        }
        
        else if ((input[0] == 'w') || (input[0] == 'W')){
            // Player asks to go to the room to the 'west'
            // Set requested direction to West
            direction = 'W';
            exitRoom(rooms, currentRoom, direction, worked);
        }
        
        else if ((input[0] == 's') || (input[0] == 'S')){
            // Player asks to go to the room to the 'south'
            // Set requested direction to South
            direction = 'S';
            exitRoom(rooms, currentRoom, direction, worked);
        }
        
        else if ((input[0] == 'h') || (input[0] == 'H')){
            // Player asks for 'help'
            // Print all commands available to player
            cout << "F : Find items\n"
                 << "I : Look at your inventory\n"
                 << "P : Pick up something from the area\n"
                 << "D : Drop an object from your inventory\n"
                 << "N : Go North\n"
                 << "E : Go East\n"
                 << "W : Go West\n"
                 << "S : Go South\n"
                 << "H : Ask for help\n"
                 << "Q : Quit game\n";                 
        }

        else if ((input[0] == 'q') || (input[0] == 'Q')){
            // Player asks to 'quit' game
            // Set playing to false thus exiting the while loop
            cout << "Quitting game..." << endl;
            playing = false;
        }

       else{
            // If player enters something other than the
            // available commands, print "invalid input"
            cout << "Invalid input, try again.\n";
            cin.clear();
        }
        
        // checking if player has already won the game
        if (won == false){
            // checking if player is in the cave
            if (currentRoom == rooms[13]){
                // checking if player has dropped required items in the cabin
                if (((player->hasItem(items[0]))  == true) // stick
		    &&  ((player->hasItem(items[2]))  == true)) { // coal
                    won = true;
                    cout << "You have sticks and coal so you made torches. Since you are in the cave, you are safe. This was all a game. You won\n"
                         << "Would you like to quit now? y/n";
                    cin.clear();
                    cin.ignore(10, '\n');
                    // Request input from player
                    cin.get(input, 2);
                    if ((input[0] == 'y') || (input[0] == 'Y')){
                        cout << "Okay, thanks for playing! Good bye.\n";
                        // Set playing to false and end while loop
                        playing = false;
                    }
                }
            }
        }
        // In case player enters too many characters:
        cin.ignore(20, '\n');
    } //end of while loop
}

void pickUpItem(Room* currentRoom, Player* player, int selected){
    // Adds the selected item to the player and removes 
    // it from the room

    // Checks if the room has an item in the selected slot
    if ((currentRoom->hasItem(currentRoom->getSelectedItem(selected))) == 1){
        // Tells the player the item they picked up
        cout << "You picked up ";
        currentRoom->getSelectedItem(selected)->printItem();
        
        // Adds the item selected from the current room 
        // to the player's inventory
        player->addItem(currentRoom->getSelectedItem(selected));

        // Removes the selected item from the current room
        currentRoom->removeItem(currentRoom->getSelectedItem(selected));

        // Tells the player what items are now in the current room
        cout << "Now that you have picked that up, \n";
        currentRoom->printItems();
    }
    // If the room does not have any item in the selected slot
    else {
        cout << "There is no item in that slot!\n";
    }
}

void dropItem(Room* currentRoom, Player* player, int selected){
    // Checks if the player has an item in the selected slot
    if ((player->hasItem(player->getSelectedItem(selected))) == 1){
        // Add the item selected from the player's inventory 
        // to the room        
        currentRoom->addItem(player->getSelectedItem(selected));
        // Tells the player the item they dropped
        cout << "You dropped ";
        // Prints the selected item
        player->getSelectedItem(selected)->printItem();
        // Removes the item from the player's inventory
        player->removeItem(player->getSelectedItem(selected));
        cout << "\nYour inventory now contains:\n";
        player->printInventory();
    }
    // If the player does not have any item in the selected slot
    else {
        cout << "There is no item in that slot!\n";
    }
}
void createRooms(vector<Room*> &rooms, vector<Item*> &items){
    // Create room objects and put in the vector of room pointers
    rooms.push_back(new Room( // 0
                "a desert island", "You're on an island completely barren and void of life."));

    rooms.push_back(new Room( // 1
                "an ocean", "The water is crystal clear. There are several squids swimming in the distance. They're probably harmless."));

    rooms.push_back(new Room( // 2
                "an ocean temple", "There's a strange creature trying to attack you. The purpose of the temple is unknown, but it is clearly quite dangerous."));

    rooms.push_back(new Room( // 3
                "the shore", "There are lots of rooms to go to from here.. Well, this was the shore."));
       
    rooms.push_back(new Room( // 4
                "a mushroom forest", "The forest is dark "
                "and smells of pine. These mushrooms on the ground could be used to make soup.."));

    rooms.push_back(new Room( // 5
                "a field", "There's nothing here but a few sheep."));

    rooms.push_back(new Room( // 6
                "a desert", "The wind picks up and a storm starts."
                "\nThere are no other travellers here."));  

    rooms.push_back(new Room(// 7
                "a village", "There are a lot of houses. Maybe there's treasure inside"));
    
    rooms.push_back(new Room(// 8
                "a ravine", "There is a spawner here and lots of skeletons. Run!"));

    rooms.push_back(new Room(// 9
                "null", "There are a lot of houses. Maybe there's treasure inside.")); 

    rooms.push_back(new Room(// 10
                "a desert temple", "The air is eerie. There are lots of traps here. Make one mistake and you could die.")); 
    
    rooms.push_back(new Room(// 11
                "a forest", "There are lots of trees. Wood could be useful for something maybe")); 
    
    rooms.push_back(new Room(// 12
                "a mountain", "The rough hillside exposes some ores.")); 
    
    rooms.push_back(new Room(// 13
                "a cave", "The cave is dark but it looks like there might be treasure around")); 
    
    rooms.push_back(new Room(//14
                "a cavern", "This seems to be the end. The only way back is out. The walls are shinier than before.")); 
    
    rooms.push_back(new Room(// 15
                "a mineshaft", "The walls are filled with "
                "veins of jewels and crystals.\nSadly you did not "
                "bring a pick to mine them, and there are only a "
                "few loose enough to grab."));  
    

    // Connect rooms by defining their exits
    // desert island and ocean
    (rooms[0])->createExit((rooms[1]), 'E') ; 
    (rooms[1])->createExit((rooms[0]), 'W') ; 

     // desert island and ocean temple
    (rooms[0])->createExit((rooms[2]), 'W') ;
    (rooms[2])->createExit((rooms[0]), 'E') ;

    // ocean temple to shore
    (rooms[2])->createExit((rooms[3]), 'S') ;   

    // ocean to shore
    (rooms[1])->createExit((rooms[3]), 'S') ;
    
    // shore and forest
    (rooms[3])->createExit((rooms[11]), 'N') ; 
    (rooms[11])->createExit((rooms[3]), 'S') ; 
    
    // shore and field
    (rooms[3])->createExit((rooms[5]), 'W') ;
    (rooms[5])->createExit((rooms[3]), 'E') ;
    
    // shore and mountain
    (rooms[3])->createExit((rooms[12]), 'S') ; 
    (rooms[12])->createExit((rooms[3]), 'N') ;
    
    // shore and desert
    (rooms[3])->createExit((rooms[6]), 'E') ;  
    (rooms[6])->createExit((rooms[3]), 'W') ;
    
    // mushroom forest and forest
    (rooms[4])->createExit((rooms[11]), 'W') ; 
    (rooms[11])->createExit((rooms[4]), 'E') ;  
    
    // mushroom forest and field    
    (rooms[4])->createExit((rooms[5]), 'S') ;  
    (rooms[5])->createExit((rooms[4]), 'N') ;

    // field and mineshaft
    (rooms[5])->createExit((rooms[15]), 'W') ;  
    (rooms[15])->createExit((rooms[5]), 'E') ;
    
    // desert and ravine
    (rooms[6])->createExit((rooms[8]), 'S') ;  
    (rooms[8])->createExit((rooms[6]), 'N') ;
    
    // desert and village
    (rooms[6])->createExit((rooms[7]), 'E') ;  
    (rooms[7])->createExit((rooms[6]), 'W') ;
    
    // village and desert temple
    (rooms[7])->createExit((rooms[10]), 'S') ; 
    (rooms[10])->createExit((rooms[7]), 'N') ;

    // mountain and cave
    (rooms[12])->createExit((rooms[13]), 'S') ;
    (rooms[13])->createExit((rooms[12]), 'N') ;

    // cave and cavern
    (rooms[13])->createExit((rooms[14]), 'S') ;
    (rooms[14])->createExit((rooms[13]), 'N') ;
    
    
    // Create items by adding Item pointers to a vector
    items.push_back(new Item("a stick"));                // 0
    items.push_back(new Item("a piece of iron"));        // 1
    items.push_back(new Item("a piece of coal"));        // 2
    items.push_back(new Item("armour"));                 // 3
    items.push_back(new Item("diamonds!"));              // 4
    items.push_back(new Item("mushroom soup"));          // 5

    
    // Put items in rooms
    (rooms[11])->addItem(items[0]);  // stick in forest
    (rooms[13])->addItem(items[1]);  // iron in cave
    (rooms[12])->addItem(items[2]);  // coal on mountain
    (rooms[8])->addItem(items[3]);   // armour in ravine
    (rooms[15])->addItem(items[4]);  // diamonds in mineshaft
    (rooms[10])->addItem(items[4]);  // diamonds in desert temple
    (rooms[7])->addItem(items[4]);   // diamonds in village
    (rooms[14])->addItem(items[4]);  // diamonds in cavern
    (rooms[4])->addItem(items[5]);   // mushroom soup in mushroom forest
}

void exitRoom(vector<Room*> rooms, Room* &currentRoom, char direction, bool worked){
    // Sets current room to the room defined as 
    // the exit to the selected direction

    // worked is for checking whether there is a room defined
    // in the selected direction
    worked = false;
    // Goes through each room and finds if that room is the room
    // defined as the requested exit
    for (int i = 0; i < rooms.size(); i++){
        // If there is not an exit to the requested direction, 
        // the exit will be set as the current room
        // So if the exit is not pointing to the current room, that
        // means that there is an exit
        if (rooms[i] != currentRoom){
            // Finds what room the current room's exit points to
            // and if that is the current room in the iterator
            if (rooms[i] == currentRoom->getExit(direction)){
                cout << "You went to "
                        // prints the room that the exit points to
                     << currentRoom->getExit(direction)->getID()
                     << endl;
                // changes current room to the room that 
                // the player is exiting to
                currentRoom = rooms[i];
                // a room was found, so worked equals true
                worked = true;
                break;
            }
        }
    }
    // If the iterator did not find a room in the requested direction
    if (worked == false){
        cout << "There is no exit in that direction!\n";
    }
}
