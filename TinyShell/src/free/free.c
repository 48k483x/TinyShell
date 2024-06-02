#include "../../minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		_memdel(tmp->value);
		_memdel(tmp);
		tmp = NULL;
	}
}

void	free_token(t_tiny *tiny)
{
	t_token	*tmp;
	while (tiny->start)
	{
		tmp = tiny->start;
		tiny->start = tiny->start->next;
		_memdel(tmp->str);
		_memdel(tmp);
		tmp = NULL;
	}
}


void	free_all(t_tiny *tiny)
{
	free_env(tiny->env);
	free_env(tiny->private_env);
	free_token(tiny);
	rl_clear_history();
	printsdr("exit");
}
