//10진수를 입력받고
//stack를 이용해 2진수로 변환
//2진수 출력


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
		printf("프로그램 시작하려면 1을 누르세요 : ");
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

//push하고 push한 val 리턴
int push(int val, NODE * head) {
	NODE * ptr = head->next;
	NODE* prev = head;
	while (ptr) {
		prev = ptr;
		ptr = ptr->next;
	}//push할 위치 찾기
	NODE* newnode = (NODE*)malloc(sizeof(NODE*)); //새로운 노드 생성
	prev->next = newnode;//linking
	newnode->prev = prev;
	newnode->val = val; //vlaue 할당
	newnode->next = NULL; //초기화

	return newnode->val; //push한 value 리턴
}

//pop하고 pop한 val리턴
//비어있으면 -1 리턴
int pop(NODE* head) {
	if (stack_empty(head)) {
		return -1; //비어있음
	}
	else {
		NODE* ptr = head->next;
		NODE* prev = head;
		int a = -1;
		while (ptr) {
			prev = ptr;
			ptr = ptr->next;
		}
		prev->prev->next = NULL; //뒤에 노드와 linking 끊어줌
		a = prev->val;
		free(prev);
		return a; //pop한 value 리턴
	}

}

//비어있으면 1리턴, 아니면 0
int stack_empty(NODE * head) {
	if (head->next) {
		return 0; //비어있지않음
	}
	else {
		return 1; //비어있음
	}
}

//10진수를 2진수로 스택에 저장
void convBin(int dec, NODE * head) {
	while (true) {
		push(dec % 2, head); //스택에 저장
		if (dec / 2 == 0) {
			break; //마지막 push 하고 탈출
		}
		dec = dec / 2;
	}

}

//스택에 저장된 2진수를 프린트
void printBin(NODE* head) {
	NODE * ptr = head->next;
	NODE* prev = head;
	while (ptr) { //제일 끝 노드를 찾아줌
		prev = ptr;
		ptr = ptr->next;
	}
	while (true) { //헤드를 prev가 가리킬 떄까지 프린트
		ptr = prev;
		prev = prev->prev;
		if (!prev) break;
		printf("%d", ptr->val);
	}
}