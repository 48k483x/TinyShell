#include "minishell.h"

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
        signal(SIGQUIT, quit_handler);
        tiny.line = readline(read);
        if (!tiny.line || _strlen(tiny.line) == 0)
        {
            continue;
        }
        history(tiny.line);
        if (tiny.line && !check_syntax(tiny.line))
        {
            parse(&tiny);
            // _memdel(tiny.line);
        }

    }
    _memdel(read);
    free_all(&tiny);
    rl_clear_history();
}
