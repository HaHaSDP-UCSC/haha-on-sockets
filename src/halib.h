/**
 * @file halib.h
 * @brief stdlib for HAHA project, contains imports and defines
 * @author August Valera (avalera)
 * @version
 * @date 2017-02-28
 */

#ifndef _HA_HALIB_
#define _HA_HALIB_

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

#endif // _HA_HALIB_
