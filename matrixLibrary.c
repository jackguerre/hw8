#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int rows;
    int cols;
    int** data;
} Matrix;

Matrix createMatrix(int rows, int cols){
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i)
        m.data[i] = (int*)calloc(cols, sizeof(int));
    return m;
}

void freeMatrix(Matrix* m){
    for (int i = 0; i < m->rows; ++i){
        free(m->data[i]);
    }
    free(m->data);
    m->data = NULL;
}

Matrix scalarMultiply(Matrix m, int scalar) {
    Matrix result = createMatrix(m.rows, m.cols);
    for (int i = 0; i < m.rows; i++){
        for (int j = 0; j < m.cols; j++){
            result.data[i][j] = m.data[i][j] * scalar;
        }
    }
    return result;
}

Matrix transpose(Matrix m) {
    Matrix result = createMatrix(m.cols, m.rows);
    for (int i = 0; i < m.rows; i++){
        for (int j = 0; j < m.cols; j++){
            result.data[j][i] = m.data[i][j];
        }
    }
    return result;
}

Matrix multiply(Matrix a, Matrix b){
    Matrix result = createMatrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++){
        for (int j = 0; j < b.cols; j++){
            for (int k = 0; k < a.cols; k++){
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

Matrix add(Matrix a, Matrix b){
    Matrix result = createMatrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++){
        for (int j = 0; j < a.cols; j++){
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

void printMatrix(Matrix m){
    for (int i = 0; i < m.rows; i++){
        for (int j = 0; j < m.cols; j++){
            printf("%d ", m.data[i][j]);
        }
        printf("\n");
    }
}

int main(){
    Matrix A = createMatrix(2, 2);
    Matrix B = createMatrix(2, 3);
    Matrix C = createMatrix(2, 3);

    //Fill A
    A.data[0][0] = 6; 
    A.data[0][1] = 4;
    A.data[1][0] = 8; 
    A.data[1][1] = 3;

    //Fill B
    B.data[0][0] = 1; 
    B.data[0][1] = 2; 
    B.data[0][2] = 3;
    B.data[1][0] = 4; 
    B.data[1][1] = 5; 
    B.data[1][2] = 6;

    //Fill C
    C.data[0][0] = 2; 
    C.data[0][1] = 4; 
    C.data[0][2] = 6;
    C.data[1][0] = 1; 
    C.data[1][1] = 3; 
    C.data[1][2] = 5;

    Matrix B_scaled = scalarMultiply(B, 3);
    Matrix C_T = transpose(C);
    Matrix product = multiply(B_scaled, C_T);
    Matrix D = add(A, product);

    printf("Matrix D: ");
    printMatrix(D);

    // Free memory
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&B_scaled);
    freeMatrix(&C_T);
    freeMatrix(&product);
    freeMatrix(&D);

    return 0;
}
