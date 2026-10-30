/* CS210 Lesson 29 - Lab 29: Playlist Deletion
 *
 * Driver demonstrating both new operations. Builds a playlist with your
 * insert_tail, removes the first song twice with your delete_head,
 * printing the list and count after each change, then frees what is
 * left with the provided free_list.
 */

#include <stdio.h>

#include "playlist.h"
#include "tests.h"

static void show(song_t *head, const char *caption) {
    printf("%s (%d song%s):\n", caption, count(head), count(head) == 1 ? "" : "s");
    print_list(head);
    printf("\n");
}

int main(void) {
    /* Built with -D RUNTESTS (make run_tests)? Run your tests and stop.
     * Without the flag the preprocessor drops this block and the program
     * runs normally. Leave this block in place. */
#ifdef RUNTESTS
    run_all_tests();
    return 0;
#endif

    song_t *head = NULL;

    /* Build the playlist with your insert_tail: each song joins at the end. */
    head = insert_tail(head, "Espresso");
    head = insert_tail(head, "Levitating");
    head = insert_tail(head, "Anti-Hero");
    head = insert_tail(head, "Blinding Lights");
    show(head, "Built playlist");

    /* Remove the first song. The caller must reassign head. */
    head = delete_head(head);
    show(head, "After delete_head");

    /* Remove the first song again. */
    head = delete_head(head);
    show(head, "After a second delete_head");

    /* Required cleanup: the provided free_list returns every remaining
     * node and its title to the heap. valgrind should report no leaks
     * after this. */
    free_list(head);
    printf("Freed the rest of the playlist.\n");
    return 0;
}
