#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

// Define a stack structure
typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

// Push an element onto the stack
void push(Stack *s, char c) {
    if (s->top == MAX_SIZE - 1) {
        printf("Stack overflow");
        exit(EXIT_FAILURE);
    }
    s->top++;
    s->items[s->top] = c;
}

// Pop an element from the stack
char pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack underflow");
        exit(EXIT_FAILURE);
    }
    char c = s->items[s->top];
    s->top--;
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
    Stack s;
    s.top = -1;
    int i, j;
    char c;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        c = infix[i];
        if (isdigit(c) || isalpha(c)) {
            postfix[j] = c;
            j++;
        } else if (is_operator(c)) {
            while (s.top != -1 && precedence(s.items[s.top]) >= precedence(c)) {
                postfix[j] = pop(&s);
                j++;
            }
            push(&s, c);
        } else if (c == '(') {
            push(&s, c);
        } else if (c == ')') {
            while (s.top != -1 && s.items[s.top] != '(') {
                postfix[j] = pop(&s);
                j++;
            }
            pop(&s);
        }
    }

    while (s.top != -1) {
        postfix[j] = pop(&s);
        j++;
    }
    postfix[j] = '\0';
}

// Main function
int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Enter infix expression: ");
    fgets(infix, MAX_SIZE, stdin);

    infix_to_postfix(infix, postfix);
    printf("Postfix expression: %s", postfix);

    return 0;
}
