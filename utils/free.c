#include "./minishell.h"

void _free(t_tiny *tiny)
{
    free_split(tiny->s);
    free(tiny->line);
    free(tiny->prompt);
}