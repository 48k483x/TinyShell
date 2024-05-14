#include "../../minishell.h"

int		ret_size(int ret)
{
	char	*tmp;
	int		ret_len;

	tmp = _itoa(ret);
	ret_len = _strlen(tmp);
	_memdel(tmp);
	return (ret_len);
}

int		get_var_len(const char *arg, int pos, t_env *env, int ret)
{
	char	var_name[BUFFER_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
		return (ret_size(ret));
	if (_isdigit(arg[pos]))
		return (0);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFFER_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = fetch_env(var_name, env);
	i = _strlen(var_value);
	_memdel(var_value);
	return (i);
}

int		arg_alloc_len(const char *arg, t_env *env, int ret)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (arg[++i])
	{
		if (arg[i] == EXPANSION)
		{
			i++;
			if ((arg[i] == '\0' || _isalnum(arg[i]) == 0) && arg[i] != '?')
				size++;
			else
				size += get_var_len(arg, i, env, ret);
			if (_isdigit(arg[i]) == 0)
			{
				while (arg[i + 1] && is_env_char(arg[i]))
					i++;
			}
			else
				size--;
		}
		size++;
	}
	return (size);
}

char	*get_var_value(const char *arg, int pos, t_env *env, int ret)
{
	char	var_name[BUFFER_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
	{
		var_value = _itoa(ret);
		return (var_value);
	}
	if (_isdigit(arg[pos]))
		return (NULL);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFFER_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = fetch_env(var_name, env);
	return (var_value);
}
