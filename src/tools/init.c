#include "../../minishell.h"

char *initialise_prompt(void)
{
    char *prompt;
    char dir[200];
    char p[200];
    char *pwd;
    char hostname[1024];

    gethostname(hostname, 1024);

    pwd = getcwd(dir, 4096);
    while (*pwd)
    {
        if (*pwd == '/')
        {
            pwd++;
            _strcpy(p, pwd);
        }
        pwd++;
    }
    prompt = _strcat(getenv("USER"), "@");
    prompt = _strcat(prompt, hostname);
    prompt = _strcat(prompt, ":");
    prompt = _strcat(prompt, p);
    prompt = _strcat(prompt, "$ ");
    return (prompt);
}

void init(t_tiny *tiny, char **env)
{
    tiny->in = dup(STDIN);
    tiny->out = dup(STDOUT);
    tiny->exit = 0;
    tiny->ret = 0;
    tiny->no_exec = 0;
    reset_fds(tiny);
    init_env(tiny, env);
    private_init_env(tiny, env);
    set_shell_level(tiny->env);
}