#ifndef _CELL_H_
#define _CELL_H_

#include "info.h" //info.h contains Row and Col of a cell, pluss the enum statetype: {Snake,empty,food}

class Cell {
    private:
        Info info;
    public:
        Cell(Info temp);
        Info getInfo();
        void setInfo(Info s);
};


#endif