//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct QNode {
	int data;
	struct QNode* next;
} QNode;

typedef struct Queue {
	QNode* front;
	QNode* rear;
} Queue;



typedef struct stackNode {
	unsigned int size;
	struct Queue* head;
	struct stackNode* link;
}stackNode;

typedef struct {
	struct stackNode* top;
} Stack;


int sIdx = 0; // index for stack
int qIdx = 0; // index for Queue
int sSize = 0;


int enQ(Stack* s, int item);
void deQ(Stack* s);
int isQEmpty(Stack* s);
int isQFull(Stack* s);
int isStackEmpty(Stack* s);
int isStackFull(); 
void push(Stack* s, int d);
int pop(Stack* s);



int enQ(Stack* s, int item) {
	if (isQFull(s)) {
		printf("ENQUEUE(OVERFLOW ERROR)\n");
	}
	else {
		QNode* newNode = (QNode*)malloc(sizeof(QNode));
		Queue* head = s->top->head;
		newNode->data = item;
		newNode->next = NULL;

		if (head->front == NULL) {
			head->front = newNode;
			head->rear = newNode;
			qIdx++;
		}
		else {
			head->rear->next = newNode;
			head->rear = newNode;
			qIdx++;
		}
		printf("- ENQUEUE(%d)\n", item);
	}
	
}

void deQ(Stack* s) {
	QNode* tmp;
	Queue* head = s->top->head;
	int data;
	if (isQEmpty(s)) {
		printf("- DEQUEUE(UNDERFLOW ERROR)\n");
	}
	else {
		tmp = head->front;
		data = tmp->data;
		head->front = tmp->next;

		if (head->front == NULL)
			head->rear = NULL;
		free(tmp);
		printf("- DEQUEUE(%d)\n", data);
	}
}



int isQEmpty(Stack* s) {
	Queue* head = s->top->head;
	if (head->front == NULL && head->rear == NULL) {
		return 1;
	}
	else return 0;
}

int isQFull(Stack* s) {
	if (qIdx >= s->top->size) {
		return 1;
	}
	else return 0;
}


int isStackEmpty(Stack* s) {
	if (sIdx == 0) {
		return 1;
	}
	else return 0;
}


int isStackFull() {
	if (sIdx >= sSize) {
		return 1;
	}
	else return 0;
}



void push(Stack *s, int d) {
	if (isStackFull()) {
		printf("- STACK PUSH(OVERFLOW ERROR)\n");
	}
	else {
		stackNode* tmp = (stackNode*)malloc(sizeof(stackNode));
		tmp->head = (Queue*)malloc(sizeof(Queue));
		tmp->head->front = NULL;
		tmp->head->rear = NULL;
		tmp->link = s->top;
		tmp->size = d;
		s->top = tmp;
		sIdx++;
		qIdx = 0;
		printf("- STACK PUSH(%d, QUEUE SIZE=%d CREATED)\n", d, d);
	}
}


int pop(Stack*s) {
	int sData, qData;
	if (isStackEmpty(s)) {
		printf("- STACK POP(UNDERFLOW ERROR)\n");
	}
	else {
		stackNode* tmp = s->top;
		// 삭제 값 반환 위한 작업 필요
		sData = tmp->size;
		if (s->top->head->front == NULL)
			printf("- STACK POP(ST%d -)\n", sData);
		else {
			printf("- STACK POP(ST%d -", sData);
			QNode* p;
			for (p = s->top->head->front; p != NULL; p = p->next) {
				printf(" Q(%d)", p->data);
			}		
			printf(")\n");
		}
		
		s->top = s->top->link;
		free(tmp);
		sIdx--;
	}
}


Stack createStack(char* sArr[]) {
	for (int i = 0; i < 1; i++) {
		if (sArr[i] != NULL) {
			if (sArr[i][0] == 'C' && sArr[i][1] == 'S') {
				Stack s;
				s.top = NULL;
				sSize = (int)sArr[i][2] - 48;
				printf("- STACK CREATED (SIZE=%d)\n", sSize);
				return s;
			}
			else {
				printf("INPUT ERROR. Create stack first. PLEASE.\n");
				return;
			}
		}
	}
}

void handle(Stack s, char* sArr[]) {
	for (int i = 1; i < 25; i++) {
		if (sArr[i] != NULL) {
			if (sArr[i][0] == 'P' && sArr[i][1] == 'U') {
				push(&s, (int)sArr[i][2] - 48);
			}
			else if (sArr[i][0] == 'E' && sArr[i][1] == 'Q') {
				enQ(&s, (int)sArr[i][2] - 48);
			}
			else if (sArr[i][0] == 'D' && sArr[i][1] == 'Q') {
				deQ(&s);
			}
			else if (sArr[i][0] == 'P' && sArr[i][1] == 'O') {
				pop(&s);
			}
			else {
				printf("input error\n");
				return 0;
			}
		}
	}
}

int main() {
	printf(">./stack_queue\n");
	printf("? ");

	char str[100];
	char* sArr[25] = { NULL, };
	int i = 0;
	gets(str);
	char* p = strtok(str, " ");
	while (p != NULL) {
		sArr[i] = p;
		i++;
		p = strtok(NULL, " ");
	}

	printf("\n\nBEGIN\n");
	Stack st = createStack(sArr);
	handle(st, sArr);
	printf("END\n");

	return 0;
}
