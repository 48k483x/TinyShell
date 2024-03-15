#include "minishell.h"

char *get_name()
{
    return (getenv("USER"));
}


int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    pid_t pid;
    char *prompt = _strcat(get_name(),"\033[0;34m@TinyShell\033[0m\033[0;33m $ \033[0m");
    while (1)
    {
        char *line = readline(prompt);
        if (line != NULL)
        {
            char **s = ft_split(line, ' ');
            char *path = _strcat("/bin/", s[0]);
            pid = fork();
            if (pid == -1 )
                break ;
            else if (pid == 0 && s[0] != NULL)
            {
                if (execve(path, s, NULL) == -1)
                {
                    cmd_not_found(s[0], s, line, path);
                    continue ;
                }
            }
            else
                waitpid(pid, NULL, 0);
        }
    }
}

