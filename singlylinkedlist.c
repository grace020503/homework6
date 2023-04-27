/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �꾩슂�� �ㅻ뜑�뚯씪 異붽� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �⑥닔 由ъ뒪�� */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

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
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode媛� NULL�� �꾨땲硫�, freeNode瑜� �몄텧�섏뿬 �좊떦�� 硫붾え由� 紐⑤몢 �댁젣 */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� 硫붾え由щ� �좊떦�섏뿬 由ы꽩 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� �곌껐�� listNode 硫붾え由� �댁젣
	 * headNode�� �댁젣�섏뼱�� ��.
	 */
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


/* 由ъ뒪�몃� 寃��됲븯��, �낅젰諛쏆� key蹂대떎 �곌컪�� �섏삤�� �몃뱶 諛붾줈 �욎뿉 �쎌엯 */
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

	/* key瑜� 湲곗��쇰줈 �쎌엯�� �꾩튂瑜� 李얜뒗�� */
	while(n != NULL) {
		if(n->key >= key) {
			/* 泥� �몃뱶 �욎そ�� �쎌엯�댁빞�� 寃쎌슦 �몄� 寃��� */
			if(n == h->first) {
				h->first = node;
				node->link = n;
			} else { /* 以묎컙�닿굅�� 留덉�留됱씤 寃쎌슦 */
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 留덉�留� �몃뱶源뚯� 李얠� 紐삵븳 寃쎌슦 , 留덉�留됱뿉 �쎌엯 */
	trail->link = node;
	return 0;
}

/**
 * list�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
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

/**
 * list 泥섏쓬�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}

/**
 * list�먯꽌 key�� ���� �몃뱶 ��젣
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key瑜� 湲곗��쇰줈 �쎌엯�� �꾩튂瑜� 李얜뒗�� */
	while(n != NULL) {
		if(n->key == key) {
			/* 泥� �몃뱶 �욎そ�� �쎌엯�댁빞�� 寃쎌슦 �몄� 寃��� */
			if(n == h->first) {
				h->first = n->link;
			} else { /* 以묎컙�� 寃쎌슦嫄곕굹 留덉�留됱씤 寃쎌슦 */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 李얠� 紐� �쒓꼍�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list�� 留덉�留� �몃뱶 ��젣
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* �몃뱶媛� �섎굹留� �덈뒗 寃쎌슦, 利� first node == last node��  寃쎌슦 泥섎━ */
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 留덉�留� �몃뱶源뚯� �대룞 */
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	/* n�� ��젣�섎�濡�, �댁쟾 �몃뱶�� 留곹겕 NULL 泥섎━ */
	trail->link = NULL;
	free(n);

	return 0;
}
/**
 * list�� 泥ル쾲吏� �몃뱶 ��젣
 */
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


/**
 * 由ъ뒪�몄쓽 留곹겕瑜� ��닚�쇰줈 �� 諛곗튂
 */
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

