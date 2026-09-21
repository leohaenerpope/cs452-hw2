# HW 2 - Memory Hole

* Author: Leo Haener-Pope
* Class: CS452 Section #002
* Semester: Fall 2026

## Overview

This program implements a memory management buddy system. It utilizes freelists and buddy bitmap systems
to track free locations of memory, and also remember where the "buddies" of taken up memory spots are.

## Reflection/Notes

This was a challenging assignment for me. I took a while to understand what bm and bbm were doing, and even after putting in my comments for them, I still would get slowed down when implementing freelist/balloc because I would kind of forget what was happening with the bit maps. I think I understood the concept of what I was trying to implement decently, however I just struggled with creating it in C, since I don't really have too much experience with it.

I implemented my freelist as a ** C array pointer system and was able to use the *(void**) syntax to kind of go along
the array (it felt similar to the deq assignment with storing the prev and next). It is important to note that the minimum l would be 3, pointers are 8 bytes in C on 64 bit systems so having data that would be smaller than 8 bytes would probably lead to weird overlaps with the pointer memory locations. Also, note that the buddy system that my program uses will have issues freeing blocks where both buddies have memory allocated, since the bittst will fail when trying to find the size of the buddy to free due to the value of the buddy bitmap location being 0, from both buddies being used.

 I think the thing that gave me the most trouble with this assignment was just trying to figure out where to start with some of the functions, like allocating/freeing, because I would try to think about how to implement it, but I would get stuck thinking about how the freelists/bitmaps would work together. I think I was also confused by some of the functions that bbm provided and how they would correlate with what I was trying to do.

Overall however, this assignment definitely gave me more of an understanding of the buddy system for memory storage. It also definitely helped with my lack of C knowledge, as I now feel more confident with using pointers, especially the ** pointer array things.

## Compiling and Using

Inside of the source `hw2` directory, run the `make` command.

The main program consists of some smaller tests for freelist and utils,
and it should also show the funcionality of balloc with the previous homework's
Deqs (the functions are linked by wrapper.c).

To run the main program, run the `./balloc` command.

## Testing

To test this program, make sure your terminal is located inside the source `hw2` directory.

If you haven't already, run the `make` command.

Next, run the `./balloc_test` command to run the test suite. Output will be printed in the terminal.

**NOTE**: The test program will run functions that are expected to cause problems within balloc,
which may print error/warning messages.

Valgrind can be ran on the test suite as well, using 
`valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./balloc_test`




## Results

After creating and finishing all my tests, they fortunately all successfully passed.

Valgrind reported no memory leaks as well.

## Works Cited

Gemini helped me through understanding more of using C with the bitmap/freelist buddy system. Also it helped me write some tests.