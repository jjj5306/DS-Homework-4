#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996) /* scan 경고 무시*/



/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- JoJunHwa  2020039071 -----]\n");

    int row, col;
    srand(time(NULL)); 

    printf("Input row and col : ");
    scanf("%d %d", &row, &col); /* 시드 초기화 */
    int** matrix_a = create_matrix(row, col); //행렬 a 생성
    int** matrix_b = create_matrix(row, col); //행렬 b 생성
    int** matrix_a_t = create_matrix(col, row); //행렬 a의 전치행렬을 저장할 변수
    if(matrix_a != NULL) /*잘 생성 됐으면*/
        printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; }

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); //command를 입력받음

        switch (command) {
        case 'z': case 'Z': //Z의 경우 martrix 초기화
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    int** matrix;
    if (row > 0 && col > 0) //정상적인 입력이면
    {
        matrix = (int**)malloc(sizeof(int*)*col); /* 행의 수만큼 메모리 할당 */ 
        for (int i = 0; i < col; i++)
            matrix[i] = (int*)malloc(sizeof(int) * row); /* 열의 수만큼 메모리 할당 */
        
        if (matrix != NULL) /* 정상적인 출력이면 */
            return matrix; /* matirx에 할당한 메모리를 반환 */
        else /* 비정상적인 출력이면 */
        {
            printf("Error!\n");
            return NULL;
        }
    }
    else /*비정상적인 입력이면 */
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    if (matrix == NULL) /* 비정상적인 입력이면 */
    {
        printf("Error!\n");
    }
    else /* 정상적인 입력이면 */
    {
        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < row; j++)
                printf("%5d ", matrix[i][j]); /* i행 j열의 값 출력 */
            printf("\n"); /* 각 행마다 줄바꿈 */
        }
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    if (matrix == NULL) /* matrix가 비어있으면 -1 반환 */
    {
        printf("Already free matrix\n");
        return -1;
    }
    else
    {
        for (int i = 0; i < col; i++) /* 행들에 대해 col번 만큼 malloc했으므로 그만큼 free */
            free(matrix[i]);
        free(matrix); /* 처음에 한 번 malloc 또 했으므로 또 free */
    }
    matrix = NULL; /* free한 함수는 NULL을 할당하여 처리 */
    if (matrix == NULL) /* 잘 free됐으면 0반환 */
        return 0;
    else /* free에 실패했으면 -1 반환 */
    {
        printf("Fail to free\n");
        return -1;
    }
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    int error; // error가 있는지 검사하는 변수
    int i, j;
    if (matrix != NULL) /* 정상적인 입력이면 */
    {
        for (i = 0; i < col; i++)
            for ( j = 0; j < row; j++)
                matrix[i][j] = rand() % 20; //martrix에 0~19의 값 입력
        for ( i = 0; i < col; i++)
            for ( j = 0; j < row; j++)
                if (matrix[i][j] < 20 && matrix[i][j] > 0)
                    error = 0; /* 이상 없으면 error에 0 할당 */
        if (error == 0) /* error가 없으면 0 반환 */
            return 0;
        else /* 비정상적인 출력이면 -1 반환*/
        {
            printf("Error!\n");
            return -1;
        }
    }
    else /* 비정상적인 입력이면 -1 반환 */
    {
        printf("Error!\n");
        return -1;
    }
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_add = create_matrix(row, col); /* create_matrix함수를 호출해 a, b행렬의 합을 저장할 배열을 생성. */
    

    if (matrix_a == NULL || matrix_b == NULL) /* 비정상적인 입력이면 -1 리턴 */
    {
        printf("Error!\n");
        return -1;
    }
    else
    {
        for (int i = 0; i < col; i++)
            for (int j = 0; j < row; j++)
                matrix_add[i][j] = matrix_a[i][j] + matrix_b[i][j]; /* matrix_add 에 matrix_a 와 matrix_b의 각 원소의 합을 저장 */
        if (matrix_add != NULL) /*add 배열에 값이 잘 들어갔다면 print 후 free 후 0 리턴*/
        {
            print_matrix(matrix_add, row, col);
            free_matrix(matrix_add, row, col);
            return 0;
        }
        else /* 비정상적인 출력이면 -1 리턴 */
        {
            printf("Error!\n"); 
            return -1;
        }
    }
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col); /* create_matrix함수를 호출해 a, b행렬의 차를 저장할 배열을 생성. */


    if (matrix_a == NULL || matrix_b == NULL) /* 비정상적인 입력이면 -1 리턴 */
    {
        printf("Error!\n");
        return -1;
    }
    else
    {
        for (int i = 0; i < col; i++)
            for (int j = 0; j < row; j++)
                matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; /* matrix_sub 에 matrix_a 와 matrix_b의 각 원소의 차를 저장*/
        if (matrix_sub != NULL) /*sub 배열에 값이 잘 들어갔다면 print 후 free 후 0 리턴*/
        {
            print_matrix(matrix_sub, row, col);
            free_matrix(matrix_sub, row, col);
            return 0;
        }
        else /* 비정상적인 출력이면 -1 리턴 */
        {
            printf("Error!\n");
            return -1;
        }
    }
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if (matrix == NULL) /* 비정상적인 입력이면 -1 리턴 */
    {
        printf("Error!\n");
        return -1;
    }
    else
    {
        for (int i = 0; i < col; i++)
            for (int j = 0; j < row; j++)
                matrix_t[i][j] = matrix[j][i]; /* matrix의 행과 열을 바꿔서 matrix_t에 저장 */
        if (matrix_t == NULL) /* 비정상적인 출력이면 -1 리턴 */
        {
            printf("Error!\n");
            return -1;
        }
        else /* 정상적인 출력이면 0 리턴 */
            return 0;
    }
}
    

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{ 
    int** matrix_mul = create_matrix(col, col); /* create_matrix함수를 호출해 a, a의 전치행렬의 곱을 저장할 배열을 생성. mul행렬의 크기는 matrix_a의 행과 matrix_t의 열이므로 col,col이다 */
    if (matrix_a == NULL || matrix_t == NULL) /*matrix_a 가 비정상적이라면 -1 출력*/
    {
        printf("Error!\n");
        return -1;
    }
    else
    {
        for (int i = 0; i < col; i++)
            for (int j = 0; j < col; j++)
            {
                matrix_mul[i][j] = 0;
                for (int k = 0; k < row; k++)
                    matrix_mul[i][j] += matrix_a[i][k] * matrix_t[k][j]; /* mul행렬의 [i][j]에 a행렬의 i행과 t행렬의 j열의 곱의 합을 할당*/
            }
            if (matrix_mul == NULL) /* 비정상적인 출력이면 -1 리턴 */
            {
                printf("Error!\n");
                return -1;
            }
            else /* mul에 잘 저장 됐으면 print 후 free 후 0 리턴 */
            {
                print_matrix(matrix_mul, col, col);
                free_matrix(matrix_mul, col, col);
                return 0;
            }
    }
}
