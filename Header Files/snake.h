#ifndef _SNAKE_H_
#define _SNAKE_H_


#include "info.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>


class GameOver {};// Exception Class


class Cell;
class Board;

class Snake{
    Board *mainBoard;
    std::vector<Cell *> snake; //Body of the snake
    Direction direction; //Direction the Snake is going in
    int to_add; //# of new cells to be added to the end of the snake(Should be checked every cycle)
    Cell *back; //Pointer which points to the back of the snake - For efficiency purposes
	int increaseBy;
    public:
		int size = 0;
        Snake(int row, int col, Direction dir,Board *tb,int snakeSize);//Creates a snake at row, col with dir as the direction(Only creates a one block)
        void notify(int location);//Notify all the observers and pass the index that they are within the snake body
		 Cell *getCell(int location); //return cell at index location
        void update(Direction dir); //Update the direction the snake is going and notify the cells subsequently
        Info getFront(); //Return the info for the front of the snake
		Direction getDir();
		bool isFront(int row, int col);

		void getSnakeLoc(); //Testing function to determine what every snake points to and what foodblock points to
};


#endif