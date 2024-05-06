#include "../../minishell.h"

int  init_env(t_tiny *tiny, char **envp)
{
    t_env *env; 
    t_env *new;
    int i;

    env = _malloc(sizeof(t_env));
    env->value = _strdup(envp[0]);
    env->next = NULL;
    tiny->env = env;
    i = 1;
    while (envp && envp[0] && envp[i])
    {
        new = _malloc(sizeof(t_env));
        new->value = _strdup(envp[i]);
        new->next = NULL;
        env->next = new;
        env = new;
        i++;
    }
    return (0);
}

int private_init_env(t_tiny *tiny, char **envp)
{
    t_env *env; 
    t_env *new;
    int i;

    env = _malloc(sizeof(t_env));
    env->value = _strdup(envp[0]);
    env->next = NULL;
    tiny->private_env = env;
    i = 1;
    while (envp && envp[0] && envp[i])
    {
        new = _malloc(sizeof(t_env));
        new->value = _strdup(envp[i]);
        new->next = NULL;
        env->next = new;
        env = new;
        i++;
    }
    return (0);
}