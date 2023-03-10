#include "utility_snake.hpp"

void initialize_board(char (&board)[game_constants::board_width][game_constants::board_height]) {
    for(int y = 0; y < game_constants::board_height; y++) {
        for(int x = 0; x < game_constants::board_width; x++) {
            board[x][y] = game_constants::empty_boardblock;
        }
    }
}

//Get input without enter
// -> Problem was that programm only proceeded, when any key was pressed -> Ok for testing, but bad for game, as loops just kept on getting stuck 
// --> Solution is through the use of "Input" global var, protected by Mutex and returntyp void -> function sets global instead of returning
char getCharWithoutEnter() {
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
    return buffer;
}

int getRandNumber(int const max) {
    std::random_device seed_gen;
    const uint_least32_t seed = seed_gen();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<uint_least32_t> distribute(0, max);

    return distribute(generator);
}