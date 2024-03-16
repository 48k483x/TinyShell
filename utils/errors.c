#include "../minishell.h"

void cmd_not_found(char *cmd, char **s, char *line, char *path)
{
    printf("TinyShell: %s: command not found\n", cmd);
    free_split(s);
    free(path);
    free(line);
}
