#include "../../minishell.h"

int		_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096))
	{
		printf("%s\n",cwd);
		return (0);
	}
	else
		return (0);
}
