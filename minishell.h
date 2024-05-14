#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <limits.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# define BUFFER_SIZE 4096
# define STDIN 0
# define STDOUT 1

# define SKIP 1
# define NOSKIP 0

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define APPEND_OPPOSITE 5
# define DELIM 6
# define INPUT 7
# define PIPE 8
# define END 9



typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;
extern t_sig g_sig;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_tiny
{
	char			*line;
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




/* _libft functions */
int		_strisnum(char *str);
void 	_str_trim(char *line);
char	*_strchr(const char *s, int c);
void	_skip_32(char *line, int *i);
int		_strcmp(const char *s1, const char *s2);


/* __libft functions */
int		_strcpy(char *dest, char *src);
char	*_strcat(char *dest, char *src);
size_t	_strlen(const char *s);
char	*_strdup(const char *s1);
char	*_strjoin(char *dest, char *src);


/* Errors functions*/
void	*_malloc(size_t size);
void	*_memdel(void *ptr);
void 	_perror(char *str);
int		printsdr(char *str);


/* Split functions */
char	**_split(char const *s, char c);
int		_atoi(char *s);
int		count_strings(char const *s, char c);
char	*malloc_strings(const char *s, char c);
void	free_split(char **split);


/* Env Functions */
int		init_env(t_tiny *tiny, char **envp);
int		private_init_env(t_tiny *tiny, char **envp);



/* ENV GET_ENV FUNCTIONS*/
int		env_value_len(char *env_value);
char	*get_env_value(char *env_value);
char	*fetch_env(char *arg, t_env *env);



/* SHLVL FUNCTIONS */
void	set_shell_level(t_env *env);
char	*get_env_name(char *dest, char *src);
int		false_lvl(char *sh_val);




/* Signals Functions */
void	int_handler(int signum);
void	quit_handler(int signum);
void	disable_echo(void);


/* Check Syntax Functions */
int		check_syntax(char *str);
int		redirection_syntax_errors(char *str, int i);
int		check_for_quote(char c, int quote);
int		check_quote_errors(char *s);
int		skip_quotes(char *str, int i);
int		check_redir_errors(char *str);
int		check_pipe_errors(char *str);
int		pipe_and_semi_errors(char *str);



/* PARSE GET_TOKENS FUNCTIONS */
int 	ignore_ope(char *line, int i);
void	token_type(t_token *token, int sep);
int 	next_alloc(char *line, int *i);
t_token *next_token(char *line, int *i);
t_token	*get_token(char *line);

/* PARSE FUNCTIONS */
int		is_operator(char *s, int index);
char	*spacing(char *s);
char	*space_line(char *line);
void	parse(t_tiny *tiny);
int 	quotes(char *s, int index);



/* Exec Bin Functions*/
char	**path_checker(t_token *token);
char	**two_dx(t_token *start);
void 	magic(t_token *token, t_tiny *tiny);



/* Exec Redir Functions*/
void	redir(t_tiny *tiny, t_token *token, int type);
int		tinypipe(t_tiny *tiny);
void	input(t_tiny *tiny, t_token *token);
void	redir_her_doc(t_tiny *tiny, t_token *token);



/* Exec Builitin Functions*/
char	*last_word(char *str);
int 	is_builtin(char *str);
int 	exec_builtin(char **args, t_tiny *tiny);



/* _CD  Functions*/
void	print_error(char **args);
int		is_in_env(t_env *env, char *args);
int		env_add(const char *value, t_env *env);
int		update_oldpwd(t_env *env);
int 	go_to_path(int option, t_env *env);
int		_cd(char **args, t_env *env);



/* Echo Functions */
int 	nb_args(char **args);
int		_echo(char **args);



/* ENV BUILTIN FUNCTION */
void	_putendl(char *s);
int 	_env(t_env *env);



/* EXIT BUILTIN FUNCTION */
void 	__exit(t_tiny *tiny, char **args);




/* PWD BUILTIN FUNCTION */
int 	_pwd(void);



/* TOOLS FILE DESCREPTORS FD.C FUNCTIONS */
void	_close(int fd);
void	reset_fds(t_tiny *tiny);
void	reset_std(t_tiny *tiny);
void	_close_fds(t_tiny *tiny);



/* TOOLS TOKEN.C FUNCITONS */
t_token	*next_run(t_token *token);
t_token	*prev_sep(t_token *token);
t_token	*next_sep(t_token *token);
int 	has_pipe(t_token *token);



/* TOOLS TYPE.C FUNCTIONS */
int		is_type(t_token *token, int type);
int		is_types(t_token *token, char *types);




/* MINISHELL.C OR THE MAIN.C, THE BEGINING OF THE PROGRAM*/
void	history(char *line);
char	*initialise_prompt(void);
void	redir_exec(t_tiny *tiny, t_token *token);
void	exec(t_tiny *tiny);



/* free */
void	free_env(t_env *env);
void	free_all(t_tiny *tiny);

#endif // MINI_SHELL_H