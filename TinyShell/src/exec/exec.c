#include "../../minishell.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	if (_strchr(path, '/') == NULL)
		cmd_error(path, ": command not found");
	else if (fd == -1 && folder == NULL)
		cmd_error(path, ": No such file or directory");
	else if (fd == -1 && folder != NULL)
		cmd_error(path, ": is a directory");
	else if (fd != -1 && folder == NULL)
		cmd_error(path, ": Permission denied");
	if (_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	_close(fd);
	return (ret);
}

int	exec_bin(char **str, t_tiny *tiny)
{
	char	*path;
	char	**env;
	int		ret;

	ret = 0;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		path = env_to_str(tiny->env);
		env = _split(path, '\n');
		execve(str[0], str, env);
		ret = error_message(str[0]);
		_memdel(path);
		free_split(env);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	if (ret == 32512 || ret == 32256)
		ret /= 256;
	else
		ret = !!ret;
	return (ret);
}

void	exec_cmd(t_tiny *tiny, t_token *token)
{
	char	**cmd;
	int		i;

	if (tiny->charge == 0)
		return ;
	cmd = path_checker(token);
	i = -1;
	while (cmd && cmd[++i])
		cmd[i] = expansions(cmd[i], tiny->env, tiny->ret);
	if (cmd && _strcmp(cmd[0], "exit") == 0 && has_pipe(token) == 0)
		__exit(tiny, cmd);
	else if (cmd && is_builtin(cmd[0]))
		tiny->ret = exec_builtin(cmd, tiny);
	else if (cmd)
		tiny->ret = exec_bin(cmd, tiny);
	free_split(cmd);
	_close(tiny->pipin);
	_close(tiny->pipout);
	tiny->pipin = -1;
	tiny->pipout = -1;
	tiny->charge = 0;
}
