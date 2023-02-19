#ifndef SNAKE_FRUIT_HPP
#define SNAKE_FRUIT_HPP

#include <utility>
#include "utility_snake.hpp"

class snake_fruit {
    private :
        const int fruit_id;
        static int fruit_id_counter;

        char fruit_symbol;
        
        std::pair<int, int> spawn_coordinates;

        void generate_set_coordinates();
    public :
        snake_fruit();
        virtual ~snake_fruit();

        void drawFruit(char (&board)[game_constants::board_width][game_constants::board_height]);

        int getX() const;
        int getY() const;
};

#endif