#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
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
bool isMin = true;

void minSortNode(node* n);
void maxSortNode(node* n);
node* insertNode(node* root, char* str, int heapSize);
node* deleteNode(node* root);
node* findLastNode(node* root);
void resortMinNode(node* root);
void resortMaxNode(node* root);
int isEmpty();


void minSortNode(node* n) {
	node* tmp = n;
	while (tmp->parent != NULL && strcmp(tmp->key, tmp->parent->key) <= 0) {
		char tmpStr[100] = { NULL };
 		strcpy(tmpStr, tmp->key);
		strcpy(tmp->key, tmp->parent->key);
		strcpy(tmp->parent->key, tmpStr);
		tmp = tmp->parent;		
	}
}

void maxSortNode(node* n) {
	node* tmp = n;
	while (tmp->parent != NULL && strcmp(tmp->key, tmp->parent->key) > 0) {
		char tmpStr[100] = { NULL };
		strcpy(tmpStr, tmp->key);
		strcpy(tmp->key, tmp->parent->key);
		strcpy(tmp->parent->key, tmpStr);
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
	strcpy(newNode->key, str);
	newNode->parent = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	
	// empty
	if (heap_head == NULL) {
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
					
					if (isMin)
						minSortNode(newNode);
					else
						maxSortNode(newNode);
											
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

					if (isMin) 
						minSortNode(newNode);
					else 
						maxSortNode(newNode);

				
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



void resortMinNode(node* root) {
	char tmpStr[10] = {NULL};
	node* tmp = root;
	while (tmp->left) {
		if (tmp->left != NULL && tmp->right != NULL) {
			if (strcmp(tmp->left->key, tmp->right->key) <= 0 && strcmp(tmp->key, tmp->left->key) >= 0) {
				strcpy(tmpStr, tmp->key);
				strcpy(tmp->key, tmp->left->key);
				strcpy(tmp->left->key, tmpStr);
				tmp = tmp->left;
			}
			else if (strcmp(tmp->left->key, tmp->right->key) > 0 && strcmp(tmp->key, tmp->right->key) < 0) {
				strcpy(tmpStr, tmp->key);
				strcpy(tmp->key, tmp->right->key);
				strcpy(tmp->right->key, tmpStr);
				tmp = tmp->right;
			}
		}
		else if (tmp->left != NULL && tmp->right == NULL) {
			if (strcmp(tmp->left->key, tmp->key) < 0) {
				strcpy(tmpStr, tmp->key);
				strcpy(tmp->key, tmp->left->key);
				strcpy(tmp->left->key, tmpStr);
			}
			else break;
		}
		else break;
	}
}

void resortMaxNode(node* root) {
	char tmpStr[10] = { NULL };
	node* tmp = root;
	while (tmp->left) {
		if (tmp->left != NULL && tmp->right != NULL) {
			if (strcmp(tmp->left->key, tmp->right->key) >= 0 && strcmp(tmp->key, tmp->left->key) <= 0) {
				strcpy(tmpStr, tmp->key);
				strcpy(tmp->key, tmp->left->key);
				strcpy(tmp->left->key, tmpStr);
				tmp = tmp->left;
			}
			else if (strcmp(tmp->left->key, tmp->right->key) < 0 && strcmp(tmp->key, tmp->right->key) > 0) {
				strcpy(tmpStr, tmp->key);
				strcpy(tmp->key, tmp->right->key);
				strcpy(tmp->right->key, tmpStr);
				tmp = tmp->right;
			}
		}
		else if (tmp->left != NULL && tmp->right == NULL) {
			if (strcmp(tmp->left->key, tmp->key) > 0) {
				strcpy(tmpStr, tmp->key);
				strcpy(tmp->key, tmp->left->key);
				strcpy(tmp->left->key, tmpStr);
			}
			else break;
		}
		else break;
	}
}

int isEmpty() {
	if (heap_head == NULL) {
		printf("Heap is Empty. INSERT first.\n");

		return 1;
	}
	else return 0;
}

node* findLastNode(node* root) {
	node* ptr;
	ptr = root;
	while (ptr != NULL) {
		if (ptr->left && ptr->right) {
			ptr = ptr->right;
		}
		else if (ptr->left && !(ptr->right)) {
			ptr = ptr->left;
		}
		else return ptr;
	}
	return ptr;
}



node* deleteNode(node* root) {
	if (isEmpty()) {
		return;
	}
	else {
		printf("%s\n", heap_head->key);

		strcpy(heap_head->key, heap_tail->key);
		node* tmp = heap_tail;
		if (tmp->parent == NULL) {
			free(tmp);
			heapSize--;
			root = NULL;
			heap_head = NULL;
			return root;
		}
		else if (tmp->parent != NULL) {
			if (tmp->parent->right == tmp) {
				tmp->parent->right = NULL;
			}
			else {
				tmp->parent->left = NULL;
			}
			free(tmp);
		}
		

		if (isMin)
			resortMinNode(root);
		else
			resortMaxNode(root);

		heap_tail = findLastNode(root);

		heapSize--;

		return root;
	}
	
}


void sort(node* root) {
	while (!isEmpty()) {
		deleteNode(root);
	}
}



int main() {	
	char str[20];
	
	/*handler*/
	while (true) {
		printf("> ");
		fgets(str, MAX_LENGTH, stdin);
		if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';
		// set mode
		if (strcmp("START MIN", str) == 0) {
			isMin = true;
			break;
		}
		else if (strcmp("START MAX", str) == 0) {
			isMin = false;
			break;
		}
		else {
			printf("Input \"START MIN\" or \"START MAX\".\n");
		}
	}

	int i = 0;

	printf("> ");
	fgets(str, MAX_LENGTH, stdin);
	if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';

	if (strcmp("QUIT", str) != 0) {
		while (strcmp("QUIT", str) != 0) {

			// INSERT
			if(strncmp("INSERT", str, 6) == 0) {
				heapSize++;	 // start of size is 1.

				char sArr[MAX_LENGTH];
				strcpy(sArr, str);
				char* ptr = strtok(sArr, "INSERT ");
				if (islower(ptr[0]) || isdigit(ptr[0])) {
					root = insertNode(root, ptr, heapSize);
				}
				else
					printf("key value must be LOWER character. Input again, please.\n");
			}

			// DELETE
			else if (strcmp("DELETE", str) == 0) {
				deleteNode(root);
			}

			// SORT
			else if (strcmp("SORT", str) == 0) {
				sort(root);
			}
			else {
				printf("Input \"INSERT\" || \"DELETE\" || \"SORT\".\n");
			}
						
			printf("> ");
			fgets(str, MAX_LENGTH, stdin);
			if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';
		}
	}
	


}
