//
// Created by james on 17-12-13.
//
#include <iostream>
#include <stack>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "curses.h"
#define SIZE 4
#define BEGIN_X 0
#define BEGIN_Y 0
#ifndef MAIN_LOGIC_H
#define MAIN_LOGIC_H
enum Direction{
    Up, Down, Left, Right
};

enum Condition{
    Processing, Win, Lose
};

class MainLogic{
public:
    MainLogic();
    ~MainLogic();
    void start();
private:
    void moveDir(Direction dir);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void newEntry();
    void display();
    void welcome();
    Condition judge();

    int store[SIZE][SIZE];
    int score;
};

#endif