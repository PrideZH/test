#ifndef _LIST_H
#define _LIST_H

typedef struct Node NODE, *PNODE;
struct Node
{
	int x, y; // �ڵ�����
	PNODE next;
};

PNODE list_create(); // ��������
int list_empty(PNODE head); // �Ƿ�Ϊ�ձ�
PNODE list_add(PNODE head, int x, int y); // β��
void list_delete(PNODE head, int x, int y); // ɾ��

#endif