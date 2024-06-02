#include "../../minishell.h"

int	_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

size_t	size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += _strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char	*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	env = _malloc(sizeof(char) * size_env(lst) + 1);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				i++;
				j++;
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

int	init_env(t_tiny *tiny, char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = _malloc(sizeof(t_env));
	env->value = _strdup(envp[0]);
	env->next = NULL;
	tiny->env = env;
	i = 1;
	while (envp && envp[0] && envp[i])
	{
		new = _malloc(sizeof(t_env));
		new->value = _strdup(envp[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

int	private_init_env(t_tiny *tiny, char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = _malloc(sizeof(t_env));
	env->value = _strdup(envp[0]);
	env->next = NULL;
	tiny->private_env = env;
	i = 1;
	while (envp && envp[0] && envp[i])
	{
		new = _malloc(sizeof(t_env));
		new->value = _strdup(envp[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
