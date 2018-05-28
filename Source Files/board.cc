//#include <vld.h>
#include "board.h"
#include "info.h"
#include "cell.h"
#include "snake.h"

using namespace std;

Board::Board(int r, int c,int snakeSize){
    if(c < 4 || r < 4) cout << "Error: Col or Row are less than 4" <<endl;
    else{
        row = r; 
        col = c;
        highScore = 0;
        currScore = 0;
        currFoodBlock = nullptr;
        for(int i  = 0 ; i  < r ; ++i){
            vector<Cell *> tempVector;
            for(int j = 0 ; j < c ; ++j){
                Info temp = {i,j,StateType::Empty,Direction::None};
                tempVector.push_back(new Cell(temp));
            }
            theBoard.push_back(tempVector);;
        }
	}
	s = new Snake{ 2, 2, Direction::Down, this, snakeSize};


}

Board::~Board(){
	cout << "The destructor for board was called" << endl;
    for(int i = 0 ; i < theBoard.size() ; ++i){
        for(int j = 0 ; j < theBoard[i].size() ; ++j){
            delete theBoard[i][j];
			theBoard[i][j] = nullptr;
        }
	}delete s;
}

void Board::printBoard(){
    cout << "Current Score is: " << currScore << endl;
    cout << "Highscore is: " << highScore << endl;
    for(int i = 0 ; i < row ; ++i){
        for(int j = 0 ; j < col ; ++j){
            Info temp = theBoard[i][j]->getInfo();
            StateType tempType = temp.statetype;
			if(tempType == StateType::Empty) cout << '-';
			else if (tempType == StateType::Food) cout << 'F';
			else if (tempType == StateType::Snake) {
				if (s->isFront(i,j)) cout << 'H';
				else cout << 'S';
			}
        }cout << endl;
    }
}


bool Board::gameOver(){

    Info temp;
	
    Info front = s->getFront();
    for(int i = 0 ; i < s->size ; ++i){
        temp = (s->getCell(i))->getInfo();
        if(temp.row >= row || temp.col >= col) return true;
        else if(i != 0 && (front.row == temp.row || front.col == temp.col)) return true;
    }
    return false;
}

void Board::makeFoodBlock(){
	int attempts = 0;
    if(currFoodBlock != nullptr) return;
    srand(time(0));
    while(1){
        int r;
        int c;
        r = rand() % row;
        c = rand() % col;
        Info temp = theBoard[r][c]->getInfo();
        if(temp.statetype == StateType::Empty){
            temp.statetype = StateType::Food;
            theBoard[r][c]->setInfo(temp);
			currFoodBlock = theBoard[r][c];
            break;
        }
		if (attempts >= 50) {
			if (isFull())throw Winner{};
		}
		++attempts;
    }

}




bool Board::isDirValid(Direction dir){
	if (s->size == 1) return true;

	Direction d = s->getDir();

	if (d == Direction::Up && dir == Direction::Down) return false;
	else if(d == Direction::Down && dir == Direction::Up) return false;
	else if (d == Direction::Left && dir == Direction::Right) return false;
	else if (d == Direction::Right && dir == Direction::Left) return false;
	
	return true;
}

void Board::nextMove(Direction dir) {
    char c;
	switch (dir) {
		case Direction::Up: c = 'u';
			break;
		case Direction::Down: c = 'd';
			break;
		case Direction::Left: c = 'l';
			break;
		case Direction::Right: c = 'r';
			break;
		default: c = 0;
			break;
	}

	if (c == 'd' && isDirValid(Direction::Down)) s->update(Direction::Down);
	else if (c == 'u' && isDirValid(Direction::Up)) s->update(Direction::Up);
	else if (c == 'l' && isDirValid(Direction::Left)) s->update(Direction::Left);
	else if (c == 'r' && isDirValid(Direction::Right)) s->update(Direction::Right);
	
} 

Cell *Board::getCell(int r, int c){
	return theBoard[r][c];
}

void Board::test() {
	Info temp = theBoard[0][0]->getInfo();
	temp.statetype = StateType::Snake;
	theBoard[0][0]->setInfo(temp);
}

int Board::getRow() {
	return row;
}

int Board::getCol() {
	return col;
}

void Board::getSnakeLoc() {
	s->getSnakeLoc();
}

void Board::getFoodBlock() {
	Info tempInfo = currFoodBlock->getInfo();
	cout << "The location of the food block is at row: " << tempInfo.row << " col: " << tempInfo.col << endl;
}

void Board::clearFoodBlock() {
	currFoodBlock = nullptr;
}

void Board::update(vector<vector<char>> &charBoard) {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			char c = 0;
			switch (theBoard[i][j]->getInfo().statetype) {
				case StateType::Empty: c = '-';
					break;
				case StateType::Food: c = 'f';
					break;
				case StateType::Snake: c = 's';
					break;
			}
			if (charBoard[i][j] != c) charBoard[i][j] = c;
		}

	}
}

Cell *Board::getFront() {
	Info temp = s->getFront();
	return theBoard[temp.row][temp.col];
}

void Board::nextMove() {
	s->update(s->getDir());
}

bool Board::sameDirection(Direction dir) {
	
	Direction d = s->getDir();
	return dir == d;
}

bool Board::isFront(int row, int col) {
	return s->isFront(row, col);
}

bool Board::isFull() {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (theBoard[i][j]->getInfo().statetype == StateType::Empty) return false; 
		}
	}return true;
}
