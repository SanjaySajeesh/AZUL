#include <string>
#include <vector>

#include "Player.h"
#include "Factory.h"
#include "LinkedList.h"
#ifndef A2_GameEngine
#define A2_GameEngine


class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    void startGame(Command type, std::istream& sstream); 
    void loadTileBag(std::istream& sstream);
private:
    Player** players;
    LinkedList* tileBag;
    std::vector <std::string> gameLog;
    Factory* factory;

    void setUp(Command const type, std::istream& sstream);
    void createTileBag(int seed);
    bool takeTurns(Command& type, std::istream &sstream);
    bool promptInput(std::string& command, int &factoryIndex, char& tile, int& rowIndex, Player* currentPlayer, const Command type, std::istream& sstream);
    void saveGame(std::string& filename);
    void saveGameDetails();
    //void saveLog(std::ofstream &outStream);
};

#endif // COSC_ASSIGN_ONE_Position
