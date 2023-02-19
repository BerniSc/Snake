#include <iostream>
#include <vector>
#include <chrono>

#include <mutex>
#include <thread>
//For input without enter
#include <unistd.h>
#include <termios.h>

#include "snake_node.hpp"
#include "snake_fruit.hpp"
#include "game_constants.hpp"
#include "utility_snake.hpp"
#include "snake_exception.hpp"

using namespace std;

char gameBoard[game_constants::board_width][game_constants::board_height];

static mutex inputMutex;
static char input = ' ';

static mutex stopMutex;
static bool stop;

//Sort Of Beautified Version of the Output
void print_board(const char (&board)[game_constants::board_width][game_constants::board_height]) {
    //clear terminal
    cout << "\033[2J\033[1;1H";
    cout << "\t\t\t  +";
    for(int i = 0; i < game_constants::board_width; i++) cout << "=";
    cout << "+" << endl;
    for(int y = 0; y < game_constants::board_height; y++) {
        cout << "\t\t\t = ";
        for(int x = 0; x < game_constants::board_width; x++) {
            cout << board[x][y];
        }
        cout << " = " << endl;
    }
    cout << "\t\t\t  +";
    for(int i = 0; i < game_constants::board_width; i++) cout << "=";
    cout << "+" << endl;
}

//Barebone print of the GameBoard
void print_board_2(const char (&board)[game_constants::board_width][game_constants::board_height]) {
    //clear terminal
    cout << "\033[2J\033[1;1H";
    for(int y = 0; y < game_constants::board_height; y++) {
        for(int x = 0; x < game_constants::board_width; x++) {
            cout << board[x][y];
        }
        cout << endl;
    }
}

//For Solution with thread -> needs while Loop 
void getCharWithoutEnterVoid() {
    while(!stop) {
        char buffer = 0;
        struct termios old = {0};
        if(tcgetattr(0, &old) < 0) perror("tcsetattr()");
        //Disable canonical Mode
        //Supress Echo
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if(tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANONO");
        //Read Char
        if(read(0, &buffer, 1) < 0) perror("read()");
        //Reset Changes
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if(tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");
        //return Char
        inputMutex.lock();
        input = buffer;
        inputMutex.unlock();
    }
}

void waitThreadCallback(const std::chrono::milliseconds &waitTime) {
    this_thread::sleep_for(waitTime);
}

int main() {
    initialize_board(gameBoard);
    print_board(gameBoard);

    snake_node *head = new snake_node();
    //preventing the outer three columns from beeing a spawnpoint
    int randX = getRandNumber(game_constants::board_width - 6) + 3;
    //preventing the outer three rows from beeing a spawnpoint
    int randY = getRandNumber(game_constants::board_height - 6) + 3;
    head->setPosition(pair<int, int>(randX, randY));

    int randDirectionNumber = getRandNumber(3);
    //Standard value down
    game_constants::direction randDirection = game_constants::direction::down;
    //Overwriting and setting direction value
    if(randDirectionNumber >= 0 && randDirectionNumber <= 3) 
        randDirection = static_cast<game_constants::direction>(randDirectionNumber);
    
    head->setDirection(randDirection);

    for(int i = 0; i < game_constants::start_size_snake; i++) {
        head->addNode(new snake_node);
    }

    snake_fruit *fruit_holder = new snake_fruit;
    fruit_holder->drawFruit(gameBoard);

    //starting thread for Inputs;
    thread inputThread(getCharWithoutEnterVoid);

    char tickCounter = 0;

    while(!stop) {
        thread waitThread(waitThreadCallback, game_constants::tick_duration);

        //Ensuring Thread/Variable Integrety through Mutex -> new Variable required
        inputMutex.lock();
        char inputDummy = input;
        inputMutex.unlock();

        switch(inputDummy) {
            case 'a' :
                if(head->getDirection() == game_constants::direction::right) break;
                head->setDirection(game_constants::direction::left);
                input = '+';
                break;
            case 'd' :
                if(head->getDirection() == game_constants::direction::left) break;
                head->setDirection(game_constants::direction::right);
                input = '+';
                break;
            case 's' :
                if(head->getDirection() == game_constants::direction::up) break;
                head->setDirection(game_constants::direction::down);
                input = '+';
                break;
            case 'w' :
                if(head->getDirection() == game_constants::direction::down) break;
                head->setDirection(game_constants::direction::up);
                input = '+';
                break;
            case 'q' :
                head->deleteSnake();
                delete fruit_holder;
                print_board(gameBoard);
                cout << "Quitting..." << endl;
                stop = 1;
                break;
            case ' ' :
                tickCounter = game_constants::tick_number - 1;
                input = '+';
                break;
            //Normal input if nothing pressed
            case '+' :
                break;
            default :
                cout << "Wrong Input" << endl;
                input = ' ';
                break;
        }
        tickCounter++;

        if(!stop && tickCounter == game_constants::tick_number) {
            tickCounter = 0;
            if(head->checkHeadFruit(fruit_holder)) {
                delete fruit_holder;
                fruit_holder = new snake_fruit;
                fruit_holder->drawFruit(gameBoard);
                head->addNode(new snake_node);
            }
            head->moveHead();
            head->drawSnake(gameBoard);
            print_board(gameBoard);
        }
        
        waitThread.join();
        /*dropdownCounter++;
        try {
            if(dropdownCounter == game_constants::falltime_factor) {
                dropdownCounter = 0;
                controller->getCurrentTetromino().moveDown(gameBoard);
                controller->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
            }
        } catch(const Tetromino_Stuck &tetromino_stuck_exp) {
            //controller->generateNewTetromino(0, pair<int, int>(0,2), 0, 0);
            //ADD TRY FOR GAME OVER TODO
            removeCompletedRows(gameBoard);
            controller->generateNewRandomTetromino();
            controller->getCurrentTetromino().drawTetromino(gameBoard);
            print_board(gameBoard);
            //cout << tetromino_stuck_exp.print_what();
            //this_thread::sleep_for(2s);
        }
    }*/
    }

    inputThread.join();

    return 0;
}