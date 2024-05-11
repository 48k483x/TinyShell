#include "minishell.h"

t_sig g_sig;

char *get_name(void)
{
    return (getenv("USER"));
}

void history(char *line)
{
    if (line && *line)
        add_history(line);
}
char *initialise_prompt(void)
{
    char *prompt;
    char dir[200];
    char *pwd;

    pwd = getenv("PWD");
    while (*pwd)
    {
        if (*pwd == '/')
        {
            pwd++;
            _strcpy(dir, pwd);
        }
        pwd++;
    }
    prompt = _strcat(dir, " \033[1;33m$ \033[0m");
    return (prompt);
}

void redir_exec(t_tiny *tiny, t_token *token)
{
    t_token *prev;
    t_token *next;
    int pipe;

    prev = prev_sep(token);
    next = next_sep(token);
    // printf("prev->str: %s\n", prev->str);
    // printf("prev->type: %d\n", prev->type);
    // printf("token->str: %s\n", token->str);
    // printf("next->type: %d\n", next->type);
    pipe = 0;
    if (is_type(prev, TRUNC))
        redir(tiny, token, TRUNC);
    else if (is_type(prev, APPEND))
        redir(tiny, token, APPEND);
    else if (is_type(prev, INPUT))
        input(tiny, token);
    else if (is_type(prev, PIPE))
        pipe = tinypipe(tiny);
    printf("prev->str: %s\n", prev->str);
    printf("prev->type: %d\n", prev->type);
    magic(prev);

}

void exec(t_tiny *tiny)
{
    t_token *token;
    // int status;

    token = next_run(tiny->start);
    if (is_types(tiny->start, "TAIW"))
        token = tiny->start->next; 
    while (tiny->exit == 0 && token)
    {
        tiny->parent = 0;
        tiny->charge = 0;
        tiny->last = 0;
        redir_exec(tiny, token);
        reset_std(tiny);
        _close_fds(tiny);
        reset_fds(tiny);
        token = token->next;
        token = next_run(token);
    }
}

int main(int ac, char **av, char **env)
{
    if(ac != 1 || !env)
        return (1);
    t_tiny tiny;
    char *read = initialise_prompt();
    (void)ac;
    (void)av;
    tiny.in = dup(STDIN);
    tiny.out = dup(STDOUT);
    tiny.exit = 0;
    tiny.ret = 0;
    tiny.no_exec = 0;
    reset_fds(&tiny);
    init_env(&tiny, env);
    private_init_env(&tiny,env);
    set_shell_level(tiny.env);
    while (tiny.exit == 0)
    {
        disable_echo();
        signal(SIGINT, int_handler);
        signal(SIGQUIT, SIG_IGN);
        tiny.line = readline(read);
        if (!tiny.line || _strlen(tiny.line) == 0)
        {
            continue;
        }
        history(tiny.line);
        if (tiny.line && !check_syntax(tiny.line))
        {
            parse(&tiny);
            exec(&tiny);
        }

    }
    _memdel(read);
    free_all(&tiny);
    rl_clear_history();
}
