#ifndef _LIST_H
#define _LIST_H

typedef struct Node NODE, *PNODE;
struct Node
{
	int x, y; // 节点坐标
	PNODE next;
};

PNODE list_create(); // 创建链表
int list_empty(PNODE head); // 是否为空表
PNODE list_add(PNODE head, int x, int y); // 尾插
void list_delete(PNODE head, int x, int y); // 删除

#endif