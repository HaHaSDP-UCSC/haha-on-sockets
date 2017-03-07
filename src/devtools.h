/*
 * devtools.h
 *
 *  Edited on: March 2, 2017
 *      Author: Kevin Lee
 */

// NOTICE! This file is depreciated.
// TODO: Move contents into halib.h

#ifndef SRC_DEVTOOLS_H_
#define SRC_DEVTOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Boolean values.
#define bool int
#define TRUE 1
#define FALSE 0
#define ERROR -1

//Set these parameters.
#define DEBUG TRUE
#define VERBOSE TRUE
#define COLORED TRUE

//Color codes
#define CDEF  "\033[0m"
#define CRED  "\x1B[31m"
#define CGRN  "\x1B[32m"
#define CBLU  "\x1B[34m"

#define CYEL  "\x1B[33m"
#define CMAG  "\x1B[35m"
#define CCYN  "\x1B[36m"
#define CWHT  "\x1B[37m"

//Toggle Debug messages.
#if DEBUG
#if COLORED
#define printd(args...) fprintf(stdout, CBLU); fprintf(stdout, args); fprintf(stdout, CDEF);
#else
#define printd(args...) fprintf(stdout, args);
#endif
#else
#define printd(...) (void)0
#endif

//Toggle Verbose messages.
#if VERBOSE
#if COLORED
#define printv(args...) fprintf(stdout, CGRN); fprintf(stdout, args); fprintf(stdout, CDEF);
#else
#define printv(args...) fprintf(stdout, args);
#endif
#else
#define printv(...) (void)0
#endif

#if COLORED
#define printe(args...) fprintf(stderr, CRED); fprintf(stderr, args); fprintf(stderr, CDEF);
#else
#define printe(args...) fprintf(stderr, args);
#endif

#endif /* SRC_DEVTOOLS_H_ */
