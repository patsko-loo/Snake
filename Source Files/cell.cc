#include "cell.h"
#include <iostream>

using namespace std;

Cell::Cell(Info temp){
    info = temp;
}


Info Cell::getInfo(){
	return info;
}
void Cell::setInfo(Info s){
    info = s;
}
  