#ifndef MENU_H
#define MENU_H

#include "gfx.h"
#include "game.h"

#define MENUOPTIONS 4

void draw_menu(){
    clr();
    cursormove(0,0);
    draw_component_square(12,7,0);
    char *item[] = { "Play", "Options", "Credits", "Exit" };
    for(int count = 0; count < MENUOPTIONS; count++){
        cursormove(3, count + 2);
        printf("%s", item[count]);
    }
}


void main_menu(){
    draw_menu();
    int choice = 0, lastchoice = 0, key = 0;
    while(1){
        cursormove(2, 2 + lastchoice);
        printf(" ");
        cursormove(2, 2 + choice);
        printf(">");
        cursormove(0, 16);

        key = getch();
        switch(key){
        case KB_ESCAPE:
            exit(0);
            break;
        case KB_ARROW_UP:
            lastchoice = choice;
            if(--choice < 0){
                choice = MENUOPTIONS - 1;
            };
            break;
        case KB_ARROW_DOWN:
            lastchoice = choice;
            if(++choice > MENUOPTIONS - 1){
                choice = 0;
            };
            break;
        case KB_ENTER:
            switch(choice){
                case 0:
                    game();
                    break;
                case 1:
                    options();
                    break;
                case 2:
                    credits();
                    break;
                case 3:
                    exit(0);
                    break;
            }
            draw_menu();
            break;
        }
    };
}

#endif // MENU_H
