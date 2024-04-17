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
    printf("K = %d\n", k);
    printf("i = %d\n", i);
    printf("j = %d\n", j);
    printf("\nfull_cmd[%d] = %s\n\n\n", i, tiny->full_cmd[k]);
    tiny->cmds[j] = malloc(sizeof(char *) * (i - k + 1));
    if (!tiny->cmds[j])
        return ;
    while (tiny->full_cmd[k])
    {
        tiny->cmds[j][x] = strdup(tiny->full_cmd[k]);
        printf("tiny->cmds[%d][%d] = %s\n", j, x, tiny->cmds[j][x]);
        k++;
        x++;
        printf("k = %d\n", k);
    }
    tiny->cmds[j][x] = NULL;
    j++;
    tiny->cmds[j] = NULL;
}

void    pipe_handle(t_tiny *tiny)
{
    int i = 0;
    int j = -1;
    int k = 0;
    int cmd_count = 0;

    char *cmd = "/bin/echo  ana | wc -l | echo yes | hello | ls";
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
    i = 0;
    while (tiny->full_cmd[i] != NULL)
    {
        if (_strcmp(tiny->full_cmd[i], "|") == 0)
        {
            while (++j < i)
                printf("%s ", tiny->full_cmd[j]);
            printf("\n");
            j = i;
        }
        i++;
    }
    j++;
    while (tiny->full_cmd[j] != NULL)
        printf("%s ", tiny->full_cmd[j++]);
    printf("\n");

    copy(tiny);

    for (int i = 0; tiny->cmds[i]; i++)
    {
        for (int j = 0; tiny->cmds[i][j]; j++)
            printf(" cmds[%d][%d] = ['%s'] ",i, j, tiny->cmds[i][j]);
        printf("i = %d\n", i);
        printf("\n");        
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