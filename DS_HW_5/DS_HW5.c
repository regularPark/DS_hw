#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_COUNT 150000
#define MAX_LENGTH 20




void insertSort() {

}

void quickSort() {

}

void mergeSort() {

}

void heapSort() {

}

void bubbleSort(char(*str)[MAX_LENGTH + 1], int size) {
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			
			if (strcmp(*str, *(str+1)) > 0)
			{
				char tmp[MAX_LENGTH] = { NULL, };
				strcpy(tmp, *str);
				strcpy(*(str+1), *str);
				strcpy(*str, tmp);
			}
			*(str++);

		}
	}
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
		printf("%s ", &str[i]);
	}


	bubbleSort(str, n);

}
