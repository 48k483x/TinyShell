#include "../../minishell.h"

void	_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_fds(t_tiny *tiny)
{
	tiny->fdin = -1;
	tiny->fdout = -1;
	tiny->pipin = -1;
	tiny->pipout = -1;
	tiny->pid = -1;
}

void	reset_std(t_tiny *tiny)
{
	dup2(tiny->in, STDIN);
	dup2(tiny->out, STDOUT);
}

void	_close_fds(t_tiny *tiny)
{
	_close(tiny->fdin);
	_close(tiny->fdout);
	_close(tiny->pipin);
	_close(tiny->pipout);
}
