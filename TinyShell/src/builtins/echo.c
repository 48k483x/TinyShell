#include "../../minishell.h"

int	nb_args(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	_echo(char **args)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	if (nb_args(args) > 1)
	{
		while (args[i] && _strcmp(args[i], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1] && args[i][0] != '\0')
				printf(" ");
			i++;
		}
	}
	if (n_option == 0)
		printf("\n");
	return (0);
}
