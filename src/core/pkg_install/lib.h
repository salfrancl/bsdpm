/* $FreeBSD$ */

/*
 * FreeBSD install - a package for the installation and maintainance
 * of non-core utilities.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * Jordan K. Hubbard
 * 18 July 1993
 *
 * Include and define various things wanted by the library routines.
 *
 */

/*
 * This file was modified in order to fit BSDPM requirements
 */
 
#ifndef _INST_LIB_LIB_H_
#define _INST_LIB_LIB_H_

/* Includes */
#include <sys/param.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/queue.h>
#include <ctype.h>
#include <dirent.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum _plist_t {
    PLIST_FILE, PLIST_CWD, PLIST_CMD, PLIST_CHMOD,
    PLIST_CHOWN, PLIST_CHGRP, PLIST_COMMENT, PLIST_IGNORE,
    PLIST_NAME, PLIST_UNEXEC, PLIST_SRC, PLIST_DISPLAY,
    PLIST_PKGDEP, PLIST_CONFLICTS, PLIST_MTREE, PLIST_DIR_RM,
    PLIST_IGNORE_INST, PLIST_OPTION, PLIST_ORIGIN, PLIST_DEPORIGIN,
    PLIST_NOINST
};
typedef enum _plist_t plist_t;

struct _plist {
    struct _plist *prev, *next;
    char *name;
    unsigned int marked;
    plist_t type;
};
typedef struct _plist *PackingList;

struct _pack {
    struct _plist *head, *tail;
    const char *name;
    const char *origin;
    int fmtver_maj, fmtver_mnr;
};
typedef struct _pack Package;

/* Version */
int		verscmp(Package *, int, int);
int		version_cmp(const char *, const char *);

#endif /* _INST_LIB_LIB_H_ */
