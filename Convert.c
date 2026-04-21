// This program converts a valid infix expression into postfix expression

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Define the structure for stack
typedef struct Stack {
    int top;
    int MS;
    int *a;
} Stack;

// Function to create a stack of given capacity
void init (Stack *s) {
    s->top = -1;
    s->MS = MAX;
    s->a = (int *)malloc(s->MS * sizeof(int));
}

// Stack is full when top is equal to the last index
int isFull(Stack *s) {
    if (s->top == s->MS - 1)
        return 1;
    else
        return 0;
}

// Stack is empty when top is -1
int isEmpty(Stack *s) {
    if (s->top == -1)
        return 1;
    else
        return 0;
}

// Function to add an item to stack
void push(Stack *s, int item) {
    if (isFull(s)) {
        printf("ERROR : Stack overflow\n");
        return;
    }
        
    s->a[++s->top] = item;
}

// Function to remove an item from stack
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("ERROR : Stack underflow\n");
        return -1;
    }
        
    return s->a[s->top--];
}

// Function to check validity of an infix expression
int valid(char exp[]) {
    int i;
    int opnd = 0, optr = 0;

    // Only some specific characters are allowed
    for (i = 0 ; exp[i] != '\0'; i++) {
        if (!(isdigit(exp[i])) && 
        !((exp[i] == '+')||(exp[i] == '-')||(exp[i] == '*')||(exp[i] == '/')||(exp[i] == '^')
        ||(exp[i] == '%')||(exp[i] == ' ')||(exp[i] == '(')||(exp[i] == ')'))) {
            return 0;
        }
    }

    // Last character should be digit or closing bracket
    while (exp[i-1] == ' ') {
        i--;
    }
    if (!(isdigit(exp[i-1])||(exp[i-1] == ')'))) {
        return 0;
    }

    // First character should be digit (if not opening bracket)
    i = 0;
    int len = strlen(exp);
    while (i < len) {
        if ((exp[i] == ' ')||(exp[i] == '(')) {
            i++;
            continue;
        }
        if (isdigit(exp[i])) {
            break;
        }
        else {
            return 0;
        }
        i++;
    }

    // Second character should be operator
    i++;
    while (i < len) {
        if (exp[i] == ' ') {
            i++;
            continue;
        }
        if (!(isdigit(exp[i]))) {
            if ((exp[i] == '(')||(exp[i] == ')')) {
                return 0;
            }
            else {
                break;
            }
        }
        i++;
    }

    // Number of operand should be one more than that of operator
    for (i = 0 ; exp[i] != '\0' ; i++) {
        if (isdigit(exp[i])) {
            opnd++;
        }
        else if ((exp[i] == ' ')||(exp[i] == '(')||(exp[i] == ')')) {
            continue;
        }
        else {
            optr++;
        }
    }
    optr++;
    if (opnd != optr) {
        return 0;
    }

    return 1;
}

// Function returning higher value for operators having higher precedence
int prec(char ch) {
    if (ch == '^') {
        return 3;
    }
    else if ((ch == '*')||(ch == '/')||(ch == '%')) {
        return 2;
    }
    else if ((ch == '+')||(ch == '-')) {
        return 1;
    }
    else {
        return 0;
    }
}

// Function to convert infix expression into postfix expression
void convert(char in[], char post[], Stack *p) {
    int i, j = 0;
    int x;

    for (i = 0 ; in[i] != '\0' ; i++) {
        if (isdigit(in[i])) {
            post[j++] = in[i];
        }
        else if (in[i] == ' ') {
            continue;
        }
        else {
            switch (in[i]) {
                case '(' : {
                    push(p, in[i]);
                    break;
                }
                case ')' : {
                    while (((x = pop(p)) != '(') && !(isEmpty(p))) {
                        post[j++] = x;
                    }
                    break;
                }
                default : {
                    if (isEmpty(p)) {
                        push (p, in[i]);
                    }
                    else {
                        while((prec(in[i]) < prec(p->a[p->top])) || ((prec(in[i]) == prec(p->a[p->top]))&&(in[i] != '^'))) {
                            post[j++] = pop(p);
                        }
                        push(p, in[i]);
                    }
                    break;
                }
            }
        }
    }
    while (!(isEmpty(p))) {
        post[j++] = pop(p);
    }
    post[j] = '\0';
}

int main() {
    char in[MAX], post[MAX];

    Stack P;
    init(&P);

    printf("Enter a infix expression : ");
    fgets(in, MAX, stdin);
    in[strcspn(in, "\n")] = '\0';

    if(!(valid(in))) {
        printf("ERROR : Invalid syntax\n");
        printf("Exiting the program...\n");
        exit(1);
    }

    convert(in, post, &P);

    printf("Postfix expression : ");
    puts(post);

    return 0;
}
