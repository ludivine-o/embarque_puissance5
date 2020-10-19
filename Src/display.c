/*
 * display.c
 *
 *  Created on: Apr 15, 2020
 *      Author: ludivineo
 */

#include<pthread.h>
#include <unistd.h>



#include "__debug.h"
#include "gp4_game.h"
#include "messages.h"
#include "leds_control.h"


extern Color Black, Red, Green, Blue, White, Purple, Yellow;


static Color matrix[LINE_COUNT + 1][COL_COUNT];
static Color actual_matrix[LINE_COUNT + 1][COL_COUNT];
static bool is_matrix_init = false;



void matrix_to_nbr(int number, Color nbr_color, Color bckgrnd_color) {
	int row, col;
	for (row = 0; row < 7; row++) {
		for (col = 0; col < 7; col++) {
			if (number == 1) { /*Ensemble de conditions pour afficher le chiffre 1*/
				if ((col == 4) || (row == 3 && col == 1)
						|| (row == 2 && col == 2) || (row == 1 && col == 3)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
			if (number == 2) { /*Ensemble de conditions pour afficher le chiffre 2*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 1 && col == 5) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 1)
						|| (row == 5 && col == 1) || (row == 6 && col == 2)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
			if (number == 3) { /*Ensemble de conditions pour afficher le chiffre 3*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 1 && col == 5) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 5)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 5 && col == 1)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
			if (number == 4) { /*Ensemble de conditions pour afficher le chiffre 4*/
				if ((row == 0 && col == 4) || (row == 1 && col == 3)
						|| (row == 1 && col == 4) || (row == 2 && col == 2)
						|| (row == 2 && col == 4) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 4) || (row == 5 && col == 4)
						|| (row == 6 && col == 4)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
			if (number == 5) { /*Ensemble de conditions pour afficher le chiffre 5*/
				if ((row == 0 && col == 1) || (row == 0 && col == 2)
						|| (row == 0 && col == 3) || (row == 0 && col == 4)
						|| (row == 0 && col == 5) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 5)
						|| (row == 5 && col == 5) || (row == 6 && col == 1)
						|| (row == 6 && col == 2) || (row == 6 && col == 3)
						|| (row == 6 && col == 4)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}

			if (number == 6) { /*Ensemble de conditions pour afficher le chiffre 6*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 1)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
			if (number == 7) { /*Ensemble de conditions pour afficher le chiffre 7*/
				if ((row == 0 && col == 1) || (row == 0 && col == 2)
						|| (row == 0 && col == 3) || (row == 0 && col == 4)
						|| (row == 0 && col == 5) || (row == 1 && col == 5)
						|| (row == 2 && col == 5) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 5) || (row == 5 && col == 5)
						|| (row == 6 && col == 5)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
			if (number == 8) { /*Ensemble de conditions pour afficher le chiffre 8*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 1)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
			if (number == 9) { /*Ensemble de conditions pour afficher le chiffre 9*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
			if (number == 0) { /*Ensemble de conditions pour afficher le chiffre 0*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 2 && col == 5)
						|| (row == 3 && col == 5) || (row == 4 && col == 1)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5) || (row == 3 && col == 1)) {
					matrix[row][col] = nbr_color;
				} else
					matrix[row][col] = bckgrnd_color;
			}
		}
	}
}

void SetLedMatrix(void) {
	for (int row = 0; row < 7; row++) {
		int col = 0;
		while (col < 7) {
			if 		(is_matrix_init
					&& actual_matrix[row][col].RValue == matrix[row][col].RValue //led est deja de la bonne couleur
					&& actual_matrix[row][col].GValue == matrix[row][col].GValue
					&& actual_matrix[row][col].BValue
							== matrix[row][col].BValue) {
			} else {
				setLedColor((row + 1), (col + 1), matrix[row][col].RValue,
						matrix[row][col].GValue, matrix[row][col].BValue);
				actual_matrix[row][col].RValue = matrix[row][col].RValue;
				actual_matrix[row][col].GValue = matrix[row][col].GValue;
				actual_matrix[row][col].BValue = matrix[row][col].BValue;
				debug_printf(1, "SetLedMatrix() SLC = ok");
			}
			col++;
		}
	}
	is_matrix_init = 1;
}

void SetAllBlack(){
	for (int row = 0; row < 7; row++) {
		for (int col = 0; col < 7; col++) {
			matrix[row][col].RValue = Blue.RValue;
			matrix[row][col].GValue = Blue.GValue;
			matrix[row][col].BValue = Blue.BValue;
		}
	}
}

void SetAllWhite(){
	for (int row = 0; row < 7; row++) {
		for (int col = 0; col < 7; col++) {
			matrix[row][col].RValue = White.RValue;
			matrix[row][col].GValue = White.GValue;
			matrix[row][col].BValue = White.BValue;
		}
	}
}

void *display(void) {
	debug_pr_fn(1, "display()entrée dans thread display\n");
	data_msg request;
	int receive_status;
	//SetLedMatrix();
	while (1) {
		receive_status = ReceiveMessage(LIST_DISPLAY, &request,	sizeof(data_msg));
		debug_pr_fn(1, "display() : receive = %d\n", receive_status);
		if (receive_status == 1) {
			if (request.type == MSG_MOVE_TOKEN) {
				debug_pr_fn(1, "display() : msg player = %d \n", request.type);

				pos_token_t positions = request.params.move_token.positions;
				matrix[positions.beg_position.l][positions.beg_position.c] = Black;
				matrix[positions.end_position.l][positions.end_position.c] = request.params.move_token.color;
				SetLedMatrix();
				debug_printf(1, "display()SetLedColor = OK\n");
			}
			if (request.type == MSG_DISPLAY_OFF) {
				SetAllBlack();
				SetLedMatrix();
			}
//			if (request.type == MSG_VICTORY) {
//				SetAllWhite();
//				SetLedMatrix();
//			}
		}
	}
	//pthread_exit(NULL);
}

//void setledmatrix(struct Element *message) {
//	int beg_row = message->data.token.position.beg_position.l;
//	int beg_col = message->data.token.position.beg_position.c;
//	int end_row = message->data.token.position.end_position.l;
//	int end_col = message->data.token.position.end_position.c;
//	if (beg_row == 10 && beg_col == 10) {
//	} else {
//		matrix_led[beg_row ][beg_col] = BACKGROUND;
//	}
//	matrix_led[end_row ][end_col] = message->data.token.color;
//}

//void *thread_display(void *arg) {
//	struct Element value_compt;
//	data_msg request;
//	while (1) {
//		if (ReceiveMessage(LIST_DISPLAY, &request,	sizeof(data_msg))) {
////			printf(" display b %d%d  e %d%d \n",
////					value_compt.data.token.position.beg_position.c,
////					value_compt.data.token.position.beg_position.l,
////					value_compt.data.token.position.end_position.c,
////					value_compt.data.token.position.end_position.l);
////			//			set_number(value_compt.data.value[1]);
////			setledmatrix(&value_compt);
////			for (int row = 0; row < 7; row++){
////				for (int col = 0; col < 7; col++){
////					if ((matrix[row][col].RValue == actual_matrix[row][col].RValue)
////							&& (matrix[row][col].GValue == actual_matrix[row][col].GValue)
////							&& (matrix[row][col].BValue == actual_matrix[row][col].BValue)) {
////					} else {
////						setLedColor((row + 1 ), (col + 1 ),
////								matrix[row][col].RValue,
////								matrix[row][col].GValue,
////								matrix[row][col].BValue);
////						actual_matrix[row ][col] = matrix[row ][col];
////					}
//				}
//			}
//		}
//	}
//}
