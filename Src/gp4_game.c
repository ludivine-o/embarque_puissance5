#include "gp4_game.h"


static int8_t g_token_top_selector = 0;
int8_t active_player = NO_PLAYER;
static int8_t g_matrix[LINE_COUNT][COL_COUNT];
//static bool game = false;


Color Black = { 0, 0, 0 }, Blue = { 0, 0, 255 }, Red = { 255, 0, 0 }, White = {
		255, 255, 255 }, Purple = { 255, 0, 255 }, Yellow = { 255, 255, 0 },
		Green = { 0, 255, 0 };


//static void gp4_show_board(void) {
//	debug_printf(1, "Affichage de la matrice complete\n");
//	top_line_display();
//	matrix_lines_display();
//	printf("\n");
//}

bool gp4_is_col_empty(int col) {
	if (col < 0) {
		return false;
	}
	if (col >= COL_COUNT) {
		return false;
	}
	if (g_matrix[col][0] == 0) {
		return true;
	}
	return false;
}

data_msg gp4_init(void) {
	int row, col;
	data_msg instructions_to_send;
	active_player = PLAYER_1;
	g_token_top_selector = START_POSITION;
	for (row = 0; row < 6; row++) {
		for (col = 0; col < 7; col++) {
			g_matrix[row][col] = NO_PLAYER;
		}
	}
	instructions_to_send.params.player.player = PLAYER_1;
	instructions_to_send.type = MSG_MOVE_TOKEN;
	instructions_to_send.params.move_token.positions.end_position.c =
			START_POSITION;
	instructions_to_send.params.move_token.positions.end_position.l = 0;
	instructions_to_send.params.move_token.color = color_P1;
	return instructions_to_send;
}

pos_token_t gp4_move_right_test(void) {
	int direction = +1;
	int destination;
	pos_token_t return_moved_token;
	return_moved_token.beg_position.c = g_token_top_selector;
	return_moved_token.beg_position.l = 0;
	return_moved_token.end_position.l = 0;
	destination = g_token_top_selector + direction;
	while (1) {
		if (destination >= COL_COUNT) {
			destination = 0;
		}
		if (gp4_is_col_empty(destination) == true) {
			g_token_top_selector = destination;
			return_moved_token.end_position.c = g_token_top_selector;
			return_moved_token.is_ok = true;
			return return_moved_token;
		}
		destination++;
	}
	//TO FIX : attention risque de while infini
}

pos_token_t gp4_move_left_test(void) {
	int direction = -1;
	pos_token_t return_moved_token;
	return_moved_token.beg_position.c = g_token_top_selector;
	return_moved_token.beg_position.l = 0;
	return_moved_token.end_position.l = 0;
	int destination = g_token_top_selector + direction;
	while (1) {
		if (destination < 0) {
			destination = 6;
		}
		if (gp4_is_col_empty(destination) == true) {
			g_token_top_selector = destination;
			return_moved_token.end_position.c = destination;
			return_moved_token.is_ok = true;
			return return_moved_token;
		}
		destination--;
	}
	//TOFIX : attention risque de while infini
}

//TODO : faire une fonction mixte (qui prend en parma un enum left = -1, right = +1)

pos_token_t gp4_play_token(void) {
	int column = g_token_top_selector;
	int line = 5;	//ou LINE_COUNT-1
	while (g_matrix[column][line] != 0) {
		line--;
	}
	g_matrix[(column)][line] = active_player;
	pos_token_t return_played_token = { 0 };
	return_played_token.is_ok = true;
	return_played_token.beg_position.c = column;
	return_played_token.beg_position.l = 0;
	return_played_token.end_position.c = column;
	return_played_token.end_position.l = line + 1;
	return return_played_token;
}

winner_t gp4_check_win_vertical(void) {
	winner_t game_status = { .status = live };
	for (int line = 0; line < 7; line++) {
		for (int col = 0; col < 7; col++) {
			//for (int col = 0; col < 4; col++) {
			if ((g_matrix[line][col] == g_matrix[line][col + 1])
					&& (g_matrix[line][col] == g_matrix[line][col + 2])
					&& (g_matrix[line][col] == g_matrix[line][col + 3])
					&& (g_matrix[line][col] != 0)) {
				game_status.status = stop_winner;
				game_status.win_type = vert;
				if (g_matrix[line][col] == 1) {
					game_status.win_player = PLAYER_1;
					return game_status;
				} else {
					game_status.win_player = PLAYER_2;
					return game_status;
				}
			}

		}
	}
	return game_status;
}

winner_t gp4_check_win_horizontal(void) {
	winner_t game_status = { .status = live };
	for (int col = 0; col < 7; col++) {
		for (int line = 0; line < 7; line++) {
			//for (int line = 0; line < 3; line++) {
			if (g_matrix[line][col] == g_matrix[line + 1][col]) {
				if (g_matrix[line][col] == g_matrix[line + 2][col]) {
					if (g_matrix[line][col] == g_matrix[line + 3][col]) {
						if (g_matrix[line][col] != 0) {
							game_status.status = stop_winner;
							game_status.win_type = horiz;
							if (g_matrix[line][col] == 1) {
								game_status.win_player = PLAYER_1;
								return game_status;
							} else {
								game_status.win_player = PLAYER_2;
								return game_status;
							}
						}
					}
				}
			}
		}
	}
	return game_status;
}

winner_t gp4_check_win_rightdiag(void) {
	winner_t game_status;
	game_status.status = live;
	int col, line;
	//for (line = 0; line < 3; line++) {
	for (col = 0; col < 7; col++) {
		for (line = 0; line < 7; line++) {
			//for (col = 0; col < 4; col++) {
			if (g_matrix[line][col] == g_matrix[line + 1][col + 1]) {
				if (g_matrix[line][col] == g_matrix[line + 2][col + 2]) {
					if (g_matrix[line][col] == g_matrix[line + 3][col + 3]) {
						if (g_matrix[line][col] != 0) {
							game_status.status = stop_winner;
							game_status.win_type = right_diag;
							if (g_matrix[line][col] == 1) {
								game_status.win_player = PLAYER_1;
								return game_status;
							} else {
								game_status.win_player = PLAYER_2;
								return game_status;
							}
						}
					}
				}
			}
		}
	}
	return game_status;
}

winner_t gp4_check_win_leftdiag(void) {
	winner_t game_status;
	game_status.status = live;
	int col, line;
	//for (col = 3; col < 7; col++) {
	for (col = 0; col < 7; col++) {
		//for (line = 0; line < 3; line++) {
		for (line = 0; line < 7; line++) {
			if (g_matrix[line][col] == g_matrix[line - 1][col - 1]) {
				if (g_matrix[line][col] == g_matrix[line - 2][col - 2]) {
					if (g_matrix[line][col] == g_matrix[line - 3][col - 3]) {
						if (g_matrix[line][col] != 0) {
							game_status.status = stop_winner;
							game_status.win_type = left_diag;
							if (g_matrix[line][col] == 1) {
								game_status.win_player = PLAYER_1;
								return game_status;
							} else {
								game_status.win_player = PLAYER_2;
								return game_status;
							}

						}
					}
				}
			}
		}
	}
	return game_status;
}

winner_t gp4_check_equal(void) {
	winner_t game_status = { .status = live };
	int compteur = 0;
	for (int col = 0; col < 7; col++) {
		if (!gp4_is_col_empty(col)) {
			compteur++;
		}
	}
	if (compteur == 6) {
		game_status.status = stop_equal;
	}
	return game_status;
}

winner_t gp4_check_status(void) {
	winner_t game_status;
	game_status = gp4_check_equal();
	if (game_status.status == live) {
		game_status = gp4_check_win_horizontal();
	}
	if (game_status.status == live) {
		game_status = gp4_check_win_vertical();
	}
	if (game_status.status == live) {
		game_status = gp4_check_win_rightdiag();
	}
	if (game_status.status == live) {
		game_status = gp4_check_win_leftdiag();
	}
	return game_status;
}

pos_token_t gp4_next_playerV2(void) {
	pos_token_t pos_token_top = { 0 };
	pos_token_top.end_position.l = 0;

	if (active_player == PLAYER_1) {
		active_player = PLAYER_2;
	} else {
		active_player = PLAYER_1;
	}
	g_token_top_selector = START_POSITION;
	//TODO : verifier si la colonne est vide

	while (g_matrix[g_token_top_selector][0] != EMPTY_SPACE) {
		g_token_top_selector += 1;
		if (g_token_top_selector > (COL_COUNT - 1)) {
			g_token_top_selector = EMPTY_SPACE;
		} else if (g_token_top_selector < 0) {
			g_token_top_selector = COL_COUNT - 1;
		}

		//while (!gp4_is_col_empty(g_token_top_selector)) {
		//pos_token_top = gp4_move_right_test();
		//}
	}
	pos_token_top.end_position.c = g_token_top_selector;
	return pos_token_top;
}

