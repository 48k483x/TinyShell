#include "../../minishell.h"


int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i])
	{
		if ((s1[i] == '\0' && s2[i] == '\0') || i == n - 1)
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

void		free_node(t_tiny *tiny, t_env *env)
{
	if (tiny->env == env && env->next == NULL)
	{
		_memdel(tiny->env->value);
		tiny->env->value = NULL;
		tiny->env->next = NULL;
		return ;
	}
	_memdel(env->value);
	_memdel(env);
}

int				_unset(char **a, t_tiny *tiny)
{
	t_env	*env;
	t_env	*tmp;
	printf("im here\n");
	env = tiny->env;
	if (!(a[1]))
		return (0);
	if (_strncmp(a[1], env->value, env_size(env->value)) == 0)
	{
		tiny->env = (env->next) ? env->next : tiny->env;
		free_node(tiny, env);
		return (0);
	}
	while (env && env->next)
	{
		if (_strncmp(a[1], env->next->value, env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_node(tiny, env->next);
			env->next = tmp;
			return (0);
		}
		env = env->next;
	}
	return (0);
}
