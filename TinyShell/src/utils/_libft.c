#include "../../minishell.h"

int	_strisnum(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	_str_trim(char *line)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = _strlen(line);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[len - 1] == ' ' || line[len - 1] == '\t')
		len--;
	while (i < len)
	{
		line[j] = line[i];
		i++;
		j++;
	}
	line[j] = '\0';
}

char	*_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

void	_skip_32(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

int	_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
