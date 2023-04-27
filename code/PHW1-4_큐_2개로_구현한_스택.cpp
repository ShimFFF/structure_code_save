//linked list ť�� ���� ����

#include<stdio.h>
#include <stdlib.h>

#define DEBUG

typedef struct NODE {
	int val;
	struct NODE* next;
}NODE;

int enqueue(NODE*, int);
int dequeue(NODE*);
int queue_empty(NODE*);
void all_free(NODE*);
void Qpop(NODE*, NODE*);
void Qpush(NODE*, int);

int main() {
	NODE head_Q1 = { -1,NULL };
	NODE head_Q2 = { -1,NULL };
	int val[4] = { 2,3,4,5 };

	for (int i = 0; i < 4; i++) {
		Qpush(&head_Q1, val[i]);
		printf("\n\n------------------------\n\n");
	}


	for (int i = 0; i < 5; i++) {
		Qpop(&head_Q1, &head_Q2);
		printf("\n\n------------------------\n\n");
	}


	all_free(&head_Q1);
	all_free(&head_Q2);
}

/*enqueue�� ������ ��,
���ϰ����� enqueue�� value�� ����*/
int enqueue(NODE* head, int val) {

	NODE* ptr = head->next;
	NODE* prev = head;
	while (ptr) {
		prev = ptr;
		ptr = ptr->next;
	}
	//new node ����
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	prev->next = newnode;
	newnode->next = ptr;
	newnode->val = val;

#ifdef DEBUG
	printf("enqueue : %d\n", newnode->val);
#endif // DEBUG
	return val;
}

/*dequeue�� ������ ��,
���ϰ����� dequeue�� value�� ����*/
int dequeue(NODE* head) {
	int Rval = -1;

	NODE* ptr = head->next;
	NODE* next = NULL; //dequeue �ϴ� ����� ���� ��� �ּҸ� ����
	if (!queue_empty(head)) {
		next = ptr->next;
		Rval = ptr->val; //���� �� ����
#ifdef DEBUG
		printf("dequeue : %d\n", ptr->val);
#endif // DEBUG
		free(ptr);
		head->next = next;
		return Rval;
	}
	else {
#ifdef DEBUG
		printf("this queue is empty\n");
#endif // DEBUG
		return -1;

	}

}

int queue_empty(NODE* head) {
	if (head->next == NULL) {
		return 1; //empty�� �� 1 ����
	}
	else {
		return 0;
	}
}

void all_free(NODE* head) {
	NODE* ptr1, * ptr2;
	ptr1 = head->next;
	while (ptr1) {
		//���� ������ free�� �ּ� ŵ
		ptr2 = ptr1->next;
		free(ptr1);
		ptr1 = ptr2;
	}

}

//�ΰ��� Q�� Ȱ���� pop
void Qpop(NODE* head1, NODE* head2) {

	if (queue_empty(head1)) {
#ifdef DEBUG
		printf("\n\nTHIS STACK IS EMPTY\n\n\n");
#endif // DEBUG

	}
	else {
		while (head1->next->next) { //�ϳ��� ��常 �����, 2�� ť�� ��� �ű�
			enqueue(head2, dequeue(head1));
		}
#ifdef DEBUG
		printf("\n\nPOP : %d\n\n\n", head1->next->val);
#endif // DEBUG
		dequeue(head1); //���������� �����ִ� ��� ����
#ifdef DEBUG
		printf("\n\n");
#endif // DEBUG


		while (head2->next) {
			enqueue(head1, dequeue(head2));
		}
	}


}

void Qpush(NODE* head, int val) {
	enqueue(head, val);
#ifdef DEBUG
	printf("\n\nPUSH : %d\n\n\n", val);
#endif // DEBUG

}


