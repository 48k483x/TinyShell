#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>


/* Structs of TinyShell */
typedef struct s_tiny
{
    int i;
    int j;
    int k;
    char ***cmds;
    char **operators;
    char **full_cmd;
    char *name;
    char **env;
    char *prompt;
    char *path;
    char **s;
    char *line;
    pid_t pid;
}   t_tiny;

// typedef struct s_cmd
// {
//     char **cmd;
//     char *r_input; // redirect input    |   of course a si ay_man if any
//     char *r_output; // redirect output  |   of course a si ay_man if any
//     char *append; // > append file      |   of course a si ay_man if any
//     char *here_doc; // << here doc      |   of course a si ay_man if any
//     char *pipe; // | pipe               |   of course a si ay_man if any
//     struct  s_cmd *next;
// }; t_cmd;

/* functions of lib_ft utils*/
char *_strcat(char *dest, char *src);
char	**_split(char const *s, char c);
int _strcmp(const char *s1, const char *s2);
size_t    _strlen(const char *s);

/* Split Utils */
int	count_strings(char const *s, char c);
char	*malloc_strings(const char *s, char c);

/* Free Utils */
void	free_split(char **split);

/* Error Handling functions */
void cmd_not_found(char *cmd, char **s, char *line, char *path);
void execve_error(t_tiny *tiny);

/* Parsing function */
char *get_name();
char *initialise_prompt(t_tiny *tiny);
void path_checker(t_tiny *tiny);
/* Signal */
void    sig_handler(int signum);
void sigchld_handler(int signum);

/* Free */
void _free(t_tiny *tiny);


#endif // MINI_SHELL_H