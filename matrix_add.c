#include <stdio.h>
#define MAX 100

typedef struct SparseMatrix {
    int row;
    int col;
    int value;
} Sparse;

int main() {
    Sparse a[MAX], b[MAX], result[MAX];
    int i, j, k, t1, t2;

    printf("Enter the number of non-zero elements in the first matrix: ");
    scanf("%d", &t1);
    printf("Enter the row, column and value respectively for each non-zero element of the first matrix:\n");
    for (i = 0; i < t1; i++) {
        scanf("%d %d %d", &a[i].row, &a[i].col, &a[i].value);
    }

    printf("Enter the number of non-zero elements in the second matrix: ");
    scanf("%d", &t2);
    printf("Enter the row, column and value respectively for each non-zero element of the second matrix:\n");
    for (i = 0; i < t2; i++) {
        scanf("%d %d %d", &b[i].row, &b[i].col, &b[i].value);
    }

    i = j = k = 0;
    while (i < t1 && j < t2) {
        if (a[i].row == b[j].row && a[i].col == b[j].col) {
            result[k].row = a[i].row;
            result[k].col = a[i].col;
            result[k].value = a[i].value + b[j].value;
            i++;
            j++;
            k++;
        } else if (a[i].row < b[j].row || (a[i].row == b[j].row && a[i].col < b[j].col)) {
            result[k] = a[i];
            i++;
            k++;
        } else {
            result[k] = b[j];
            j++;
            k++;
        }
    }
    while (i < t1) {
        result[k++] = a[i++];
    }
    while (j < t2) {
        result[k++] = b[j++];
    }

    printf("The sum of the two sparse matrices is:\n");
    printf("\tRow \tColumn \tValue\n");
    for (i = 0; i < k; i++) {
        printf("\t%d \t%d \t%d\n", result[i].row, result[i].col, result[i].value);
    }
    
    return 0;
}