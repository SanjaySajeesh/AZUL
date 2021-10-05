/* Menu Class Description
 *Author:Sara Imamura Sanjay Sajeesh Krishnan Kee Chew Huang
 *The Menu class is responsible for the creation of the menu
 * which when an option is chosen, calls a specific method in GameEngine.
 */

//Header Files
#include <iostream>
#include <string>
#include <fstream>

#include "GameEngine.h"

void printMainMenu();
void startMainMenu();
void makeDecision(int input);
void startGame();
void loadGame();
void printCredits();

int main(int argc, char** argv)
{
    // this checks if the game is in testing mode
    if(argc == 3 && std::string(argv[1]) == "-t"){
        std::ifstream file(argv[2]);
        if(file.is_open()){
            GameEngine* ge = new GameEngine();
            ge->loadTileBag(file);
            ge->startGame(TESTGAME, file);
            file.close();
            delete ge;
        }else
        {
            std::cerr << "File not found" << std::endl;
        }
    }else{
        std::cout << "Welcome to Azul!" << std::endl
            << "------------------" << std::endl;
        startMainMenu();
    }
    return EXIT_SUCCESS;
}

//Prints the Menu
void printMainMenu()
{

    std::cout << std::endl
         << "Menu" << std::endl
         << "----" << std::endl;
    std::cout << "1. New Game\n"
         << "2. Load Game\n"
         << "3. Credits (Show student information)\n"
         << "4. Quit\n\n";
}

// Shows the initial Menu
void startMainMenu()
{
    int input = -1;
    while(input != 4 && !std::cin.eof()){
        printMainMenu();
        std::cout << USERINPUT;
        std::cin >> input;
        makeDecision(input);
    }
    std::cout << "GoodBye" << std::endl;
}

//Checks for user input
void makeDecision(int input)
{
    if (input == 1)
    {
        startGame();
        
    }else if(input ==2){
        loadGame();
        
        
    }else if(input ==3){
        printCredits();
    }else if(input ==4){
    }else {
        std::cerr << ERROR << std::endl;
        std::cin.clear();
        std::cin.ignore();
    }
}

//Helper Method to call a GameEngine Method to start a game
void startGame(){
    std::cout<<"Starting a new Game"<< std::endl;
    GameEngine* ge = new GameEngine();
    
    ge->startGame(NEWGAME, std::cin);

    delete ge;
}

//Helper Method to call a GameEngine Method to load a game
void loadGame(){
    std::cout<<"\nEnter the filename which loads a game"<< std::endl;
    GameEngine* ge = new GameEngine();
    std::string filename;

    std::cout << USERINPUT;
    std::cin >> filename;
    std::ifstream file(filename);
    
    if(file.is_open()){
        ge->loadTileBag(file);
        ge->startGame(LOADGAME, file);
        file.close();
        delete ge;
    }else
    {
        std::cerr << ERROR << std::endl;
    }
}

//Prints credits
void printCredits()
{
    std::cout << "Name: Kee Chew Huang\nStudent ID: s3808292\nEmail: s3808292@student.rmit.edu.au\n";
    std::cout << "Name: Sara Imamura\nStudent ID: s3808578\nEmail: s3808578@student.rmit.edu.au\n";
    std::cout << "Name: Sanjay Sajeesh Krishnan\nStudent ID: s3776159\nEmail: s3776159@student.rmit.edu.au\n";
}