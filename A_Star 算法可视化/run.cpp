#include "run.h"
#include "map.h"
#include "list.h"
#include "visual.h"
#include "main.h"

int direction[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
int fgh[PY][PX][3];
int father[PY][PX][2];

PNODE open_list; // �洢��������
PNODE close_list; // �洢��ʹ�õ�

void run(int x, int y, int e_x, int e_y)
{
	// �ж��Ƿ񵽴��յ�
	int win = 0;

	// ��ʼ��open_list 
	open_list = list_create();
	// ��ʼ��close_list 
	close_list = list_create();
	// �����㵽open
	list_add(open_list, x, y);
	map[y][x] = 2; // ��Ǹýڵ�Ϊ��������
	// ����fghֵ
	fgh[y][x][1] = 0;
	fgh[y][x][2] = (abs(e_y - y) + abs(e_x - x)) * 10;
	fgh[y][x][0] = fgh[y][x][1] + fgh[y][x][2];
	// �������ĸ��ڵ�Ϊ�Լ�
	father[y][x][0] = y;
	father[y][x][1] = x;
	// ����յ�
	map[e_y][e_x] = 4;

	while(1)
	{
		// open_listΪ����Ѱ·ʧ��
		if(list_empty(open_list))
		{
			break;
		}
		// ����open_list ������СFֵ�ڵ�
		int f_min = 999;
		PNODE p = open_list->next;
		PNODE node = p; // ��СFֵ�ڵ�
		for(; p != NULL; p = p->next)
		{
			if(fgh[p->y][p->x][0] < f_min)
			{
				f_min = fgh[p->y][p->x][0];
				node = p;
			}
		}
		// ���ýڵ���ӵ�close_list
		node = list_add(close_list, node->x, node->y);
		map[node->y][node->x] = 3; // ���Ϊ��������
		// ���ýڵ��open_list�Ƴ�
		list_delete(open_list, node->x, node->y);

		// �����ýڵ��8������ ������СFֵ
		for(int i = 0; i < 8; i++)
		{	
			// ��ô������ڵ������
			int next_y_tem = node->y + direction[i][0];
			int next_x_tem = node->x + direction[i][1];
			// ������Ϊ���ɵ�������close_list��ʱ����
			if(1 == map[next_y_tem][next_x_tem] // ǽ
				|| 3 == map[next_y_tem][next_x_tem] // ������
				|| next_y_tem < 0 || next_y_tem >= PY || next_x_tem < 0 || next_x_tem > PX) //Խ��
			{
				fgh[node->y][node->x][0]  = 999;
				continue;
			}
			// ������Ϊ�յ�����
			if(4 == map[next_y_tem][next_x_tem]){
				// ���ø��ڵ�
				father[next_y_tem][next_x_tem][0] = node->y;
				father[next_y_tem][next_x_tem][1] = node->x;
				draw_map();
				// ����·��
				draw_path(e_x, e_y);
				win = 1;
			}
			//  ����fgh
			int g = fgh[node->y][node->x][1] + (i < 4 ? 10 : 14);
			int h = (abs(e_y - next_y_tem) + abs(e_x - next_x_tem)) * 10;
			int f = g + h;
			
			// �Ѿ���open_list��ʱ �Ƚ�Gֵ 
			if(2 == map[next_y_tem][next_x_tem])
			{
				if(fgh[next_y_tem][next_x_tem][1] > g)
				{
					// G��С ���õ�ǰ�ڵ�Ϊ���ĸ��ڵ�
					father[next_y_tem][next_x_tem][0] = node->y;
					father[next_y_tem][next_x_tem][1] = node->x;
				}
				else
				{
					continue;
				}
			}
			else if(0 == map[next_y_tem][next_x_tem])
			{
				father[next_y_tem][next_x_tem][0] = node->y;
				father[next_y_tem][next_x_tem][1] = node->x;
				//  ����������ӵ�open_list
				list_add(open_list, next_x_tem, next_y_tem);
				map[next_y_tem][next_x_tem] = 2;
			}
			// ���¸�������fghֵ
			fgh[next_y_tem][next_x_tem][0] = f;
			fgh[next_y_tem][next_x_tem][1] = g;
			fgh[next_y_tem][next_x_tem][2] = h;
		}
		// �ж��Ƿ񵽴��յ�
		if(1 == win)
		{
			break;
		}
		// ���Ƶ�ͼ
		draw_map();
	}
}