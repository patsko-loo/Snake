#ifndef _INFO_H_
#define _INFO_H_

enum class StateType {Snake,Empty,Food};

enum class Direction {Up,Down,Left,Right,None};

struct Info{
    int row;
    int col;
    StateType statetype;
    Direction dir;
};



#endif