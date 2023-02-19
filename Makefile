COMPILER = "g++"
PROJECTNAME = snake_output
SOURCE = game.cpp snake_node.cpp snake_fruit.cpp utility_snake.cpp snake_exception.cpp
FLAGS = -std=c++17 -pthread

$(PROJECTNAME) : $(SOURCE)
		$(COMPILER) $(SOURCE) $(FLAGS) -o $(PROJECTNAME)