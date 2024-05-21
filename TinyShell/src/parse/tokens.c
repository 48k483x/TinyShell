#include "../../minishell.h"

int	ignore_ope(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '<')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>' && \
				line[i + 2] && line[i + 2] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '<' && \
				line[i + 2] && line[i + 2] == '<')
		return (1);
	return (0);
}

void	token_type(t_token *token, int sep)
{
	if (_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (_strcmp(token->str, "|") == 0 && sep == 0)
		token->type = PIPE;
	else if (_strcmp(token->str, ";") == 0 && sep == 0)
		token->type = END;
	else if (_strcmp(token->str, ">") == 0 && sep == 0)
		token->type = TRUNC;
	else if (_strcmp(token->str, ">>") == 0 && sep == 0)
		token->type = APPEND;
	else if (_strcmp(token->str, "<<") == 0 && sep == 0)
		token->type = APPEND_OPPOSITE;
	else if (_strcmp(token->str, "<") == 0 && sep == 0)
		token->type = INPUT;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

int	next_alloc(char *line, int *i)
{
	int	j;
	int	c;
	int	count;

	c = ' ';
	j = 0;
	count = 0;
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == 32 && (line[*i + j] == '"' || line[*i + j] == '\''))
			c = line[*i + j++];
		else if (c != 32 && c == line[*i + j])
		{
			c = ' ';
			count += 2;
			j++;
		}
		else if (line[*i + j] == '\\')
			j++;
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	int		c;

	c = ' ';
	j = 0;
	token = _malloc(sizeof(t_token));
	token->str = _malloc(sizeof(char) * next_alloc(line, i));
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '"' || line[*i] == '\''))
			c = line[(*i)++];
		else if (c != ' ' && c == line[*i])
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && (*i)++)
			token->str[j++] = line[(*i)++];
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
	return (token);
}

t_token	*get_token(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	_str_trim(line);
	while (line[i])
	{
		sep = ignore_ope(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		token_type(next, sep);
		_skip_32(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
