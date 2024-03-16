#include "minishell.h"

int main()
{
    t_tiny tiny;

    while (1)
    {
        tiny.line = readline(initialise_prompt(&tiny));
        if (tiny.line)
            path_checker(&tiny);
        printf("tiny.path: %s\n", tiny.path);
        tiny.pid = fork();
        if (tiny.pid == 0)
            execve(tiny.path, tiny.s, NULL);
        else
            waitpid(tiny.pid, NULL, 0);
    }   
}
