#include "../../minishell.h"

void		__error(char **args)
{
	_perror("cd: ");
	_perror(args[1]);
	if (args[2])
		printsdr("string not in pwd: ");
	else
	{
		_perror(": ");
		printsdr(strerror(errno));
	}
}

int			is_in_env(t_env *env, char *args)
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

int			env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = _strdup(value);
		return (0);
	}
	new = _malloc(sizeof(t_env));
	new->value = _strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (0);
}


 int		update_oldpwd(t_env *env)
{
	char	cwd[4096];
	char	*oldpwd;

	if (getcwd(cwd, 4096) == NULL)
		return (0);
	if (!(oldpwd = _strjoin("OLDPWD=", cwd)))
		return (0);
	if (is_in_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	_memdel(oldpwd);
	return (0);
}

int		go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = getenv("HOME");
		if (!env_path)
			return (printsdr("tiny: cd: HOME not set"));
	}
	else if (option == 1)
	{
		env_path = getenv("OLDPWD");
		if (!env_path)
			return (printsdr("tiny: cd: OLDPWD not set"));
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	// _memdel(env_path);
	return (ret);
}

int				_cd(char **args, t_env *env)
{
	int		cd_ret;

	if (!args[1])
		return (go_to_path(0, env));
	if (_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			__error(args);
	}
	return (cd_ret);
}
