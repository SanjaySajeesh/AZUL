/* GameEngine Class Description
 *Author:Sara Imamura Sanjay Sajeesh Krishnan Kee Chew Huang
 *The GameEngine class is responsible for the functioning of the 
 *game. It integrates the player and factory class
 *predominantly to run the game logically. It also facilitates game saving
 *and loading from an existing file present in the source folder.
 */

//Header Files
#include <random>
#include "GameEngine.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

GameEngine::GameEngine()
{
    this->tileBag = new LinkedList();
    this->factory = new Factory();
    this->players = new Player *[NUM_OF_PLAYERS];
}

GameEngine::~GameEngine()
{
    delete this->factory;

    for (int i = 0; i < NUM_OF_PLAYERS; ++i)
    {
        delete this->players[i];
    }
    delete[] this->players;

    delete this->tileBag;
}

// add to game log
void GameEngine::saveGameDetails()
{
    Node *current = this->tileBag->getHead();
    std::string bag;
    while (current != nullptr)
    {
        bag += enumToChar(current->data);
        current = current->next;
    }

    this->gameLog.push_back(bag);

    for (int i = 0; i < NUM_OF_PLAYERS; ++i)
    {
        this->gameLog.push_back(this->players[i]->getName());
    }
}

//to create a tileBag with randomized sequence of tiles
void GameEngine::createTileBag(int seed)
{
    Tile tileBagArr[TILEBAG_SIZE];

    //initialize values in an array
    for (int i = 0; i < TILEBAG_SIZE; ++i)
    {
        if (i < NUM_OF_TILES)
        {
            tileBagArr[i] = RED; //RYBLU
        }
        else if (i < 2 * NUM_OF_TILES)
        {
            tileBagArr[i] = YELLOW;
        }
        else if (i < 3 * NUM_OF_TILES)
        {
            tileBagArr[i] = DARK_BLUE;
        }
        else if (i < 4 * NUM_OF_TILES)
        {
            tileBagArr[i] = LIGHT_BLUE;
        }
        else
        {
            tileBagArr[i] = BLACK;
        }
    }

    //to ensure a consistent output, a seed is given to the random engine
    std::default_random_engine engine(seed);
    std::uniform_int_distribution<int> randomInt(0, TILEBAG_SIZE - 1);

    //shuffle the array to produce a random sequence
    for (int i = 0; i < TILEBAG_SIZE; ++i)
    {
        int index = randomInt(engine);
        Tile current = tileBagArr[i];
        tileBagArr[i] = tileBagArr[index];
        tileBagArr[index] = current;
    }

    //transferring the tiles into a LinkedList
    for (int i = 0; i < TILEBAG_SIZE; ++i)
    {
        this->tileBag->addFront(tileBagArr[i]);
    }
}

// this loads a tile bag from the saved file
void GameEngine::loadTileBag(std::istream &sstream)
{
    for (int i = 0; i < TILEBAG_SIZE; i++)
    {
        char tileC;
        sstream >> tileC;
        Tile tile = charToEnum(tileC);
        this->tileBag->addBack(tile);
    }
}

//this sets up the players and tile bag
void GameEngine::setUp(Command const type, std::istream &sstream)
{
    //get player name and instantiate players
    std::string playerName;
    for (int i = 0; i < NUM_OF_PLAYERS; ++i)
    {
        if (type == NEWGAME)
        {
            std::cout << "Enter name for Player " << std::to_string(i + 1) << ":\n"
                      << USERINPUT;
        }
        sstream >> playerName;
        this->players[i] = new Player(playerName);
    }
    sstream.ignore();

    // the game starts here
    if (type == NEWGAME)
    {
        std::cout << "\nLet's Play!" << std::endl;
        createTileBag(DEFAULT_SEED);
    }

    //saved the initial details before game starts
    this->saveGameDetails();
}

// executes the game play
void GameEngine::startGame(Command type, std::istream &sstream)
{
    // this is the type of command for game play (LOAD or NEWGAME)
    Command t = type;

    setUp(t, sstream);

    //round counter
    int round = 1;
    // endGame true when the game is terminated by eof()
    bool endGame = false;

    //the game is carried for 5 rounds
    while (round <= 5 && !endGame)
    {
        // create factories at the start of every round
        Tile factoryPlates[FACTORY_PLATE * FACTORY_NUM] = {NO_TILE};

        for (int i = 0; i < (FACTORY_NUM * FACTORY_PLATE); i++)
        {
            factoryPlates[i] = tileBag->get(0);
            tileBag->deleteFront();
        }
        this->factory->createFactory(factoryPlates);

        //Players take turns at this stage
        if (t == NEWGAME)
        {
            std::cout << "\n=== Start Round ===" << std::endl;
            takeTurns(t, std::cin);
            if (std::cin.eof())
            {
                endGame = true;
            }
        }
        else if (t == LOADGAME)
        {
            if (takeTurns(t, sstream))
            {
                // if game is complete, the game is set to new game
                // where the user continue the game from this point
                t = NEWGAME;
            }
            if (std::cin.eof())
            {
                endGame = true;
            }
        }
        else
        {
            takeTurns(t, sstream);
            if (sstream.eof())
            {
                endGame = true;
            }
        }

        if (!endGame)
        {
            //Before a new round is started, players will have the mosaic and scores updated.
            for (int i = 0; i < NUM_OF_PLAYERS; ++i)
            {
                std::vector<Tile> discardedTiles = this->players[i]->wallTiling();

                //returning the discardedTiles to the tilebag
                for (Tile t : discardedTiles)
                {
                    this->tileBag->addBack(t);
                }
            }
        }
        if (t == NEWGAME && !endGame)
        {
            std::cout << "\n=== END ROUND ===\n"
                      << std::endl;
            for (int i = 0; i < NUM_OF_PLAYERS; ++i)
            {
                std::cout << "Score for Player " << players[i]->getName() << ": " << players[i]->getScore() << std::endl;
            }
        }
        ++round;
    }
    // calculates the final score for the game
    if (t == NEWGAME && !endGame)
    {
        std::cout << "\n=== GAME OVER ===" << std::endl;
        std::cout << "\nFinal Scores:" << std::endl;
    }
    else if (t == TESTGAME)
    {
        // prints out the final state of the game
        std::cout << "Factories:" << std::endl;
        std::cout << this->factory->printTiles() << std::endl
                  << std::endl;
    }
    int winnerIndex = 0;
    for (int i = 0; i < NUM_OF_PLAYERS; ++i)
    {

        if (t == TESTGAME)
        {
            std::cout << "Score for Player " << players[i]->getName() << ": " << players[i]->getScore() << std::endl;
            std::cout << "Mosaic for " << players[i]->getName() << ":" << std::endl;
            std::cout << players[i]->printMosaic() << std::endl
                      << std::endl;
        }
        else if (t == NEWGAME && !endGame)
        {
            std::cout << "Player " << this->players[i]->getName() << ": " << this->players[i]->getScore() << std::endl;

            // determine the winner
            if (players[i]->getScore() > players[winnerIndex]->getScore())
            {
                winnerIndex = i;
            }
        }
    }
    //print the winner of the game
    if (t == NEWGAME && !endGame)
    {
        std::cout << "Player " << players[winnerIndex]->getName() << " wins!" << std::endl;
    }
}

// execute the turn for each rond
bool GameEngine::takeTurns(Command &type, std::istream &sstream)
{
    bool returnLoadStatus = false;
    Player *currentPlayer = nullptr;
    int currentPlayerIndex = 0;

    // this checks which player holds FIRST PLAYER tile in previous turn
    for (int i = 0; i < NUM_OF_PLAYERS; ++i)
    {
        if (this->players[i]->firstPlayer)
        {
            currentPlayerIndex = i;
        }
    }

    // a round continues until all the factories are empty or ^D is entered by user
    bool endGame = false;
    while (!factory->isEmpty() && !std::cin.fail() && !endGame)
    {
        currentPlayer = this->players[currentPlayerIndex];

        // these varialbles stores the command for turn
        bool input = false;
        std::string command;
        int factoryIndex;
        char tile;
        int rowIndex;

        if (type == NEWGAME)
        {
            std::cout << "TURN FOR PLAYER:" << currentPlayer->getName() << std::endl
                      << std::endl;

            //print factory and mosaic
            std::cout << "Factories:" << std::endl
                      << std::endl;
            std::cout << this->factory->printTiles() << std::endl
                      << std::endl;
            std::cout << "Mosaic for " << currentPlayer->getName() << ":" << std::endl
                      << std::endl;
            std::cout << currentPlayer->printMosaic() << std::endl
                      << std::endl;

            // take command input from user
            input = promptInput(command, factoryIndex, tile, rowIndex, currentPlayer, type, std::cin);
        }
        else
        {
            // take command input from user
            input = promptInput(command, factoryIndex, tile, rowIndex, currentPlayer, type, sstream);
        }

        // get input commands from the user
        if (input)
        {
            std::string log = command + " " + std::to_string(factoryIndex) + " " + tile + " " + std::to_string(rowIndex);
            this->gameLog.push_back(log);
            Tile tileType = charToEnum(tile);
            // get vector of tiles to be moved to player's mosaic
            std::vector<Tile> collectedTiles = this->factory->getTile(factoryIndex, tileType);

            // iterate each tiles and add to the player's pattern line
            for (Tile t : collectedTiles)
            {
                if (!currentPlayer->factoryOffer(t, rowIndex))
                {
                    tileBag->addBack(t);
                }
            }

            if (type == NEWGAME)
            {
                std::cout << "Turn successful.\n"
                          << std::endl;
            }
        }

        if (std::cin.eof())
        {
            endGame = true;
        }

        if (sstream.eof())
        {
            if (type == TESTGAME)
            {
                endGame = true;
            }
            else if (type == LOADGAME)
            {
                returnLoadStatus = true;
                std::cin.ignore();
                type = NEWGAME;
                std::cout << "Successfully loaded" << std::endl;
                currentPlayerIndex = (currentPlayerIndex + 1) % NUM_OF_PLAYERS;
            }
        }
        //pass the round to the next Player
        currentPlayerIndex = (currentPlayerIndex + 1) % NUM_OF_PLAYERS;
        command = "";
    }
    return returnLoadStatus;
}

// get input command from user
bool GameEngine::promptInput(std::string &command, int &factoryIndex, char &tile, int &rowIndex, Player *currentPlayer, const Command type, std::istream &sstream)
{
    bool valid = false;
    // this variables stores input commands from user (save or turn)
    std::string input;
    std::string filename;
    do
    {
        if (type == NEWGAME)
        {
            std::cout << USERINPUT;
        }
        // get command
        std::getline(sstream, input);
        std::istringstream sstreamline(input);
        sstreamline >> command;

        if (std::cin.eof())
        {
            std::cout << "^D" << std::endl;
        }
        else if (command == "turn")
        {
            sstreamline >> factoryIndex;
            sstreamline >> tile;
            sstreamline >> rowIndex;
            if (sstreamline.fail() || !sstreamline.eof())
            {
                valid = false;
            }
            else
            {
                if (rowIndex <= WALL_DIM && rowIndex >= 0 && factoryIndex <= FACTORY_NUM && factoryIndex >= 0 && this->factory->checkValid(charToEnum(tile), factoryIndex))
                {
                    valid = currentPlayer->checkValid(charToEnum(tile), rowIndex);
                }
            }
            if (!valid)
            {
                std::cerr << ERROR << std::endl;
            }
        }
        else if (command == "save")
        {

            sstreamline >> filename;
            if (sstreamline.fail() || !sstreamline.eof())
            {
                std::cerr << ERROR << std::endl;
            }
            else
            {
                saveGame(filename);
                std::cerr << "Saved successfully." << std::endl;
            }
        }
    } while (!valid && !sstream.eof());
    return valid;
}

// save the game to file
void GameEngine::saveGame(std::string &filename)
{
    std::ofstream saveFile;
    saveFile.open(RELATIVE_PATH + filename);

    for (std::string s : this->gameLog)
    {
        saveFile << s << std::endl;
    }
    saveFile.close();
}