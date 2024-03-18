#include "minishell.h"

void _fork(t_tiny *tiny)
{
    tiny->pid = fork();
    if (tiny->pid < 0)
        perror("fork");
    if (tiny->pid == 0)
        execve_error(tiny);
    else
        waitpid(tiny->pid, NULL, 0);
}

int main()
{
    t_tiny tiny;

    while (1)
    {
        signal(SIGINT, sig_handler);
        signal(SIGCHLD, sigchld_handler);
        tiny.line = readline(initialise_prompt(&tiny));
        if (!tiny.line || strlen(tiny.line) == 0)
            continue;
        if (tiny.line)
        {
            path_checker(&tiny);
            add_history(tiny.line);
        }
        _fork(&tiny);
    }
    _free(&tiny);
}
