#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <ctime>
#include <vector>
#include "info.h"

class Winner {}; // Exception class

class Cell;
class Snake;

class Board{
    private:
        std::vector<std::vector<Cell *>> theBoard;
        Snake *s;//The snake currently on the board
        int row;
        int col;
        int currScore;
        int highScore;
        Cell *currFoodBlock;

	
    public:
        Board(int r, int c,int snakeSize);//Creates a row x col board with 2 rows above as buffer for score and highscore(Must be at least four)(Maybe throw an exception)
        ~Board();
        void printBoard();//Consider overriding <<
        bool gameOver(); //Checks if the game is over(Snake ran into a wall, or itself)
        void makeFoodBlock(); //Randomly generates a food block that is not apart of the snake and stores in currFoodBlock
     
      
       
		bool isDirValid(Direction dir); //Checks if a direction the player wants to go is valid(Essentially it can't go opposite itself)
        void nextMove(Direction dir); //Takes the nextMove from the player(This should be key strokes when implement with openGL), but for now will be every input. Calls update on the snake.
		void nextMove();

		Cell *getCell(int r, int c); //Returns a pointer to Cell at row r and col c

		int getRow();
		int getCol();

		void test();

		void clearFoodBlock();

		void update(std::vector<std::vector<char>> &charBoard);
	
		bool sameDirection(Direction dir);

		void getSnakeLoc(); // Testing function
		void getFoodBlock(); // Testing function that display the corrdinates of the food blockT

		Cell *getFront(); //Testing function;
		bool isFront(int row, int col);
		bool isFull(); //Checks if the board is filled
	
};

#endif
