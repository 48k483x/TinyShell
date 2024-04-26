#include "../minishell.h"

void print_linked_list(t_cli *cli)
{
    int i;
    int j = 0;

    t_cli *tmp = cli;
    while (tmp && tmp->next)
    {
        i = 0;
        while (tmp->cmd[i])
        {
            printf("cmd %d : ['%s']\n", j, tmp->cmd[i]);
            i++;
        }
        j++;
        printf("\n");
        tmp = tmp->next;
    }
}

void _copy(t_tiny *tiny, t_cli *cli)
{
    int i = 0;
    int j;
    int k = 0;

    while (tiny->full_cmd[i] && cli)
    {
        if (_strcmp(tiny->full_cmd[i], "|") == 0 || tiny->full_cmd[i + 1] == NULL)
        {
            j = 0;
            cli->cmd = _malloc(sizeof(char **) * (i - k + 1));
            while (k <= i && _strcmp(tiny->full_cmd[k], "|") != 0)
            {
                cli->cmd[j] = strdup(tiny->full_cmd[k]);
                k++;
                j++;
            }
            cli->cmd[j] = NULL;
            k = i + 1;
            cli->next = _malloc(sizeof(t_cli));
            cli = cli->next;
        }
        i++;
    }
    cli->next = NULL;
}

void    pipe_handle(t_tiny *tiny, t_cli *cli)
{
    int cmd_count = 0;
    int i = 0;
    char *cmd = "/bin/echo  hello world | /bin/echo what'up it's me" ;
    tiny->full_cmd = _split(cmd, ' ');
    _copy(tiny, cli);
    print_linked_list(cli);
}




void fork_s(t_cli *cli)
{
    while (cli)
    {
        if (fork() == 0)
            execve(cli->cmd[0], cli->cmd, NULL);
        else
            waitpid(-1, NULL, 0);
        cli = cli->next;
    }
}
int main (int ac, char **av)
{
    (void)ac; (void)av; t_tiny tiny; t_cli cli;

    pipe_handle(&tiny, &cli);
    fork_s(&cli);
}