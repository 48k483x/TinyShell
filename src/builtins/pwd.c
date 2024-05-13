#include "../../minishell.h"

int		_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n",cwd);
		return (0);
	}
	else
		return (0);
}
