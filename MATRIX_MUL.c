#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 100

void matrix_chain_order(int p[], int n, int M[][n + 1], int S[][n + 1]) {
    for (int i = 1; i <= n; i++) {
        M[i][i] = 0;
    }

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            M[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = M[i][k] + M[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < M[i][j]) {
                    M[i][j] = q;
                    S[i][j] = k;
                }
            }
        }
    }
}

void print_optimal_parenthesization(int S[][5], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        print_optimal_parenthesization(S, i, S[i][j]);
        print_optimal_parenthesization(S, S[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int p[n + 1];
    printf("Enter the dimensions of matrices: ");
    for (int i = 0; i <= n; i++) {
        scanf("%d", &p[i]);
    }

    int M[n + 1][n + 1], S[n + 1][5];
    matrix_chain_order(p, n, M, S);

    printf("Number of scalar multiplications: %d\n", M[1][n]);
    printf("Optimal Parenthesization: ");
    print_optimal_parenthesization(S, 1, n);

    return 0;
}
