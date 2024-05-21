#include "../../minishell.h"

int	skip_quotes(char *str, int i)
{
	if (str[i] == '"')
	{
		while (str[i] && str[i] != '"')
			i++;
	}
	if (str[i] == '\'')
	{
		while (str[i] && str[i] != '\'')
			i++;
	}
	return (i + 1);
}

int	check_for_quote(char c, int quote)
{
	if (c == '"' && quote == 0)
		quote = 2;
	else if (c == '\'' && quote == 0)
		quote = 1;
	else if ((c == '"' && quote == 2) || (c == '\'' && quote == 1))
		quote = 0;
	return (quote);
}

int	check_quote_errors(char *s)
{
	int	quote;

	quote = quotes(s, _strlen(s));
	if (quote != 0)
		return (printsdr("tiny: unclosed double quote error"));
	return (0);
}
