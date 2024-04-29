#include "../minishell.h"

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

int	redirection_syntax_errors(char *str, int i)
{
	if ((str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
		i += 2;
	else
		i++;
	while (str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		if (!str[i])
			printsdr("Tinyshell: syntax error near unexpected token `newline'");
		else
			printsdr("Tinyshell: syntax error near unexpected token `");
		return (-100);
	}
	return (i);
}

int	check_redir_errors(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip_quotes(str, i);
		while (str[i] == ' ')
			i++;
		if (str[i] == '>' || str[i] == '<')
			i = redirection_syntax_errors(str, i);
		if (i == -100)
			return (1);
		i++;
	}
	return (0);
}



// triming the inial space and the ending space
char *ft_strtrim_inplace(char *s) 
{
  if (s == NULL) 
    return NULL;
  while ((*s == ' ' || *s == '\t') && *s != '\0')
    s++;
  if (*s == '\0')
    return s;
  char *end = s + _strlen(s) - 1;
  while (*end == ' ' && end > s)
    end--;
  *(end + 1) = '\0';

  return s;
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
// checking if there is a single/double quote for each single/double quote
int	check_quote_errors(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (s[i] != '"')
				return (printsdr("Tinyshell: unclosed double quote error"));
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] != '\'')
				return (printsdr("Tinyshell: unclosed single quote error"));
		}
		i++;
	}
	return (0);
}
//checking if there is a pipe without actual commands
int	check_pipe_errors(char *s)
{
	int		i;
	int		quote;

	quote = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			quote = check_for_quote(s[i++], quote);
		if (s[i] == '|' && !quote)
		{
			i++;
			while (s[i] == ' ')
				i++;
			if (s[i] == '|')
				return (printsdr("Tinyshell: syntax error near unexpected token `|'"));
		}
		i++;
	}
	return (0);
}
// checking for unexpected placement for pipe and semi-colon
int	pipe_and_semi_errors(char *str)
{
	if (str == NULL)
		return (0);
	if (str[0] == '|')
	{
		if (str[1] == '|')
			return (printsdr("Tinyshell: syntax error near unexpected token `||'"));
		else
			return (printsdr("Tinyshell: syntax error near unexpected token `|'"));
	}
	else if (str[0] == ';')
	{
		if (str[1] == ';')
			return (printsdr("Tinyshell: syntax error near unexpected token `;;'"));
		else
			return (printsdr("Tinyshell: syntax error near unexpected token `;'"));
	}
	if (check_pipe_errors(str))
		return (1);
	return (0);
}


int	check_syntax(char *s)
{
  char *str;

  str = ft_strtrim_inplace(s);
  
  if (pipe_and_semi_errors(str) || check_quote_errors(str) || check_redir_errors(str))
    return 1;
  return 0;
}
// int main ()
// {
// 	char s[100];
// 	printf("Enter the string: ");
// 	scanf("%[^\n]%*c", s);
// 	check_syntax_errors(s);
// }
