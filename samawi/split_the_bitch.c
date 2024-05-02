#include "../minishell.h"
static char	*change_pipe(char *s)
{
	int		i;
	int		quote;
	char	*temp;

	quote = 0;
	temp = (char *)malloc(sizeof(char) * (_strlen(s) + 1));
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == 39) && quote == 0)
			quote = 1;
		else if ((s[i] == '"' || s[i] == 39) && quote == 1)
			quote = 0;
		if (s[i] == 124 && quote == 0)
			temp[i++] = -124;
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
t_list	*split_by_pipes(t_list *head, char *input, t_list *env_lst)
{
    char    **cmds;
    t_cmd   *tmp;
    t_list  *new_head;
    int     i;

    i = 0;
    input = change_pipe(input);
    cmds =  _split(input, '|');
    while (cmds[i])
    {
        
    }
}