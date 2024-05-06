void path_checker(t_tini *tiny)
{
    if (!tiny->line)
        return ;
    tiny->s = _split(tiny->line, ' ');
    tiny->env = _split(getenv("PATH"), ':');
    if (access(tiny->s[0], X_OK) == 0)
        tiny->path = tiny->s[0];
    else
    {
        tiny->i = 0;
        while (tiny->env[tiny->i])
        {
            tiny->path = _strcat(tiny->env[tiny->i], "/");
            tiny->path = _strcat(tiny->path, tiny->s[0]);
            if (access(tiny->path, X_OK) == 0)
                break ;
            tiny->i++;
        }
    }
}