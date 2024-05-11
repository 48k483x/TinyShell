#include "../../minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TokenNode {
    char *token;
    struct TokenNode *next;
} TokenNode;

TokenNode *tokenize_command(char *input) {
    TokenNode *head = NULL;
    TokenNode *tail = NULL;
    char *token_start = NULL;
    bool in_double_quotes = false;
    bool in_single_quotes = false;

    for (char *c = input; *c; c++) {
        if (*c == '"') {
            in_double_quotes = !in_double_quotes;
            if (!in_double_quotes && token_start) {
                // Create a token (excluding quotes)
                TokenNode *node = malloc(sizeof(TokenNode));
                node->token = malloc(c - token_start + 1);
                strncpy(node->token, token_start, c - token_start);
                node->token[c - token_start] = '\0';
                node->next = NULL;
                if (!head) {
                    head = tail = node;
                } else {
                    tail->next = node;
                    tail = node;
                }
                token_start = NULL; // Reset token buffer
            }
        } else if (!isalnum(*c) && *c != '_' && (!in_double_quotes)) {
            // Delimiter outside quotes, create a token
            if (token_start) {
                TokenNode *node = malloc(sizeof(TokenNode));
                node->token = malloc(c - token_start + 1);
                strncpy(node->token, token_start, c - token_start);
                node->token[c - token_start] = '\0';
                node->next = NULL;
                if (!head) {
                    head = tail = node;
                } else {
                    tail->next = node;
                    tail = node;
                }
                token_start = NULL; // Reset token buffer
            }
        } else {
            // Not a delimiter, accumulate characters in the token buffer
            if (!token_start) {
                token_start = c;
            }
        }
    }

    // Handle the last token (if any)
    if (token_start) {
        TokenNode *node = malloc(sizeof(TokenNode));
        node->token = malloc(strlen(token_start) + 1);
        strcpy(node->token, token_start);
        node->next = NULL;
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}


#include <stdio.h>

int main() {
    char input_string[100];

    printf("Enter a command string (with quotes): ");
    fgets(input_string, sizeof(input_string), stdin);

    // Remove the trailing newline character (if present)
    if (input_string[strlen(input_string) - 1] == '\n') {
        input_string[strlen(input_string) - 1] = '\0';
    }

    TokenNode *head = tokenize_command(input_string);

    printf("Tokens:\n");
    TokenNode *current = head;
    while (current) {
        printf("  - %s\n", current->token);
        current = current->next;
    }

    // Free the allocated memory for the linked list
    while (head) {
        current = head->next;
        free(head->token);
        free(head);
        head = current;
    }

    return (0);
}
