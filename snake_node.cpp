#include "snake_node.hpp"

int snake_node::node_id_counter = 0;

snake_node::snake_node() : node_id(node_id_counter++), nextNode(nullptr) {
    int randSymbol = getRandNumber(4);
    setSymbol(game_constants::snake_blocks[randSymbol]);
}

snake_node::~snake_node() {
    std::cout << "Removed (Destructed) Snake-Node with ID: " << this->node_id << std::endl;
}

void snake_node::addNode(snake_node *next) {
    if(this->nextNode != nullptr) {
        nextNode->addNode(next);
    } else {
        this->nextNode = next;
    }
}

void snake_node::deleteSnake() {
    if(nextNode != nullptr) {
        nextNode->deleteSnake();
    }
    delete this;
}

void snake_node::drawSnake(char (&board)[game_constants::board_width][game_constants::board_height]) {
    board[this->coordinates.first][this->coordinates.second] = this->node_symbol;
    if(this->nextNode == nullptr) {
        board[this->previous_coordinates.first][this->previous_coordinates.second] = game_constants::empty_boardblock;
    } else {
        nextNode->drawSnake(board);
    }
}

snake_node* snake_node::getNodeWithID(int ID) {
    if(ID > snake_node::node_id_counter || ID < 0) {
        //TODO Exception machen
        std::cerr << "Get Node with ID failed because of wrong index" << std::endl;
        return nullptr;
    }
    if(ID == this->node_id) {
        return this;
    } else {
        nextNode->getNodeWithID(ID);
    }
    return nullptr;
}

void snake_node::setDirection(game_constants::direction direction) {
    this->node_direction = direction;
}

game_constants::direction snake_node::getDirection() const {
    return this->node_direction;
}

void snake_node::setPosition(std::pair<int, int> position) {
    this->coordinates = position;
}

void snake_node::setSymbol(char symbol) {
    node_symbol = symbol; 
}

char getSymbol();

//Move gives own coordinates recursivly to next Node
void snake_node::moveNode(std::pair<int, int> coordinates) {
    this->previous_coordinates = this->coordinates;
    this->coordinates = coordinates; 
    if(nextNode != nullptr) {
        nextNode->moveNode(this->previous_coordinates);
    }
}

//Move gives own coordinates recursivly to next Node
void snake_node::moveHead() {
    if(this->node_id != 0) {
        //TODO ERROR
        return;
    }
    this->previous_coordinates = this->coordinates;

    bool moveSnakeNodes = true;
    switch(this->node_direction) {
        case game_constants::right :
            if(this->coordinates.first < (game_constants::board_width - 1)) {
                this->coordinates = std::pair<int, int>(this->coordinates.first + 1, this->coordinates.second);
                this->setSymbol('>');
            } else {
                moveSnakeNodes = false;
            }
            break;
        case game_constants::up :
            if(this->coordinates.second > 0) {
                this->coordinates = std::pair<int, int>(this->coordinates.first, this->coordinates.second - 1);
                this->setSymbol('^');
            } else {
                moveSnakeNodes = false;
            }
            break;
        case game_constants::left :
            if(this->coordinates.first > 0) {
                this->coordinates = std::pair<int, int>(this->coordinates.first - 1, this->coordinates.second);
                this->setSymbol('<');
            } else {
                moveSnakeNodes = false;
            }
            break;
        case game_constants::down :
            if(this->coordinates.second < (game_constants::board_height - 1)) {
                this->coordinates = std::pair<int, int>(this->coordinates.first, this->coordinates.second + 1);
                this->setSymbol('v');
            } else {
                moveSnakeNodes = false;
            }
            break;
    }
    if(moveSnakeNodes) nextNode->moveNode(previous_coordinates);
}

bool snake_node::checkHeadFruit(const snake_fruit *fruit) const{
    if(this->node_id != 0) {
        //TODO ERROR
    }
    switch(this->node_direction) {
        case game_constants::right :
            if(this->coordinates.first < game_constants::board_width && this->coordinates.second < game_constants::board_height) {
                if(this->coordinates.first + 1 == fruit->getX() && this->coordinates.second == fruit->getY()) return true;
            } else {
                //TODO ERROR
            }
            break;
        case game_constants::up :
            if(this->coordinates.first < game_constants::board_width && this->coordinates.second < game_constants::board_height) {
                if(this->coordinates.first == fruit->getX() && this->coordinates.second - 1 == fruit->getY()) return true;
            } else {
                //TODO ERROR
            }
            break;
        case game_constants::left :
            if(this->coordinates.first < game_constants::board_width && this->coordinates.second < game_constants::board_height) {
                if(this->coordinates.first - 1 == fruit->getX() && this->coordinates.second == fruit->getY()) return true;
            } else {
                //TODO ERROR
            }
            break;
        case game_constants::down :
            if(this->coordinates.first < game_constants::board_width && this->coordinates.second < game_constants::board_height) {
                if(this->coordinates.first == fruit->getX() && this->coordinates.second + 1 == fruit->getY()) return true;
            } else {
                //TODO ERROR
            }
            break;
    }
    return false;
}