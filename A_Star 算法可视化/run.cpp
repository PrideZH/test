#include "run.h"
#include "map.h"
#include "list.h"
#include "visual.h"
#include "main.h"

int direction[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
int fgh[PY][PX][3];
int father[PY][PX][2];

PNODE open_list; // 存储待搜索点
PNODE close_list; // 存储已使用点

void run(int x, int y, int e_x, int e_y)
{
	// 判断是否到达终点
	int win = 0;

	// 初始化open_list 
	open_list = list_create();
	// 初始化close_list 
	close_list = list_create();
	// 添加起点到open
	list_add(open_list, x, y);
	map[y][x] = 2; // 标记该节点为待搜索点
	// 计算fgh值
	fgh[y][x][1] = 0;
	fgh[y][x][2] = (abs(e_y - y) + abs(e_x - x)) * 10;
	fgh[y][x][0] = fgh[y][x][1] + fgh[y][x][2];
	// 设置起点的父节点为自己
	father[y][x][0] = y;
	father[y][x][1] = x;
	// 添加终点
	map[e_y][e_x] = 4;

	while(1)
	{
		// open_list为空则寻路失败
		if(list_empty(open_list))
		{
			break;
		}
		// 遍历open_list 查找最小F值节点
		int f_min = 999;
		PNODE p = open_list->next;
		PNODE node = p; // 最小F值节点
		for(; p != NULL; p = p->next)
		{
			if(fgh[p->y][p->x][0] < f_min)
			{
				f_min = fgh[p->y][p->x][0];
				node = p;
			}
		}
		// 将该节点添加到close_list
		node = list_add(close_list, node->x, node->y);
		map[node->y][node->x] = 3; // 标记为已搜索点
		// 将该节点从open_list移除
		list_delete(open_list, node->x, node->y);

		// 遍历该节点的8个方向 查找最小F值
		for(int i = 0; i < 8; i++)
		{	
			// 获得待搜索节点的坐标
			int next_y_tem = node->y + direction[i][0];
			int next_x_tem = node->x + direction[i][1];
			// 搜索点为不可到达点或在close_list中时忽略
			if(1 == map[next_y_tem][next_x_tem] // 墙
				|| 3 == map[next_y_tem][next_x_tem] // 已搜索
				|| next_y_tem < 0 || next_y_tem >= PY || next_x_tem < 0 || next_x_tem > PX) //越界
			{
				fgh[node->y][node->x][0]  = 999;
				continue;
			}
			// 搜索点为终点跳出
			if(4 == map[next_y_tem][next_x_tem]){
				// 设置父节点
				father[next_y_tem][next_x_tem][0] = node->y;
				father[next_y_tem][next_x_tem][1] = node->x;
				draw_map();
				// 绘制路径
				draw_path(e_x, e_y);
				win = 1;
			}
			//  计算fgh
			int g = fgh[node->y][node->x][1] + (i < 4 ? 10 : 14);
			int h = (abs(e_y - next_y_tem) + abs(e_x - next_x_tem)) * 10;
			int f = g + h;
			
			// 已经在open_list中时 比较G值 
			if(2 == map[next_y_tem][next_x_tem])
			{
				if(fgh[next_y_tem][next_x_tem][1] > g)
				{
					// G更小 设置当前节点为他的父节点
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
				//  将搜索点添加到open_list
				list_add(open_list, next_x_tem, next_y_tem);
				map[next_y_tem][next_x_tem] = 2;
			}
			// 更新该搜索点fgh值
			fgh[next_y_tem][next_x_tem][0] = f;
			fgh[next_y_tem][next_x_tem][1] = g;
			fgh[next_y_tem][next_x_tem][2] = h;
		}
		// 判断是否到达终点
		if(1 == win)
		{
			break;
		}
		// 绘制地图
		draw_map();
	}
}