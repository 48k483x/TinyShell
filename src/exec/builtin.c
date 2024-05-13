#include "../../minishell.h"

char *last_word(char *str)
{
    char *last;
    int i;

    i = 0;
    last = NULL;
    while (str[i])
    {
        if (str[i] == '/')
            last = &str[i + 1];
        i++;
    }
    return (last);
}

int is_builtin(char *str)
{
    char *lw = last_word(str);
    printf("im in is_builtin -> str: %s\n", lw);
    if (!lw)
        return (0);
    if (_strcmp(lw, "echo") == 0)
        return (1);
    if (_strcmp(lw, "cd") == 0)
        return (1);
    if (_strcmp(lw, "pwd") == 0)
        return (1);
    if (_strcmp(lw, "export") == 0)
        return (1);
    if (_strcmp(lw, "unset") == 0)
        return (1);
    if (_strcmp(lw, "env") == 0)
        return (1);
    return (0);
}

int exec_builtin(char **args, t_tiny *tiny)
{
    (void)tiny;
    char *lw = last_word(args[0]);
    if (_strcmp(lw, "echo") == 0)
        return (_echo(args));
    if (_strcmp(lw, "pwd") == 0)
        return (_pwd());
    return (0);
}