#ifdef _WIN32
#ifndef __GETOPT_H__
#define __GETOPT_H__

/* All the headers include this file. */
#include <crtdefs.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define REPLACE_GETOPT /* use this getopt as the system getopt(3) */

//extern int optind;        /* index of first non-option in argv      */
//extern int optopt;        /* single option character, as parsed     */
//extern int opterr;        /* flag to enable built-in diagnostics... */
//              /* (user may set to zero, to suppress)    */
//
//extern char *optarg;      /* pointer to argument of current option  */

#define PRINT_ERROR ((opterr) && (*options != ':'))

#define FLAG_PERMUTE 0x01 /* permute non-options to the end of argv */
#define FLAG_ALLARGS 0x02 /* treat non-options as args to option "-1" */
#define FLAG_LONGONLY 0x04 /* operate as getopt_long_only */

/* return values */
#define BADCH (int)'?'
#define BADARG ((*options == ':') ? (int)':' : (int)'?')
#define INORDER (int)1

#ifndef __CYGWIN__
#define __progname __argv[0]
#else
extern char __declspec(dllimport)* __progname;
#endif

#ifdef __CYGWIN__
static char EMSG[] = "";
#else
#define EMSG ""
#endif

static int getopt_internal(int, char* const*, const char*,
                           const struct option*, int*, int);
static int parse_long_options(char* const*, const char*,
                              const struct option*, int*, int);
static int gcd(int, int);
static void permute_args(int, int, int, char* const*);

static char* place = EMSG; /* option letter processing */

/* XXX: set optreset to 1 rather than these two */
static int nonopt_start = -1; /* first non option argument (for permute) */
static int nonopt_end = -1; /* first option after non options (for permute) */

/* Error messages */
static const char recargchar[] = "option requires an argument -- %c";
static const char recargstring[] = "option requires an argument -- %s";
static const char ambig[] = "ambiguous option -- %.*s";
static const char noarg[] = "option doesn't take an argument -- %.*s";
static const char illoptchar[] = "unknown option -- %c";
static const char illoptstring[] = "unknown option -- %s";

static void _vwarnx(const char* fmt, va_list ap);

static void warnx(const char* fmt, ...);

/*
    Compute the greatest common divisor of a and b.
*/
static int gcd(int a, int b);

/*
    Exchange the block from nonopt_start to nonopt_end with the block
    from nonopt_end to opt_end (keeping the same order of arguments
    in each block).
*/
static void permute_args(int panonopt_start, int panonopt_end, int opt_end, char* const* nargv);

#ifdef REPLACE_GETOPT
/*
    getopt --
    Parse argc/argv argument vector.

    [eventually this will replace the BSD getopt]
*/
int getopt(int nargc, char* const* nargv, const char* options);
#endif /* REPLACE_GETOPT */

//extern int getopt(int nargc, char * const *nargv, const char *options);

#ifdef _BSD_SOURCE
/*
    BSD adds the non-standard `optreset' feature, for reinitialisation
    of `getopt' parsing.  We support this feature, for applications which
    proclaim their BSD heritage, before including this header; however,
    to maintain portability, developers are advised to avoid it.
*/
#define optreset __mingw_optreset
extern int optreset;
#endif
#ifdef __cplusplus
}
#endif
/*
    POSIX requires the `getopt' API to be specified in `unistd.h';
    thus, `unistd.h' includes this header.  However, we do not want
    to expose the `getopt_long' or `getopt_long_only' APIs, when
    included in this manner.  Thus, close the standard __GETOPT_H__
    declarations block, and open an additional __GETOPT_LONG_H__
    specific block, only when *not* __UNISTD_H_SOURCED__, in which
    to declare the extended API.
*/
#endif /* !defined(__GETOPT_H__) */

#if !defined(__UNISTD_H_SOURCED__) && !defined(__GETOPT_LONG_H__)
#define __GETOPT_LONG_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
    parse_long_options --
    Parse long options in argc/argv argument vector.
    Returns -1 if short_too is set and the option does not match long_options.
*/
static int parse_long_options(char* const* nargv, const char* options, const struct option* long_options, int* idx, int short_too);

/*
    getopt_internal --
    Parse argc/argv argument vector.  Called by user level routines.
*/
static int getopt_internal(int nargc, char* const* nargv, const char* options, const struct option* long_options, int* idx, int flags);

/*
    getopt_long --
    Parse argc/argv argument vector.
*/
int getopt_long(int nargc, char* const* nargv, const char* options, const struct option* long_options, int* idx);

/*
    getopt_long_only --
    Parse argc/argv argument vector.
*/
int getopt_long_only(int nargc, char* const* nargv, const char* options, const struct option* long_options, int* idx);

/*
    Previous MinGW implementation had...
*/
#ifndef HAVE_DECL_GETOPT
/*
    ...for the long form API only; keep this for compatibility.
*/
#define HAVE_DECL_GETOPT 1
#endif

#ifdef __cplusplus
}
#endif

#endif /* !defined(__UNISTD_H_SOURCED__) && !defined(__GETOPT_LONG_H__) */
#endif
