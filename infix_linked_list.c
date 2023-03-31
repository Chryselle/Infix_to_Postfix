#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

// Add a node to the end of the linked list
void append(Node **head, char c) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = c;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
    }
}

// Remove the last node from the linked list
char remove_last(Node **head) {
    if (*head == NULL) {
        printf("List is empty");
        exit(EXIT_FAILURE);
    }

    char c;
    if ((*head)->next == NULL) {
        c = (*head)->data;
        free(*head);
        *head = NULL;
    } else {
        Node *second_last = *head;
        while (second_last->next->next != NULL) {
            second_last = second_last->next;
        }
        c = second_last->next->data;
        free(second_last->next);
        second_last->next = NULL;
    }
    return c;
}

// Check if a character is an operator
int is_operator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/') {
        return 1;
    }
    return 0;
}

// Get the precedence of an operator
int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    }
    return 0;
}

// Convert infix expression to postfix expression
void infix_to_postfix(char infix[], char postfix[]) {
    Node *head = NULL;
    int i, j;
    char c;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        c = infix[i];
        if (isdigit(c) || isalpha(c)) {
            postfix[j] = c;
            j++;
        } else if (is_operator(c)) {
            while (head != NULL && precedence(head->data) >= precedence(c)) {
                postfix[j] = remove_last(&head);
                j++;
            }
            append(&head, c);
        } else if (c == '(') {
            append(&head, c);
        } else if (c == ')') {
            while (head != NULL && head->data != '(') {
                postfix[j] = remove_last(&head);
                j++;
            }
            if (head != NULL && head->data == '(') {
                remove_last(&head);
            }
        }
    }

    while (head != NULL) {
        postfix[j] = remove_last(&head);
        j++;
    }
    postfix[j] = '\0';
}

// Main function
int main() {
    char infix[100];
    char postfix[100];

    printf("Enter infix expression: ");
    fgets(infix, 100, stdin);

    infix_to_postfix(infix, postfix);
    printf("Postfix expression: %s", postfix);

    return 0;
}
