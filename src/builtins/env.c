#include "../../minishell.h"

void	_putendl(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
		write(1, &s[i++], 1);
	write(1, "\n", 1);
}

int	_env(t_env *env)
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
