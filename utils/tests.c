#include "../minishell.h"

void    copy(t_tiny *tiny)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int x = 0;
    while (tiny->full_cmd[i] != NULL)
    {
        if (_strcmp(tiny->full_cmd[i], "|") == 0)
        {
            tiny->cmds[j] = malloc(sizeof(char **) * (i - k + 1));
            if (!tiny->cmds[j])
                return ;
            while (k < i)
            {
                tiny->cmds[j][x] = strdup(tiny->full_cmd[k]);
                k++;
                x++;
            }
            tiny->cmds[j][x] = NULL;
            j++;
            k = i + 1;
            x = 0;
        }
        i++;
    }
    tiny->cmds[j] = malloc(sizeof(char *) * (i - k + 1));
    if (!tiny->cmds[j])
        return ;
    while (tiny->full_cmd[k])
    {
        tiny->cmds[j][x] = strdup(tiny->full_cmd[k]);
        k++;
        x++;
    }
    tiny->cmds[j][x] = NULL;
    j++;
    tiny->cmds[j] = NULL;
}

void    pipe_handle(t_tiny *tiny)
{
    int cmd_count = 0;
    int i = 0;
    char *cmd = "/bin/echo  ana | wc -l" ;
    while (cmd[i] != '\0')
    {
        if (cmd[i] == '|')
            cmd_count++;
        i++;
    }
    tiny->cmds = malloc(sizeof(char ***) * (cmd_count + 2));
    if (!tiny->cmds)
        return ;
    tiny->full_cmd = _split(cmd, ' ');
    copy(tiny);

    for (int i = 0; tiny->cmds[i]; i++)
    {
        for (int j = 0; tiny->cmds[i][j]; j++)
            printf(" cmds[%d][%d] = ['%s'] ",i, j, tiny->cmds[i][j]);
        printf("i = %d\n", i);
        printf("\n");        
    }
    
}

void lexer()
{
    char *cmd = "echo  ana | wc -l" ;
    int i = -1;
    while (++i && cmd[i])
    {
        
    }
}


void fork_s(t_tiny *tiny)
{
    pid_t pid;
    int i = 0;
        if (!(pid = fork()))
            execve(tiny->cmds[i][0], tiny->cmds[i], NULL);
        else
            waitpid(pid, NULL, 0);
}
int main (int ac, char **av)
{
    (void)ac; (void)av; t_tiny tiny;

    pipe_handle(&tiny);
    fork_s(&tiny);
}