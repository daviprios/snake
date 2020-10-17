#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define KB_SPACE 32
#define KB_ESCAPE 27
#define KB_ENTER 13
#define KB_ARROW_UP 72
#define KB_ARROW_RIGHT 77
#define KB_ARROW_DOWN 80
#define KB_ARROW_LEFT 75

#if __unix__
void cursormove(int x, int y){
    printf("\033[%d;%dH", y, x);
}
#endif // __unix__

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
void cursormove(int x, int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}
#endif // _WIN32

void clr(){
    system("cls");
}

void save(char* filename, void *data, int datasize){
}

void load(char* filename, void *data, int datasize){
}

#endif // UTIL_H
