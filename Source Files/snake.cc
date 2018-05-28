#include "snake.h"
#include "cell.h"
#include "board.h"

using namespace std;


Snake::Snake(int row, int col, Direction dir,Board *tb,int snakeSize){
    mainBoard = tb;
    direction = dir;
    Cell *newCell = tb->getCell(row,col);
	increaseBy = snakeSize;
    Info temp = newCell->getInfo();
	temp.dir = direction;
    temp.statetype = StateType::Snake;
    newCell->setInfo(temp);
    back = newCell;
	snake.push_back(newCell);
    to_add = 0;
    size = 1;
}


void Snake::update(Direction dir) {

	direction = dir;//Updates the direction the snake is going in
	int newRow;
	int newCol;
	Cell *oldFront = snake[0];
	Info oldInfo = oldFront->getInfo();
	if (dir == Direction::Down) {
		newRow = oldInfo.row + 1;
		newCol = oldInfo.col;
	}
	else if (dir == Direction::Up) {
		newRow = oldInfo.row - 1;
		newCol = oldInfo.col;
	}
	else if (dir == Direction::Left) {
		newRow = oldInfo.row;
		newCol = oldInfo.col - 1;
	}
	else if (dir == Direction::Right) {
		newRow = oldInfo.row;
		newCol = oldInfo.col + 1;
	}


	if (newRow < 0 || newCol < 0 || newRow >= mainBoard->getRow() || newCol >= mainBoard->getCol()) throw GameOver();
	else if(((mainBoard->getCell(newRow, newCol))->getInfo()).statetype == StateType::Snake) throw GameOver();
	
	for (int i = size - 1; i >= 1; --i) {
		notify(i);
	}

	 if(to_add == 0){
 
		 Cell *oldBack = back;
		 Info oldInfoBack = oldBack->getInfo();

		 oldInfoBack.statetype = StateType::Empty;
		 oldInfoBack.dir = Direction::None;
		 oldBack->setInfo(oldInfoBack);

	 }else {
		 size++;
		 to_add--;
		 snake.emplace_back(back);
	 }

	
	Cell *toChange = mainBoard->getCell(newRow, newCol);
	Info infoToChange = toChange->getInfo();

	if (((mainBoard->getCell(newRow, newCol))->getInfo()).statetype == StateType::Food) {
		to_add += increaseBy;
		mainBoard->clearFoodBlock();
		mainBoard->makeFoodBlock();
	}

	infoToChange.statetype = StateType::Snake;
	infoToChange.dir= direction;

	toChange->setInfo(infoToChange);

	snake[0] = toChange;
	back = snake[size - 1];

}

void Snake::notify(int location){

    Info tempInfo = snake[location-1]->getInfo();
	Cell *tempCell = mainBoard->getCell(tempInfo.row, tempInfo.col);
	snake[location] = tempCell;
}

Info Snake::getFront() {
	return snake[0]->getInfo();
}

Cell *Snake::getCell(int location) {
	return snake[location];
}

Direction Snake::getDir() {
	return direction;
}

void Snake::getSnakeLoc() {
	Info tempInfo = snake[0]->getInfo();
	cout << "The head of the snake is at row: " << tempInfo.row << " col: " << tempInfo.col <<endl;
	for (int i = 1; i < size; ++i) {

		tempInfo = snake[i]->getInfo();
		cout << "The snake at " << i << " is at row: " << tempInfo.row << " col: " << tempInfo.col << endl;
		
	}
}

bool Snake::isFront(int row, int col) {
	Info temp = snake[0]->getInfo();
	if (temp.row == row && temp.col == col) return true;
	else return false;
}
