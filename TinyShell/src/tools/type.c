#include "../../minishell.h"

int	is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int	is_types(t_token *token, char *types)
{
	if (_strchr(types, ' ') && is_type(token, EMPTY))
		return (1);
	else if (_strchr(types, 'X') && is_type(token, CMD))
		return (1);
	else if (_strchr(types, 'x') && is_type(token, ARG))
		return (1);
	else if (_strchr(types, 'T') && is_type(token, TRUNC))
		return (1);
	else if (_strchr(types, 'A') && is_type(token, APPEND))
		return (1);
	else if (_strchr(types, 'I') && is_type(token, INPUT))
		return (1);
	else if (_strchr(types, 'W') && is_type(token, APPEND_OPPOSITE))
		return (1);
	else if (_strchr(types, 'D') && is_type(token, DELIM))
		return (1);
	else if (_strchr(types, 'P') && is_type(token, PIPE))
		return (1);
	else if (_strchr(types, 'E') && is_type(token, END))
		return (1);
	return (0);
}
