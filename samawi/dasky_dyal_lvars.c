#include "../minishell.h"

char	*variable_expander(char *key, t_list *env_lst)
{
	t_env	*temp;
	char	*expanded;

	expanded = NULL;
	while (env_lst != NULL)
	{
		temp = env_lst->content;
		if (!(_strcmp(key, temp->key)))
			expanded = ft_strdup(temp->value);
		env_lst = env_lst->next;
	}
	return (expanded);
}