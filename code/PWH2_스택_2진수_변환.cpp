//10������ �Է¹ް�
//stack�� �̿��� 2������ ��ȯ
//2���� ���


#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
	int val;
	struct NODE* next;
	struct NODE* prev;
}NODE;

int push(int, NODE*);
int push(NODE*);
int stack_empty(NODE*);
void convBin(int dec, NODE*);
void printBin(NODE *);


int main() {
	int key = 1;
	while (True) {
		printf("���α׷� �����Ϸ��� 1�� �������� : ");
		scanf_s("%d", &key);
		if (key != 1) break;

		int val;
		printf("Enter the decimal numder : ");
		scanf_s("%d", &val);
		NODE head = { -1, NULL, NULL };
		convBin(val, &head);
		printBin(&head);
	}


}

//push�ϰ� push�� val ����
int push(int val, NODE * head) {
	NODE * ptr = head->next;
	NODE* prev = head;
	while (ptr) {
		prev = ptr;
		ptr = ptr->next;
	}//push�� ��ġ ã��
	NODE* newnode = (NODE*)malloc(sizeof(NODE*)); //���ο� ��� ����
	prev->next = newnode;//linking
	newnode->prev = prev;
	newnode->val = val; //vlaue �Ҵ�
	newnode->next = NULL; //�ʱ�ȭ

	return newnode->val; //push�� value ����
}

//pop�ϰ� pop�� val����
//��������� -1 ����
int pop(NODE* head) {
	if (stack_empty(head)) {
		return -1; //�������
	}
	else {
		NODE* ptr = head->next;
		NODE* prev = head;
		int a = -1;
		while (ptr) {
			prev = ptr;
			ptr = ptr->next;
		}
		prev->prev->next = NULL; //�ڿ� ���� linking ������
		a = prev->val;
		free(prev);
		return a; //pop�� value ����
	}

}

//��������� 1����, �ƴϸ� 0
int stack_empty(NODE * head) {
	if (head->next) {
		return 0; //�����������
	}
	else {
		return 1; //�������
	}
}

//10������ 2������ ���ÿ� ����
void convBin(int dec, NODE * head) {
	while (true) {
		push(dec % 2, head); //���ÿ� ����
		if (dec / 2 == 0) {
			break; //������ push �ϰ� Ż��
		}
		dec = dec / 2;
	}

}

//���ÿ� ����� 2������ ����Ʈ
void printBin(NODE* head) {
	NODE * ptr = head->next;
	NODE* prev = head;
	while (ptr) { //���� �� ��带 ã����
		prev = ptr;
		ptr = ptr->next;
	}
	while (true) { //��带 prev�� ����ų ������ ����Ʈ
		ptr = prev;
		prev = prev->prev;
		if (!prev) break;
		printf("%d", ptr->val);
	}
}