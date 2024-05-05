#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minishell.h"

typedef struct s_token
{
    char *token;
    struct s_token *next;
} t_token;

void copy_token(char *token_start, char *c, t_token **tail)
{
    size_t len = c - token_start;
    (*tail)->token = malloc(len + 1);
    if ((*tail)->token)
    {
        strncpy((*tail)->token, token_start, c - token_start);
        (*tail)->token[c - token_start] = '\0';
    }
    (*tail)->next = malloc(sizeof(t_token));
    if ((*tail)->next != NULL)
    {
        (*tail)->next->token = NULL;
        (*tail)->next->next = NULL;
    }
    *tail = (*tail)->next;
}

int quote_type(char c)
{
    if (c == '"')
        return 2;
    if (c == '\'')
        return 1;
    return 0;
}

int quotes_num(char *cmd, int quote)
{
    int i;
    int count;

    i = 0;
    count = 0;
    printf("cmd = %s\n", cmd);
    if (quote == 1)
    {
        while (cmd[i])
        {
            if (cmd[i] == '\'')
                count++;
            
            i++;
        }
    }
    else if (quote == 2)
    {
        while (cmd[i])
        {
            if (cmd[i] == '"')
                count++;
            i++;
        }
    }
    return (count);
}

void remove_char(char *str, char target) {
    int len = strlen(str);
    int i, j;

    for (i = 0, j = 0; i < len; i++) {
        if (str[i] != target) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Null-terminate the string
}

void cmd_tokenize(char *cmd, t_token *head)
{
    int quote = 0;  // 0: no quote, 1: single quote, 2: double quote
    char *token_start = NULL;
    t_token *tail = head;
    int count = 0;
    int i = 0;
    char *c;
    char start = cmd[0];

    for (c = cmd; *c; c++) {
        printf("c = %c\n", *c);
        if (*c == '"' || *c == '\'') {
            
            if (quote == 0) {
                quote = quote_type(*c);
                    count = quotes_num(c, quote) - 1;
                printf("c = %s\n", c);
                printf("token_start = %s\n", token_start);
                printf("count = %d\n", count);
                token_start = c + 1;  // Skip the quote
            } else if ((quote == 2 && *c == '"')) {
                i++;
                if (i < count)
                    remove_char(c, '"');
            } else if ((quote == 1 && *c == '\'')) {
                i++;
                if (i < count)
                    remove_char(c, '\'');
            } if (((quote == 2 && *c == '"') || (quote == 1 && *c == '\'')) && i == count) {
                copy_token(token_start, c, &tail);
                token_start = NULL;
                quote = 0;
                i = 0;
            }
        } else if (quote == 0 && (*c == ' ' || *c == '\t')) {
            if (token_start) {
                copy_token(token_start, c, &tail);
                token_start = NULL;
            }
        } else if (token_start == NULL) {
            token_start = c;
        }
    }
    if (token_start) {
        printf("c = %s\n", c);
        printf("token_start = %s\n", token_start);
        copy_token(token_start, c, &tail);
    }
    tail->token = NULL;  // Mark the end of the tokens
}

int main() {
    char input_string[100];
    t_token head;

    printf("Enter a command: ");
    fgets(input_string, sizeof(input_string), stdin);

    // Remove the trailing newline character (if present)
    if (input_string[strlen(input_string) - 1] == '\n') {
        input_string[strlen(input_string) - 1] = '\0';
    }
    // printf("quotes num = %d\n", quotes_num(input_string, 1));
    cmd_tokenize(input_string, &head);

    printf("Tokens:\n");
    t_token *current = &head;
    while (current) {
        printf("  - %s\n", current->token);
        current = current->next;
    }
}
