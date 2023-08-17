#include "menu.h"
#include "GameController.h"
#include <iostream>
#include <limits>
#include <exception>
#include "IOStream.h"
#include <sstream>
#include "Player.h"
#include <fstream>


Menu::Menu() {

    this->enhancementsOn = false;
}


Menu::~Menu() {

}


void Menu::printMenu() {

    int input = 0;
    bool validInput = false;
    bool endOfFile = false;
    bool creditsOrEnhancementsRan = false;

    while (!validInput && input != EXIT && !endOfFile) {

        std::cout << "Menu" << std::endl;
        std::cout << "-----" << std::endl;
        std::cout << "1. New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        std::cout << "3. Credits (Show Student Information)" << std::endl;

        if (!enhancementsOn) {
            std::cout << "4. Turn Enhancements On" << std::endl;
        }
        else if (enhancementsOn) {
            std::cout << "4. Turn Enhancements Off" << std::endl;
        }

        std::cout << "5. Quit" << std::endl;

        if (!creditsOrEnhancementsRan) {
            std::cout << "> ";
            creditsOrEnhancementsRan = false;
        }

        while (std::cin.peek() == '\n') {
            std::cout << "> ";
            std::cin.get(); // Consume the newline character
        }

        if (std::cin >> input) {

            if (input == START) {

                if (!enhancementsOn) {
                    startNewGame();
                }
                else if (enhancementsOn) {
                    startEnhancedNewGame();
                }

                validInput = true;
            }
            else if (input == LOAD) {
                endOfFile = loadGame();
                validInput = true;
            }
            else if (input == CREDITS) {
                creditsOrEnhancementsRan = printCredits();
            }
            else if (input == ENHANCEMENTS) {
                enhancementsOn = !enhancementsOn;

                if (!enhancementsOn) {
                    std::cout << "Enhancements Turned Off" << std::endl;
                }
                else if (enhancementsOn) {
                    std::cout << "Enhancements Turned On" << std::endl;
                }
                std::cout << std::endl;
                creditsOrEnhancementsRan = true;
            }
            else if (input != EXIT) {
                std::cout << "Invalid Input" << std::endl;

            }
        }
        else {

            if (std::cin.eof()) {
                endOfFile = true;
            }
            else {
                std::cout << "Invalid Input" << std::endl;
                //clears error state from bad input to prevent infinite loop
                std::cin.clear();

                //empty while loop to consume and discard bad input from user until newline is reached.
                //uses std::cin.get() to keep receiving input.
                char randomInput;
                while ((randomInput = std::cin.get()) != '\n') {}
            }
        }
    }
}


void Menu::startNewGame() {

    std::cout << "Starting A New Game" << std::endl;
    std::cout << std::endl;

    std::string p1Name, p2Name, p3Name, p4Name;

    std::cout << "Enter A Name For Player 1 (uppercase characters only)" << std::endl;
    std::cout << "> ";

    bool validInput = false;
    bool eofReceived = false;

    while (!validInput && !eofReceived) {
        if (std::cin >> p1Name) {
            if (!isValidName(p1Name)) {
                std::cout << "Error: please enter a valid name for Player 1 (uppercase characters only)" << std::endl;
                std::cout << "> ";
            }
            else {
                validInput = true;
            }
        }
        else if (std::cin.eof()) {
            eofReceived = true;
        }
        else {
            //clear error state and consume contents of buffer
            std::cin.clear();
            char randomInput;
            while ((randomInput = std::cin.get()) != '\n') {}
            std::cout << "Error: please enter a valid name for Player 1 (uppercase characters only)" << std::endl;
            std::cout << "> ";
        }
    }

    if (!eofReceived) {

        std::cout << "Enter A Name For Player 2 (uppercase characters only)" << std::endl;
        std::cout << "> ";

        validInput = false;

        while (!validInput && !eofReceived) {
            if (std::cin >> p2Name) {
                if (!isValidName(p2Name)) {
                    std::cout << "Error: please enter a valid name for Player 2 (uppercase characters only)" << std::endl;
                    std::cout << "> ";
                }
                else {
                    validInput = true;
                }
            }
            else if (std::cin.eof()) {
                eofReceived = true;
            }
            else {
                //clear error state and consume contents of buffer
                std::cin.clear();
                char randomInput;
                while ((randomInput = std::cin.get()) != '\n') {}
                std::cout << "Error: please enter a valid name for Player 2 (uppercase characters only)" << std::endl;
                std::cout << "> ";
            }
        }

    }

    if (!eofReceived) {


        std::cout << "Player 1's Name = " << p1Name << std::endl;
        std::cout << "Player 2's Name = " << p2Name << std::endl;

        std::cout << "Lets Play!" << std::endl;

        try {
            GameController* gc = new GameController(p1Name, p2Name, p3Name, p4Name, enhancementsOn);
            gc->prepareGame();
            delete gc;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

    }
}


void Menu::startEnhancedNewGame() {

    std::cout << "Starting A New Game With Enhancements On" << std::endl;
    std::cout << std::endl;

    int input = 0;
    bool validInput = false;
    bool endOfFile = false;
    bool invalidInput = false;

    std::string p1Name, p2Name, p3Name, p4Name;


    while (!validInput && !endOfFile) {

        std::cout << "How many players will be playing today? (between 2-4 players)" << std::endl;

        if (invalidInput) {
            std::cout << "> ";
            invalidInput = false;
        }


        while (std::cin.peek() == '\n') {
            std::cout << "> ";
            std::cin.get(); // Consume the newline character
        }


        if (std::cin >> input) {

            if (input == 2 || input == 3 || input == 4) {

                p1Name = insertPlayerName(1);

                if (!p1Name.empty()) {
                    p2Name = insertPlayerName(2);
                }

                validInput = true;
            }
            else if (input != std::cin.eof()) {
                std::cout << "Invalid Input" << std::endl;
                invalidInput = true;

            }
        }
        else {

            if (std::cin.eof()) {
                endOfFile = true;
            }
            else {
                std::cout << "Invalid Input" << std::endl;
                //clears error state from bad input to prevent infinite loop
                std::cin.clear();

                //empty while loop to consume and discard bad input from user until newline is reached.
                //uses std::cin.get() to keep receiving input.
                char randomInput;
                while ((randomInput = std::cin.get()) != '\n') {}
            }
        }
    }

    if (input == 3 || input == 4) {

        if (!p2Name.empty()) {
            p3Name = insertPlayerName(3);
        }
    }

    if (input == 4) {

        if (!p3Name.empty()) {
            p4Name = insertPlayerName(4);
        }
    }

    if ((input == 2 && !p2Name.empty()) || (input == 3 && !p3Name.empty()) || (input == 4 && !p4Name.empty())) {

        std::cout << "Player 1's Name = " << p1Name << std::endl;
        std::cout << "Player 2's Name = " << p2Name << std::endl;

        if (!p3Name.empty()) {
            std::cout << "Player 3's Name = " << p3Name << std::endl;
        }

        if (!p4Name.empty()) {
            std::cout << "Player 4's Name = " << p4Name << std::endl;
        }

        std::cout << "Lets Play!" << std::endl;

        try {

            GameController* gc = new GameController(p1Name, p2Name, p3Name, p4Name, enhancementsOn);
            gc->prepareGame();
            delete gc;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }


}


std::string Menu::insertPlayerName(int playerNo) {

    std::string name;

    std::cout << "Enter A Name For Player " << playerNo << " (uppercase characters only)" << std::endl;
    std::cout << "> ";

    bool validInput = false;
    bool eofReceived = false;

    while (!validInput && !eofReceived) {
        if (std::cin >> name) {
            if (!isValidName(name)) {
                std::cout << "Error: please enter a valid name for Player " << playerNo << " (uppercase characters only)" << std::endl;
                std::cout << "> ";
            }
            else {
                validInput = true;
            }
        }
        else if (std::cin.eof()) {
            eofReceived = true;
        }
        else {
            //clear error state and consume contents of buffer
            std::cin.clear();
            char randomInput;
            while ((randomInput = std::cin.get()) != '\n') {}
            std::cout << "Error: please enter a valid name for Player " << playerNo << " (uppercase characters only)" << std::endl;
            std::cout << "> ";
        }
    }
    return name;
}


bool Menu::isValidName(std::string& input) {
    bool valid = true;


    for (char c : input) {
        if (!std::isalpha(c) || !std::isupper(c)) {
            valid = false;

        }
    }

    return valid;

}

bool Menu::loadGame() {

    std::string filename;
    std::string save = "saved_games/";
    bool validFileName = true;
    bool eofReceived = false;

    do {
        validFileName = true;
        save = "saved_games/";
        std::cout << "Enter the filename from which to load the game" << std::endl;

        std::cout << "> ";
        std::cin >> filename;
        save.append(filename);
        std::ifstream file(save);

        if (file.fail()) {
            std::cerr << "Error: can't find file" << std::endl;
            validFileName = false;
        }

    } while (!validFileName && !std::cin.eof());

    if (std::cin.eof()) {
        eofReceived = true;
    }

    if (!eofReceived) {

        //load game from file here, whilst also checking if filename is valid.
        IOStream load = IOStream();
        std::string game = load.loadGame(save);

        std::stringstream stream;
        stream.str(game);

        std::string saveType;
        stream >> saveType;

        if (saveType == "s3775648") {

            this->enhancementsOn = true;

            // Get Board Size and create board
            std::string boardSize;
            stream >> boardSize;

            std::stringstream boardSizeStream;
            boardSizeStream.str(boardSize);
            int boardRow;
            std::string row;
            std::getline(boardSizeStream, row, ',');
            boardRow = stoi(row);
            int boardCol;
            boardSizeStream >> boardCol;

            std::string boardState;
            stream >> boardState;

            Board* board = new Board(boardRow, boardCol);

            LinkedList* playedTiles = new LinkedList();
            if (boardState != "0") {

                std::stringstream boardStateStream;
                boardStateStream.str(boardState);


                // Load Board State
                std::string state;

                while (std::getline(boardStateStream, state, ',')) {
                    if (state.size() <= 2) {

                    }
                    else {
                        char colour = std::toupper(state[0]);
                        int shape = state[1] - '0';

                        Tile* tile = new Tile(shape, colour);

                        int row = state[3] - ASCII;
                        int col = (stoi(state.substr(4)) - 1);

                        board->setTile(row, col, tile);
                        playedTiles->addBack(tile);
                    }
                }
            }

            // Create/Load Tile Bag
            std::string tempTileBag;
            stream >> tempTileBag;
            std::stringstream tileBagStream;
            tileBagStream.str(tempTileBag);

            LinkedList* tileBag = new LinkedList();
            if (tempTileBag != "0") {

                std::string tempTile;

                while (std::getline(tileBagStream, tempTile, ',')) {
                    char colour = std::toupper(tempTile[0]);
                    int shape = tempTile[1] - '0';

                    Tile* tile = new Tile(shape, colour);

                    tileBag->addBack(tile);
                    delete tile;
                }
            }

            std::string currentPlayer;
            stream >> currentPlayer;


            // Create Player One
            std::string p1Name, p2Name, p3Name, p4Name;
            stream >> p1Name;

            int p1Score;
            stream >> p1Score;

            std::string hand;
            stream >> hand;

            std::stringstream stream2;
            stream2.str(hand);

            LinkedList* p1Hand = new LinkedList;

            std::string hand1;
            while (std::getline(stream2, hand1, ','))
            {
                char colour = std::toupper(hand1[0]);
                int shape = hand1[1] - '0';

                Tile* tile = new Tile(shape, colour);
                p1Hand->addBack(tile);
                delete tile;
            }

            Player* p1 = new Player(p1Name, p1Hand, p1Score);

            // Create Player Two
            stream >> p2Name;

            int p2Score;
            stream >> p2Score;

            std::string hand2;
            stream >> hand2;

            std::stringstream stream3;
            stream3.str(hand2);

            LinkedList* p2Hand = new LinkedList;

            std::string hand3;
            while (std::getline(stream3, hand3, ','))
            {
                char colour = std::toupper(hand3[0]);
                int shape = hand3[1] - '0';

                Tile* tile = new Tile(shape, colour);
                p2Hand->addBack(tile);
                delete tile;
            }

            Player* p2 = new Player(p2Name, p2Hand, p2Score);
            Player* p3 = nullptr;
            Player* p4 = nullptr;

            // Create Player Three
            if (stream >> p3Name) {

                int p3Score;
                stream >> p3Score;

                std::string hand4;
                stream >> hand4;

                std::stringstream stream4;
                stream4.str(hand4);

                LinkedList* p3Hand = new LinkedList;

                std::string hand5;
                while (std::getline(stream4, hand5, ','))
                {
                    char colour = std::toupper(hand5[0]);
                    int shape = hand5[1] - '0';

                    Tile* tile = new Tile(shape, colour);
                    p3Hand->addBack(tile);
                    delete tile;
                }

                p3 = new Player(p3Name, p3Hand, p3Score);

                // Create Player Four
                if (stream >> p4Name) {

                    int p4Score;
                    stream >> p4Score;

                    std::string hand6;
                    stream >> hand6;

                    std::stringstream stream5;
                    stream4.str(hand6);

                    LinkedList* p4Hand = new LinkedList;

                    std::string hand7;
                    std::cout << "in p4 load" << std::endl;
                    std::cout << "hand7: " << hand7 << std::endl;
                    while (std::getline(stream5, hand7, ','))
                    {
                        char colour = std::toupper(hand7[0]);
                        int shape = hand7[1] - '0';

                        Tile* tile = new Tile(shape, colour);
                        p4Hand->addBack(tile);
                        delete tile;
                    }

                    p4 = new Player(p4Name, p4Hand, p4Score);

                }
            }

            GameController* gc = new GameController(p1, p2, p3, p4, board, tileBag, playedTiles, this->enhancementsOn);

            if (p1->getName() == currentPlayer) {
                gc->setCurrPlayer(p1);
            }
            else if (p2->getName() == currentPlayer) {
                gc->setCurrPlayer(p2);
            }
            else if (p3->getName() == currentPlayer) {
                gc->setCurrPlayer(p3);
            }
            else {
                gc->setCurrPlayer(p4);
            }

            // Needed to clear cin buffer for first turn only.
            char randomInput;
            while ((randomInput = std::cin.get()) != '\n') {}
            std::cout << "Qwirkle game successfully loaded" << std::endl;
            gc->playGame();
            delete gc;

        }
        else {

            // Create Player One
            std::string p1Name, p2Name;
            stream >> p1Name;

            int p1Score;
            stream >> p1Score;

            std::string hand;
            stream >> hand;

            std::stringstream stream2;
            stream2.str(hand);

            LinkedList* p1Hand = new LinkedList;

            std::string hand1;
            while (std::getline(stream2, hand1, ','))
            {
                char colour = std::toupper(hand1[0]);
                int shape = hand1[1] - '0';

                Tile* tile = new Tile(shape, colour);
                p1Hand->addBack(tile);
                delete tile;
            }

            Player* p1 = new Player(p1Name, p1Hand, p1Score);

            // Create Player Two
            stream >> p2Name;

            int p2Score;
            stream >> p2Score;

            std::string hand2;
            stream >> hand2;

            std::stringstream stream3;
            stream3.str(hand2);

            LinkedList* p2Hand = new LinkedList;

            std::string hand3;
            while (std::getline(stream3, hand3, ','))
            {
                char colour = std::toupper(hand3[0]);
                int shape = hand3[1] - '0';

                Tile* tile = new Tile(shape, colour);
                p2Hand->addBack(tile);
                delete tile;
            }

            Player* p2 = new Player(p2Name, p2Hand, p2Score);

            // Get Board Size and create board
            std::string boardSize;
            stream >> boardSize;

            std::stringstream boardSizeStream;
            boardSizeStream.str(boardSize);
            int boardRow;
            std::string row;
            std::getline(boardSizeStream, row, ',');
            boardRow = stoi(row);
            int boardCol;
            boardSizeStream >> boardCol;

            std::string boardState;
            stream >> boardState;

            Board* board = new Board(boardRow, boardCol);

            LinkedList* playedTiles = new LinkedList();
            if (boardState != "0") {

                std::stringstream boardStateStream;
                boardStateStream.str(boardState);


                // Load Board State
                std::string state;

                while (std::getline(boardStateStream, state, ','))
                {
                    if (state.size() <= 2)
                    {

                    }
                    else
                    {
                        char colour = std::toupper(state[0]);
                        int shape = state[1] - '0';

                        Tile* tile = new Tile(shape, colour);

                        int row = state[3] - ASCII;
                        int col = (stoi(state.substr(4)) - 1);

                        board->setTile(row, col, tile);
                        playedTiles->addBack(tile);
                    }
                }
            }

            // Create/Load Tile Bag
            std::string tempTileBag;
            stream >> tempTileBag;
            std::stringstream tileBagStream;
            tileBagStream.str(tempTileBag);

            LinkedList* tileBag = new LinkedList();
            if (tempTileBag != "0") {

                std::string tempTile;

                while (std::getline(tileBagStream, tempTile, ','))
                {
                    char colour = std::toupper(tempTile[0]);
                    int shape = tempTile[1] - '0';

                    Tile* tile = new Tile(shape, colour);

                    tileBag->addBack(tile);
                    delete tile;
                }
            }

            std::string currentPlayer;
            stream >> currentPlayer;

            Player* p3 = nullptr;
            Player* p4 = nullptr;

            GameController* gc = new GameController(p1, p2, p3, p4, board, tileBag, playedTiles, this->enhancementsOn);

            if (p1->getName() == currentPlayer)
            {
                gc->setCurrPlayer(p1);
            }
            else
            {
                gc->setCurrPlayer(p2);
            }

            // Needed to clear cin buffer for first turn only.
            char randomInput;
            while ((randomInput = std::cin.get()) != '\n') {}
            std::cout << "Qwirkle game successfully loaded" << std::endl;
            gc->playGame();
            delete gc;
        }
    }
    return eofReceived;
}

bool Menu::printCredits() {

    std::cout << "------------------------------------------" << std::endl;

    std::cout << "Name: David Bradbury" << std::endl;
    std::cout << "Student ID: s3775590" << std::endl;
    std::cout << "Email: s3775590@student.rmit.edu.au\n" << std::endl;

    std::cout << "Name: Josh Coppen" << std::endl;
    std::cout << "Student ID: s3775648" << std::endl;
    std::cout << "Email: s3775648@student.rmit.edu.au\n" << std::endl;

    std::cout << "Name: Jack Lynch" << std::endl;
    std::cout << "Student ID: s3782003" << std::endl;
    std::cout << "Email: s3782003@student.rmit.edu.au\n" << std::endl;

    std::cout << "Name: David Pulvirenti" << std::endl;
    std::cout << "Student ID: s3858853" << std::endl;
    std::cout << "Email: s3858853@student.rmit.edu.au" << std::endl;

    std::cout << "------------------------------------------" << std::endl;

    return true;
}



