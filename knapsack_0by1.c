#include<stdio.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve the 0/1 Knapsack problem
int knapsack(int capacity, int weights[], int values[], int n) {
    // Create a table to store the computed results
    int table[n + 1][capacity + 1];

    // Initialize the table with zeros
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= capacity; j++) {
            if (i == 0 || j == 0)
                table[i][j] = 0;
            else if (weights[i - 1] <= j)
                table[i][j] = max(values[i - 1] + table[i - 1][j - weights[i - 1]], table[i - 1][j]);
            else
                table[i][j] = table[i - 1][j];
        }
    }

    // Return the maximum value that can be obtained
    return table[n][capacity];
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    int weights[n], values[n];

    printf("Enter the weights of the items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    printf("Enter the values of the items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    int capacity;
    printf("Enter the knapsack capacity: ");
    scanf("%d", &capacity);

    int maxValue = knapsack(capacity, weights, values, n);

    printf("\nInput:\n");
    printf("Number of items: %d\n", n);
    printf("Weights of items: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", weights[i]);
    }
    printf("\nValues of items: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\nKnapsack capacity: %d\n", capacity);

    printf("Output:\nMaximum value: %d\n", maxValue);

    return 0;
}
