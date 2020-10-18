#ifndef GAME_H
#define GAME_H

#include "gfx.h"
#include <time.h>

#define HEIGHT 20
#define WIDTH 40
#define OFFSET 1
#define FRAMERATE 150
#define INITIAL_SIZE 3

void handle_win(){
    cursormove(0, 23);
    printf("YOU WON\n");
    system("pause");
}

void handle_lose(){
    cursormove(0, 23);
    printf("YOU LOSE\n");
    system("pause");
}

void random(int *number, int minimum, int maximum){
    *number = (rand() % maximum) + minimum;
}

void food_create(int body[HEIGHT*WIDTH][2], int length, int food[2]){
    cursormove(WIDTH + 3, 3);
    printf("%d - %d     ", food[0], food[1]);

    int position[2] = {};
    int verifybody = 1;
    do{
        random(&position[0], OFFSET, WIDTH);
        random(&position[1], OFFSET, HEIGHT);
        for(int count = 0; count < length; count++){
            if(food[0] == body[count][0] || food[1] == body[count][1]){
                verifybody = 1;
                break;
            }
            verifybody--;
        }
    }while(verifybody);
    food[0] = position[0];
    food[1] = position[1];
    cursormove(food[0], food[1]);
    printf("X");
}

int food_eat(int moviment[2], int food[2], int *length, int body[HEIGHT*WIDTH][2]){
    if(moviment[0] == food[0] && moviment[1] == food[1]){
        ++*length;
        food[0] = 0;
        food[1] = 0;
        food_create(body, *length, food);
        return 1;
    }
    return 0;
}

int verifyalive(int head[2], int body[HEIGHT*WIDTH][2], int length){
    if(head[0] == 0 || head[0] == (OFFSET * 2 + WIDTH) || head[1] == 0 || head[1] == (OFFSET * 2 + HEIGHT)) return 0;
    for(int count = 1; count < length; count++)
        if(head[0] == body[count][0] && head[1] == body[count][1]) return 0;
    return 1;
}

void ajustbody(int body[HEIGHT*WIDTH][2], int length, int moviment[2]){
    int temp1[] = { moviment[0], moviment[1] }, temp2[2] = {};
    for(int count = 0; count < length; count++){
        temp2[0] = body[count][0];
        temp2[1] = body[count][1];
        body[count][0] = temp1[0];
        body[count][1] = temp1[1];
        temp1[0] = temp2[0];
        temp1[1] = temp2[1];
    }
    moviment[0] = temp1[0];
    moviment[1] = temp1[1];
}

void handlecontrol(int direction, int *changedirection){
    int newdirection = getch();
    if((newdirection == KB_ARROW_DOWN || newdirection == KB_ARROW_LEFT || newdirection == KB_ARROW_RIGHT || newdirection == KB_ARROW_UP)){
        if((direction == KB_ARROW_DOWN && newdirection == KB_ARROW_UP)
         || (direction == KB_ARROW_UP && newdirection == KB_ARROW_DOWN)
         || (direction == KB_ARROW_LEFT && newdirection == KB_ARROW_RIGHT)
         || (direction == KB_ARROW_RIGHT && newdirection == KB_ARROW_LEFT))
            return;
        else *changedirection = newdirection;
    }
}

void game(){
    clr();

    clock_t start, stop;
    int time = 0;

    int direction = KB_ARROW_DOWN, changedirection = KB_ARROW_DOWN;
    int length = INITIAL_SIZE, body[HEIGHT*WIDTH][2] = {}, newmove[2] = {};
    int alive = 1, food[2] = {};
    int score = 0;

    draw_component_square(WIDTH + 1, HEIGHT + 1, 0);
    for(int count = 0; count < INITIAL_SIZE; count++){
        body[count][0] = WIDTH/2;
        body[count][1] = HEIGHT/2 - count;
    }
    food_create(body, length, food);

    while(alive){
        start = clock();
        if(kbhit()) handlecontrol(direction, &changedirection);
        if(time > FRAMERATE){
            direction = changedirection;
            if(direction == KB_ARROW_DOWN || direction == KB_ARROW_UP || direction == KB_ARROW_RIGHT || direction == KB_ARROW_LEFT){
                newmove[0] = body[0][0];
                newmove[1] = body[0][1];
                switch(direction){
                    case KB_ARROW_UP:
                        newmove[1] = body[0][1] - 1;
                        break;
                    case KB_ARROW_RIGHT:
                        newmove[0] = body[0][0] + 1;
                        break;
                    case KB_ARROW_DOWN:
                        newmove[1] = body[0][1] + 1;
                        break;
                    case KB_ARROW_LEFT:
                        newmove[0] = body[0][0] - 1;
                        break;
                }
                alive = verifyalive(newmove, body, length);
                score += food_eat(newmove, food, &length, body);
                ajustbody(body, length, newmove);
            }
            if(alive){
                draw_snake(body[0], length, newmove, food);
                time -= FRAMERATE;
            }
            cursormove(WIDTH + 3, 1);
            printf("Score: %d", score);
            cursormove(0,0);
        }
        stop = clock();
        time += stop - start;
    }

    if(score == HEIGHT * WIDTH - INITIAL_SIZE) handle_win();
    else handle_lose();
}

#endif // GAME_H
