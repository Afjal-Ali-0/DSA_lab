//This program takes a number as input and reverses it using stack.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Define the structure for stack
typedef struct Stack {
    int top;
    int MS;
    char *a;
} Stack;

// Function to create a stack of given capacity
void init (Stack *s) {
    s->top = -1;
    s->MS = MAX;
    s->a = (char *)malloc(s->MS * sizeof(char));
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
void push(Stack *s, char item) {
    if (isFull(s)) {
        printf("ERROR : Stack overflow\n");
        return;
    }
        
    s->a[++s->top] = item;
}

// Function to remove an item from stack
char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("ERROR : Stack underflow\n");
        return -1;
    }
        
    return s->a[s->top--];
}

// Function to reverse the digits of a number using stack
void reverse(char num[], char rev[], Stack *s) {
    int i = 0, j;

    while (num[i] != '\0') {
        push(s, num[i]);
        i++;
    }

    for (j = 0 ; j < i ; j++) {
        rev[j] = pop(s);
    }
    rev[i] = '\0';
}

// Main method
int main() {
    Stack s;
    init(&s);
    
    char num[MAX], rev[MAX];

    printf("Enter a number : ");
    fgets(num, MAX, stdin);
    num[strcspn(num, "\n")] = '\0';

    reverse(num, rev, &s);

    printf("Reversed number : ");
    puts(rev);

    free(s.a);

    printf("Do you want to reverse the number again?\nYES : 1\nNO : 0\n");
    int choice;
    printf("Enter your choice : ");
    scanf("%d", &choice);

    if (choice == 1) {
        init(&s);
        char _rev_[MAX];

        reverse(rev, _rev_, &s);

        printf("Reversed number : ");
        puts(_rev_);

        free(s.a);

        printf("Exiting the program... Bye !!\n");
    }
    else if (choice == 0) {
    
        printf("Exiting the program... Bye !!\n");
    }
    else {
        printf("Invalid choice.\nExiting the program... Bye !!\n");
    }
    
    return 0;
}