#include "../../minishell.h"

t_token	*prev_sep(t_token *token)
{
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}

t_token	*next_sep(t_token *token)
{
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

t_token	*next_run(t_token *token)
{
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD && token->prev->type < END)
			token = token->next;
	}
	return (token);
}

int	has_pipe(t_token *token)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}
