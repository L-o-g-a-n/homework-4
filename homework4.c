#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void input_data(int *row, int *col); //행과 열의 값을 입력받는 함수
int **create_matrix(int row, int col); //동적할당을 통해 행렬을 만드는 함수
int free_matrix(int **matrix, int row, int col); //동적할당을 해제하는 함수
void print_matrix(int **matrix, int row, int col); //행렬을 출력하는 함수
int fill_data(int **matrix, int row, int col); //행렬을 0 ~ 19 사이의 랜덤값으로 초기화시키는 함수
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col); //두 행렬의 합을 구하는 함수
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col); //두 행렬의 차를 구하는 함수
int transpose_matrix(int **matrix, int **matrix_t, int row, int col); //행렬을 전치시키는 함수
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col); //전치 행렬과의 곱을 하는 행렬 곱 함수



int i,j,u; //for문에서 사용할 변수;

int main(void)
{
	srand(time(NULL)); //매번 다른 난수를 뽑기 위함
	int checking_return; //함수 호출 시에 반환값을 통해 정상 반환인지 비정상 반환인지 판별하기 위한 변수
	int row, col; //행과 열
	int **a; //행렬 A
	int **b; //행렬 B
	int **result; //연산의 결과를 담기 위한 이중 포인터
	printf("------------software 2017038063 박성진-------------\n");

	//행렬의 합과 차를 구하기 위한 동적할당 및 초기화입니다
	input_data(&row, &col);
	a = create_matrix(row,col); //행렬 A에 동적할당
	b = create_matrix(row,col); //행렬 B에 동적할당
	result = create_matrix(row,col); //리절트에 동적할당

	checking_return = fill_data(a,row,col); //A에 난수를 채우며 오류 검사
	if(checking_return != 1)
	{
		printf("Error!\n");
		exit(1);
	}

	checking_return = fill_data(b,row,col); //B에 난수를 채우며 오류 검사
	if(checking_return != 1)
	{
		printf("Error!\n");
		exit(1);
	}

	printf("행렬 A\n");
	print_matrix(a,row,col); //행렬 A 출력
	printf("행렬 B\n");
	print_matrix(b,row,col); //행렬 B 출력

	printf("행렬 A + B\n");
	checking_return = addition_matrix(a,b,result,row,col); //행렬 A + B 연산
	if(checking_return != 1)
	{
		printf("Error!\n");
		exit(1);
	}
	print_matrix(result,row,col); //행렬 A + B 결과 출력

	printf("행렬 A - B\n");
	checking_return = subtraction_matrix(a,b,result,row,col); //행렬 A - B 연산
	if(checking_return != 1)
	{
		printf("Error!\n");
		exit(1);
	}
	print_matrix(result,row,col); //행렬 A - B 결과 출력

	checking_return = free_matrix(b,row,col); //행렬 B 동적할당 해제
	if(checking_return != 1)
	{
		printf("Error!\n");
		exit(1);
	}

	checking_return = free_matrix(result,row,col); //행렬 RESULT 동적할당 해제
	if(checking_return != 1)
	{
		printf("Error!\n");
		exit(1);
	}

	//여기서부터 b행렬은 전치 함수를 담을 것이고, result는 전치 행렬과의 곱을 담을 것이다
	b = create_matrix(col,row); //전치 함수를 담을 것이기 때문에 행과 열을 바꿔 동적할당한다
	result = create_matrix(row,row); //전치 행렬과의 곱을 담을 것이라 행과 열은 모두 row이다

	checking_return = transpose_matrix(a,b,row,col); //행렬 A의 전치행렬을 B에 담는다
	if(checking_return != 1)
	{
		printf("Error!\n");
		exit(1);
	}

	printf("행렬 A의 전치행렬 B\n");
	print_matrix(b,col,row); //행렬 A의 전치행렬 B를 출력

	checking_return = multiply_matrix(a,b,result,row,col); //전치행렬과의 곱을 연산
	if(checking_return != 1)
	{
		printf("Error!\n");
		exit(1);
	}

	printf("행렬 A의 전치행렬 B와의 곱\n");
	print_matrix(result,row,row); //전치행렬과의 곱을 출력


	return 0;
}

void input_data(int *row, int *col) //행과 열의 값을 입력받는 함수
{
	printf("row(행)의 값 : ");
	scanf("%d", row); //행을 입력받는다
	printf("column(열)의 값 : ");
	scanf("%d", col); //열을 입력받는다

	if (row <= 0 || col <= 0) //행과 열의 입력 오류를 검사
	{
		printf("check the size of rows and columns\n");
		exit(1); //오류 발생시 프로그램 강제 종료
	}
}

int **create_matrix(int row, int col) //동적할당으로 배열을 생성하는 함수
{
	if (row <= 0 || col <= 0) //전처리 과정으로 행과 열의 입력 오류를 검사
	{
		printf("check the size of rows and columns\n");
		exit(1); //오류 발생시 프로그램 강제 종료
	}

	int **ptr; //동적할당으로 만들 배열을 가리키는 이중 포인터 변수
	ptr = (int **)malloc(sizeof(int*) * row); //행을 동적할당으로 만들어준다

	if (ptr == NULL) //동적할당이 제대로 되었는지 검사
	{
		printf("malloc error\n");
		exit(1); //오류 발생시 프로그램 강제 종료
	}

	for(int i=0;i<row;i++)
	{
		ptr[i] = (int *)malloc(sizeof(int) * col); //열을 동적할당으로 만들어주고 행과 매핑시킨다

		if (ptr[i] == NULL) //동적할당이 제대로 되었는지 검사
		{
			printf("malloc error\n");
			exit(1); //오류 발생시 프로그램 강제 종료
		}
	}

	return ptr; //만들어진 배열의 주소값을 반환
}

int free_matrix(int **matrix, int row, int col) //동적할당을 해제하는 함수
{
	if (row <= 0 || col <= 0) //전처리 과정으로 행과 열의 입력 오류를 검사
	{
		printf("check the size of rows and columns\n");
		exit(1); //오류 발생시 프로그램 강제 종료
	}

	for(i=0;i<row;i++) //우선 열부터 해제를 해주고
	{
		free(matrix[i]);
	}
	free(matrix); //행을 해제해준다

	return 1;
}

void print_matrix(int **matrix, int row, int col)
{
	if (row <= 0 || col <= 0) //행과 열의 입력 오류를 검사
	{
		printf("check the size of rows and columns\n");
		exit(1); //오류 발생시 프로그램 강제 종료
	}

	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int fill_data(int **matrix, int row, int col) //배열을 0~19사이의 랜덤값으로 초기화시키는 함수
{
	if (row <= 0 || col <= 0) //행과 열의 입력 오류를 검사
	{
		printf("check the size of rows and columns\n");
		exit(1); //오류 발생시 프로그램 강제 종료
	}


	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			matrix[i][j] = rand() % 20; //난수를 활용해서 0~19 사이의 랜덤값 구현
		}
	}

	if(matrix == NULL) //최종적으로 반환할 배열의 오류 검사
		return -1; //오류시에 -1을 반환하도록 통일

	return 1; //정상 반환시 1을 반환

}

int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col) //두 행렬의 합을 구하는 함수
{
	if (row <= 0 || col <= 0) //행과 열의 입력 오류를 검사
	{
		printf("check the size of rows and columns\n");
		exit(1); //오류 발생시 프로그램 강제 종료
	}

	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
		}
	}

	if(matrix_sum == NULL) //최종적으로 반환할 배열의 오류 검사
		return -1; //오류시에 -1을 반환하도록 통일

	return 1; //정상 반환시 1을 반환
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col)
{
	if (row <= 0 || col <= 0) //행과 열의 입력 오류를 검사
	{
		printf("check the size of rows and columns\n");
		exit(1); //오류 발생시 프로그램 강제 종료
	}

	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
		}
	}

	if(matrix_sub == NULL) //최종적으로 반환할 배열의 오류 검사
		return -1; //오류시에 -1을 반환하도록 통일

	return 1; //정상 반환시 1을 반환
}

int transpose_matrix(int **matrix, int **matrix_t, int row, int col) //전치 행렬을 구하는 함수이다
{//여기서 row와 col은 전치시키기 전의 행과 열을 기준으로 한다
	if (row <= 0 || col <= 0) //행과 열의 입력 오류를 검사
	{
		printf("check the size of rows and columns\n");
		exit(1); //오류 발생시 프로그램 강제 종료
	}

	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			matrix_t[j][i] = matrix[i][j]; //행렬의 행과 열을 바꿔준다
		}
	}

	if(matrix_t == NULL) //최종적으로 반환할 배열의 오류 검사
		return -1; //오류시에 -1을 반환하도록 통일

	return 1; //정상 반환시 1을 반환
}

int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col) //전치행렬과의 곱을 하는 행렬곱 함수
{ //매개변수로 넘겨받는 행과 열은 전치 시키기 전의 행과 열이다
	if (row <= 0 || col <= 0) //행과 열의 입력 오류를 검사
	{
		printf("check the size of rows and columns\n");
		exit(1); //오류 발생시 프로그램 강제 종료
	}

	int sum=0; //곱셈의 결과를 누적합하기 위한 변수이다

	for(i=0;i<row;i++) //결과 행렬의 1열 계산할때마다 도는 사이클이다
	{

		for(j=0;j<row;j++) //가장안쪽 포문과 함께 곱셈을 수행한다
		{

			for(u=0;u<col;u++)
			{
				sum += matrix_a[j][u] * matrix_t[u][i]; //결과 행렬의 1원소를 구할때까지 sum에 누적합한다
			}
			matrix_axt[i][j] = sum; //누적합 결과를 원소로 넣어준다
			sum = 0; //다음 누적합 계산에 오류가 없도록 0으로 초기화시켜준다

		}

	}

	if(matrix_axt == NULL) //최종적으로 반환할 배열의 오류 검사
		return -1; //오류시에 -1을 반환하도록 통일

	return 1; //정상 반환시 1을 반환
}
