#include <stdio.h>
#include <stdlib.h>

#define lrg 10

void acceptMatrix(int matrix[lrg][lrg], int rows, int cols);
void displayMatrix(int matrix[lrg][lrg], int rows, int cols);
void addMatrices(int mat1[lrg][lrg], int mat2[lrg][lrg], int result[lrg][lrg], int rows, int cols);
void subtractMatrices(int mat1[lrg][lrg], int mat2[lrg][lrg], int result[lrg][lrg], int rows, int cols);
void multiplyMatrices(int mat1[lrg][lrg], int mat2[lrg][lrg], int result[lrg][lrg], int r1, int c1, int c2);
void transposeMatrix(int matrix[lrg][lrg], int transpose[lrg][lrg], int rows, int cols);
int i, j, k;

int main() 
{
    int matA[lrg][lrg], matB[lrg][lrg], result[lrg][lrg];
    int r1, c1, r2, c2, ch;

    printf("Enter rows and columns for Matrix A: ");
    scanf("%d %d", &r1, &c1);
    printf("Enter rows and columns for Matrix B: ");
    scanf("%d %d", &r2, &c2);

    printf("\n--- Input Matrix A ---\n");
    acceptMatrix(matA, r1, c1);
    printf("\n--- Input Matrix B ---\n");
    acceptMatrix(matB, r2, c2);

    do
    {
        printf("\n MATRIX OPERATIONS MENU ");
        printf("\n1. Display Matrices");
        printf("\n2. Add Matrices");
        printf("\n3. Subtract Matrices");
        printf("\n4. Multiply Matrices");
        printf("\n5. Transpose Matrix A");
        printf("\n6. Exit");
        printf("\nEnter your choice (1-6): ");
        scanf("%d", &ch);

        switch (ch) 
        {
            case 1:
                printf("\nMatrix A:\n");
                displayMatrix(matA, r1, c1);
                printf("\nMatrix B:\n");
                displayMatrix(matB, r2, c2);
                break;

            case 2:
                if (r1 == r2 && c1 == c2) {
                    addMatrices(matA, matB, result, r1, c1);
                    printf("\nResult of Addition:\n");
                    displayMatrix(result, r1, c1);
                } else {
                    printf("\nError: Matrices must have identical dimensions for addition.\n");
                }
                break;

            case 3:
                if (r1 == r2 && c1 == c2) {
                    subtractMatrices(matA, matB, result, r1, c1);
                    printf("\nResult of Subtraction:\n");
                    displayMatrix(result, r1, c1);
                } else {
                    printf("\nError: Matrices must have identical dimensions for subtraction.\n");
                }
                break;

            case 4:
                if (c1 == r2) {
                    multiplyMatrices(matA, matB, result, r1, c1, c2);
                    printf("\nResult of Multiplication:\n");
                    displayMatrix(result, r1, c2);
                } else {
                    printf("\nError: Columns of Matrix A must equal rows of Matrix B for multiplication.\n");
                }
                break;

            case 5:
                transposeMatrix(matA, result, r1, c1);
                printf("\nTranspose of Matrix A:\n");
                displayMatrix(result, c1, r1);
                break;

            case 6:
                printf("\nExiting program.\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please enter a number between 1 and 6.\n");
        }
    }while(ch!=6);
    
    return 0;
}

void acceptMatrix(int matrix[lrg][lrg], int rows, int cols) 
{
    for (i = 0; i < rows; i++) 
    {
        for (j = 0; j < cols; j++) 
        {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void displayMatrix(int matrix[lrg][lrg], int rows, int cols) 
{
    for (i = 0; i < rows; i++) 
    {
        for (j = 0; j < cols; j++) 
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(int mat1[lrg][lrg], int mat2[lrg][lrg], int result[lrg][lrg], int rows, int cols) 
{
    for (i = 0; i < rows; i++) 
	{
        for (j = 0; j < cols; j++) 
		{
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void subtractMatrices(int mat1[lrg][lrg], int mat2[lrg][lrg], int result[lrg][lrg], int rows, int cols) 
{
    for (i = 0; i < rows; i++) 
    {
        for (j = 0; j < cols; j++) 
        {
            result[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}

void multiplyMatrices(int mat1[lrg][lrg], int mat2[lrg][lrg], int result[lrg][lrg], int r1, int c1, int c2) 
{
    for (i = 0; i < r1; i++) 
    {
        for (j = 0; j < c2; j++) 
        {
            result[i][j] = 0;
            for (k = 0; k < c1; k++) 
            {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void transposeMatrix(int matrix[lrg][lrg], int transpose[lrg][lrg], int rows, int cols) 
{
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++) 
        {
            transpose[j][i] = matrix[i][j];
        }
    }
}
