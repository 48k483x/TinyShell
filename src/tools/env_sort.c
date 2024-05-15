#include "../../minishell.h"

int			str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void		sort_env(char **s, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (s && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (_strcmp(s[i], s[i + 1]) > 0)
			{
				tmp = s[i];
				s[i] = s[i + 1];
				s[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void		print_sorted_env(t_env *env)
{
	int		i;
	char	**s;
	char	*str_env;

	str_env = env_to_str(env);
	// printf("str_env: %s\n", str_env);
	s = _split(str_env, '\n');
	_memdel(str_env);
	sort_env(s, str_env_len(s));
	i = 0;
	while (s[i])
	{
		printf("declare -x ");
		printf("%s\n", s[i]);
		i++;
	}
	free_split(s);
}
