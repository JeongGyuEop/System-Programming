#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols;

    // 행렬의 크기를 입력받음
    printf("행렬의 행 수를 입력하세요: ");
    scanf("%d", &rows);
    printf("행렬의 열 수를 입력하세요: ");
    scanf("%d", &cols);

    // 행렬 A 동적 할당
    double **matrixA = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrixA[i] = (double *)malloc(cols * sizeof(double));
    }

    // 행렬 A 입력
    printf("첫 번째 행렬의 원소를 입력하세요:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%lf", &matrixA[i][j]);
        }
    }

    // 행렬 B 동적 할당
    double **matrixB = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrixB[i] = (double *)malloc(cols * sizeof(double));
    }

    // 행렬 B 입력
    printf("두 번째 행렬의 원소를 입력하세요:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%lf", &matrixB[i][j]);
        }
    }

    // 결과 행렬 C 동적 할당
    double **matrixC = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrixC[i] = (double *)malloc(cols * sizeof(double));
    }

    // 두 행렬을 더함
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    // 결과 출력
    printf("두 행렬의 합:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.lf ", matrixC[i][j]);
        }
        printf("\n");
    }

    // 동적 할당된 메모리 해제
    for (int i = 0; i < rows; i++) {
        free(matrixA[i]);
        free(matrixB[i]);
        free(matrixC[i]);
    }
    free(matrixA);
    free(matrixB);
    free(matrixC);

    return 0;
}

