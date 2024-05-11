#include "minishell.h"

int		_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		_putendl(env->value);
		env = env->next;
	}
	if (env)
		_putendl(env->value);
	return (0);
}
