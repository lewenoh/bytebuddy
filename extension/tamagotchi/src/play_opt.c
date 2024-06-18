#include "../include/play_opt.h"
#include <ncurses.h>
#include <stdlib.h>

static int display_firstnum(int row, int col, int num1, int score){
	y = (row/2) - 4 //for num1
	x = (col/2) - 13
	//put number num1 at y, x^^
	//put ? at y = row/2 + 4 and x=col/2 + 13
	//also print score to screen
	
	keypad(stdscr, TRUE);
	refresh();
	int guess = getch();
	int result;
	if (guess == KEY_LEFT){
		result = 1; //lower
	}
	else if (guess == KEY_RIGHT){
		result = 2; //higher
	}
	else {
		result = 0; //quit game
	}

	keypad(stdscr, FALSE);
	return result;
}

void play_opt(struct stats *s, int row, int col) {
    // this function starts the game
    // increases happy by 1 if player wins
    // plays happy or sad emote
	int score = 0;
	int num1;
	int num2;
	int guess;
	for (int x=0; x < 5; x++){
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
		else if (((guess == 1) && (num2 < num1)) || ((guess == 2) && (num2 > 1))){
			score++;
			//display correct, num1, num2
		}
		else {
			//display wrong, num1, num2
		}
	
	}
	if (score > 2){
		//won game
		s->happy > 5? 5 : s->full++;
		//display happy
	}
	else{
		//display sad
	}


	return;
}
