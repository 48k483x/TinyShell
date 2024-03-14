#include "minishell.h"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    while (1)
    {
        printf("minishell$ ");
        char *line = readline(" ");
        if (line == NULL)
        {
            printf("exit\n");
            break;
        }
        printf("%s\n", line);
    }
}