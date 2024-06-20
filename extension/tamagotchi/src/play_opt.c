#include "../include/play_opt.h"
#include "../include/stats_def.h"
#include "../include/happy_emote.h"
#include "../animation/tamagotchi_frames.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define QUESTION_MARK "?"
#define SCOREBUT_LENGTH 10
#define EMOTE_ROWS 4

void print_instructions(int row, int col) {
    char header[3][30] = {
            "Guess if ? is higher or lower",
            "using up or down arrow keys. ",
            "To exit, press any key.      "};
    for( int i = 0; i < 3; i ++){
        mvprintw(2+i, (col-30)/2, "%s", header[i]);
    }
    refresh();
}

static int display_firstnum(int row, int col, int num1, int score){
    int all_start_row = (row/2) - 10;
    int num1_start_col = (col/2) - 13;
	// y = (row/2) - 4 //for num1
    // x = (col/2) - 13
	//put number num1 at y, x^^
	//put ? at y = row/2 + 4 and x=col/2 + 13
	//also print score to screen

    int question_start_col = col/2 + 13;

    char scorebuf[SCOREBUT_LENGTH];
    snprintf(scorebuf, SCOREBUT_LENGTH, "Score: %d", score);

    mvprintw(all_start_row, num1_start_col, "%d", num1);
    mvprintw(all_start_row, question_start_col, "%s", QUESTION_MARK);
    mvprintw(row - 1, (col - strlen(scorebuf))/2, "%s", scorebuf);
    mvprintw(row, col, "%s", tamagotchi[0][4]);
    refresh();
	keypad(stdscr, TRUE);

	int guess = getch();
	int result;
	if (guess == KEY_DOWN){
		result = 1; //lower
	}
	else if (guess == KEY_UP){
		result = 2; //higher
	}
	else {
		result = 0; //quit game
	}

	keypad(stdscr, FALSE);
	return result;
}

static void display_both_numbers(int row, int col, int num1, int num2) {
    int all_start_row = (row/2) - 4;
    int num1_start_col = (col/2) - 13;
    int num2_start_col = col/2 + 13;

    mvprintw(all_start_row, num1_start_col, "%d", num1);
    mvprintw(all_start_row, num2_start_col, "%d", num2);
    refresh();
}

void print_thinking_tama(int row, int col, int tama_rows, int tama_cols) {
    int tama_start_row = (row - tama_rows)/2;
    for( int i = 0; i < tama_rows; i++) {
        mvprintw(tama_start_row + i, (col - tama_cols)/2, "%s", reversed_tamagotchi[1][i]);
    }
    int emote_start_row = (row - tama_rows)/2 + 4;
    int emote_start_col = (col + tama_cols) / 2 + 1;
    int question_rows = sizeof(question_bubble)/sizeof(question_bubble[0]);
    for( int i = 0; i < question_rows; i++) {
        mvprintw(emote_start_row + i, emote_start_col, "%s", question_bubble[i]);
    }
    refresh();
}

void print_emote_tama(int row, int col, int tama_rows, int tama_cols, char *emotion[4]) {
    int tama_start_row = (row - tama_rows)/2;
    for( int i = 0; i < tama_rows; i++) {
        mvprintw(tama_start_row + i, (col - tama_cols)/2, "%s", reversed_tamagotchi[0][i]);
    }
    int emote_start_row = (row - tama_rows)/2 + 4;
    int emote_start_col = (col + tama_cols) / 2 + 1;

    for( int i = 0; i < EMOTE_ROWS; i ++) {
        mvprintw(emote_start_row + i, emote_start_col, "%s", emotion[i]);
    }

}

void play_opt(struct stats *s, int row, int col) {
    clear();
    print_instructions(row, col);
    int tama_rows = sizeof(tamagotchi[0]) / sizeof(tamagotchi[0][0]);
    int tama_cols = strlen(tamagotchi[0][0]);
    // this function starts the game
    // increases happy by 1 if player wins
    // plays happy or sad emote

	int score = 0;
	int num1;
	int num2;
	int guess;
	for (int x=0; x < 5; x++){
        print_thinking_tama(row, col, tama_rows, tama_cols);
		srand(time(NULL));
		num1 = (rand() % 9) + 1;
		num2 = (rand() % 9) + 1;
		if (num1 == num2){
			if (num2 == 9){
				num2 --;
			}
			else{
				num2 ++;
			}
		}
		guess = display_firstnum(row, col, num1, score);
		//display tamagotchi with random number on left, ? on right
		//get return val
		if (guess == 0){
			return;
		}
		else if (((guess == 1) && (num2 < num1)) || ((guess == 2) && (num2 > num1))){
			score++;
            display_both_numbers(row, col, num1, num2);
            print_emote_tama(row, col, tama_rows, tama_cols, correct_emote);
            refresh();
            sleep(2);
            clear();
			//display correct, num1, num2
		}
		else {
            display_both_numbers(row, col, num1, num2);
            print_emote_tama(row, col, tama_rows, tama_cols, wrong_emote);
            refresh();
            sleep(2);
            clear();
			//display wrong, num1, num2
		}
	
	}
	if (score > 2){
		//won game
		s->happy > 5? 5 : s->full++;
        int tama_start_row = (row - tama_rows)/2;
        for( int i = 0; i < tama_rows; i++) {
            mvprintw(tama_start_row + i, (col - tama_cols)/2, "%s", tamagotchi[4][i]);
        }
        happy_emote(row, col);
		//display happy
	}
	else{
		//display sad
	}


	return;
}
