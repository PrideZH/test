#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>

#define PX 16 //最小8
#define PY 16
#define PIC 40
#define U 0
#define D 1
#define L 2
#define R 3

typedef struct Snake SNAKE, *PSNAKE;
struct Snake //蛇节点
{
	int x, y; 
	PSNAKE front, rear;
};
PSNAKE head, tail;

struct Food
{
	int x, y; 
}food = {0, 0};

char map[PY][PX]; //0-Space 1-Snake 2-Food
char path[PY][PX]; //环路地图 规定蛇移动方向
char direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //方向 0-Up 1-Down 2-Left 3-Right
int snake_len = 3;

void init_snake();
void update_map();
void init_window();
void draw_map();
void move_snake();
void collision(); //碰撞分析
void compose_path(int y_0, int x_0, int y_1, int x_1); //组合环路
void gameover();

int main()
{
	init_window(); //初始化窗口
	init_snake(); 
	update_map(); //更新地图
	while(1)
	{	   
		move_snake(); 
		update_map(); //更新地图
		draw_map();
		collision();  //碰撞检测
		update_map(); //更新地图
		Sleep(100);
	}
	return 0;
}

void init_snake()
{
	//init head
	PSNAKE node = (PSNAKE)malloc(sizeof(SNAKE));
	node->y = PY/2;
	node->x = PX/2;
	head = node;
	head->front = NULL;
	tail = node;
	//init body
	for(int i = 0; i < 2; i++)
	{
		PSNAKE node = (PSNAKE)malloc(sizeof(SNAKE));
		node->y = tail->y;
		node->x = tail->x - 1;
		node->front = tail;
		tail->rear = node;
		tail = node;
	}
	tail->rear = NULL;
}

void update_map()
{
	for(int i = 0 ; i < PY; i++) for(int j = 0 ; j < PX; j++) map[i][j] = 0; //Init map 
	//将蛇加载进地图
	PSNAKE p;
	p = head;
	do {
		map[p->y][p->x] = 1;
	}while((p = p->rear) != NULL);
	map[food.y][food.x] = 2;
	//初始化环路地图
	for(int i = 0; i < PY; i++)
	{
		for(int j = 0; j < PX; j++)
		{
			if(i%2)
			{
				if(j%2) path[i][j] = L;
				else path[i][j] = U;
			}
			else
			{
				if(j%2) path[i][j] = D;
				else path[i][j] = R;
			}
		}
	}
	//组合蛇环路（使蛇能绕着尾巴移动）
	p = head;
	do {
		compose_path(p->y/2, p->x/2, p->rear->y/2, p->rear->x/2); //每个蛇节点所在的小环路组成大环路
	}while(((p = p->rear)->rear) != NULL);
	//组成路径环路(用A*算法搜索路径)
	int food_path_y = food.y/2, food_path_x = food.x/2; //食物路径坐标（所在小环路的坐标）
	int snake_path_y = head->y/2, snake_path_x = head->x/2; //蛇头路径坐标
	if(!(food_path_y == snake_path_y && food_path_x == snake_path_x)) //蛇头环路路径不在食物环路路径时，不在组合环路
	{
		int min_f = 999; //初始化代价
		int move = 0; //移动方向
		for(int i = 0; i < 4; i++) //搜索蛇的4个方向
		{
			//获得该方向的下个路径坐标
			int next_path_y = snake_path_y + direction[i][0];
			int next_path_x = snake_path_x + direction[i][1];
			if(next_path_y < 0 || next_path_y > PY / 2 - 1 || next_path_x < 0 || next_path_x > PX / 2 - 1) continue; //是否越界
			if(1 == map[head->y + direction[i][0]][head->x + direction[i][1]]) continue; //下个路径是否有蛇
			int f = abs(food_path_x - next_path_x) + abs(food_path_y - next_path_y); //获得代价 哈曼吨距离 + h (4个方向h相同，忽略)
			if(f < min_f) 
			{
				min_f = f;
				move = i; //获得最小代价的方向
			}
		}
		//如果找不到方向，保持原状，找到方向，组合环路	
		if(min_f != 999) compose_path(snake_path_y, snake_path_x, snake_path_y + direction[move][0], snake_path_x + direction[move][1]); 	
	}
}

void init_window()
{
	srand((unsigned)time(NULL));
	initgraph(PX * PIC, PY *PIC);
}

void draw_map()
{
	BeginBatchDraw();
	for(int i = 0; i < PY; i++)
	{
		for(int j = 0; j < PX; j++)
		{
			switch(map[i][j])
			{
			case 0: //空
				setfillcolor(COLORREF RGB(128,128,128));
				break;
			case 1: //蛇
				setfillcolor(BLUE);
				break;
			case 2: //Food
				setfillcolor(RED);
				break;
			}
			fillrectangle(j * PIC, i * PIC, j * PIC + PIC, i * PIC + PIC);
		}	
	}
	//蛇头
	setfillcolor(GREEN);
	fillrectangle(head->x * PIC, head->y * PIC, head->x * PIC + PIC, head->y * PIC + PIC);
	EndBatchDraw();
}

void move_snake()
{
	//Move snake body
	PSNAKE p;
	p = tail;
	do {
		p->x = p->front->x;
		p->y = p->front->y;
	}while((p = p->front) != head);
	//Move snake head
	int next = path[head->y][head->x];
	head->y += direction[next][0];
	head->x += direction[next][1];
}

void collision() //碰撞分析
{
	//Snake head <-> Food
	if(food.y == head->y && food.x == head->x) 
	{
		//获得新的Food坐标
		int size = PX * PY - snake_len; //和空的个数
		if(!size) //空为0，胜利
		{
			getchar();
			exit(0);
		}
		int point = rand()%size; //取空个数的随机值
		int i; 
		for(i = 0; i < PY * PX; i++) //计算生成Food的位置
		{
			if(map[i / PX][i % PX] == 1 || (i / PX == food.y && i % PX == food.x)) point++; //防止生成在蛇节点或旧食物上
			if(point-- == 0) break; 
		}
		food.y = i / PX;
		food.x = i % PX;
		//增加蛇节点
		PSNAKE node = (PSNAKE)malloc(sizeof(SNAKE));
		node->y = tail->y;
		node->x = tail->x;
		node->front = tail;
		node->rear = NULL;
		tail->rear = node;
		tail = node;
		snake_len++;
	}
	//Snake head <-> Snake body
	PSNAKE p;
	p = head->rear;
	do {
		if(head->y == p->y && head->x == p->x) gameover(); 
	}while((p = p->rear) != NULL);
	//蛇出界
	if(head->x < 0 || head->x > PX - 1 || head->y < 0 || head->y > PY - 1) gameover();  
}

void compose_path(int y_0, int x_0, int y_1, int x_1) //组合环路
{
	if(y_0 == y_1 && x_0 < x_1) //与右组合
	{
		path[y_0 * 2][x_0 * 2 + 1] = R;  
		path[y_1 * 2 + 1][x_1 * 2] = L;   
	}
	else if(y_0 == y_1 && x_0 > x_1) //与左组合
	{
		path[y_0 * 2 + 1][x_0 * 2] = L;
		path[y_1 * 2][x_1 * 2 + 1] = R;
		
	}
	else if(y_0 < y_1 && x_0 == x_1) //与下组合
	{
		path[y_0 * 2 + 1][x_0 * 2 + 1] = D;
		path[y_1 * 2][x_1 * 2] = U;
	}
	else if(y_0 > y_1 && x_0 == x_1) //与上组合
	{	
		path[y_0 * 2][x_0 * 2] = U;
		path[y_1 * 2 + 1][x_1 * 2 + 1] = D;
	}
}

void gameover()
{
	getchar();
	exit(0);
}
