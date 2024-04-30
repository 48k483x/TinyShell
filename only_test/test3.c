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
    strncpy((*tail)->token, token_start, c - token_start);
    (*tail)->token[c - token_start] = '\0';
    (*tail)->next = malloc(sizeof(t_token));
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

void cmd_tokenize(char *cmd, t_token *head)
{
    int quote = 0;  // 0: no quote, 1: single quote, 2: double quote
    char *token_start = NULL;
    t_token *tail = head;

    for (char *c = cmd; *c; c++) {
        if (*c == '"' || *c == '\'') {
            if (quote == 0) {
                // Start of a quoted string
                quote = quote_type(*c);
                token_start = c + 1;  // Skip the quote
            } else if ((quote == 2 && *c == '"') && (*(c+1) != ' ' && *(c+1) != '\t' && *(c+1) != '\0')) {
                // If we're inside a double quoted string and the next character is not a space, tab, or end of string,
                // then we're dealing with a nested quote. Ignore it.
                continue;
            } else if ((quote == 1 && *c == '\'') && (*(c+1) != ' ' && *(c+1) != '\t' && *(c+1) != '\0')) {
                // If we're inside a single quoted string and the next character is not a space, tab, or end of string,
                // then we're dealing with a nested quote. Ignore it.
                continue;
            } else if ((quote == 2 && *c == '"') || (quote == 1 && *c == '\'')) {
                // End of a quoted string
                copy_token(token_start, c, &tail);
                token_start = NULL;
                quote = 0;
            }
        } else if (quote == 0 && (*c == ' ' || *c == '\t')) {
            // End of an unquoted token
            if (token_start) {
                copy_token(token_start, c, &tail);
                token_start = NULL;
            }
        } else if (!token_start) {
            // Start of an unquoted token
            token_start = c;
        }
    }
    if (token_start) {
        // End of the last token
        copy_token(token_start, cmd + strlen(cmd), &tail);
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

    cmd_tokenize(input_string, &head);

    printf("Tokens:\n");
    t_token *current = &head;
    while (current) {
        printf("  - %s\n", current->token);
        current = current->next;
    }
}
