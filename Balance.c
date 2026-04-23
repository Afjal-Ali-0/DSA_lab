// This program checks if an infix statement is balanced in terms of parentheses

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Define the structure for the stack
typedef struct stack {
    int top;
    int MS;
    char *a;
}Stack;

// Function to initialize stack of given capacity
void init (Stack *p) {
    p->top = -1;
    p->MS = MAX;
    p->a = (char *)calloc(MAX, sizeof(char));
    if (p->a == NULL) {
        printf("ERROR : Stack memory allocation failed\n");
        printf("Exiting the programe...\n");
        exit(1);
    }
}

// Stack is full when top equals the last index
int isFull (Stack *p) {
    if (p->top == MAX-1) {
        return 1;
    }
    else {
        return 0;
    }
}

// Stack is empty when top equals -1
int isEmpty (Stack *p) {
    if (p->top == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

// Function to add an item to the top of the stack
void push (char item, Stack *p) {
    if (isFull(p)) {
        printf("ERROR : Stack overflow\n");
        return;
    }

    p->a[++(p->top)] = item;
}

// Function to remove an item from the top of the stack
char pop (Stack *p) {
    if (isEmpty(p)) {
        printf("ERROR : Stack underflow\n");
        return '\0';
    }

    return p->a[(p->top)--];
}

// Function to check matching pair
int isMatching (char open, char close) {
    if ((open == '(') && (close == ')')) {
        return 1;
    }
    else {
        return 0;
    }
}

// Function to check the balance of parentheses
int isBalanced (char expr[], Stack *p) {
    int i;
    char ch, top;

    for (i = 0 ; expr[i] != '\0' ; i++) {
        ch = expr[i];

        if (ch == '(') {
            push ('(', p);
        }
        if (ch == ')') {
            if(isEmpty(p)) {
                return 0;
            }
            
            top = pop(p);
            if(!isMatching(top, ch)) {
                return 0;
            }
        }
    }
    if (!isEmpty(p)) {
        return 0;
    }

    return 1;
}

// Main method
int main() {
    char in[MAX];

    Stack P;
    init(&P);

    printf("Enter a infix statement : ");
    fgets(in, MAX, stdin);
    in[strcspn(in, "\n")] = '\0';

    if (isBalanced(in, &P)) {
        printf("The infix expression is balanced in terms of parentheses.\n");
    }
    else {
        printf("The infix expression is NOT balanced in terms of parentheses.\n");
    }

    free (P.a);

    printf("Exiting the program...");

    return 0;
}
