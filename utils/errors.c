#include "../minishell.h"

void cmd_not_found(char *cmd, char **s, char *line, char *path)
{
    printf("TinyShell: %s: command not found\n", cmd);
    free_split(s);
    free(path);
    free(line);
}

void execve_error(t_tiny *tiny)
{
    if ((execve(tiny->path, tiny->s, NULL) == -1))
        cmd_not_found(tiny->s[0], tiny->s, tiny->line, tiny->path);
}
