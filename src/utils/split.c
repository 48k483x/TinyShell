#include "../../minishell.h"

char	**_split(char const *s, char c)
{
	int		words;
	char	**str;
	int		i;

	if (!s)
		return (NULL);
	words = count_strings(s, c);
	str = (char **)malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			str[i] = malloc_strings(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	str[i] = NULL;
	return (str);
}

int	count_strings(char const *s, char c)
{
	int	i;
	int	str_count;

	i = 0;
	str_count = 0;
	if (s[i] == c)
		str_count--;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			str_count++;
		i++;
	}
	str_count++;
	return (str_count);
}

char	*malloc_strings(const char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	_atoi(char *s)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	while (s[i] == ' ' && (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * sign);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		_memdel(split[i]);
		i++;
	}
	_memdel(split);
}
