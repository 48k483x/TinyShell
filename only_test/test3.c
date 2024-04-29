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
    (*tail)->token = malloc(c - token_start + 1);
    // printf("token_start: %s\n", token_start);
    // printf("c: %s\n", c);
    strncpy((*tail)->token, token_start, c - token_start);
    (*tail)->token[c - token_start] = '\0';
    (*tail)->next = malloc(sizeof(t_token));
    *tail = (*tail)->next;
}

void cmd_tokenize(char *cmd, t_token *head)
{
    bool out_double_quotes = false;
    bool out_single_quotes = false;
    char *token_start = NULL;
    t_token *tail = head;

    for (char *c = cmd; *c; c++) {
        // printf("c: %s\n", c);
        if (*c == '"') 
        {
            out_double_quotes = !out_double_quotes;
            if (!out_double_quotes && token_start) 
            {
                copy_token(token_start, c, &tail);
                token_start = NULL;
            }
        }
        else if (*c == '\'') 
        {
            out_single_quotes = !out_single_quotes;
            if (!out_single_quotes && token_start) {
                copy_token(token_start, c, &tail);
                token_start = NULL;
            }
        }
        else if (!isalnum(*c) && *c != '-' && (!out_double_quotes) && (!out_single_quotes)) {
            if (token_start) {
                copy_token(token_start, c, &tail);
                token_start = NULL;
            }
        }
        else
            if (!token_start)
                token_start = c;
    }
    if (token_start) 
    {
        tail->token = malloc(strlen(token_start) + 1);
        strcpy(tail->token, token_start);
        tail->next = NULL;
        token_start = NULL;
    }
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

    cmd_tokenize(input_string, &head);

    printf("Tokens:\n");
    t_token *current = &head;
    while (current) {
        printf("  - %s\n", current->token);
        current = current->next;
    }
}
