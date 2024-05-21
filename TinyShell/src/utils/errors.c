#include "../../minishell.h"

void	cmd_error(char *str, char *error)
{
	_perror("tiny: ");
	_perror(str);
	printsdr(error);
}

void	_perror(char *str)
{
	size_t	i;

	if (!str)
		return ;
	i = _strlen(str);
	write(2, str, i);
}

int	printsdr(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = _strlen(str);
	write(2, str, i);
	write(2, "\n", 1);
	return (1);
}

void	*_memdel(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	*_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	return (ptr);
}
