#include "../../minishell.h"

char	*last_word(char *str)
{
	char	*last;
	int		i;

	i = 0;
	last = str;
	while (str[i])
	{
		if (str[i] == '/')
			last = &str[i + 1];
		i++;
	}
	return (last);
}

int	is_builtin(char *str)
{
	char	*lw;

	lw = last_word(str);
	if (!lw)
		return (0);
	if (_strcmp(lw, "echo") == 0)
		return (1);
	if (_strcmp(lw, "cd") == 0)
		return (1);
	if (_strcmp(lw, "pwd") == 0)
		return (1);
	if (_strcmp(lw, "export") == 0)
		return (1);
	if (_strcmp(lw, "unset") == 0)
		return (1);
	if (_strcmp(lw, "env") == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **args, t_tiny *tiny)
{
	char	*lw;

	(void)tiny;
	lw = last_word(args[0]);
	if (_strcmp(lw, "echo") == 0)
		return (_echo(args));
	if (_strcmp(lw, "pwd") == 0)
		return (_pwd());
	if (_strcmp(lw, "cd") == 0)
		return (_cd(args, tiny->env));
	if (_strcmp(lw, "env") == 0)
		return (_env(tiny->env));
	if (_strcmp(lw, "unset") == 0)
		return (_unset(args, tiny));
	if (_strcmp(lw, "export") == 0)
		return (_export(args, tiny->env, tiny->private_env));
	return (0);
}
