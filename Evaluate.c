// This code checks the validity of a postfix expression
// Then evaluates the same

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

// Function to check validity of postfix expressions
int valid(char exp[]) {
    int i;
    int opnd = 0, optr = 0;

    for (i = 0 ; exp[i] != '\0'; i++) {
        if (!(isdigit(exp[i])) && 
        !((exp[i] == '+')||(exp[i] == '-')||(exp[i] == '*')||(exp[i] == '/')
        ||(exp[i] == '^')||(exp[i] == '%')||(exp[i] == ' '))) {
            return 0;
        }
    }

    loop : {
        if (exp[i] == ' ') {
            i--;
            goto loop;
        }
        if (isdigit(exp[i-1])) {
            return 0;
        }
    }

    for (i = 0 ; exp[i] != '\0' ; i++) {
        if (isdigit(exp[i])) {
            opnd++;
        }
        else if (exp[i] == ' ') {
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

    opnd = 0;
    i = 0;
    while (i < MAX) {
        if (isdigit(exp[i])) {
            opnd++;
        }
        if ((exp[i] == '+')||(exp[i] == '-')||(exp[i] == '*')
        ||(exp[i] == '/')||(exp[i] == '^')||(exp[i] == '%')) {
            return 0;
        }
        if (opnd == 2) {
            return 1;
        }

        i++;
    }
}

// Function to evaluate a postfix expression
int eval(char post[], Stack *p) {
    int i, x, y, z;
    
    for(i = 0 ; post[i] != '\0' ; i++) {
        if (post[i] == ' ') {
            continue;
        }
        else if (isdigit(post[i])) {
            push(p, (post[i] - '0'));
        }
        else {
            y = pop(p);
            x = pop(p);

            switch (post[i]) {

                case '+' : {
                    z = x + y;
                    push(p, z);
                    break;
                }
                case '-' : {
                    z = x - y;
                    push(p, z);
                    break;
                }
                case '*' : {
                    z = x * y;
                    push(p, z);
                    break;
                }
                case '/' : {
                    if(y == 0){
                        printf("ERROR : Division by zero(0)\n");
                        printf("Exiting the program...\n");
                        exit(1);
                    }
                    z = x / y;
                    push(p, z);
                    break;
                }
                case '^' : {
                    z = 1;
                    while (y > 0) {
                        z *= x;
                        y--;
                    }
                    push(p, z);
                    break;
                }
                case '%' : {
                    if (y == 0) {
                        printf("ERROR : Modulo by zero(0)\n");
                        printf("Exiting the program...\n");
                        exit(1);
                    }
                    z = x % y;
                    push(p, z);
                    break;
                }
            }
        }
    }

    return pop(p);
}

// Main method
int main() {

    Stack s;
    init(&s);

    char post[MAX];

    printf("Enter the postfix expression : ");
    fgets(post, MAX, stdin);
    post[strcspn(post , "\n")] = '\0';

    if (!(valid(post))) {
        printf("ERROR : Invalid postfix expression\n");
        printf("Exiting the program...\n");
        exit(1);
    }

    int a = eval(post, &s);

    printf("The value of the expression is : %d\n", a);
    printf("Exiting the program...\n");

    return 0;
}