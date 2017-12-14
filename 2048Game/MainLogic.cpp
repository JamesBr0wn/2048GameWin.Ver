//
// Created by james on 17-12-13.
//

#include "MainLogic.h"

using namespace std;

MainLogic::MainLogic(){
    memset(store, 0, SIZE*SIZE*sizeof(int));
    score = 0;
    srand((unsigned int)time(NULL));
    initscr();
    cbreak();
    nonl();
    noecho();
    intrflush(stdscr, false);
    keypad(stdscr, true);
    refresh();
}

MainLogic::~MainLogic(){
    endwin();
}

void MainLogic::start(){
    welcome();
    newEntry();
    newEntry();
    display();
    char help;
    Condition cond;
    while(true){
        help = (char)getch();
        switch(help){
            case 'w':
            case 'W':
                moveDir(Up);
                newEntry();
                display();
                break;
            case 's':
            case 'S':
                moveDir(Down);
                newEntry();
                display();
                break;
            case 'a':
            case 'A':
                moveDir(Left);
                newEntry();
                display();
                break;
            case 'd':
            case 'D':
                moveDir(Right);
                newEntry();
                display();
                break;
            case 'q':
            case 'Q':
                clear();
                return;
            default:
                beep();
                move(BEGIN_X+SIZE*3, 0);
                printw("Operation Not Permitted!");
                refresh();
        }
        cond = judge();
        if(cond != Processing){
            break;
        }
    }
    move(8, 0);
    if(cond == Win){
    	clear();
    	move(BEGIN_X, BEGIN_Y);
        printw("You Win!");
    }else{
        clear();
    	move(BEGIN_X, BEGIN_Y);
        printw("You Lose!");
    }
    getch();
}

void MainLogic::moveDir(Direction dir){
    switch(dir){
        case Up:
            moveUp();
            break;
        case Down:
            moveDown();
            break;
        case Left:
            moveLeft();
            break;
        case Right:
            moveRight();
            break;
    }
}

void MainLogic::moveUp(){
    stack<int> help;
    for(int i = 0; i < SIZE; i++){
        for(int j = SIZE-1; j >= 0; j--){
            if(store[j][i] != 0){
                help.push(store[j][i]);
            }
        }
        int k = 0;
        while(!help.empty()){
            int tempInt = help.top();
            help.pop();
            if(!help.empty() && tempInt == help.top()){
                tempInt = tempInt << 1;
                score += tempInt;
                help.pop();
            }
            store[k][i] = tempInt;
            k++;
        }
        for(int j = k; j < SIZE; j++){
            store[j][i] = 0;
        }
    }
}

void MainLogic::moveDown(){
    stack<int> help;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(store[j][i] != 0){
                help.push(store[j][i]);
            }
        }
        int k = SIZE-1;
        while(!help.empty()){
            int tempInt = help.top();
            help.pop();
            if(!help.empty() && tempInt == help.top()){
                tempInt = tempInt << 1;
                score += tempInt;
                help.pop();
            }
            store[k][i] = tempInt;
            k--;
        }
        for(int j = k; j >= 0; j--){
            store[j][i] = 0;
        }
    }
}

void MainLogic::moveLeft(){
    stack<int> help;
    for(int i = 0; i < SIZE; i++){
        for(int j = SIZE-1; j >= 0; j--){
            if(store[i][j] != 0){
                help.push(store[i][j]);
            }
        }
        int k = 0;
        while(!help.empty()){
            int tempInt = help.top();
            help.pop();
            if(!help.empty() && tempInt == help.top()){
                tempInt = tempInt << 1;
                score += tempInt;
                help.pop();
            }
            store[i][k] = tempInt;
            k++;
        }
        for(int j = k; j < SIZE; j++){
            store[i][j] = 0;
        }
    }
}

void MainLogic::moveRight(){
    stack<int> help;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(store[i][j] != 0){
                help.push(store[i][j]);
            }
        }
        int k = SIZE-1;
        while(!help.empty()){
            int tempInt = help.top();
            help.pop();
            if(!help.empty() && tempInt == help.top()){
                tempInt = tempInt << 1;
                score += tempInt;
                help.pop();
            }
            store[i][k] = tempInt;
            k--;
        }
        for(int j = k; j >= 0; j--){
            store[i][j] = 0;
        }
    }
}

Condition MainLogic::judge(){
    bool full = true;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(store[i][j] == 0){
                full = false;
            }else if(store[i][j] == 2048){
                return Win;
            }
        }
    }
    if(full){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE-1; j++){
                if(store[i][j] == store[i][j+1]){
                    return Processing;
                }
            }
        }
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE-1; j++){
                if(store[j][i] == store[j+1][i]){
                    return Processing;
                }
            }
        }
        return Lose;
    }else{
        return Processing;
    }
}

void MainLogic::newEntry(){
    vector<pair<int, int> > help;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(store[i][j] == 0){
                help.push_back(pair<int, int>(i,j));
            }
        }
    }
    if(help.empty()){
        return;
    }
    unsigned int place = rand() % help.size();
    srand(rand());
    store[help[place].first][help[place].second] = 2;
}

void MainLogic::display(){
    clear();
    char help[8];
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            move(BEGIN_X+i*3, BEGIN_Y+j*4);
            if(store[i][j] != 0){
                sprintf_s(help,"%4d", store[i][j]);
                printw(help);
            }else{
                printw("   ");
                attron(A_REVERSE);
                printw(" ");
                attroff(A_REVERSE);
            }
        }
    }
    move(BEGIN_X+SIZE*3, 0);
    sprintf_s(help, "%d", score);
    printw("Score:\t%s", help);
    refresh();
}

void MainLogic::welcome(){
    move(BEGIN_X, BEGIN_Y);
    printw("////////////////////////////////////////////////////////////////////////////////\n");
    printw("////////////////////////////////////////////////////////////////////////////////\n");
    printw("///////::-----:://////////::-----::///////////////:::::////////::-----::////////\n");
    printw("/////-``        `-//////-`        `.:////////////-`    ://///:.`        `.://///\n");
    printw("////:`   `...`    -////.    `--.`   `://///////:.      :////:`   .----`   .:////\n");
    printw("//////:-:////:`   .///-    -////:.   `:///////-`  `    :////-   `:////-   `:////\n");
    printw("/////////////-    -///.   `://///-   `://///:.   .:`   :////:.   `-:-.`  `-/////\n");
    printw("///////////:.    .////.   .//////:`   -////-`  `-/:`   ://////-`       `-://////\n");
    printw("/////////:-`   `-/////.   .//////:`   -//:.   .://:`   :////:-`   `..`  `.://///\n");
    printw("///////:-`   `-///////.   `://///-   `:/:`   .-----`   .-://.   `:////-`  `-////\n");
    printw("/////:.`  `.://///////:    -////:`   `:/:                ./:`   -/////:`   .////\n");
    printw("////-     `````````:///-    `.-.`   `://:----------`   .-://-    .----`   `:////\n");
    printw("////.              -////:.`       `.://///////////:`  `://///-.`        `.://///\n");
    printw("////:::::::::::::::///////::----:://///////////////::::////////:::----::////////\n");
    printw("////////////////////////////////////////////////////////////////////////////////\n");
    printw("////////////////////////////////////////////////////////////////////////////////\n");
    printw("-----------------------Press Any Key To Continue--------------------------------\n");
    refresh();
    getch();
    clear();
    refresh();
}

