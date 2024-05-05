#include "../minishell.h"

int env_value_len(char *env_value)
{
    int i;
    int value_len;

    i = 0;
    value_len = 0;
    while (env_value[i] && env_value[i] != '=')
        i++;
    //i++; i'm not incrementing cause i want to increment it in the while loop
    while (++i && env_value[i])
        value_len++;
    return (value_len);
}

char *get_env_value(char *env_value)
{
    int alloc_size;
    int i;
    int j;
    char *ev_value;

    alloc_size = env_value_len(env_value) + 1;
    ev_value = _malloc(sizeof(char) * (alloc_size));
    i = 0;
    while (env_value[i] && env_value[i] != '=')
        i++;
    j = 0;
    i++;
    while (env_value[i])
        ev_value[j++] = env_value[i++];
    ev_value[j] = '\0';
    return (ev_value);
}

char *fetch_env(char *arg, t_env *env)
{
   char *env_name[BUFFER_SIZE];
    char *env_value;

    env_value = _strdup("");
    while (env && env->value)
    {
        env_name = get_env_name(env_name, env->value);
        if (_strcmp(arg, env_name) == 0)
        {
            _memdel(env_value);
            env_value = get_env_value(env->value);
            return (env_value);
        }
        env = env->next;
    }
    return (env_value);
}