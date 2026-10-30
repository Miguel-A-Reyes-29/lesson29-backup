/* CS210 Lesson 29 - Lab 29: Playlist Deletion
 *
 * Documentation: ChatGPT assisted with debugging and drafting code
 * for this lab, including insert_tail and delete_head, and previously
 * helped write the test file. See the associated ChatGPT conversation:
 * https://chatgpt.com/share/6ae26ece-a374-83e8-8750-ffa07bf9a52d
 *
 * Functions:
 *   create_node
 *   count
 *   insert_head
 *   print_list
 *   insert_tail
 *   delete_head
 *
 * free_list is provided. Do not modify it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "playlist.h"

/* Task 1: create_node */
song_t *create_node(const char *title) {
    if (title == NULL) {
        return NULL;
    }

    song_t *head = malloc(sizeof(song_t));

    if (head == NULL) {
        return NULL;
    }

    head->title = malloc(strlen(title) + 1);

    if (head->title == NULL) {
        free(head);
        return NULL;
    }

    strcpy(head->title, title);
    head->next = NULL;

    return head;
}

/* Task 2: count */
int count(song_t *head) {
    song_t *curr = head;
    int total = 0;

    while (curr != NULL) {
        total++;
        curr = curr->next;
    }

    return total;
}

/* Task 3: insert_head */
song_t *insert_head(song_t *head, const char *title) {
    song_t *new_node = create_node(title);

    if (new_node == NULL) {
        return head;
    }

    new_node->next = head;

    return new_node;
}

/* Task 4: print_list */
void print_list(song_t *head) {
    song_t *curr = head;

    while (curr != NULL) {
        printf("%s\n", curr->title);
        curr = curr->next;
    }
}

/* Task 5: insert_tail */
song_t *insert_tail(song_t *head, const char *title) {
    song_t *new_node = create_node(title);

    if (new_node == NULL) {
        return head;
    }

    if (head == NULL) {
        return new_node;
    }

    song_t *curr = head;

    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = new_node;

    return head;
}

/* Task 6: delete_head */
song_t *delete_head(song_t *head) {
    if (head == NULL) {
        return NULL;
    }

    song_t *new_head = head->next;

    free(head->title);
    free(head);

    return new_head;
}

/* free_list - PROVIDED. Do not modify. */
void free_list(song_t *head) {
    song_t *curr = head;

    while (curr != NULL) {
        song_t *next = curr->next;
        free(curr->title);
        free(curr);
        curr = next;
    }
}
