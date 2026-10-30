/* CS210 Lesson 28 - Lab 28: Playlist Builder
 *
 * Documentation: "I received in class EI on this assignment. I could however not wrap my head around the test file and HAD CHATGPT WRITE IT. all other work is my own. here is the chatgpt link: https://chatgpt.com/share/6ae26ece-a374-83e8-8750-ffa07bf9a52d"
 *   (see README "Documentation statement": covers GenAI, internet
 *   sources, and help from any person; keep it on the line above)
 *
 * Your task: implement the five functions below.
 *
 *   create_node       (Task 1)
 *   count             (Task 2)
 *   insert_head       (Task 3)
 *   print_list        (Task 4)
 *
 * free_list is provided at the bottom of this file. Do not modify it.
 *
 * Read every contract in playlist.h before writing code. Each function
 * has specific behavior on an empty list; the autograder tests those
 * cases explicitly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "playlist.h"

/* ------------------------------------------------------------------ */
/* Task 1: create_node                                                 */
/* Allocate a fresh node, copy the title string so the node owns its   */
/* own storage, and set next to NULL. Return the new node, or NULL on  */
/* allocation failure or if title is NULL.                             */
/* The node owns its title, so the title is a second allocation, not  */
/* a borrowed pointer -- and sizing it is where this task is usually  */
/* lost. Whatever you allocate has to hold the terminator too.        */
/* ------------------------------------------------------------------ */
song_t *create_node(const char *title) {
    /* TODO: implement */
    (void)title;  /* silence the unused-parameter warning until you write the body */
 if(title==NULL){
    return NULL;
 }
    song_t *head=malloc(sizeof(song_t));
    head->title=malloc(strlen(title)+1);
    if(head->title==NULL){
       free(head);
        return NULL;
    }
    strcpy(head->title,title);
head->next=NULL;
return head;
}

/* ------------------------------------------------------------------ */
/* Task 2: count                                                       */
/* Return the number of nodes in the list. An empty list returns 0.    */
/* This is the list traversal idiom from the Lesson 28 notes; go back */
/* to them for the shape of the walk if it is not automatic yet.      */
/* ------------------------------------------------------------------ */
int count(song_t *head) {
    /* TODO: implement */
    (void)head;
    song_t *curr=head;
    int count=0;
    while(curr!=NULL){
        count+=1;
        curr=curr->next;
    }
    return count;
}

/* ------------------------------------------------------------------ */
/* Task 3: insert_head                                                 */
/* Create a new node with the given title and put it at the front of   */
/* the list. Return the new head. Order matters: the new node has to  */
/* be pointed at the old front of the list before it can become the   */
/* front itself, or the rest of the playlist is lost. The caller      */
/* reassigns its head pointer from your return value.                 */
/* On allocation failure, return the unchanged head.                  */
/* ------------------------------------------------------------------ */
song_t *insert_head(song_t *head, const char *title) {
    /* TODO: implement */
    (void)title;
    song_t * new_node=create_node(title);
    new_node->next=head;
    head=new_node;
    return head;
}

/* ------------------------------------------------------------------ */
/* Task 4: print_list                                                  */
/* Print every title in the list, one per line, in order. Each line is */
/* the title followed by a single newline. An empty list prints        */
/* nothing - not even a blank line.                                     */
/* ------------------------------------------------------------------ */
void print_list(song_t *head) {
    /* TODO: implement */
    song_t *curr=head;
    while(curr!=NULL){
        printf("%s\n",curr->title);
        curr=curr->next;
    }
}

/* ------------------------------------------------------------------ */
/* free_list - PROVIDED. Do not modify.                                */
/* This is the function you'll learn to write tomorrow (Lesson 29).    */
/* For now: call it from main before main returns so the playlist is   */
/* fully cleaned up. DFCS C Programming Standard 8.5 requires it.       */
/* ------------------------------------------------------------------ */
void free_list(song_t *head) {
    song_t *curr = head;
    while (curr != NULL) {
        song_t *next = curr->next;
        free(curr->title);
        free(curr);
        curr = next;
    }
}

song_t *insert_tail(song_t *head, const char *title){
 song_t *new_node =create_node(title);
 song_t *curr=head;
 while(curr->next!=NULL){
    curr=curr->next;
 }
 curr->next=new_node;
 return new_node;
}

song_t *delete_head(song_t *head){

    song_t *old=head;
    head=head->next;
    free(old->title);
    free(old);
    return head;
}
