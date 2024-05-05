#include "../minishell.h"

char *get_env_name(char *dest, char *src)
{
    int i;

    i = 0;
    while (src[i] && src[i] != '=' && _strlen(src) < BUFFER_SIZE)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int false_lvl(char *sh_val)
{
    int i;

    i = 0;
    while (sh_val[i])
    {
        if (!(sh_val[i] >= '0' && sh_val[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}

// int get_lvl(char *sh_val)
// {

//     if (false_lvl(sh_val))
//         return (0);
//     return (_atoi(sh_val));
// }

void set_shell_level(t_env *env)
{
    char *sh_lvl_value;
    char env_name[BUFFER_SIZE];

    sh_lvl_value = fetch_env("SHLVL", env);
    if (false_lvl(sh_lvl_value))
        return ;
    while (env && env->value)
    {
        get_env_name(env_name, env->value);
        if (_strcmp("SHLVL", env_name) == 0)
        {
            _memdel(env->value);
            env->value = _strjoin("SHLVL=", sh_lvl_value);
            _memdel(sh_lvl_value);
            return ;
        }
        env = env->next;
    }
}