/**
 * @file halib.h
 * @brief stdlib for HAHA project, contains imports and defines
 * @author August, Kevin
 * @version
 * @date 2017-03-07
 */

#ifndef _HA_HALIB_
#define _HA_HALIB_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// UNP error functions, DEPRECIATED
// TODO: replace with printex() and perrorex()
#define err_quit(...) fprintf(stderr, __VA_ARGS__), fflush(stderr), exit(1)
#define err_sys(...) perror(__VA_ARGS__), exit(1)

// String functions
#define streq(str1, str2) \
    (strlen(str1) == strlen(str2)) && (strncmp(str1, str2, strlen(str1)) == 0)

// Boolean values
#define bool int
#define true 1
#define false 0
#define TRUE 1
#define FALSE 0
#define ERROR -1

// Color preferences
#define DEBUG TRUE
#define VERBOSE TRUE
#define COLORED TRUE

// Color codes for printing
#define CDEF  "\033[0m"
#define CRED  "\x1B[31m"
#define CGRN  "\x1B[32m"
#define CBLU  "\x1B[34m"

#define CYEL  "\x1B[33m"
#define CMAG  "\x1B[35m"
#define CCYN  "\x1B[36m"
#define CWHT  "\x1B[37m"

// Debug messages
#if DEBUG
#if COLORED
#define printd(args...) fprintf(stdout, CBLU), fprintf(stdout, args), \
    fprintf(stdout, CDEF)
#else
#define printd(args...) fprintf(stdout, args)
#endif // COLORED
#else
#define printd(...) (void)0
#endif // DEBUG

// Verbose messages
#if VERBOSE
#if COLORED
#define printv(args...) fprintf(stdout, CGRN), fprintf(stdout, args), \
    fprintf(stdout, CDEF)
#else
#define printv(args...) fprintf(stdout, args)
#endif // COLORED
#else
#define printv(...) (void)0
#endif // VERBOSE

// Error messages
#if COLORED
#define printe(args...) fprintf(stderr, CRED), fprintf(stderr, args), \
    fprintf(stderr, CDEF)
#else
#define printe(args...) fprintf(stderr, args)
#endif // COLORED

// Terminating error messages
#if COLORED
#define ERRORPRINT(...) fprintf(stderr, CRED), __VA_ARGS__, fprintf(ERRORPRINT)
#else
#define ERRORPRUNT(...)  __VA_ARGS__
#endif // COLORED

#define printex(...) printe(stderr, __VA_ARGS__), fflush(stderr), exit(1)
#define perrorex(...) ERRORPRINT(perror(__VA_ARGS__)), exit(1)

#endif // _HA_HALIB_
