#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "__debug.h"
#include "messages.h"

#include "cmsis_os.h"
//#define MSGSIZE 10

extern osMessageQueueId_t appToDisplayHandle;
extern osMessageQueueId_t readToAppHandle;

//
//void init_list(struct List* liste){
//	liste->head = 0;
//	liste->tail = 0;
//	liste->init = 1;
//	liste->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
//	sem_init(&liste->semaphore_list,0,0);
//}

//int push_element(struct List *liste, data_msg * value_to_push) {
//	if (liste->init == 1) {
//		struct Element* new_element = malloc(sizeof(struct Element)); 			//new_element contient l'adresse memoire des 8 octets crée
//		if (new_element) {            											 // si le malloc contient bien une adresse
//			pthread_mutex_lock(&liste->mutex);
//			memcpy(&new_element->data, value_to_push, sizeof(data_msg));
//			new_element->next_p = 0;              								// adresse du prochain element
//			if (liste->head == 0) {                								// si la liste est vide
//				liste->tail = new_element; 										//on attache le nouvel element a la queue de liste
//				liste->head = new_element;         							  // on attache la tete aussi
//			} else {                    										//si la liste contient deja des elements
//				liste->tail->next_p = new_element;
//				liste->tail = new_element;
//			}
//			pthread_mutex_unlock(&liste->mutex);
//			debug_pr_fn(2, "push_element() : ajout de l'élément\n");
//		}
//		return 1;
//	}
//	else {
//		return 0;
//	}
//}
//
//
//int pop_element(struct List* liste, data_msg * value_to_return) {
//	pthread_mutex_lock (&liste->mutex);
//	debug_pr_fn(1, "receivemessage()entrée\n");
//	struct Element* tmp;
//	if (liste->head == 0) {
//		pthread_mutex_unlock (&liste->mutex);
//		return 0; 							// Retourne 0 = fail
//	}
//	tmp = liste->head->next_p;
//	memcpy(value_to_return, &liste->head->data, sizeof(data_msg));
//	free(liste->head);
//	liste->head = tmp;						// Le pointeur pointe sur le dernier élément.
//	pthread_mutex_unlock (&liste->mutex);
//	debug_pr_fn(2,"pop_element() : suppression de l'élément\n");
//	return 1;								// retour 1 = success
//
//}


void SendMessage(List_Id liste, data_msg* message, int message_length){
	//if (message_length<=MSGSIZE){
	if (liste == LIST_READ){
		osMessageQueuePut(readToAppHandle, message, 1, osWaitForever);
	}
	else if(liste == LIST_DISPLAY){
		osMessageQueuePut(appToDisplayHandle, message, 1, osWaitForever);
	}
	//}
}

int ReceiveMessage(List_Id liste, data_msg* message, int message_length){
	int status = 0;
	//if (MSGSIZE<=message_length){
		if (liste == LIST_READ){
			debug_pr_fn(2, "receivemessage()entrée\n");
			osMessageQueueGet(readToAppHandle, message, 0, osWaitForever);
			status = 1;
		}
		else if(liste == LIST_DISPLAY){
			osMessageQueueGet(appToDisplayHandle, message, 0, osWaitForever);
			status = 1;
		}
	//}
	debug_pr_fn(2, "receivemessage()avant return\n");
	return status;
}
