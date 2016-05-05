/*
 * This file contains the code for a extra credit assignment worker thread.
 * The main thread of execution will start a thread by using tring_thread_start.
 * Most of a student's work will go into this file.
 *
 */

#include <stdio.h>

#include "mailbox.h"
#include "tring.h"


void print_message(message *msg, int id) {
    printf("%d : %d\n", id, msg->type);
    return;
}

int checkForIncompleteInfo(int *arr, int len) {
    int i;
    int count = 0;
    for (i = 0; i < len; i++) {
        if (arr[i] == -1)
            return count;
        else
            count++;
    }
    return len;
}

/*
 * void* tring_thread_start(void* arg)
 *
 * This function is used in the creating of worker threads for this assignment.
 * Its parameter 'arg' is a pointer to a thread's designated mailbox.  The
 * thread should exit with a NULL pointer.
 *
 */
void* tring_thread_start(void* arg) {
	int id = -1;
    int num_threads =200;

    mailbox* mb;
    mailbox* next_mb = NULL;
    
    mb = (mailbox *)arg;
    
    //printf("\n Thread starting\n");
        
    message *msg;
    //msg=NEW_MSG;
    msg = mailbox_receive(mb);
    /* Message type ID */
    while (msg== NULL){
    	msg = mailbox_receive(mb);

    }
    if (msg->type != ID) {
        printf("Error\n");
        return NULL;
    }
    else {
        id = msg->payload.integer;
        //printf("%d Received ID message\n", id);
        
        //FREE_MSG(msg);
    }
    
   
    printf("\n\nhello\n");

    /* Message type MAILBOX */
    
    while ((msg = mailbox_receive(mb)) == NULL);
    if (msg->type != MAILBOX) {
        //printf("Error\n");
        return NULL;
    }
    else {
        //printf("%d Received MAILBOX message\n", id);
        next_mb = msg->payload.mb;
        //FREE_MSG(msg);
    }
    
    
    printf("exiting %d\n\n",id );  
   //msg=NEW_MSG;
   while(((msg=mailbox_receive(mb))==NULL)||(msg->type!=START));
   printf("hello bye\n");
     int* id_array=malloc(sizeof(int)*num_threads);
    mailbox* *mb_array=malloc(sizeof(mailbox *)*num_threads);
    int i, count;
    //(message*) temp_msg;
    id_array[0] = id;
    mb_array[0] = mb;
    for (i = 1; i < num_threads; i++) {
        id_array[i] = -1;
        mb_array[i] = NULL;
    }
   printf("%d\n",msg->count);
   if(msg->count>0){
   	   //msg->
	   msg->count=(msg->count)-1;
	   mailbox_send(next_mb,msg);
	   msg=NEW_MSG;
	   msg->type=INFO;
	   msg->count=num_threads-1;
	   msg->payload.integer=id;
	   msg->payload.mb=mb;
	   mailbox_send(next_mb,msg);
	   
	}
    else{
    FREE_MSG(msg);
     	} 
     	count =1;
     	id_array[0]=id;
   	mb_array[0]=mb;
     	do{
    while((msg=mailbox_receive(mb))==NULL);
   	if(msg->count>0){
   		id_array[count]=msg->payload.integer;
   		mb_array[count++]=msg->payload.mb;
	   	msg->count=msg->count-1;
		mailbox_send(next_mb,msg);
	   
	}
     else{
     	FREE_MSG(msg);
     	}  
   }while(count < num_threads);
   for(i=0;i<num_threads;i++)
   	printf("thread %d : %d ",id,id_array[i]);
   printf("\n\n");
   //Sorting array
  int next_mb_id = id+250;
    int next_mb_index = 0;
    for (i = 1; i < num_threads; i++) {
        if (id_array[i] > id) {
            if (id_array[i] < next_mb_id) {
                next_mb_index = i;
                next_mb_id = id_array[i];
            }
        }
    }
    for (i=1;i<num_threads;i++){
        if(id_array[i]==next_mb_id){
            next_mb_index=i;
            break;
        }
    }
    if (next_mb_id == id+250) {
        next_mb = NULL;
    }
    else {
        next_mb = mb_array[next_mb_index];
    }
    
    printf("%x, %d, hello %x %d\n", mb, id, next_mb, next_mb_id);
     if (first_mb == mb) {
        printf("PREV HEAD = %d\n", id);
        int min = id;
        int min_index = 0;
        for (i = 0; i < num_threads; i++) {
            if (min > id_array[i]) {
                min = id_array[i];
                min_index = i;
            }
        }
        first_mb = mb_array[min_index];
        printf("Change First_mb to %x\n", first_mb);
        
        /* Test new formed linear chain*/
    }
    
    /*while (((msg = mailbox_receive(mb)) == NULL)||(msg->type != TEST));
    if (msg->type == TEST) {
        printf("%d Received TEST\n", id);
        if (next_mb) {
            mailbox_send(next_mb, msg);
        } else {
            FREE_MSG(msg);
        }
    }
*/
    /**** Network rearrangement complete ****/
    if(first_mb == mb) {
        printf("NEW HEAD = %d\n", id);
        printf("%d Network rearrangement complete. Requesting main to check\n", id);
        tring_signal();
    }
    
    
    /*Message type PING */
    printf("%d Waiting for PING\n", id);
    //msg=NEW_MSG;
    while (((msg=mailbox_receive(mb))==NULL)||(msg->type!=PING));
    print_message(msg, id);
        printf("%d Received PING message\n", id);
        pong(id);
        if(next_mb) {
            mailbox_send(next_mb, msg);
        } else {
            FREE_MSG(msg);
            tring_signal();
        }
    
    
    /* Message type PRINT */
   /* printf("%d Waiting for PRINT\n", id);
    while ((msg = mailbox_receive(mb)) == NULL);
    print_message(msg, id);
    if (msg->type != PRINT) {
        printf("Error\n");
        return NULL;
    }
    else {
        printf("%d Received PRINT message\n", id);
        if(next_mb) {
            tring_print((int)mb, (int)next_mb);
            mailbox_send(next_mb, msg);
        } else {
            FREE_MSG(msg);
            tring_signal();
        }
    }
    
	return NULL;
   */
   return NULL;
}
