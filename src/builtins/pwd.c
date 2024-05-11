#include "minishell.h"

int		_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		printsdr(cwd, 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
