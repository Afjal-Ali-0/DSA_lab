#include <stdio.h>
#include <string.h>

#define MAX 100

void addLargeNumbers(char num1[], char num2[], char result[]) {
    char temp[MAX];
    
    int carry = 0, sum = 0;

    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int i = len1 - 1, j = len2 - 1, k = 0;

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? num1[i] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j] - '0' : 0;

        sum = digit1 + digit2 + carry;
        temp[k++] = (sum % 10) + '0';
        carry = sum / 10;

        i--;
        j--;
    }

    int idx = 0;
    k--;
    while (k >= 0) {
        result[idx++] = temp[k--];
    }
    result[idx] = '\0';
}

int main() {
    char num1[MAX], num2[MAX], result[MAX];

    printf("Enter the first large number  : ");
    scanf("%s", num1);
    printf("Enter the second large number : ");
    scanf("%s", num2);

    addLargeNumbers(num1, num2, result);

    printf("Sum of the two large numbers: %s\n", result);

    return 0;
}