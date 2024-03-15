#include "minishell.h"

char *get_name()
{
    return (getenv("USER"));
}
char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    char *prompt = ft_strcat(get_name(),"\033[0;34m@minishell\033[0m\033[0;33m $ \033[0m");
    while (1)
    {
        char *line = readline(prompt);
        if (line == NULL)
        {
            printf("exit\n");
            break;
        }
        if (strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }
        if (strcmp(line, "") == 0)
        {
            free(line);
            continue;
        }
        else
            printf("%s\n", line);
    }
}

