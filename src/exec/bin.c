#include "../../minishell.h"

char	**two_dx(t_token *start)
{
	t_token	*token;
	char	**str;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 1;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	str = _malloc(sizeof(char *) * (i + 1));
	str[0] = start->str;
	i = 1;
	token = start->next;
	while (token && token->type < TRUNC)
	{
		str[i] = token->str;
		token = token->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**path_checker(t_token *token)
{
	char	**str;
	char	*path;
	char	**env;
	int		i;

	i = -1;
	str = two_dx(token);
	env = _split(getenv("PATH"), ':');
	if (access(str[0], X_OK) == 0)
		str[0] = str[0];
	else
	{
		while (env && env[++i])
		{
			path = _strcat(env[i], "/");
			path = _strcat(path, str[0]);
			if (access(path, X_OK) == 0)
			{
				str[0] = _strdup(path);
				_memdel(path);
			}
		}
	}
	free_split(env);
	return (str);
}
