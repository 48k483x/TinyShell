#include "../../minishell.h"


char **two_dx(t_token *start)
{
    t_token *token;
    char **str;
    int i;

    if (!start)
        return (NULL);
    token = start->next;
    i = 1;
    while (token && token->type < TRUNC)
    {
        token = token->next;
        i++;
    }
    str = _malloc(sizeof(char *) * (i + 1));
    str[0] = start->str;
    i = 1;
    token = start->next;
    while (token && token->type < TRUNC)
    {
        str[i] = token->str;
        token = token->next;
        i++;
    }
    str[i] = NULL;
    return (str);
}


char **path_checker(t_token *token)
{
    char  **str;
    char *path;
    char **env;
    int i = -1;

    str = two_dx(token);
    i = 0;
    env = _split(getenv("PATH"), ':');
    if (access(str[0], X_OK) == 0)
        str[0] = str[0];
    else
    {
        while (env && env[i])
        {
            path = _strcat(env[i], "/");
            path = _strcat(path, str[0]);
            if (access(path, X_OK) == 0)
            {
                str[0] = _strdup(path);
                _memdel(path);
            }
            i++;
        }
    }
    return (str);
}

void magic(t_token *token, t_tiny *tiny)
{
    char **str;
    int ret;
    if (tiny->charge == 0)
        return ;
    ret = 1;
    str = path_checker(token);
    g_sig.pid = fork();

    if (g_sig.pid == 0)
    {
        printf("str[0]: %s\n\n\n", str[0]);
        if (is_builtin(str[0]) == 1)
            exec_builtin(str, tiny);
        else if (execve(str[0], str, NULL) == -1)
        {
            _perror(str[0]); 
            printsdr(": Command not found");
        }
        exit(ret);
    }
    else
    {
        waitpid(g_sig.pid, &ret, 0);
        // reset_std(tiny);
    }
    
    free_split(str);
    _close(tiny->pipin);
	_close(tiny->pipout);
	tiny->pipin = -1;
	tiny->pipout = -1;
	tiny->charge = 0;
}
