#include "minishell.h"

void execve_error(t_tiny *tiny)
{
    if ((execve(tiny->path, tiny->s, NULL) == -1))
        cmd_not_found(tiny->s[0], tiny->s, tiny->line, tiny->path);
}

int main()
{
    t_tiny tiny;

    while (1)
    {
        tiny.line = readline(initialise_prompt(&tiny));
        if (tiny.line)
            path_checker(&tiny);
        tiny.pid = fork();
        if (tiny.pid == 0)
            execve_error(&tiny);
        else
            waitpid(tiny.pid, NULL, 0);
    }   
}
