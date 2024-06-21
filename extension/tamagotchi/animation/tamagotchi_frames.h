//
// Created by xth23 on 17/06/24.
//

#ifndef TAMAGOTCHI_FRAMES_H
#define TAMAGOTCHI_FRAMES_H

extern char *tamagotchi[7][9];
extern int tama_rows;
extern int tama_cols;

extern char *reversed_tamagotchi[2][9];
extern char *question_bubble[3];
extern char *correct_emote[4];
extern char *wrong_emote[4];

extern char *food_options[2][6];

void initialise_tamagotchi();

/*char *tamagotchi[4][8] = {
        {
                "     ******             ",
                "  ***      ***          ",
                "**+-- %%   ==**   ******",
                " ***+    -=++*  ++****  ",
                "***      +*-==*****     ",
                "***        **=***       ",
                " **++*++*++++**         ",
                "   *=- +-+              "
        },
        {
                "     ******             ",
                "  ***      ***          ",
                "**+-- --   ==**         ",
                " ***+    -=++*          ",
                "***      +*-==********  ",
                "***        **=** ++*****",
                " **++*++*++++**         ",
                "   *=- +-+              "
        },
        // sick states
        {
                "                        ",
                "     ******             ",
                "  ***      ***          ",
                "**+-- -<    ==**        ",
                "  **+    -=++*          ",
                " **      +*-==********  ",
                " **        **=** ++*****",
                "   ++*++*++++**         ",
        },
        {
                "                        ",
                "     ******             ",
                "  ***      ***          ",
                "**+-- __    ==**        ",
                " ***+    -=++*          ",
                "***      +*-==********  ",
                "***        **=** ++*****",
                " **++*++*++++**         ",

        }
};*/

#endif //TAMAGOTCHI_FRAMES_H
