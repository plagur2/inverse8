#include <stdio.h>

#define N 8

// Function to get the cofactor of an element
void getCofactor(int mat[N][N], int temp[N][N], int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// Recursive function to find the determinant
int determinantOfMatrix(int mat[N][N], int n) {
    int D = 0;
    if (n == 1)
        return mat[0][0];

    int temp[N][N];
    int sign = 1;

    for (int f = 0; f < n; f++) {
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
        sign = -sign;
    }

    return D;
}

// Function to find the adjoint of the matrix
void adjoint(int mat[N][N], int adj[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int temp[N][N];
            getCofactor(mat, temp, i, j, N);
            adj[j][i] = determinantOfMatrix(temp, N - 1); // Transpose indices
            adj[j][i] *= (i + j) % 2 == 0 ? 1 : -1; // Apply sign
        }
    }
}

// Function to find the inverse of the matrix (rounded to integers)
void inverse(int mat[N][N], int inv[N][N]) {
    int det = determinantOfMatrix(mat, N);
    if (det == 0) {
        printf("Matrix is singular; inverse does not exist.\n");
        return;
    }

    int adj[N][N];
    adjoint(mat, adj);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            inv[i][j] = adj[i][j] / det; // Integer division
        }
    }
}

int main() {
    // Example binary matrix (replace with your actual matrix)
    int binaryMatrix[N][N] = {
            {1, 1, 0, 1, 0, 1, 0, 0},
            {1, 0, 1, 1, 1, 0, 0, 1},
            {0, 1, 1, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 1},
            {0, 1, 0, 0, 1, 1, 1, 0},
            {1, 0, 0, 1, 0, 0, 1, 1},
            {0, 1, 1, 0, 1, 0, 1, 0},
            {1, 0, 0, 1, 0, 0, 1, 0}

            // ... (fill in the rest of the rows)
    };

    int inverseMatrix[N][N];
    inverse(binaryMatrix, inverseMatrix);

    // Print the inverse matrix
    printf("Inverse Matrix (rounded to integers):\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d, ", inverseMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
