#include "../../minishell.h"


void	__exit(t_tiny *tiny, char **cmd)
{
	tiny->exit = 1;
	_perror("exit\n");
	if (cmd[1] && cmd[2])
	{
		tiny->ret = 1;
		printsdr("tinyshell: exit: too many arguments");
	}
	else if (cmd[1] && _strisnum(cmd[1]) == 0)
	{
		tiny->ret = 255;
		_perror("tinyshell: exit: ");
		_perror(cmd[1] );
		printsdr(": numeric argument required");
	}
	else if (cmd[1])
		tiny->ret = _atoi(cmd[1]);
	else
		tiny->ret = 0;
}
