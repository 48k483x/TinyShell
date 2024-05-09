#include "../../minishell.h"

int quotes(char *s, int index)
{
    int quote;
    int i;

    quote = 0;
    i = 0;
    while (s[i] && i != index)
    {
        if (i > 0 && s[i - 1] == '\\')
            ;
        else if (quote == 0 && s[i] == '\'')
            quote = 1;
        else if (quote == 0 && s[i] == '"')
            quote = 2;
        else if (quote == 1 && s[i] == '\'')
            quote = 0;
        else if (quote == 2 && s[i] == '"')
            quote = 0;
        i++;
    }
    return (quote);
}

int is_operator(char *s, int index)
{
    if (index > 0 && _strchr("|<>;", s[index]))
        return (1);
    if (_strchr("|<>;", s[index]) && quotes(s, index) == 0)
        return (1);
    else
        return (0);
}

char *spacing(char *s)
{
    char *new;
    int i;
    int count;

    i = 0;
    count = 0;
    while (s[i])
    {
        if (is_operator(s, i))
            count++;
        i++;
    }
    new = _malloc(sizeof(char) * (i + 1 + count * 2));
    return (new);
}

char *space_line(char *line)
{
    char *new;
    int i;
    int j;

    i = 0;
    j = 0;
    new = spacing(line);
    while (new  && line[i])
    {
        if (line[i] == '$' && i && line[i - 1] != '\\')
            new[j++] = (char)(-line[i++]);
        else if (quotes(line, i) == 0 && is_operator(line, i))
        {
            new[j++] = ' ';
            new[j++] = line[i++];
            if (quotes(line, i) == 0 && (line[i] == '<' || line[i] == '>'))
                new[j++] = line[i++];
            new[j++] = ' ';
        }
        else
            new[j++] = line[i++];
    }
    new[j] = '\0';
    _memdel(line);
    return (new);
}

void parse(t_tiny *tiny)
{
	tiny->line = space_line(tiny->line);
	if (tiny->line &&tiny->line[0] == '$')
	    tiny->line[0] = (char)(-tiny->line[0]);
	printf("tiny->line = %s\n", tiny->line);
	// tiny->start = get_token(tiny->line);
	if (tiny->line && tiny->line[0] == '$')
		tiny->line[0] = (char)(-tiny->line[0]);
	tiny->start = get_token(tiny->line);
}