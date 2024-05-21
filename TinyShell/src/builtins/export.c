#include "../../minishell.h"

int	print_error(int error, const char *arg)
{
	int	i;

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

int	is_in_env(t_env *env, char *args)
{
	char	var_name[BUFFER_SIZE];
	char	env_name[BUFFER_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (_strcmp(var_name, env_name) == 0)
		{
			_memdel(env->value);
			env->value = _strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	err_ret_value(int error, t_env *env, char **args)
{
	if (error == 2)
		return (1);
	else
		return (is_in_env(env, args[1]));
	return (0);
}

int	_export(char **args, t_env *env, t_env *secret)
{
	int	new_env;
	int	error_ret;

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
		new_env = err_ret_value(error_ret, env, args);
		if (new_env == 0)
		{
			if (error_ret == 1)
				env_add(args[1], env);
			env_add(args[1], secret);
		}
	}
	return (0);
}
