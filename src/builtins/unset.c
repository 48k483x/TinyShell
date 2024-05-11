#include "minishell.h"

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void		free_node(t_mini *mini, t_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	_memdel(env->value);
	_memdel(env);
}

int				_unset(char **a, t_mini *mini)
{
	t_env	*env;
	t_env	*tmp;

	env = mini->env;
	if (!(a[1]))
		return (SUCCESS);
	if (_strncmp(a[1], env->value, env_size(env->value)) == 0)
	{
		mini->env = (env->next) ? env->next : mini->env;
		free_node(mini, env);
		return (SUCCESS);
	}
	while (env && env->next)
	{
		if (_strncmp(a[1], env->next->value, env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_node(mini, env->next);
			env->next = tmp;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}
