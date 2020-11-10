/*
 * application.c
 *
 *  Created on: Oct 15, 2020
 *      Author: ludivineo
 */

#include "gp4_game.h"
#include "messages.h"
#include "application.h"
#include "__debug.h"

//static int8_t g_token_top_selector = 0;
extern int8_t active_player;
//static int8_t g_matrix[COL_COUNT][LINE_COUNT];
static bool game = false;

static data_msg write_msg_to_send(pos_token_t played_token) {
	data_msg instructions_to_send = { 0 };
	instructions_to_send.type = MSG_MOVE_TOKEN;
	instructions_to_send.params.move_token.positions = played_token;
	if (active_player == PLAYER_1) {
		instructions_to_send.params.move_token.color = color_P1;
	}
	if (active_player == PLAYER_2) {
		instructions_to_send.params.move_token.color = color_P2;
	}
	return instructions_to_send;
}

static inline void SendNewTokenToDisplay(pos_token_t played_token) {
	data_msg instructions_to_send = write_msg_to_send(played_token);
	SendMessage(LIST_DISPLAY, &instructions_to_send, sizeof(data_msg));
}


static void instructions_MSG_PLAYER(data_msg received_instructions) {
	winner_t game_status = { 0 };
	pos_token_t played_token = { 0 };
	//---------------------------------------------si partie en cours--------------------------------//
	if (received_instructions.params.player.player
			== active_player&& game == true) {
		debug_printf(1, "app()entrée dans le coeur de jeu\n");
//		stop_timer(IDLE_TIMER);
		if (received_instructions.params.player.direction == LEFT) {
			played_token = gp4_move_left_test();
//			start_timer(IDLE_TIMER, 5, Thrd_APP);
		}
		if (received_instructions.params.player.direction == RIGHT) {
			played_token = gp4_move_right_test();
//			start_timer(IDLE_TIMER, 5, Thrd_APP);
		}
		if (received_instructions.params.player.direction == DOWN) {
//			stop_timer(ROUND_TIMER);
			played_token = gp4_play_token();
			SendNewTokenToDisplay(played_token);
			game_status = gp4_check_status();
			if (game_status.status == live) {
				played_token = gp4_next_playerV2();
//				start_timer(ROUND_TIMER, 15, Thrd_APP);
//				start_timer(IDLE_TIMER, 5, Thrd_APP);
			}
			if (game_status.status == stop_winner) {
				game = 0;
//				stop_timer(ROUND_TIMER);
//				stop_timer(IDLE_TIMER);
			}
		}
		SendNewTokenToDisplay(played_token);

	}
	//------------------------------------------si pas de partie en cours---------------------------//
	if (active_player == NO_PLAYER) {
		data_msg instructions_to_send = gp4_init();
		game = 1;

		debug_printf(1, "player = %d\n", active_player);
		SendMessage(LIST_DISPLAY, &instructions_to_send, sizeof(data_msg));

		//-----------------------lancement des timers (Round timer + idle timer) --------//
//		start_timer(ROUND_TIMER, 15, Thrd_APP); 	//15 secondes ?
//		start_timer(IDLE_TIMER, 5, Thrd_APP);		//5 secondes ?
	}
	//------------------------------------------si partie finie---------------------------//
	if (active_player != NO_PLAYER && game == false) {
		data_msg instructions_to_send;
//		//--------------------------------victory blink-----------------------------------//
//		if (game_status.status == stop_winner){
//			instructions_to_send.type = MSG_VICTORY;
//			instructions_to_send.params.victory = game_status;
//			SendMessage(LIST_DISPLAY, &instructions_to_send, sizeof(data_msg));
//		}
		//--------------------------------Arret du jeu-----------------------------------//
		instructions_to_send.type = MSG_DISPLAY_OFF;
		SendMessage(LIST_DISPLAY, &instructions_to_send, sizeof(data_msg));
		active_player = NO_PLAYER;
	}
}

//----------------------------si fin d'un timer-------------------------//
void instructions_MSG_TIMER(data_msg received_instructions) {
//	pos_token_t played_token = { 0 };
//	if (received_instructions.params.timer_id == ROUND_TIMER
//			|| received_instructions.params.timer_id == IDLE_TIMER) {
//		played_token = gp4_play_token();
//		SendNewTokenToDisplay(played_token);
//		winner_t game_status = gp4_check_status();
//		if (game_status.status == live) {
//			played_token = gp4_next_playerV2();
////			start_timer(IDLE_TIMER, 5, Thrd_APP);
////			start_timer(ROUND_TIMER, 15, Thrd_APP);
//		}
//	}
//	SendNewTokenToDisplay(played_token);
//	gp4_show_board();
}


void * applicationV2(void) {
	debug_pr_fn(1, "app()entrée dans thread app\n");
	int receive_status = 0;
	pos_token_t played_token = { 0 };
	winner_t game_status = { 0 };
	while (1) {
		//---------------------------------------------...............--------------------------------------//
		data_msg received_instructions = INIT_DATA_MSG;
		debug_printf(1, "app()entrée dans while thread app\n");
		receive_status = ReceiveMessage(LIST_READ, &received_instructions, sizeof(data_msg));
		debug_printf(1, "app()receive msg status : %d\n", receive_status);
		if (receive_status == 1) {
			//-------------------------------------si saisie clavier (fleche simu)------------------------------//
			if (received_instructions.type == MSG_PLAYER) {
				instructions_MSG_PLAYER(received_instructions);
			}
			//-------------------------------------si retour du timer-------------------------------------------//
			if (received_instructions.type == MSG_TIMER) {
				instructions_MSG_TIMER(received_instructions);
			}
		}
	}
}
