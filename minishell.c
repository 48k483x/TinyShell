#include "minishell.h"

char *get_name(void)
{
    return (getenv("USER"));
}

char *initialise_prompt(void)
{
    char *prompt;

    prompt = _strcat(get_name(),"\033[0;34m@TinyShell\033[0m\033[0;33m $ \033[0m");
    return (prompt);
}


int main(int ac, char **av, char **env)
{
    t_tiny tiny;
    
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
        tiny.line = readline(initialise_prompt());
        if (!tiny.line || _strlen(tiny.line) == 0)
            continue;
        if (tiny.line && !check_syntax(tiny.line))
        {
            add_history(tiny.line);
        }
    }
    free_all(&tiny);
}
