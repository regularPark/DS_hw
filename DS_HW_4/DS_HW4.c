#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 20


typedef struct node {
	char* key;
	struct node* left;
	struct node* right;
	struct node* parent;
}node;



int heapSize = 0;
node* root = NULL;
node* heap_head = NULL;
node* heap_tail = NULL;

struct node* minSort(struct node* root, int i, int heapSize);


void minSortNode(node* n) {
	node* tmp = n;
	while (tmp->parent != NULL && strcmp(tmp->key, tmp->parent->key) > 0) {
		char tmpStr[100] = { NULL };
 		strcpy_s(tmpStr, MAX_LENGTH, tmp->key);
		tmp->key = tmp->parent->key;
		tmp->parent->key = tmpStr;
		tmp = tmp->parent;
	}
}

node* insertNode(node* root, char *str, int heapSize) {
	int i = 0;
	int j;
	int bin[20];

	node* newNode;
	node* ptr;
	ptr = root;
	newNode = (node*)malloc(sizeof(node));

	newNode->key = malloc(sizeof(char) * MAX_LENGTH);
	strcpy_s(newNode->key, MAX_LENGTH, str);
	newNode->parent = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	
	// empty
	if (root == NULL) {
		heap_head = newNode;
		heap_tail = newNode;
		root = newNode;
		newNode->parent = NULL;
		newNode->left = NULL;
		newNode->right = NULL;

	}
	
	// using binary heap for others.
	else {
		while (heapSize > 0) {
			bin[i] = heapSize % 2;
			heapSize = heapSize / 2;
			i++;
		}

		// because it is not using array but queue, it needs information of node postion
		// I decide node's position 0 : left / 1 : right. 
		// but there remains a dummy number after calculating.
		// therefore I put a function that changes the position of the dummy number to the front.
		int tmp, start = 0, end = i;
		while (start < (end - 1)) {
			tmp = bin[start];
			bin[start] = bin[end - 1];
			bin[end - 1] = tmp;
			start++;
			end--;
		}

		for (j = 1; j < i; j++) {
			if (bin[j] == 0) {
				if (ptr->left == NULL) {
					ptr->left = newNode;
					newNode->parent = ptr;
					
					minSortNode(newNode);					
						
					heap_tail = newNode;
				}
				else {
					ptr = ptr->left;
				}
			}

			if (bin[j] == 1) {
				if (ptr->right == NULL) {
					ptr->right = newNode;
					newNode->parent = ptr;

					minSortNode(newNode);					
				
					heap_tail = newNode;
				}
				else {
					ptr = ptr->right;
				}
			}
		}		
	}

	return root;

}

//
//struct node* minHeapSort(struct node* root, int heapsize) {
//	for (int i = heapsize / 2; i >= 1; i--) {
//		minSort(root, i, heapSize);
//	}
//}
//
//struct node* minSort(struct node* root, int i, int heapSize) {
//	// backward
//	
//	int s = i;
//	int j = 0, k = 0;
//	int lNode = 2 * i;
//	int rNode = 2 * i + 1;
//	struct node* ptr;
//	struct node* min;
//	ptr = root;
//	int Arr[100];
//	while (i > 0) {
//		Arr[j] = i % 2;
//		i = i / 2;
//		j++;
//	}
//
//	// use again above function.
//	int tmp, start = 0, end = j;
//	while (start < (end - 1)) {
//		tmp = Arr[start];
//		Arr[start] = Arr[end - 1];
//		Arr[end - 1] = tmp;
//		start++;
//		end--;
//	}
//
//	for (k = 1; k < j; k++) {
//		if (Arr[k] == 0) {
//			ptr = ptr->left;
//		}
//		if (Arr[k] == 1) {
//			ptr = ptr->right;
//		}
//	}
//	min = ptr;
//	if (lNode <= heapSize && strcmp(ptr->left->key, ptr->key) < 0 ) {
//		min = ptr->left;
//		s = lNode;
//	}
//	if (rNode <= heapSize && strcmp(ptr->right->key, ptr->key) >= 0) {
//		min = ptr->right;
//		s = rNode;
//	}
//	if (min != ptr) {
//		char tmp[20] = { NULL };
//		strcpy_s(tmp, MAX_LENGTH, min->key);
//		min->key = ptr->key;
//		ptr->key = tmp;
//		
//		minSort(root, s, heapSize);
//	}
//	return root;
//	
//}


int main() {
	char str[10];
	printf("> ");
	scanf_s("%s", &str, sizeof(str));
	//if (strcmp("QUIT", str) != 0) {
	//	while (strcmp("QUIT", str) != 0) {
	//		heapSize++;	 // start of size is 1.
	//		root = insertNode(root, str, heapSize);
	//		printf("> ");
	//		scanf_s("%s", &str, sizeof(str));
	//	}
	//}
	//minHeapSort(root, heapSize);
	heapSize++;	 // start of size is 1.
	root = insertNode(root, str, heapSize);
	printf("> ");
	scanf_s("%s", &str, sizeof(str));
	heapSize++;	 // start of size is 1.
	root = insertNode(root, str, heapSize);
	printf("> ");
	scanf_s("%s", &str, sizeof(str));
	heapSize++;	 // start of size is 1.
	root = insertNode(root, str, heapSize);
	printf("> ");
	scanf_s("%s", &str, sizeof(str));
	heapSize++;	 // start of size is 1.
	root = insertNode(root, str, heapSize);
	printf("> ");
	scanf_s("%s", &str, sizeof(str));
	

}
