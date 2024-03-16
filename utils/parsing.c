#include "../minishell.h"

char *get_name()
{
    return (getenv("USER"));
}

char *initialise_prompt(t_tiny *tiny)
{
    tiny->prompt = _strcat(get_name(),"\033[0;34m@TinyShell\033[0m\033[0;33m $ \033[0m");
    return (tiny->prompt);
}

void path_checker(t_tiny *tiny)
{
    if (!tiny->line)
        return ;
    tiny->s = _split(tiny->line, ' ');
    tiny->env = _split(getenv("PATH"), ':');
    if (access(tiny->s[0], X_OK) == 0)
        tiny->path = tiny->s[0];
    else
    {
        tiny->i = 0;
        while (tiny->env[tiny->i])
        {
            tiny->path = _strcat(tiny->env[tiny->i], "/");
            tiny->path = _strcat(tiny->path, tiny->s[0]);
            if (access(tiny->path, X_OK) == 0)
                break ;
            tiny->i++;
            // free(tiny->path);
        }
        // if (tiny->path == NULL || access(tiny->path, X_OK) != 0)
        //     cmd_not_found(tiny->s[0], tiny->s, tiny->line, tiny->path);
    }
}
