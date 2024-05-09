#include "../../minishell.h"

int next_alloc(char *line, int *i)
{
    int j;
    int c;
    int count;

    c = ' ';
    j = 0;
    count = 0;
    while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
    {
        if (c == 32 && (line[*i + j] == '"' || line[*i + j] == '\''))
            c = line[*i + j++];
        else if (c != 32 && c == line[*i + j])
        {
            c = ' ';
            count += 2;
            j++;
        }
        else if (line[*i + j] == '\\')
            j++;
        else
            j++;
        if (line[*i + j - 1] == '\\')
            count--;
    }
    return (j - count + 1);
}

t_token *next_token(char *line, int *i)
{
    t_token *token;
    int j;
    int c;

    c = ' ';
    j = 0;
    token = _malloc(sizeof(t_token));
    token->str = _malloc(sizeof(char) * next_alloc(line, i));
    printf("line = %s\n", line);
    printf("next_alloc = %d\n", next_alloc(line, i));
    while (line[*i] && (line[*i] != ' ' || c != ' '))
    {
        if (c == ' ' && (line[*i] == '"' || line[*i] == '\''))
            c = line[(*i)++];
        else if (c != ' ' && c == line[*i])
        {
            c = ' ';
            (*i)++;
        }
        else if (line[*i] == '\\' && (*i)++)
            token->str[j++] = line[(*i)++];
        else
            token->str[j++] = line[(*i)++];
    }
    token->str[j] = '\0';
    printf("token->str = %s\n", token->str);
    return (token);
}

t_token *get_token(char *line)
{
    // t_token *prev;
    t_token *next;
    int i;
    // int sep;

    // prev = NULL;
    next = NULL;
    i = 0;
    _str_trim(line);
    while (line[i])
    {
        next = next_token(line, &i);
        break ;
    }
    return (next);
}