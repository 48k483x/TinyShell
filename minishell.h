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
#include <stdbool.h>


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

typedef struct s_cli
{
    char **cmd;
    struct  s_cli *next;
} t_cli;

/* functions of lib_ft utils*/
char *_strcat(char *dest, char *src);
char	**_split(char const *s, char c);
int _strcmp(const char *s1, const char *s2);
size_t    _strlen(const char *s);
void *_memcpy(void *dest, const void *src, size_t n);
void *_realloc(void *ptr, size_t size);
void *_malloc(size_t size);
char	*_strdup(const char *s1);
/* Split Utils */
int	count_strings(char const *s, char c);
char	*malloc_strings(const char *s, char c);

/* Free Utils */
void	free_split(char **split);

/* Error Handling functions */
void cmd_not_found(char *cmd, char **s, char *line, char *path);
void execve_error(t_tiny *tiny);
int printsdr(char *str);

/* Parsing function */
char *get_name();
char *initialise_prompt(t_tiny *tiny);
void path_checker(t_tiny *tiny);
/* Signal */
void    sig_handler(int signum);
void sigchld_handler(int signum);

/* Free */
void _free(t_tiny *tiny);


//samawi structs

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd 
{
	char					*cmd;
	char					**args;
	t_list					*redir;
}   t_cmd;

typedef struct s_var
{
	int						i;
	char					*result;
} t_var;

typedef struct s_prs
{
	int						arg_num;
	int						i;
	int						ambigous;
	int						ret_value;
	char					**extra_args;
	int						outside_quote;
	t_var					var;
} t_prs;

typedef struct s_env
{
	char					*key;
	char					*value;
}t_env;

typedef struct s_redir
{
	char					type;
	char					*file;
}t_redir;
//samawi functions
int	        check_for_quote(char c, int quote);
int	        check_syntax(char *s);
int	        pipe_and_semi_errors(char *str);
int	        check_pipe_errors(char *s);
int	        check_quote_errors(char *s);
int	        check_redir_errors(char *str);
int	        get_size(char *s);
char        *ft_strtrim_inplace(char *s);
void	    allocate_args(char *s, t_cmd *cmd, t_list *env_lst);
char	    *_substr(char const *s, unsigned int start, size_t len);
static char	*change_pipe(char *s);
static int	skip_space_and_redir(char *s, int i);


#endif // MINI_SHELL_H