#include "../minishell.h"

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
    }
}