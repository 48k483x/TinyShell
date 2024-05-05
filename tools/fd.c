#include "../minishell.h"

void reset_fds(t_tiny *tiny)
{
    tiny->fdin = -1;
    tiny->fdout = -1;
    tiny->pipin = -1;
    tiny->pipout = -1;
    tiny->pid = -1;
}