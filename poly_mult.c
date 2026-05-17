#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;

Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

Node* createPolynomial() {
    Node* head = NULL;
    int n, coeff, exp;
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        append(&head, coeff, exp);
    }
    return head;
}

void printPolynomial(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%dx^%d ", temp->coeff, temp->exp);
        if (temp->next != NULL && temp->next->coeff >= 0) {
            printf("+ ");
        }
        temp = temp->next;
    }
    printf("\n");
}

Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    Node* temp1 = poly1;
    Node* temp2 = poly2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->exp > temp2->exp) {
            append(&result, temp1->coeff, temp1->exp);
            temp1 = temp1->next;
        } else if (temp1->exp < temp2->exp) {
            append(&result, temp2->coeff, temp2->exp);
            temp2 = temp2->next;
        } else {
            int sumCoeff = temp1->coeff + temp2->coeff;
            if (sumCoeff != 0) {
                append(&result, sumCoeff, temp1->exp);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL) {
        append(&result, temp1->coeff, temp1->exp);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        append(&result, temp2->coeff, temp2->exp);
        temp2 = temp2->next;
    }

    return result;
}

Node* multiplyPolynomials(Node* poly1, Node* poly2) {
    Node* temp1 = NULL, *temp2 = NULL, *temp3 = NULL;
    Node* result = NULL;
    for (temp1 = poly1; temp1 != NULL; temp1 = temp1->next) {
        for (temp2 = poly2; temp2 != NULL; temp2 = temp2->next) {
            int coeffProduct = temp1->coeff * temp2->coeff;
            int expSum = temp1->exp + temp2->exp;
            append(&temp3, coeffProduct, expSum);
        }
        result = addPolynomials(result, temp3);
        temp3 = NULL;
    }
    return result;
}

int main() {
    printf("Polynomial 1:\n");
    Node* poly1 = createPolynomial();
    printf("Polynomial 2:\n");
    Node* poly2 = createPolynomial();

    printf("Polynomial 1: ");
    printPolynomial(poly1);
    printf("Polynomial 2: ");
    printPolynomial(poly2);

    Node* product = multiplyPolynomials(poly1, poly2);

    printf("Product of Polynomials: ");
    printPolynomial(product);

    return 0;
}
