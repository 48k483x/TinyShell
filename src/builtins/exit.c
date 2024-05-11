#include "minishell.h"

void	mini_exit(t_mini *mini, char **cmd)
{
	mini->exit = 1;
	_putstr_fd("exit " );
	cmd[1] ? printsdr("❤️") : printsdr("💚");
	if (cmd[1] && cmd[2])
	{
		mini->ret = 1;
		printsdr("minishell: exit: too many arguments" );
	}
	else if (cmd[1] && _strisnum(cmd[1]) == 0)
	{
		mini->ret = 255;
		_putstr_fd("minishell: exit: " );
		_putstr_fd(cmd[1] );
		printsdr(": numeric argument required" );
	}
	else if (cmd[1])
		mini->ret = _atoi(cmd[1]);
	else
		mini->ret = 0;
}
