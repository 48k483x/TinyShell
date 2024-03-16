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
        printf("Error: No command entered\n");
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
                break;
            tiny->i++;
        }
    }
}
