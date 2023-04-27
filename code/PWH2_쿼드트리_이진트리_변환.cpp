//���� Ʈ��
//���̳ʸ� Ʈ�� ��ȯ
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

typedef struct Node {
	int val;
	int level;
	struct Node* left;
	struct Node* right[3];
}Node;

typedef struct Save {
	int val;

	struct Node* location;

	struct Save* next;
}Save;

// ���� Ʈ�� ��� ����ü ����
typedef struct BNode {
	int val;
	struct BNode* left, * right;
}BNode;

int compare_node(Node*, Node*);
Node* create_node(int, int, Save[]);
Save* create_save(int, Save*, Node*);
void link_leftC(Node*, Node*);
Node* link_rightC(Node*, Node*);
Node* search_node(int, Save*);
Node* create_tree(int, int, int, int, Save[]);

BNode* create_Bnode(int);
void convert_Btree(Node*, BNode*);
void preorder(BNode*);



int main() {
	Save save[5] = { -1,NULL,NULL };
	printf("TREE 1\n");

	//val, level, parent val, child val ����
	Node* root1 = create_tree(100, 1, -1, 200, save);
	create_tree(200, 2, 100, -1, save);
	create_tree(75, 2, 100, 25, save);
	create_tree(300, 2, 100, -1, save);
	create_tree(25, 3, 75, -1, save);
	create_tree(50, 3, 75, -1, save);
	create_tree(30, 3, 75, 120, save);
	create_tree(150, 3, 75, -1, save);
	create_tree(120, 4, 30, -1, save);
	create_tree(55, 4, 30, -1, save);

	BNode* roott1 = create_Bnode(root1->val);

	convert_Btree(root1, roott1);
	printf("����Ʈ�� ��ȯ �Ϸ�\n\n");

	printf("preorder : ");
	preorder(roott1);

	printf("\n\n-------------------------------\n\n\n");
	printf("TREE 2\n");
	save[0] = { -1,NULL,NULL };
	save[1] = { -1,NULL,NULL };
	save[2] = { -1,NULL,NULL };
	save[3] = { -1,NULL,NULL };
	save[4] = { -1,NULL,NULL };

	Node* root2 = create_tree(100, 1, -1, 200, save);
	create_tree(200, 2, 100, -1, save);
	create_tree(75, 2, 100, 25, save);
	create_tree(300, 2, 100, -1, save);
	create_tree(95, 2, 100, 150, save);
	create_tree(25, 3, 75, -1, save);
	create_tree(50, 3, 75, -1, save);
	create_tree(30, 3, 75, 120, save);
	create_tree(150, 3, 95, -1, save);
	create_tree(120, 4, 30, -1, save);

	BNode* roott2 = create_Bnode(root2->val);
	
	convert_Btree(root2, roott2);
	printf("����Ʈ�� ��ȯ �Ϸ�\n\n");

	printf("preorder : ");
	preorder(roott2);

	return 0;
}

//node1�� node2�� val�� ��
//���ٸ� 0, �ٸ��� 1 ����
int compare_node(Node* node1, Node* node2) {

	//defensive
	if (node1 == NULL || node2 == NULL) {
		printf("ERROR : exist empty node");
		exit(1);
	}
	else {
		if (node1->val == node2->val) return 0;
		else return 1;
	}
}

//��� ����, ���� �ּ� ����
Node* create_node(int val, int level, Save save[5]) {
	Node* newnode = (Node*)malloc(sizeof(Node));

	//defensive
	if (newnode == NULL) {
		printf("ERROR : Failed create node\n\n");
		exit(1);
	}
	else {
		newnode->val = val;
		newnode->level = level;
		newnode->left = NULL;
		newnode->right[0] = NULL;
		newnode->right[1] = NULL;
		newnode->right[2] = NULL;

		create_save(val, &save[level - 1], newnode);

		return newnode;
	}
}

//save ����
Save* create_save(int val, Save* save, Node* node) {

	Save* newsave = (Save*)malloc(sizeof(Save));

	//defensive
	if (newsave == NULL) {
		printf("ERROR : Failed create save\n\n");
		exit(1);
	}
	else {
		Save* prev = save;
		Save* ptr = save->next;
		while (ptr) {
			prev = ptr;
			ptr = ptr->next;
		}
		prev->next = newsave;
		newsave->val = val;
		newsave->next = NULL;
		newsave->location = node;


	}

}

//node1�� �θ�, node2�� �ڽ�
//node2�� node1�� left child�� ����
// 
//��� �Է� ���� �� �ڽ� ������ ���� �� ��
void link_leftC(Node* node1, Node* node2) {

	//defensive
	if (node1 == NULL || node2 == NULL) {
		printf("ERROR : exist empty node");
		exit(1);
	}
	else {
		node1->left = node2; //��ŷ
	}
}

//node1�� �θ�, node2�� �ڽ�
//node2�� node1�� left child�� ����
//node2�� �̹� left �ڽ��̶��, ����
// 
//��� �Է� ���� �� �θ� ������ ������ ��
Node* link_rightC(Node* node1, Node* node2) {

	//defensive
	if (node1 == NULL || node2 == NULL) {
		printf("ERROR : exist empty node");
		exit(1);
	}
	else {
		//left child�� �ƴ� ��
		if (compare_node(node1->left, node2)) {
			for (int i = 0; i < 3; i++) {
				if (node1->right[i] == NULL) {
					node1->right[i] = node2;

					return node1->right[i];
				}
			}
		}
		else return node1->left;
	}
}

//� save[level-1] ���·� �Է� �ް� 
//�ش��ϴ� val�� ���� treenode�� �ּҸ� ����
Node* search_node(int val, Save* save) {

	Save* ptr = save->next;
	while (ptr) {
		if (ptr->val == val) {
			return ptr->location;
		}
		ptr = ptr->next;
	}

	return NULL;
}

//Ʈ�� ����
//�θ�, �ڽ��� ���ٸ� -1�Է�
Node* create_tree(int val, int level, int parent_val, int child_val, Save save[5]) {
	if (level == 1) {
		Node* newnode = create_node(val, level, save);
		if (child_val != -1) {
			Node* child = create_node(child_val, level + 1, save); //�ڽ� ��� ����
			link_leftC(newnode, child); //����
		}
#ifdef DEBUG
		printf("%d level %d node ����\n\n", newnode->level, newnode->val);
#endif // DEBUG
		return newnode;
	}
	else {
		Node* newnode = create_node(val, level, save);
		Node* parent = search_node(parent_val, &save[level - 2]); //�θ� ��� �ּ� ã����

		Node* t = link_rightC(parent, newnode);
#ifdef DEBUG
		printf("%d level %d node ����\n\n", t->level, t->val);
#endif // DEBUG


		if (child_val != -1) {
			Node* child = create_node(child_val, level + 1, save); //�ڽ� ��� ����
			link_leftC(newnode, child); //����
		}

		return newnode;

	}

}

//����Ʈ�� ��� ����
BNode* create_Bnode(int val) {
	BNode* newnode = (BNode*)malloc(sizeof(BNode));

	if (newnode == NULL) {
		printf("ERROR : Failed create node\n\n");
		exit(1);
	}
	else {
		newnode->left = NULL;
		newnode->right = NULL;
		newnode->val = val;
		return newnode;
	}

}

// ����Ʈ������ ����Ʈ���� ��ȯ�ϴ� �Լ�
//����Ʈ���� ��Ʈ�� ���� 
void convert_Btree(Node* Qnode, BNode* Bnode) {

	if (Qnode->left) {
		Bnode->left = create_Bnode(Qnode->left->val);
		BNode* prev = Bnode->left;

		//��忡 �ڽ��� �ִٸ� ���
		if (Qnode->left->left) convert_Btree(Qnode->left, prev);

		for (int i = 0; i < 3; i++) {
			if (Qnode->right[i] == NULL) break;
			prev->right = create_Bnode(Qnode->right[i]->val);
			prev = prev->right;

			if (Qnode->right[i]->left) convert_Btree(Qnode->right[i], prev);

		}

	}


}


void preorder(BNode* node) {
	if (node == NULL) return;

	printf("%d  ", node->val);
	preorder(node->left);
	preorder(node->right);
}