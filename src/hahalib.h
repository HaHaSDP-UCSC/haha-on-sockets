/**
 * @file hahalib.h
 * @brief stdlib for HAHA project, contains imports and defines
 *
 * @author August Valera (avalera)
 * @version
 * @date 2017-02-28
 *
 * @section DESCRIPTIOM
 *
 * Includes random standard libraries
 *
 * Defines error functions
 */

#ifndef __HAHALIB_H_
#define __HAHALIB_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

#define err_quit(...) fprintf(stderr, __VA_ARGS__), fflush(stderr), exit(1)
#define err_sys(...) perror(__VA_ARGS__), exit(1)

#define streq(str1, str2) \
  (strlen(str1) == strlen(str2)) && (strncmp(str1, str2, strlen(str1)) == 0)

#endif // __HAHALIB_H_
