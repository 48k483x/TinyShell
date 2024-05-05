#include "../minishell.h"

void _free(t_tini *tiny)
{
    free_split(tiny->s);
    free(tiny->line);
    free(tiny->prompt);
}