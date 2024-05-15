#include "../../minishell.h"

int	print_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		_perror("export: not valid in this context: " );
	else if (error == 0 || error == -3)
		_perror("export: not a valid identifier: " );
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(2, &arg[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (0);
}


int			_export(char **args, t_env *env, t_env *secret)
{
	int		new_env;
	int		error_ret;

	new_env = 0;
	if (!args[1])
	{
		print_sorted_env(secret);
		return (0);
	}
	else
	{
		error_ret = is_valid_env(args[1]);
		if (args[1][0] == '=')
			error_ret = -3;
		if (error_ret <= 0)
			return (print_error(error_ret, args[1]));
		new_env = error_ret == 2 ? 1 : is_in_env(env, args[1]);
		if (new_env == 0)
		{
			if (error_ret == 1)
				env_add(args[1], env);
			env_add(args[1], secret);
		}
	}
	return (0);
}
