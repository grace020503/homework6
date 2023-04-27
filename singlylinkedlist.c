#include<stdio.h>
#include<stdlib.h>

int name(){
	char *name = "Kim sieun";
	char *id = "2021053007";
	printf("----- [%s] [%s] -----\n", name, id);}

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

headNode* initialize(headNode* h); // 연결리스트 초기화
int freeList(headNode* h); // 연결리스트 해제

int insertFirst(headNode* h, int key); // 앞에서 노드 삽임
int insertNode(headNode* h, int key); // 오름차순 노드 삽입
int insertLast(headNode* h, int key); // 뒤에서 노드 삽입

int deleteFirst(headNode* h); // 앞에서 노드 삭제
int deleteNode(headNode* h, int key); // 선택 노드 삭제
int deleteLast(headNode* h); // 뒤애서 노드 삭제
int invertList(headNode* h); // 연결리스트 앞뒤 교체

void printList(headNode* h); // 연결리스트 출력

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode); // 리스트 초기화
			break;
		case 'p': case 'P':
			printList(headnode); // 연결리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); // 오름차순 노드 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); // 선택 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); // 뒤에서 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode); // 뒤에서 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); // 앞에서 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode); // 앞에서 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); // 연결리스트 앞뒤 교차
			break;
		case 'q': case 'Q':
			freeList(headnode); // 리스트 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

// 연결리스트의 첫번쩨 노드를 가르키는 포인터
headNode* initialize(headNode* h) {

	if(h != NULL)
		freeList(h); // headnode를 초기화하고, 빈 연결 리스트 생성

	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

// 동적 할당 메모리 해제
int freeList(headNode* h){
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

// 연결리스트에서 key값 위치에 노드 삽입
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	while(n != NULL) {
		if(n->key >= key) {
			if(n == h->first) {
				h->first = node;
				node->link = n;
			} else {
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}

	trail->link = node;
	return 0;
}

// 연결리스트의 마지막 노드 삽입
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {
		n = n->link;
	}
	n->link = node;
	return 0;
}

// 연결리스트의 첫번째 노드 삽입
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}

// key값의 노드 삭제
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) {
				h->first = n->link;
			} else {
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	printf("cannot find the node for key = %d\n", key);
	return 0;

}

// 연결리스트의 마지막 노드 삭제
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	trail->link = NULL;
	free(n);

	return 0;
}

// 연결리스트의 첫번째 노드 삭제
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;
	free(n);

	return 0;
}

// 연결리스트를 역순으로 뒤집음
int invertList(headNode* h) {


	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}

// 연결리스트 출력
void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}