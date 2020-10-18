#ifndef GFX_H
#define GFX_H
#include "util.h"

#define $UR 192
#define $UD 179
#define $UL 217
#define $RD 218
#define $RL 196
#define $DL 191
#define $URD 195
#define $URL 193
#define $UDL 180
#define $RDL 194
#define $URDL 197

#define _UR 200
#define _UD 186
#define _UL 188
#define _RD 201
#define _RL 205
#define _DL 187
#define _URD 204
#define _URL 202
#define _UDL 185
#define _RDL 203
#define _URDL 206

#define $CHARACTER 219

void draw_component_square(int width, int height, int doubled){
    int ur = 0, dl = 0, rd = 0, ul = 0, ud = 0, rl = 0;

    if(!doubled){
        ur = $UR; dl = $DL; rd = $RD; ul = $UL; ud = $UD; rl = $RL;
    }else{
        ur = _UR; dl = _DL; rd = _RD; ul = _UL; ud = _UD; rl = _RL;
    }

    cursormove(0,0);
    printf("%c",rd);
    for(int count = 0; count < width; count++){
        printf("%c", rl);
    }
    printf("%c\n",dl);


    for(int count = 0; count < height; count++){
        printf("%c",ud);
        for(int count = 0; count < width; count++){
            printf(" ");
        }
        printf("%c\n",ud);
    }

    printf("%c",ur);
    for(int count = 0; count < width; count++){
        printf("%c", rl);
    }
    printf("%c\n",ul);
}

void draw_snake(int head[2], int length, int tail[2], int food[2]){
    cursormove(head[0], head[1]);
    printf("%c", $CHARACTER);
    cursormove(tail[0], tail[1]);
    if(food[0] == tail[0] && food[1] == tail[1]) printf("X");
    else printf(" ");
}

#endif // GFX_H
