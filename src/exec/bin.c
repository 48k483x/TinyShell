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
    str[i] = NULL;
    str[0] = start->str;
    i = 1;
    while (token && token->type < TRUNC)
    {
        str[i] = token->str;
        token = token->next;
        i++;
    }
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
        while (env[i])
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

void magic(t_token *token)
{
    char **str;

    str = path_checker(token);
    g_sig.pid = fork();

    if (g_sig.pid == 0)
    {
        if (execve(str[0], str, NULL) == -1){
            _perror(str[0]); 
            printsdr(": Command not found");
        }
    }
    else
       wait(NULL);
    free_split(str);
}
