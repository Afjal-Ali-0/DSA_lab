#include <stdio.h>
#define MAX 100

typedef struct SparseMatrix {
    int row;
    int col;
    int value;
} Sparse;

int nonZeroInRow(Sparse matrix[], int n, int row) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (matrix[i].row == row) {
            count++;
        }
    }
    return count;
}

int main() {
    Sparse matrix[MAX];
    int n, i, maxRow;

    printf("Enter the number of non-zero elements: ");
    scanf("%d", &n);

    printf("Enter the non-zero elements (row, column, value):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &matrix[i].row, &matrix[i].col, &matrix[i].value);
    }

    maxRow = matrix[0].row;
    for (i = 1; i < n; i++) {
        if (matrix[i].row > maxRow) {
            maxRow = matrix[i].row;
        }
    }

    printf("Number of non-zero elements in each row:\n");
    printf("\tRow\tCount\n");
    for (i = 0; i <= maxRow; i++) {
        printf("\t %d\t  %d\n", i, nonZeroInRow(matrix, n, i));
    }

    return 0;
}