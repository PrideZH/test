#include "list.h"
#include "main.h"
#include "map.h"

PNODE list_create()
{
	PNODE head = (PNODE)malloc(sizeof(NODE));
	head->next = NULL;
	return head;
}

int list_empty(PNODE head)
{
	return head->next == NULL;
}

PNODE list_add(PNODE head, int x, int y)
{
	PNODE p = head;
	for(; p->next != NULL; p = p->next); // »ñµÃÁ´±íÎ²
	PNODE node = (PNODE)malloc(sizeof(NODE));
	node->x = x;
	node->y = y;
	node->next = NULL;
	p->next = node;
	return node;
}

void list_delete(PNODE head, int x, int y)
{
	PNODE p = head->next;
	PNODE front = head;
	for(; p != NULL; front = p, p = p->next)
	{
		if(p->x == x && p->y == y)
		{
			front->next = p->next;
			free(p);
			return;
		}
	}
}
