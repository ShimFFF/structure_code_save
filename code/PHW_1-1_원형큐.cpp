#include <stdio.h>

#define DEBUG

int queue[5] = { 0 };
int first = -1;
int rear = -1;
int size = 0; //큐에 있는 변수 개수

void enqueue(int);
int queue_full();
int queue_empty();
void dequeue();

#define DEBUG


int main() {
	enqueue(10);
	enqueue(50);
	enqueue(20);
	enqueue(70);
	dequeue();
	enqueue(100);
	enqueue(40);
	enqueue(140);
	dequeue();
	dequeue();
	dequeue();

	return 0;
}
void enqueue(int val) {
	if (!queue_full()) {
		if (first == -1) {
			first = 0;
			queue[first] = val;
			rear = 0;
			size = 1;
#ifdef DEBUG
			printf("enqueue : %d\n", val);
			printf("rear:%d   first:%d  size:%d\n\n", rear + 1, first + 1, size);
#endif // DEBUG

		}
		else {
			rear = (rear + 1) % 5;
			queue[rear] = val;
			size = size + 1;
#ifdef DEBUG
			printf("enqueue : %d\n", val);
			printf("rear:%d   first:%d  size:%d\n\n", rear + 1, first + 1, size);
#endif // DEBUG
		}
	}
}
int queue_full() {
	if (size == 5) {
#ifdef DEBUG
		printf("this queue is full\n\n");
#endif // DEBUG

		return 1; //큐가 다 찼으면 1리턴
	}
	else {
		return 0;
	}
}
int queue_empty() {
	if (size == 0) {
#ifdef DEBUG
		printf("this queue is empty\n\n");
#endif // DEBUG

		first = -1;
		rear = -1;
		return 1;
	}
	else {
		return 0;
	}
}
void dequeue() {

	if (!queue_empty()) {

#ifdef DEBUG
		printf("dequeue : %d\n", queue[first]);
#endif // DEBUG
		first = (first + 1) % 5;
		size = size - 1;
#ifdef DEBUG
		printf("rear:%d   first:%d   size:%d\n\n", rear + 1, first + 1, size);
#endif // DEBUG

	}

}
