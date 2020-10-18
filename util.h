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

#define SAVE_FILENAME "highscore.sav"

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

void save(char* filename, char* savetype, void *data, int datasize, int amount){
    FILE *arq;
    arq = fopen(filename, savetype);
    if(!arq) printf("COULDN\'T SAVE");
    fwrite(data, datasize, amount, arq);
    fclose(arq);
}

void load(char* filename, void *data, int datasize, int amount){
    FILE *arq;
    arq = fopen(filename, "r");
    if(!arq) return;
    fread(data, datasize, amount, arq);
    fclose(arq);
}

void highscore_save(int *score, int highscore){
    if(*score > highscore) save(SAVE_FILENAME, "w", score, sizeof(int), 1);
}

int highscore_load(){
    int value = 0;
    load(SAVE_FILENAME, &value, sizeof(int), 1);
    return value;
}

#endif // UTIL_H
