//stack study

#include <stdio.h>
#include<stdlib.h>
struct NODE {
	int val;
	struct NODE* next;
	struct NODE* prve;
};
//헤드
struct NODE head{-1,NULL, NULL};

int Astack_full(int, int);
void Apush(int[], int, int*);
int Astack_empty(int);
void Apop(int[], int*);
void Lpush(int, struct NODE**);
void Lpop(struct NODE**);
void free();
int main() {
	//Array stack
	printf("The stack that use array\n");
	int stack[5] = { 0 }; //stack save 
	int top = -1;
	int input[7] = { 10,20,30,35,40,48,57 };
	int size = sizeof(stack) / sizeof(int);//stack size
	for (int i = 0; i < 7; i++) {
		if (Astack_full(size, top)) { 
			printf("This stack is full, failed to push %d\n", input[i]); }
		else {
			Apush(stack, input[i], &top);
		}
	}
	for (int i = 0; i < 6; i++) {
		if (Astack_empty(top)) {
			printf("This stack is empty\n");
		}
		else {
			printf("pop : %d\n", stack[top]);
			Apop(stack, &top);
		}
	}

	//linked list stack
	printf("\n\nThe stack that use linked list\n");
	struct NODE* Ltop=NULL;
	for (int i = 0; i < 7; i++) {
		Lpush(input[i],&Ltop);
	}
	for (int i = 0; i < 8; i++) {
		Lpop(&Ltop);
	}
	free();

	return 0;
}
int Astack_full(int size, int top) {
	if ((size-1) == top) {
		return 1; //when stack full return 1 
	}
	else { return 0; }
}
void Apush(int stack[], int value, int* top) {
	*top = *top + 1;
	stack[*top] = value;
	printf("push : %d\n", value);
}
int Astack_empty(int top) {
	if (top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}
void Apop(int stack[], int *top) {
	stack[*top] = -1; //delete
	*top = *top - 1;
}
//걍 투포인터 쓰지 말고
//원래 linked list 하는 것 처럼 ㄱ
void Lpush(int val,struct NODE ** top) {
	struct NODE* newnode = (struct NODE*)malloc(sizeof(struct NODE));
	if (*top == NULL) {
		head.next = newnode;
		newnode->prve = &head;
		newnode->val = val;
		newnode->next = NULL;
		*top = newnode;
		printf("first push : %d\n", val);
	}
	else {
		struct NODE* ptr;
		ptr = *top;
		newnode->prve = ptr; 
		newnode->prve->next = newnode;
		newnode->val = val;
		newnode->next = NULL;
		*top = newnode;
		printf("push : %d\n", val);
	}
}
void Lpop(struct NODE** top) {
	struct NODE* prveTop;
	if (*top == &head) {
		printf("The stack is empty\n");
	}
	else {
		prveTop = *top;
		*top = prveTop->prve;
		printf("pop : %d\n", prveTop->val);
		free(prveTop);

	}
}
void free() {
	struct NODE* ptr1, *ptr2;
	ptr1 = head.next;
	while (ptr1) {
		ptr2 = ptr1->next;
		free(ptr1);
		ptr1 = ptr2;
		
	}
	printf("free complete\n");
}