#ifndef SNAKE_NODE_HPP
#define SNAKE_NODE_HPP

#include "game_constants.hpp"
#include "snake_fruit.hpp"

#include <iostream>
#include <utility>

struct snake_fruit;

class snake_node {
    private:
        snake_node *nextNode, *previousNode;
        const int node_id;
        static int node_id_counter;

        std::pair<int, int> coordinates;
        std::pair<int, int> previous_coordinates;

        game_constants::direction node_direction;

        char node_symbol;

        //Move gives own coordinates recursivly to next Node
        void moveNode(std::pair<int, int> coordinates);

        virtual ~snake_node();
    public:
        snake_node();

        void addNode(snake_node *next);
        void deleteSnake();

        void drawSnake(char (&board)[game_constants::board_width][game_constants::board_height]);

        snake_node* getNodeWithID(int ID);

        void setDirection(game_constants::direction);
        game_constants::direction getDirection() const;

        void setPosition(std::pair<int, int> position);

        void setSymbol(char symbol);

        void moveHead();

        bool checkHeadFruit(const snake_fruit*) const;
};

#endif