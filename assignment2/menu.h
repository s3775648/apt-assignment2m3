#ifndef ASSIGN2_MENU_H
#define ASSIGN2_MENU_H 

#include <string>

enum selection {
    START = 1,
    LOAD = 2,
    CREDITS = 3,
    ENHANCEMENTS = 4,
    EXIT = 5
};

class Menu
{
public:

    // Constructor/Destructor
    Menu();
    ~Menu();

    // print the menu.
    void printMenu();

    // Starts a new game.
    void startNewGame();

    // Starts a new game with enhancements turned on. Milestone 3.
    void startEnhancedNewGame();

    // Retrieve players name from the user.
    std::string insertPlayerName(int playerNo);

    // Validate name input from user, pass by reference.
    bool isValidName(std::string& input);

    // Loads game from file.
    bool loadGame();

    // Print student credits.
    bool printCredits();


private:

    bool enhancementsOn;
};

#endif //ASSIGN2_MENU_H

