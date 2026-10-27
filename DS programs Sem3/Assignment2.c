#include <stdio.h>

void readSparse(int sparse[50][3]) 
{
    int rows, cols, i, j, val, c = 0;

    printf("Enter number of rows and columns of matrix: ");
    scanf("%d %d", &rows, &cols);

    int matrix[50][50];
    printf("Enter the matrix elements :\n");
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            scanf("%d", &matrix[i][j]);

    for (i = 0; i < rows; i++) 
	{
        for (j = 0; j < cols; j++) 
		{
            if (matrix[i][j] != 0) 
			{
                c++;
                sparse[c][0] = i;
                sparse[c][1] = j;
                sparse[c][2] = matrix[i][j];
            }
        }
    }

    sparse[0][0] = rows;
    sparse[0][1] = cols;
    sparse[0][2] = c;
}

void display(int sparse[50][3]) 
{
    int i, n = sparse[0][2];

    printf("\nRow  Col  Value\n");
    for (i = 0; i <= n; i++)
        printf("%-4d %-4d %-4d\n", sparse[i][0], sparse[i][1], sparse[i][2]);
}

void simpleTranspose(int sparse[50][3], int result[50][3]) 
{
    int rows = sparse[0][0];
    int cols = sparse[0][1];
    int n = sparse[0][2];
    int i, j, k = 1;

    result[0][0] = cols;
    result[0][1] = rows;
    result[0][2] = n;

    for (i = 0; i < cols; i++) 
	{
        for (j = 1; j <= n; j++) 
		{
            if (sparse[j][1] == i) 
			{
                result[k][0] = sparse[j][1];
                result[k][1] = sparse[j][0];
                result[k][2] = sparse[j][2];
                k++;
            }
        }
    }
}

void fastTranspose(int sparse[50][3], int result[50][3]) 
{
    int rows = sparse[0][0];
    int cols = sparse[0][1];
    int n = sparse[0][2];
    int rowTerms[50], startPos[50];
    int i, j, pos;

    result[0][0] = cols;
    result[0][1] = rows;
    result[0][2] = n;

    if (n <= 0)
        return;

    for (i = 0; i < cols; i++)
        rowTerms[i] = 0;

    for (i = 1; i <= n; i++)
        rowTerms[sparse[i][1]]++;

    startPos[0] = 1;
    for (i = 1; i < cols; i++)
        startPos[i] = startPos[i - 1] + rowTerms[i - 1];

    for (i = 1; i <= n; i++) 
	{
        j = sparse[i][1];
        pos = startPos[j];

        result[pos][0] = sparse[i][1];
        result[pos][1] = sparse[i][0];
        result[pos][2] = sparse[i][2];

        startPos[j]++;
    }
}

int main() 
{
    int sparse[50][3], result[50][3];
    int ch;

    readSparse(sparse);

    printf("\nSparse matrix:\n");
    display(sparse);

    printf("\nChoose any one transpose method:\n");
    printf("1. Simple Transpose\n2. Fast Transpose\n");
    scanf("%d", &ch);

    if (ch == 1)
        simpleTranspose(sparse, result);
    else if (ch == 2)
        fastTranspose(sparse, result);
    else 
	{
        printf("Invalid choice\n");
        return 0;
    }

    printf("\nTransposed sparse matrix:\n");
    display(result);

    return 0;
}
