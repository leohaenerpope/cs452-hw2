# HW 2 - Memory Hole

* Author: Leo Haener-Pope
* Class: CS452 Section #002
* Semester: Fall 2026

## Overview

This program implements a doubly linked list using C. 
Void pointers are used and the main deq.c utilizes Node structs for each node in the
list, as well as Rep anonymous structs to represent the void pointer linked list structure itself.
In this homework, I implemented the four main functions outlined in deq.h, which are put, get, ith, and rem.

## Reflection

This was a refreshing experience with using C. I have not utilized C too much, as the only classes I have used it
with was the 25~ C class as well as the ECE 330 class. Though the syntax can be a little confusing sometimes,
I enjoy working with pointers and I think C being so low level is very fun to work with. Also, the review of the
homework that we had on Monday (8/31) was very helpful especially for getting started, as I was definitely a little
confused to start.

I am on windows so getting everything set up for C properly is a little difficult but I was able to do it successfully
without too much trouble. One thing though is I have to use WSL in order to use valgrind which was unfortunate since I was developing not on WSL at first so maybe for future projects I will just keep with staying on WSL only (since I also feel
quite comfortable with it, I have used WSL for some classes already).

## Compiling and Using

Inside of the source `hw2` directory, run the `make` command.

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