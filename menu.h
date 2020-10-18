#ifndef MENU_H
#define MENU_H

#include "gfx.h"
#include "game.h"

#define MENUOPTIONS 4

void draw_menu(){
    clr();
    cursormove(0,0);
    draw_component_square(11,6,0);
    char *item[] = { "Play", "Options", "Credits", "Exit" };
    for(int count = 0; count < MENUOPTIONS; count++){
        cursormove(3, count + 3);
        printf("%s", item[count]);
    }
    cursormove(3, 1);
    printf("SNAKE C");
}

void options(){
    cursormove(0,0);
    draw_component_square(25, 18, 0);
    cursormove(1,1);
    printf("Color Editor:");
    cursormove(1,3);
    printf("Characters: Background:");

    int coord[16][2] = {}, oldcoord[2] = {};
    char *codes[] = { "39", "31", "32", "33", "34", "35", "36", "49", "41", "42", "43", "44", "45", "46"};
    char *itens[] = { "DEFAULT", "RED", "GREEN", "YELLOW", "BLUE", "PURPLE", "CYAN" };
    for(int countX = 0; countX < 2; countX++){
        for(int countY = 0; countY < 7; countY++){
            int item = countX * 7 + countY;
            coord[item][0] = 2 + countX * 12;
            coord[item][1] = 4 + countY * 2;
            cursormove(coord[item][0], coord[item][1]);
            printf("\033[100m");
            printf("\033[%sm", codes[countY + countX * 7]);
            printf("%s", itens[countY]);
            printf("\033[0m");
        }
    }

    int selection = 0, background = 0, foreground = 0, key = 0;

    while(key != KB_ESCAPE){
        cursormove(oldcoord[0], oldcoord[1]);
        printf(" ");
        cursormove(coord[selection][0] - 1, coord[selection][1]);
        printf(">");
        oldcoord[0] = coord[selection][0] - 1;
        oldcoord[1] = coord[selection][1];
        cursormove(0,0);

        key = getch();
        switch(key){
        case KB_ESCAPE:
            break;
        case KB_ARROW_DOWN:
            selection++;
            if(selection == 7 || selection == 14) selection -= 7;
            break;
        case KB_ARROW_UP:
            selection--;
            if(selection == -1 || selection == 6) selection += 7;
            break;
        case KB_ARROW_LEFT:
            if(selection > 6) selection -= 7;
            break;
        case KB_ARROW_RIGHT:
            if(selection < 7) selection += 7;
            break;
        case KB_ENTER:
            if(selection < 7) foreground = selection;
            else background = selection;
            break;
        }
    }
    printf("\033[%s;%sm", codes[foreground], codes[background]);
}

void credits(){
    clr();
    cursormove(0,0);
    draw_component_square(35,5,0);
    cursormove(2,1);
    printf("Author: github.com/daviprios");
    cursormove(2,3);
    printf("Thanks: github.com/stackOvercrow");
    cursormove(23,5);
    printf("ESC TO EXIT");

    while(1){
        if(getch() == KB_ESCAPE) break;
    }
}

void main_menu(){
    draw_menu();
    int choice = 0, lastchoice = 0, key = 0;
    while(1){
        cursormove(2, 3 + lastchoice);
        printf(" ");
        cursormove(2, 3 + choice);
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
