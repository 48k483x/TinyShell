#include "../../minishell.h"

void redir(t_tiny *tiny, t_token *token, int type)
{
    printf("hadda li f redir token->next->str: %s\n", token->str);
    _close(tiny->fdout);
    
    if (type == TRUNC)
        tiny->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    else if (type == APPEND)
        tiny->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
    if (tiny->fdout < 0)
    {
        _perror("tiny: ");
        _perror(token->next->str);
        printsdr(": No such file or directory");
        tiny->ret = 1;
        tiny->no_exec = 1;
        return ;
    }
    dup2(tiny->fdout, STDOUT);
}

void    input(t_tiny *tiny, t_token *token)
{
    _close(tiny->fdin);
    tiny->fdin = open(token->str, O_RDONLY, S_IRWXU);
    if (tiny->fdin == -1)
    {
        _perror("tiny : ");
        _perror(token->str);
        printsdr(": No such file or directory");
        tiny->ret = 1;
        tiny->no_exec = 1;
        return ;
    }
    dup2(tiny->fdin, STDIN);
}

int tinypipe(t_tiny *tiny)
{
    int fd[2];
    pid_t pid;

    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        _close(fd[1]);
        dup2(fd[0], STDIN);
        tiny->pid = -1;
        tiny->parent = 0;
        tiny->no_exec = 0;
        return (2);
    }
    else
    {
        _close(fd[0]);
        dup2(fd[1], STDOUT);
        tiny->pid = pid;
        tiny->last = 0;
        return (1);
    }
}