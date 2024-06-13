#include "display_tamagotchi.h"
#include <ncurses.h>
#include <string.h>
#define TAMAGOTCHI "    ******          \n ***     ***        \n**+-- %% ==** ******\n ***+    -=++*++****\n***      +*-==***   \n***        **=***   \n***++*++*++++**     \n   *=- +-+          \n"

const char *tamagotchi[] = {
        "     ******             ",
        "  ***      ***          ",
        "**+-- %%   ==**   ******",
        " ***+    -=++*  ++****  ",
        "***      +*-==*****     ",
        "***        **=***       " ,
        "***++*++*++++**         ",
        "   *=- +-+              "
};

const char*menu[] = {
        "f: food        p: play  ",
        "m: med         t: toilet",
        "________________________",
        "s: stats   q: quit & save"
};

void display_tamagotchi(int row, int col) {
    int tama_rows = sizeof(tamagotchi) / sizeof(tamagotchi[0]);
    int tama_cols = strlen(tamagotchi[0]);

    for (int i = 0; i < tama_rows; i++) {
        mvprintw(row/2 - tama_rows/2 + i, col/2 - tama_cols/2, "%s", tamagotchi[i]);
    };

    int menu_rows = sizeof(menu) / sizeof(menu[0]);
    int menu_cols = strlen(menu[0]);

    for(int i = 0; i<menu_rows; i++) {
        mvprintw((row*0.75) + i, (col / 2 - menu_cols / 2), "%s", menu[i]);
    };
}