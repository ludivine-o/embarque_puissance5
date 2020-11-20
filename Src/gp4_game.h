/*
 * app.h
 *
 *  Created on: Apr 15, 2020
 *      Author: ludivineo
 */

#ifndef GP4_GAME_H_
#define GP4_GAME_H_

#include <stdbool.h>
#include <stdint.h>

#include "messages.h"


#define COL_COUNT 7		//il y a 7 colonnes (de 0 à 6)
#define LINE_COUNT 6	//il y a 6 lignes (de 0 à 5)
#define START_POSITION 3

#define color_P1 Red
#define color_P2 Green
#define EMPTY_SPACE 0

//typedef enum {
//	input_KEY,
//	output_LED,
//	trigger_TIMER,
//}cmd_t;



extern Color Black, Red, Green, Blue, White, Purple, Yellow;


struct Element {
	data_msg data;
	struct Element *next_p;
};

#define MSGSIZE sizeof(data_msg)


bool gp4_is_col_empty(int col);
data_msg gp4_init(void);
pos_token_t gp4_move_right_test(void);
pos_token_t gp4_move_left_test(void);
pos_token_t gp4_play_token(void);
winner_t gp4_check_win_vertical(void);
winner_t gp4_check_win_horizontal(void);
winner_t gp4_check_win_rightdiag(void);
winner_t gp4_check_win_leftdiag(void);
winner_t gp4_check_equal(void);
winner_t gp4_check_status(void);
pos_token_t gp4_next_playerV2(void);
int8_t get_active_player ();



//typedef enum {
//	MSG_NONE,
//	MSG_PLAYER,
//	MSG_MOVE_TOKEN,
//	MSG_TIMER,
//	MSG_DISPLAY_OFF,
//	MSG_VICTORY,
//} MessageType;



#endif /* GP4_GAME_H_ */
