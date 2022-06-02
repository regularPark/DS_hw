#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_COUNT 15000
#define MAX_LENGTH 20

void insertSort(char(*str)[MAX_LENGTH + 1], int size);
void bubbleSort(char(*str)[MAX_LENGTH + 1], int size);


void insertSort(char (*str)[MAX_LENGTH + 1], int size) {
	clock_t isStart, isEnd;
	float isRes;
	isStart = clock();

	
	int j;
	for (int i = 1; i < size; i++) {
		char tmp[MAX_LENGTH + 1] = { NULL, };

		strcpy(tmp, *(str + i));		
		for (j = i - 1; j >= 0; j--) {
			if (strcmp(*(str + j), tmp) > 0)
				strcpy(*(str + j + 1), *(str + j));
			else
				break; 
		}
		strcpy(*(str + j + 1), tmp);
	}

	isEnd = clock();

	isRes = (float)(isEnd - isStart) / CLOCKS_PER_SEC;

	printf("\n");

	/*for (int i = 0; i < size; i++) {
		printf("%s ", str[i]);
	}*/

	printf("\nInsert sort : %f", isRes);
	printf("done");

}

void quickSort(char (*str)[MAX_LENGTH+1], int left, int right) {
	int L = left, R = right;
	char pivot[MAX_LENGTH + 1] = *(str + ((left + right) / 2));
}

void mergeSort() {

}

void heapSort() {

}

void bubbleSort(char(*str)[MAX_LENGTH + 1], int size) {
	clock_t bsStart, bsEnd;
	float bsRes;
	bsStart = clock();

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{

			if (strcmp(*(str+j), *(str + j + 1)) > 0)
			{
				char tmp[MAX_LENGTH+1] = { NULL, };
				strcpy(tmp, *(str + j));
				strcpy(*(str + j), *(str + j + 1));
				strcpy(*(str + j + 1), tmp);
			}
		}
	}
	bsEnd = clock();

	bsRes = (float)(bsEnd - bsStart) / CLOCKS_PER_SEC;

	printf("\n");
	

	printf("\nbubble sort : %f", bsRes);
	printf("done");
}

int main() {
	int n;
	int str_len;
	printf(">./sort ");
	scanf("%d", &n);

	char str[MAX_COUNT][MAX_LENGTH + 1] = { NULL, };
	

	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++) {
		str_len = 1 + rand() % 20;

		for (int j = 0; j < str_len; j++) {
			str[i][j] = 'a' + rand() % 26;
		}
	}

	insertSort(str, n);
	printf("\n");

	bubbleSort(str, n);
	printf("\n");
	

	printf("done");
	return 0;
}
