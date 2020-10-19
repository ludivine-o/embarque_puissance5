/*
 * messsages.c
 *
 *  Created on: Oct 16, 2020
 *      Author: ludivineo
 */


#include <stdbool.h>

#ifndef MESSAGES_H_
#define MESSAGES_H_

typedef enum {
LIST_READ, LIST_DISPLAY }
List_Id;

#define INIT_DATA_MSG {.type = MSG_NONE}

typedef enum {
	MSG_NONE,
	MSG_PLAYER,
	MSG_MOVE_TOKEN,
	MSG_TIMER,
	MSG_DISPLAY_OFF,
	MSG_VICTORY,
} MessageType;

typedef enum {
	live, //!< Need to continue game
	stop_winner, //!< game is finish and winner
	stop_equal //<! game is finish and equal
} status_t;

typedef enum {
	horiz, vert, right_diag, left_diag,
} victory_t;

typedef struct {
	int8_t l;
	int8_t c;
} point_t;

typedef enum {
	NO_PLAYER, PLAYER_1, PLAYER_2,
} player_t;


typedef struct {
	status_t status; //!< status of winner
	victory_t win_type; //<!
	player_t win_player; //<! the winner player
	point_t win_position[4]; //!< position of 4 winner token
} winner_t;

typedef struct {
	bool is_ok;
	point_t beg_position;
	point_t end_position;
} pos_token_t;

typedef enum {
	ON,
	OFF,
	BLINK,
}token_mode_t;



typedef enum {
	UP, RIGHT, DOWN, LEFT,
} dir_t;

typedef struct {
	player_t player;
	dir_t direction;
}player_data_msg;

typedef struct {
	unsigned char RValue;
	unsigned char GValue;
	unsigned char BValue;
} Color;

typedef struct {
	pos_token_t positions;
	Color color;
	token_mode_t mode;
}move_token_t;

typedef struct data_msg {
	MessageType type;
	union {
		player_data_msg player;		//(MSG_PLAYER) read -> app
		move_token_t move_token;	//(MSG_MOVE_TOKEN) app -> display
		char value[10];				//
		int timer_id; 				//(MSG_TIMER) timer -> thread
		winner_t victory;			//(MSG_VICTORY app --> display
	} params;
}data_msg;

//int ReceiveMessage(List_Id liste, data_msg* message, int message_length);

//struct List{
//	struct Element *head;
//	struct Element *tail;
//	pthread_mutex_t mutex;
//	sem_t semaphore_list;
//	int init;
//};

void SendMessage(List_Id liste, data_msg* message, int message_length);
int ReceiveMessage(List_Id liste, data_msg* message, int message_length);

#endif // MESSAGES_H_
