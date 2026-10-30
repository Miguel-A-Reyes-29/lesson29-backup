# CS210 Lesson 29 - Lab 29: Playlist Deletion

This lab continues the playlist from Lesson 28. You add the two functions
that work the ends of the list: one adds a song at the end, one removes the
first song without leaking memory. You also read the provided `free_list`
until you can explain every line of it.

## Starting point: bring your Lesson 28 code forward

This lab does **not** ship a `playlist.c`. You start from the one you
wrote in Lesson 28, with `create_node`, `count`, `insert_head`,
`print_list` and the provided `free_list`.

1. Copy your **Lesson 28 `playlist.c`** into this folder, next to the
   `playlist.h` and `main.c` provided here. Your Lesson 28 Makefile works
   here too: the file names and the executable name are the same.
2. Use the `playlist.h` provided here (do **not** overwrite it with your
   Lesson 28 header). It is your Lesson 28 header plus the contracts for
   `insert_tail` and `delete_head`.
3. Keep your Lesson 28 functions as they are, `free_list` included. It is
   still provided and still off limits.

## What to implement

Two functions. The full contracts (return values, edge cases, ownership)
are in `playlist.h`; follow them exactly.

| Function | What it does |
|---|---|
| `song_t *insert_tail(song_t *head, const char *title)` | Adds a new song at the end of the list and returns the head. On an empty list the new song is the whole list, so the new node is returned as the head. |
| `song_t *delete_head(song_t *head)` | Removes the first song and returns the new head. On an empty list it returns NULL instead of crashing. Deleting the only song returns NULL because the list is now empty. |

Three things `insert_tail` gets right:

- **Stop on the last node, not past it.** Nothing in the list names the
  last node, so you walk to it: `while (curr->next != NULL)`. That loop
  stops with `curr` on the last node, which is the one you link the new
  node after. A `while (curr != NULL)` loop walks past it and leaves you
  holding NULL.
- **Return the head.** On a non-empty list that is the unchanged head; on
  an empty list it is the new node. The caller reassigns either way:
  `head = insert_tail(head, title);`

Three things `delete_head` gets right:

- **Move head before you free.** The first node has nothing in front of
  it, so there is no link to rewire. Point `head` at the second node
  first, then free the node you just left. Free it first and `head->next`
  reads memory you have already given back.
- **Free both blocks, title first.** Each node owns two heap blocks: the
  node struct and its `title` string. Free the title *before* the node;
  once the node is freed you can no longer reach `node->title`.
- **Return the new head.** Deleting the first node changes which node is
  first, so `delete_head` returns the possibly-new head and the caller
  reassigns: `head = delete_head(head);`

## free_list: provided, and yours to understand

`free_list` was handed to you in Lesson 28 with the words "do not modify".
That still holds. What changes today is that you can read it: it is the
`delete_head` steps applied to every node in a loop, with one extra move,
**save `next` before you free.** After `free(curr)` you may not read
`curr->next`, so the loop copies it into a local variable first. The
deletion walkthrough on the lesson page runs this loop one step at a time;
by the end of the lab you should be able to explain every line of
`free_list` without looking at it.

## Build and run

Build with the Makefile you write for this lab (see "The Makefile
(you write it)" below), then run the demo driver:

```
make
./playlist
```

Your code must compile cleanly with `-Wall -Werror` (no warnings).

## Self-test before you submit

The provided `main.c` builds four songs with `insert_tail`, deletes the
first one twice, and frees the rest. Before submitting, also confirm your
functions handle these cases; the autograder checks every one:

- `insert_tail` into an **empty list** returns the new node as the head,
  and that node's `next` is NULL.
- `insert_tail` onto a **longer list** keeps the existing order and puts
  the new song last, with its `next` NULL.
- After `insert_tail` on a non-empty list, `head` is **unchanged** (the
  function returned the same pointer it was given).
- `delete_head(NULL)` on an **empty list** returns NULL and does not
  crash.
- `delete_head` on a **single-song list** returns NULL: the list is now
  empty.
- `delete_head` on a longer list returns the old second node, and the
  songs after it are untouched and still in order.
- Calling `delete_head` until the list is empty, then once more, is safe.

Then check for leaks. Your two functions and the provided `free_list`
together must leave no memory unfreed:

```
valgrind --leak-check=full ./playlist
```

You are aiming for `All heap blocks were freed -- no leaks are possible`
and `0 errors`. The autograder runs a build, delete, free cycle under
valgrind, so a leak, a double free, or a read of freed memory costs
points.

## Documentation statement (5% of this lab)

The comment header of `playlist.c` must contain a documentation statement: a
line beginning with `Documentation:` that lists ALL outside help you
received on this lab. That covers GenAI tools (documented per the course
GenAI policy), internet sources such as Stack Overflow, and help from any
person (classmates, friends, EI with your instructor). If you received no
outside help, write exactly:

    Documentation: None

Keep the statement on the same line as `Documentation:`. This lab ships no
`playlist.c` template, so add the line to the top comment of the copy you
carried forward from Lesson 28 (a leftover placeholder from that lab does
not count). This component is worth 0.10 of the lab's 2 points.

## The Makefile (you write it)

Worth **0.20 of this lab**. Since Lesson 7 you have known how to write a Makefile, and from Lesson 9 on you write one for every lab. The stub states the target name and nothing else. Open `Makefile` and fill it in before you start on the C.

The autograder checks that your Makefile:

- builds an executable named `playlist`
- compiles each `.c` to its own `.o` and links them
- puts `-Wall` and `-Werror` in `CFLAGS`
- has a `clean` rule that removes `playlist` and the `.o` files
- does nothing on a second `make` when nothing has changed

Put `-g` in `CFLAGS` too. It is not graded, but it is what lets `gdb` and `valgrind` show you file names and line numbers instead of `???`.

Recipe lines must start with a real tab character, not spaces. If `make` says `missing separator`, that is what happened. The Lesson 7 lab and the Makefile walkthrough on the Lesson 7 page are the reference.

If your C does not compile, this check is not counted against you: the build points here are about your Makefile, not your code.

<!-- cadet-tests:begin (generated) -->
## Your tests, with assert

`test_lab29.c` is yours this time: the file ships with a header comment and no code. The shape is the Lesson 18 one: no `main`, one static function per case, named for what it checks, with a comment naming the edge case, and one public `run_all_tests()` (its prototype is in the provided `tests.h`) that calls every test in order. You need **at least 6 `assert` calls**. `make run_tests` builds the program with `-D RUNTESTS`, so the provided block at the top of `main` hands off to your tests; `./run_tests` runs them. `make test` does the same and then prints how much of each function your tests reached. Keep `test_lab29.c` out of your Makefile's object list: the provided `run_tests` rule is the only thing that compiles it.

From Lesson 28 on, the first half is graded by **coverage**, not by which functions you call. The autograder compiles your tests with *your* `playlist.c` under `--coverage`, runs them, and reads gcov's per-function line counts. Each named function has a bar, the share of its lines your tests must execute:

| Function | Bar (lines executed) |
| --- | --- |
| `insert_tail` | 80% |
| `delete_head` | 80% |

A bar under 80% means the instructor's own tests could not reach every line of that function either (an allocation-failure branch, say); the bar is set from what good tests can reach. The lines that go unexecuted are almost always the edge cases: the empty list, the single node, the not-found search, the boundary value. Your tests must pass on your own module first: an assert that fails aborts the program before gcov writes anything, so no coverage is recorded and the first half scores zero.

The three rules from Lesson 18 still apply: work the expected value out by hand first; a test that fails against correct code is itself the bug (the autograder also runs your file against the instructor's `playlist.c`, through its own `main` that just calls `run_all_tests()`); a failing assert skips everything below it, including your frees. A test you write but never list in `run_all_tests()` compiles and never runs; `./run_tests` prints one line per test, so count them.

Graded as 0.2 of the lab: 0.1 for coverage (the share of the named functions, `insert_tail`, `delete_head`, at or above their bar) and 0.1 for those tests holding against the reference module. The second half is not scored until the first scores.
<!-- cadet-tests:end -->

<!-- visible-tests:begin (generated) -->
## Visible tests

The provided driver's expected output is saved in `tests/visible/`. Run the check any time with

```
make test
```

(`make test` just runs `bash run_local.sh`, so either works. The script builds with your Makefile, falling back to a direct gcc build while your Makefile is unfinished, so you can always check your C.)

The autograder tests your functions directly, with more cases than the demo driver exercises. Passing the visible check is necessary, not sufficient.

`make test` also compiles and runs your `test_lab29.c` and reports whether every assert held, then prints the share of each function's lines your tests executed (gcov, on your own `playlist.c`). The autograder grades that file separately, against the bars in "Your tests, with assert" above.
<!-- visible-tests:end -->

## Submitting

Push to your assignment repo for this lab and submit the repo
to the Lab 29 assignment on Gradescope. Your repository must contain
`playlist.c`, `playlist.h`, `main.c`, and `test_lab29.c` at the top level. The autograder
builds your `playlist.c` against its own tests, so make sure it compiles
on its own with `-Wall -Werror`.
