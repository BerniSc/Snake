#ifndef UTILITY_SNAKE_HPP
#define UTILITY_SNAKE_HPP

//For input without enter
#include <unistd.h>
#include <termios.h>

//For Random Number
//Stack Overflow 13445688 "How to generate a random number in C"
#include <random>
#include <cctype>

#include "game_constants.hpp"
#include "snake_node.hpp"

void initialize_board(char (&board)[game_constants::board_width][game_constants::board_height]);

char getCharWithoutEnter();

int getRandNumber(int const max);

#endif