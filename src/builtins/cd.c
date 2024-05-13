#include "../../minishell.h"

static void		print_error(char **args)
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

static char		*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (_strncmp(env->value, var, len) == 0)
		{
			s_alloc = _strlen(env->value) - len;
			if (!(oldpwd = malloc(sizeof(char) * s_alloc + 1)))
				return (NULL);
			i = 0;
			j = 0;
			while (env->value[i++])
			{
				if (i > (int)len)
					oldpwd[j++] = env->value[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int		update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (0);
	if (!(oldpwd = _strjoin("OLDPWD=", cwd)))
		return (0);
	if (is_in_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	_memdel(oldpwd);
	return (0);
}

static int		go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			printsdr("tiny: cd: HOME not set");
		if (!env_path)
			return (0);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			printsdr("tiny: cd: OLDPWD not set");
		if (!env_path)
			return (0);
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	_memdel(env_path);
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
			print_error(args);
	}
	return (cd_ret);
}
