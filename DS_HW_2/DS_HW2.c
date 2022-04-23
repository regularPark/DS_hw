// 2019113632 Park Jeong-Kyu
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ 5	// 원래 500
#define SIZE 3		// 0 하나씩 더 붙일것
#define TOTAL_SIZE 9 // 마찬가지


typedef struct ListNode {
	int data;
	int idx;
	struct ListNode* prev;
	struct ListNode* next;
} Node;


Node* createHead(Node* p);
void appendNode(Node*head, int n, int i);
int createRandNum(Node* head);
void printList(Node*head);
Node* searchNode(Node*head, int a, int c);





Node* createHead(Node* p) {
	Node* head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->idx = 0;
	head->next = NULL;
	head->prev = NULL;
	return head;
}




void appendNode(Node*head, int n, int i) {
	Node*newNode = (Node*)malloc(sizeof(Node));
	newNode->prev = NULL;
	newNode->next = NULL;
	newNode->data = n;
	newNode->idx = i;
	
	
	if (head->next == NULL) {
		newNode->prev = head;
		newNode->next = NULL;
		head->next = newNode;
		head->prev = NULL;
		head->data = 0;
	}
	else {
		Node*p = head;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = newNode;
		newNode->prev = p;
	}
}



int createRandNum(Node* head) {
	int i, j, k, l, tmp, nums[3][SIZE];
	srand(time(NULL));
	
	// create random number
	for (l = 0; l < 3; l++) {
		for (i = 0; i < SIZE;) {
			nums[l][i] = rand() % MAX_ + 1;
			for (j = 0, k = 0; j < i; j++) {
				if (nums[l][i] == nums[l][j]) {
					k = 1; break;
				}
			}
			if (k == 0)
				i = i + 1;
		}
	}
	
	// sort
	for (l = 0; l < 3; l++) {
		for (i = 0; i < SIZE; i++)
			for (j = i+1; j < SIZE; j++) {
				if (nums[l][i] > nums[l][j]) {
					tmp = nums[l][i];
					nums[l][i] = nums[l][j];
					nums[l][j] = tmp;
				}
			}
	}

	// input data in Node
	for (l = 0; l < 3; l++) {
		for (i = 0; i < SIZE; i++) {
			appendNode(head, nums[l][i], l + 1);
		}
	}
}

void printList(Node*head) {
	if (head == NULL) {
		printf("empty list");
	}
	else {
		Node* p = head;
		while (p->next != NULL) {
			p = p->next;
			if (p->idx != p->prev->idx) {				
				if (p->idx == 1) printf("\nA : ");
				if (p->idx == 2) printf("\nB : ");
				if (p->idx == 3) printf("\nC : ");

			}
			if (p->next == NULL) {
				
				printf("%d ", p->data);
			}
			else {
				printf("%d ", p->data);
			}
		}
	}
	printf("\n");
}


Node* searchNode(Node*head, int a, int c) {
	Node*p = head;
	
	// search
	int cnt = 0;
	
	while (p->next != NULL) {
		if (p->idx == a) {			
			++cnt;
			if (cnt == c) return p;
		}		
		p = p->next;
	}
	return p;
}

void insertNode(Node*p, Node*q, int i) {
	if (p->prev->data != 0)p->prev->next = p->next;
	if (p->next != NULL) p->next->prev = p->prev;

	if (q->prev == NULL) {
		q->prev = p;
		p->prev = NULL;
		p->next = q;
		p->idx = i;
	}
	else if (q->next == NULL) {
		q->next = p;
		p->next = NULL;
		p->prev = q;
		p->idx = i;
	}
	else {
		p->prev = q;
		p->next = q->next;
		q->next = p;
		p->next->prev = p;
		p->idx = i;
	}
}




int main() {
	printf("\n");
	Node* head = NULL;
	head = createHead(head);
	createRandNum(head);
	printList(head);
	
	
	// make random number for change
	int i, j, k, r, s[2];
	srand(time(NULL));
		
	for (i = 0; i < 2;) {
		s[i] = rand() % 3 + 1;
		for (j = 0, k = 0; j < i; j++) {
			if (s[i] == s[j]) {
				k = 1; break;
			}
		}
		if (k == 0)
			i = i + 1;
	}
	
	r = rand() % 3 + 1; // 30개로 늘려라

	printf("\n%d %d %d", s[0], s[1], r);

	Node*p = searchNode(head, s[0], r);
	printf("\n%d %d\n", p->idx, p->data);
	Node*q = searchNode(head, s[1], r);
	printf("\n%d %d\n", q->idx, q->data);


	insertNode(p, q, s[1]);
	printList(head);
}
