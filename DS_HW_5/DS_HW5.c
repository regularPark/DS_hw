#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_COUNT 150000
#define MAX_LENGTH 21

// 시간 리턴하기

void insertSort(char(**str)[MAX_COUNT], int size);
void bubbleSort(char(**str)[MAX_COUNT], int size);
void merge(char(**str)[MAX_COUNT], int start, int middle, int end);
void mergeSort(char(**str)[MAX_COUNT], int start, int end);
void quickSort(char(**str)[MAX_COUNT], int left, int right);
void qSortHandler(char *str[MAX_COUNT], int size);

char mergeSorted[MAX_COUNT][MAX_LENGTH];
char *sArr[MAX_COUNT] = { NULL, };


void insertSort(char (**str)[MAX_COUNT], int size) {
	// malloc
	for (int i = 0; i < size; i++) {
		sArr[i] = (char*)malloc(sizeof(char)*(MAX_LENGTH));
		strcpy(sArr[i], *(str + i));
	}

	clock_t isStart, isEnd;
	float isRes;
	isStart = clock();

	printf("\n=> Starting – Insert sort\n");

	int j;
	for (int i = 1; i < size; i++) {
		char tmp[MAX_LENGTH] = { NULL, };

		strcpy(tmp, sArr[i]);		
		for (j = i - 1; j >= 0; j--) {
			if (strcmp(sArr[j], tmp) > 0)
				strcpy(sArr[j + 1], sArr[j]);
			else
				break; 
		}
		strcpy(sArr[j + 1], tmp);
	}

	isEnd = clock();

	isRes = (float)(isEnd - isStart) / CLOCKS_PER_SEC;


	/*for (int i = 0; i < size; i++) {
		printf("%s ", str[i]);
	}*/

	printf("=> Finished\n");
	printf("Insert sort : %f\n", isRes);

	FILE *fp;
	if ((fp = fopen("insertSort.txt", "w")) == NULL) {
		fprintf(stderr, "Error ");
		exit(1);
	}
	for (int i = 0; i < size; i++)
		fprintf(fp, "%s ", sArr[i]);
	fclose(fp); 

	// free malloc
	for (int i = 0; i < size; i++) {
		free(sArr[i]);
	}
}


void quickSort(char(**str)[MAX_COUNT], int left, int right) {
	int L = left, R = right;
	char tmp[MAX_LENGTH] = { NULL, };
	char pivot[MAX_LENGTH] = { NULL, };
	strcpy(pivot, *(str + ((left + right) / 2)));
	while (L <= R) {
		while (strcmp(pivot, *(str + L)) > 0)
			L++;
		while (strcmp(pivot, *(str + R)) < 0)
			R--;
		if (L <= R) {
			if (L != R) {
				strcpy(tmp, *(str + L));
				strcpy(*(str + L), *(str + R));
				strcpy(*(str + R), tmp);
			}
			L++;
			R--;
		}
	}
	if (left < R)
		quickSort(str, left, R);
	if (right > L)
		quickSort(str, L, right);
}

void qSortHandler(char *str[MAX_COUNT], int size) {
	// malloc for quick sort
	for (int i = 0; i < size; i++) {
		sArr[i] = (char*)malloc(sizeof(char)*(MAX_LENGTH));
		strcpy(sArr[i], str[i]);
	}

	clock_t qsStart, qsEnd;
	float qsRes;
	qsStart = clock();
	printf("=> Starting – Quick sort\n");

	quickSort(sArr, 0, size - 1);

	qsEnd = clock();
	qsRes = (float)(qsEnd - qsStart) / CLOCKS_PER_SEC;
	printf("=> Finished\n");
	printf("Quick sort : %f", qsRes);
	printf("\n");

	FILE *fp;
	if ((fp = fopen("quickSort.txt", "w")) == NULL) {
		fprintf(stderr, "Error ");
		exit(1);
	}
	for (int i = 0; i < size; i++)
		fprintf(fp, "%s ", sArr[i]); 
	fclose(fp); 

	for (int i = 0; i < size; i++) {
		free(sArr[i]);
	}
}


void merge(char(**str)[MAX_COUNT], int start, int middle, int end) {
	int i, j, k;
	i = start;
	j = middle + 1;
	k = start;

	// crossed case
	while (i <= middle && j <= end) {
		if (strcmp(*(str + j), *(str + i)) >= 0) {
			strcpy(mergeSorted[k], *(str + i));
			i++;
		}
		else {
			strcpy(mergeSorted[k], *(str + j));
			j++;
		}
		k++; // next of array
	}

	if (i > middle) {
		for (int t = j; t <= end; t++) {
			strcpy(mergeSorted[k], *(str + t));
			k++;
		}
	}
	else{
		for (int t = i; t <= middle; t++) {
			strcpy(mergeSorted[k], *(str + t));
			k++;
		}
	}

	// insert sorted array
	for (int t = start; t <= end; t++) {
		strcpy(*(str + t), mergeSorted[t]);
	}
}

void mergeSort(char(**str)[MAX_COUNT], int start, int end) {
	
	if (start < end) {
		int middle;
		middle = (start + end) / 2;
		mergeSort(str, start, middle);
		mergeSort(str, middle + 1, end);
		merge(str, start, middle, end);
	}
}

void mgSortHandler(char *str[MAX_COUNT], int size) {
	// malloc for merge sort
	for (int i = 0; i < size; i++) {
		sArr[i] = (char*)malloc(sizeof(char)*(MAX_LENGTH));
		strcpy(sArr[i], str[i]);
	}

	clock_t mgStart, mgEnd;
	float mgRes;
	mgStart = clock();
	printf("=> Starting – Merge sort\n");

	mergeSort(sArr, 0, size - 1);

	FILE *fp;
	if ((fp = fopen("mergeSort.txt", "w")) == NULL) {
		fprintf(stderr, "Error ");
		exit(1);
	}
	for (int i = 0; i < size; i++)
		fprintf(fp, "%s ", mergeSorted[i]);
	fclose(fp);
	

	mgEnd = clock();
	mgRes = (float)(mgEnd - mgStart) / CLOCKS_PER_SEC;
	printf("=> Finished\n");
	printf("Merge sort : %f", mgRes);

	

	for (int i = 0; i < size; i++) {
		free(sArr[i]);
	}
}


void bubbleSort(char(**str)[MAX_COUNT], int size) {
	// malloc
	for (int i = 0; i < size; i++) {
		sArr[i] = (char*)malloc(sizeof(char)*(MAX_LENGTH));
		strcpy(sArr[i], *(str + i));
	}

	clock_t bsStart, bsEnd;
	float bsRes;
	bsStart = clock();

	printf("\n=> Starting – Bubble sort\n");

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{

			if (strcmp(sArr[j], sArr[j+1]) > 0)
			{
				char tmp[MAX_LENGTH] = { NULL, };
				strcpy(tmp, sArr[j]);
				strcpy(sArr[j], sArr[j + 1]);
				strcpy(sArr[j + 1], tmp);
			}
		}
	}
	bsEnd = clock();

	bsRes = (float)(bsEnd - bsStart) / CLOCKS_PER_SEC;


	/*for (int i = 0; i < size; i++) {
		printf("%s ", bsArr[i]);
	}
	printf("\n");*/
	
	

	printf("=> Finished\n");
	printf("Bubble sort : %f", bsRes);

	FILE *fp;
	if ((fp = fopen("bubbleSort.txt", "w")) == NULL) {
		fprintf(stderr, "Error "); 
		exit(1);
	}
	for(int i = 0; i < size; i++)
		fprintf(fp, "%s ", sArr[i]); 
	fclose(fp); 

	// free malloc
	for (int i = 0; i < size; i++) {
		free(sArr[i]);
	}



}


void heapSort() {

}



int main() {
	int n;
	int str_len;
	printf(">./sort ");
	scanf("%d", &n);

	char *wArr[MAX_COUNT];	

	srand((unsigned int)time(NULL));
	
	printf("\n=> Generating random characters…");

	for (int i = 0; i < n; i++) {
		str_len = 1 + rand() % 20;
		char word[MAX_LENGTH] = { NULL,};

		for (int j = 0; j < str_len; j++) {
			word[j] = 'a' + rand() % 26;
		}
		wArr[i] = (char*)malloc(sizeof(char)* (MAX_LENGTH));
		strcpy(wArr[i], word);
	}
	
	bubbleSort(wArr, n);
	printf("\n");

	insertSort(wArr, n);
	printf("\n");


	qSortHandler(wArr, n);
	printf("\n");

	mgSortHandler(wArr, n);
	printf("\n");
	

	//for (int i = 0; i < n; i++) {
	//	printf("%s ", wArr[i]);
	//}
	//printf("\n");

	printf("done");
	return 0;
}
