#include <stdio.h>
#include <stdlib.h>
#define SIZE 5 // 임시 설정 나중에 빼야됨.

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



int enQ(Stack* s, int item) {
	if (isQFull(s)) {
		printf("\nOVERFLOW\n");
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
	}
	
}

void deQ(Stack* s) {
	QNode* tmp;
	Queue* head = s->top->head;
	int data;
	if (isQEmpty(s)) {
		printf("\nUNDERFLOW\n");
	}
	else {
		tmp = head->front;
		data = tmp->data;
		head->front = tmp->next;

		if (head->front == NULL)
			head->rear = NULL;
		free(tmp);
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
	if (s->top == NULL) {
		return 1;
	}
	else return 0;
}


int isStackFull() {
	if (sIdx >= SIZE) {
		return 1;
	}
	else return 0;
}



void push(Stack *s, int d) {
	if (isStackFull()) {
		printf("\nOVERFLOW ERROR\n");
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
	}
}


int pop(Stack*s) {
	if (isStackEmpty(s)) {
		printf("\nUNDERFLOW ERROR\n");
	}
	else {
		stackNode* tmp = s->top;
		// 삭제 값 반환 위한 작업 필요

		s->top = s->top->link;
		free(tmp);
		sIdx--;
	}
}


int main() {
	Stack s;
	s.top = NULL;
	push(&s, 4);
	enQ(&s, 3);
	enQ(&s, 6);
	push(&s, 2);
	enQ(&s, 1);
	deQ(&s);
	deQ(&s);


}
