#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*p;

	if (alst != NULL)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			p = *alst;
			while (p->next != NULL)
				p = p->next;
			p->next = new;
		}
	}
}

int	get_size(char *s)
{
	int		i;
	int		quote;
	int		ret;

	ret = 0;
	quote = 0;
	i = 0;
	while (s[i])
	{
		i = skip_space_and_redir(s, i);
		if (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
		{
			while ((s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
				|| (s[i] == ' ' && quote)
				|| ((s[i] == '>' || s[i] == '<') && quote))
				quote = check_for_quote(s[i++], quote);
			ret++;
		}
	}
	return (ret);
}

static size_t	_smallest(const char *s, unsigned int start, size_t len)
{
	if (len > _strlen(s + start))
		return (_strlen(s + start) + 1);
	return (len + 1);
}

char	*_substr(char const *s, unsigned int start, size_t len)
{
	char	*x;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start > _strlen(s))
		len = 0;
	i = 0;
	x = (char *)malloc(sizeof(char) * _smallest(s, start, len));
	if (x == 0)
		return (NULL);
	while (i < (_smallest(s, start, len) - 1))
	{
		x[i] = s[i + start];
		i++;
	}
	x[i] = '\0';
	return (x);
}