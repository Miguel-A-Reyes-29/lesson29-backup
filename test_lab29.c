#include <assert.h>
#include <string.h>
#include "playlist.h"

/* Tests inserting into an empty list. */
static void test_insert_tail_empty(void) {
    song_t *head = insert_tail(NULL, "Song A");

    assert(head != NULL);
    assert(strcmp(head->title, "Song A") == 0);
    assert(head->next == NULL);

    free_list(head);
}

/* Tests inserting at the end of a list with multiple nodes. */
static void test_insert_tail_multiple(void) {
    song_t *head = insert_tail(NULL, "Song A");
    assert(head != NULL);

    song_t *original_head = head;

    head = insert_tail(head, "Song B");
    assert(head == original_head);

    head = insert_tail(head, "Song C");

    assert(strcmp(head->title, "Song A") == 0);
    assert(strcmp(head->next->title, "Song B") == 0);
    assert(strcmp(head->next->next->title, "Song C") == 0);
    assert(head->next->next->next == NULL);
    assert(count(head) == 3);

    free_list(head);
}

/* Tests deleting from an empty list. */
static void test_delete_head_empty(void) {
    song_t *head = delete_head(NULL);

    assert(head == NULL);
}

/* Tests deleting the only node in a list. */
static void test_delete_head_single(void) {
    song_t *head = insert_tail(NULL, "Only Song");
    assert(head != NULL);

    head = delete_head(head);

    assert(head == NULL);
}

/* Tests deleting the first node while preserving the rest. */
static void test_delete_head_multiple(void) {
    song_t *head = insert_tail(NULL, "Song A");
    head = insert_tail(head, "Song B");
    head = insert_tail(head, "Song C");

    song_t *second_node = head->next;

    head = delete_head(head);

    assert(head == second_node);
    assert(strcmp(head->title, "Song B") == 0);
    assert(strcmp(head->next->title, "Song C") == 0);
    assert(head->next->next == NULL);

    free_list(head);
}

/* Tests deleting repeatedly until the list is empty. */
static void test_delete_head_until_empty(void) {
    song_t *head = insert_tail(NULL, "Song A");
    head = insert_tail(head, "Song B");

    head = delete_head(head);
    assert(head != NULL);
    assert(strcmp(head->title, "Song B") == 0);

    head = delete_head(head);
    assert(head == NULL);

    head = delete_head(head);
    assert(head == NULL);
}

/* Runs every test. */
void run_all_tests(void) {
    test_insert_tail_empty();
    test_insert_tail_multiple();
    test_delete_head_empty();
    test_delete_head_single();
    test_delete_head_multiple();
    test_delete_head_until_empty();
}
