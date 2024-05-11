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

#define BUFFER_SIZE 4096
#define STDIN 0
#define STDOUT 1

/* gnl */
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

int		found_newline(t_list *list);
t_list	*find_lst_node(t_list *list);
char	*get_line(t_list *list);
void	copy_str(t_list *list, char *str);
int		len_to_newline(t_list *list);
void	polish_list(t_list **list);
char	*get_next_line(int fd);
void	dealloc(t_list **list, t_list *clean_node, char *buf);
void	create_list(t_list **list, int fd);
void	append(t_list **list, char *buf);

/* finish gnl */

typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
} t_token;

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_tiny
{
	char            *line; 
	t_token			*start;
	t_env			*env;
	t_env			*private_env;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				no_exec;
}				t_tiny;

/* Structs of TinyShell */
typedef struct s_tini
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
}   t_tini;



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
void *_memdel(void *ptr);
int _atoi(char *s);
char *_strjoin(char *dest, char *src);
/* Split Utils */
int	count_strings(char const *s, char c);
char	*malloc_strings(const char *s, char c);

/* Free Utils */
void	free_split(char **split);

/* Error Handling functions */
void cmd_not_found(char *cmd, char **s, char *line, char *path);
void execve_error(t_tini *tiny);
int printsdr(char *str);

/* Parsing function */
char *get_name(void);
char *initialise_prompt(void);
void path_checker(t_tini *tiny);
/* Signal */
void    sig_handler(int signum);
void sigchld_handler(int signum);

/* Free */
void _free(t_tini *tiny);

/* Check Syntax */
int check_syntax(char *str);
int redirection_syntax_errors(char *str, int i);
int check_for_quote(char c, int quote);
int check_quote_errors(char *s);
int skip_quotes(char *str, int i);
int check_redir_errors(char *str);
char *_strtrim_inplace(char *s);
int check_pipe_errors(char *str);
int pipe_and_semi_errors(char *str);


/* tools */
void reset_fds(t_tiny *tiny);

/* env */
int  init_env(t_tiny *tiny, char **envp);
int private_init_env(t_tiny *tiny, char **envp);

/* get env */
int env_value_len(char *env_value);
char *get_env_value(char *env_value);
char *fetch_env(char *arg, t_env *env);

/* shlvl */
void set_shell_level(t_env *env);
char *get_env_name(char *dest, char *src);
int false_lvl(char *sh_val);

/* free */
void free_env(t_env *env);
void free_all(t_tiny *tiny);

#endif // MINI_SHELL_H