#include "../../minishell.h"
void _perror(char *str)
{
    size_t i;

    if (!str)
        return ;
    i = _strlen(str);
    write(2, str, i);
}
int printsdr(char *str)
{
    size_t i;

    if (!str)
        return 0;
    i = _strlen(str);
    write(2, str, i);
    write(2, "\n", 1);
    return 1;
}
