#ifndef PLAYLIST_H
#define PLAYLIST_H

/* CS210 Lesson 29 - Lab 29: Playlist Deletion
 *
 * This is the same singly-linked playlist you built in Lesson 28, with
 * two operations added: adding at the end and removing from the front.
 * Each node holds the title of a song (a heap-allocated copy of the
 * string the caller passed in) and a pointer to the next song in the
 * list. The list is identified by a single song_t * named "head". An
 * empty playlist is represented as head == NULL.
 *
 * A function that may change which node is first returns the
 * possibly-new head. The caller is expected to reassign:
 *
 *     head = insert_tail(head, "Levitating");
 *     head = delete_head(head);
 *
 * Adding to an empty list and removing the first node both change
 * which node is first, so both follow the return-the-new-head pattern
 * from insert_head.
 *
 * Memory rule for this lesson: every node owns TWO heap blocks, the
 * node struct and its title string. Removing a node means freeing both,
 * title first, then the node.
 *
 * Each declaration carries a DFCS-standard function header
 * (@brief / @param / @return). Write headers in this same format above
 * every function you implement in playlist.c.
 */

#include <stddef.h>

typedef struct song {
    char *title;            /* heap-allocated copy of the song title */
    struct song *next;      /* next node, or NULL if this is the tail */
} song_t;

/* ---- Carried forward from Lesson 28 (unchanged contracts) ---------- */

/**
* @brief creates a fresh playlist node
* Allocates the node on the heap, copies the title string so the node
* owns its own storage, and sets next to NULL.
* @param title the song title to copy into the node
* @return the new node, or NULL on allocation failure; OWNER: caller,
*         release with free_list
*/
song_t *create_node(const char *title);

/**
* @brief counts the nodes in the list
* @param head first node of the list, or NULL if the list is empty
* @return the number of nodes; 0 for an empty list
*/
int count(song_t *head);

/**
* @brief inserts a new node at the head of the list
* Works on an empty list. The caller must reassign:
*     head = insert_head(head, title);
* @param head current first node, or NULL if the list is empty
* @param title the song title to insert
* @return the new head
*/
song_t *insert_head(song_t *head, const char *title);

/**
* @brief prints every title in the list, one per line, in playlist order
* Each line is exactly the title, then a newline. An empty list prints
* nothing.
* @param head first node of the list, or NULL if the list is empty
*/
void print_list(song_t *head);

/* ---- New in Lesson 29: you write these two -------------------------- */

/**
* @brief inserts a new node at the tail of the list
* Walks from head to the last node (the one whose next is NULL) and links
* the new node after it. On an empty list there is nothing to walk: the
* new node becomes the whole list, and it is returned as the head. The
* caller must reassign: head = insert_tail(head, title);
*
*   head    current first node, or NULL if the list is empty
*   title   the song title to copy into the new node
*
* @param head current first node, or NULL if the list is empty
* @param title the song title to insert
* @return the head: the new node if the list was empty, otherwise the
*         unchanged head; the head unchanged if allocation fails
*/
song_t *insert_tail(song_t *head, const char *title);

/**
* @brief deletes the first node of the list
* Moves head to the second node, then frees the old first node: its
* title string first, then the node. Safe to call on an empty list.
* The caller must reassign: head = delete_head(head);
* @param head first node of the list, or NULL if the list is empty
* @return the new head: the old second node, or NULL if the list becomes
*         (or already was) empty
*/
song_t *delete_head(song_t *head);

/**
* @brief frees every node in the list, including each node's title string
* Provided for you in Lesson 28 and still provided here - do not modify.
* Read it until you can explain every line: it is the delete_head steps
* applied to every node in a loop (save the next pointer, free the title,
* free the node, move on). The deletion walkthrough runs it one step at a
* time. Safe to call on an empty list. After the call, every node is gone
* and the caller's head must not be used again until it is reassigned.
* @param head first node of the list, or NULL if the list is empty
*/
void free_list(song_t *head);

#endif /* PLAYLIST_H */
