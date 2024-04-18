#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define ERR 666
#define norm 555

#define ALL \
{ NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, \
NULL, NULL, 0, 0, NULL, 0, 0, 0}
extern char **environ;
/**
 * struct list - singly linked list
 * @num: num
 * @str: string
 * @next: next pointer
 */
typedef struct list
{
int num;
char *str;
struct list *next;
} list_t;

/**
 * struct all - contains pseudo-arguments to pass into a function
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit() s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct all
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;
char **cmd_buf;
int cmd_buf_type;
int readfd;
int histcount;
} info_t;


/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;

int _putchar(char c);

/* print all */
int putchar_all(char c, int fd);
int putsall(char *str, int fd);

/* Shell things */
int r_history(info_t *info);
int headsh(info_t *, char **);

/* Old and standard */

/* hsh.c */
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* path.c */
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);


/* string_functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *my_start(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *my_strdup(char *);

int is_delimiter(char ch, char *d);
/* string_functions3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *, char);

char **str_to_words(char *, char *);

void *_realloc(void *, unsigned int, unsigned int);

int must_free(void **);
char *_memset(char *s, char b, unsigned int n);


int erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convertSnumber(long int, int, int);
void removeComments(char *);

/* Builtin emulators.c */
int myexit(info_t *);
int mycd(info_t *);
int _myhelp(info_t *);

/* Builtin emulators2.c */
int _myhistory(info_t *);
int myalias(info_t *);

/* getline.c module */
size_t _get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void siginHandler(int);
size_t take_all_line(info_t *info, char **buf, size_t *len);


void set_info(info_t *, char **);
void free_info(info_t *, int);

/* env.c module */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);

/* env2.c module */
char **gets_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* file_io_functions.c */
char *get_history_file(info_t *info);
int end_history(info_t *info);
int creat_history_list(info_t *info, char *buf, int linecount);
int resum_history_lines(info_t *info);

/* liststr.c module */
list_t *add_node(list_t **, char *, int);
list_t *add_node_end(list_t **, char *, int);
size_t print_list_string(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_all_list(list_t **);

/* liststr2.c module */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t get_node_index(list_t *, list_t *);

/* chain.c */
int is_chain(info_t *, char *, size_t *);
void check_if_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **old, char *new);

#endif

