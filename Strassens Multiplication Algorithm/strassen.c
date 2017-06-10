#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

/*
 * Create n x n matrix
 * */
float **generateMatrix(int n){
    float **tempMatrix = (float **) malloc(n * sizeof(float*));
    int i,j;
    for(i = 0; i < n; i++){
        tempMatrix[i] = (float *) malloc (n * sizeof(float));
        for(j = 0; j < n; j++){
            tempMatrix[i][j] = (((float)rand() / (float)RAND_MAX) * 10)-5;

        }
    }
    return tempMatrix;
}

/*
 * Print n x n matrix
 * */
void printMatrix(float **matrix, int n){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%- 03.2f  ", matrix[i][j]);
        }
        printf("\n");
    }
}

/*
 * Free the space allocated to matrix
 * */
void freeMatrix(float **matrix, int n){
    int i;
    for(i = 0; i < n; i++){
        free(matrix[i]);
    }
    free(matrix);
}

/*
 * Add two matrices
 * */
void add(int n, float matrixA[][n], float matrixB[][n], float matrixC[][n]){
    int i, j;
    float result[n][n];
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        } 
    }
}

/*
 * Substract two matrices
 * */
void sub(int n, float matrixA[][n], float matrixB[][n], float matrixC[][n]){
    int i, j;
    float result[n][n];
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            matrixC[i][j] = matrixA[i][j] - matrixB[i][j];
        } 
    }
}

/*
 * Custom function to calculate multiplication of matrices recursively.
 * */
void recStrassensMultiplication(int n, float matrixA[][n], float matrixB[][n], float matrixC[][n]){
    int mid, i, j, newI, newJ;
    if(n == 2){
        //Base Case: 2 x 2 matrix
        float m1, m2, m3, m4, m5, m6, m7;
        
        m1 = (matrixA[0][0] + matrixA[1][1]) * (matrixB[0][0] + matrixB[1][1]);
        m2 = (matrixA[1][0] + matrixA[1][1]) * matrixB[0][0];
        m3 = matrixA[0][0] * (matrixB[0][1] - matrixB[1][1]);
        m4 = matrixA[1][1] * (matrixB[1][0] - matrixB[0][0]);
        m5 = (matrixA[0][0] + matrixA[0][1]) * matrixB[1][1];
        m6 = (matrixA[1][0] - matrixA[0][0]) * (matrixB[0][0] + matrixB[0][1]);
        m7 = (matrixA[0][1] - matrixA[1][1]) * (matrixB[1][0] + matrixB[1][1]);

        matrixC[0][0] = m1 + m4 - m5 + m7;
        matrixC[0][1] = m3 + m5;
        matrixC[1][0] = m2 + m4;
        matrixC[1][1] = m1 + m3 - m2 + m6;
        return;
    }
    mid = n/2;
    float a11[mid][mid], a12[mid][mid], a21[mid][mid], a22[mid][mid],
          b11[mid][mid], b12[mid][mid], b21[mid][mid], b22[mid][mid],
          c11[mid][mid], c12[mid][mid], c21[mid][mid], c22[mid][mid],
          m1[mid][mid], m2[mid][mid], m3[mid][mid], m4[mid][mid],
          m5[mid][mid], m6[mid][mid], m7[mid][mid],
          temp[mid][mid], temp1[mid][mid];
    
    //Divide matrix into 4 parts
    for(i = 0; i < mid; i++){
        for(j = 0; j < mid; j++){
            newI = i + mid;
            newJ = j + mid;
            a11[i][j] = matrixA[i][j];
            a12[i][j] = matrixA[i][newJ];
            a21[i][j] = matrixA[newI][j];
            a22[i][j] = matrixA[newI][newJ];

            b11[i][j] = matrixB[i][j];
            b12[i][j] = matrixB[i][newJ];
            b21[i][j] = matrixB[newI][j];
            b22[i][j] = matrixB[newI][newJ];
        }
    }
    
    //Recursive calls to compute multiplication 
    add(mid, a11, a22, temp);
    add(mid, b11, b22, temp1);
    recStrassensMultiplication(mid, temp, temp1, m1);

    add(mid, a21,a22, temp);
    recStrassensMultiplication(mid,temp, b11, m2);

    sub(mid, b12, b22, temp);
    recStrassensMultiplication(mid, a11, temp, m3);

    sub(mid, b21, b11, temp);
    recStrassensMultiplication(mid, a22, temp, m4);

    add(mid, a11, a12, temp);
    recStrassensMultiplication(mid, temp, b22, m5);

    sub(mid, a21, a11, temp);
    add(mid, b11, b12, temp1);
    recStrassensMultiplication(mid, temp, temp1, m6);

    sub(mid, a12, a22, temp);
    add(mid, b21, b22, temp1);
    recStrassensMultiplication(mid, temp, temp1, m7);

    add(mid, m1, m4, temp);
    sub(mid, temp, m5, temp1);
    add(mid, temp1, m7, c11);

    add(mid, m3, m5, c12);

    add(mid, m2, m4, c21);

    add(mid, m1, m3, temp);
    sub(mid, temp, m2, temp1);
    add(mid, temp1, m6, c22);

    //Combine divided matrices into single matrix
    for(i = 0; i < mid; i++){
        for(j = 0; j < mid; j++){
            newI = i + mid;
            newJ = j + mid;

            matrixC[i][j] = c11[i][j];
            matrixC[i][newJ] = c12[i][j];
            matrixC[newI][j] = c21[i][j];
            matrixC[newI][newJ] = c22[i][j];
        }
    }
}

/*
 * Wrapper function for Strassen's multiplication
 * */
void strassensMultiplication(float **matrixA, float **matrixB, int n){
    int i,j,newN = n;
    
    //Check if n is power of 2. If not convert it to next power of 2.
    if((n & (n-1)) && n > 0){
        newN = pow(2, ceil(log(n)/log(2)));
    }

    float A[newN][newN], B[newN][newN], C[newN][newN];
    
    for(i = 0; i < newN; i++){
        for(j = 0; j < newN; j++){
            if(i >= n || j >= n){
                A[i][j] = 0;
                B[i][j] = 0;
            }
            else{
                A[i][j] = matrixA[i][j];
                B[i][j] = matrixB[i][j];
            }
            C[i][j] = 0;
        }
    }
    
    recStrassensMultiplication(newN, A, B, C);
    
    //Print multiplication result
    printf("\nStrassen's Multiplication Output:\n");
    for(i = 0; i < n; i++){
        for(j =0; j <n; j++){
            printf("%- 03.2f  ", C[i][j]);
        }
        printf("\n");
    }
}

/*
 * Standard multiplication of matrices
 * */
void standardMultiplication(float **matrixA, float **matrixB, int n){
    int i,j,k;
    float **tempMatrix = (float **) malloc (n * sizeof(float *));
    for(i = 0; i < n; i++){
        tempMatrix[i] = (float *) malloc (n * sizeof(float));
        for(j = 0; j < n; j++){
            tempMatrix[i][j] = 0;
            for(k = 0; k < n; k++){
                tempMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    
    printf("\nStandard Multiplicaton Output:\n");
    printMatrix(tempMatrix, n);
    freeMatrix(tempMatrix, n);
}

/*
 * Input validations
 * */
int checkValidations(int argc, char **argv1){
    
    if(argc != 2){
        printf("Enter number greater than 0\n");
        return 1;
    }
    if(atoi(argv1[1]) < 2){
        printf("Value of n should be greater than or equal to 2\n");
        return 1;
    }
    return 0;
}

int main(int argc, char **argv){
    int n;
    float **matrixA, **matrixB;

    srand(time(NULL));

    if(checkValidations(argc, argv)){
        return 1;
    }
    n = atoi(argv[1]);

    matrixA = generateMatrix(n);
    matrixB = generateMatrix(n);

    printf("\nMatrix A:\n");
    printMatrix(matrixA, n);

    printf("\nMatrix B:\n");
    printMatrix(matrixB, n);

    strassensMultiplication(matrixA, matrixB, n);
    standardMultiplication(matrixA, matrixB, n);

    freeMatrix(matrixA, n);
    freeMatrix(matrixB, n);
    return 0;
}
