#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_token {
    char *token;
    struct s_token *next;
} t_token;

void copy_token(char *token_start, char *c, t_token **tail) {
    (*tail)->token = malloc(c - token_start + 1);
    strncpy((*tail)->token, token_start, c - token_start);
    (*tail)->token[c - token_start] = '\0';
    (*tail)->next = malloc(sizeof(t_token));
    *tail = (*tail)->next;
}

void cmd_tokenize(char *cmd, t_token *head) {
    char *token_start = NULL;
    t_token *tail = head;
    int quote = 0;  // 0: no quote, 1: single quote : double quote

    for (char *c = cmd; *c; c++) {
        if ((*c == '"' || *c == '\'') && (quote == 0 || *c == quote)) {
            if (quote == 0) {
                quote = *c;
                token_start = c + 1;  // Skip the quote
            } else {
                if (quote == *c) { // If the current quote matches the starting quote, it's the end of the quoted string
                    copy_token(token_start, c, &tail);
                    token_start = NULL;
                    quote = 0;
                }
            }
        } else if (quote == 0 && (*c == ' ' || *c == '\t')) {
            if (token_start) {
                copy_token(token_start, c, &tail);
                token_start = NULL;
            }
        } else if (!token_start) {
            token_start = c;
        }
    }
    if (token_start) {
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
    while (current->token) {
        printf("  - %s\n", current->token);
        current = current->next;
    }

    // Free memory
    current = head.next;
    while (current) {
        t_token *temp = current;
        current = current->next;
        free(temp->token);
        free(temp);
    }

    return 0;
}
