#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>

#define HEIGHT GetSystemMetrics(SM_CYSCREEN)
#define WIDTH GetSystemMetrics(SM_CXSCREEN)

// 字符雨
typedef struct CharNode CHAR_NODE, *PCHAR_NODE;
struct CharNode
{
	int x, y; // 首字符位置
	int length; // 字符串长度
	int speed; // 下落速度
	int size; // 字符大小
	PCHAR_NODE next;
};
PCHAR_NODE char_rain;

void add()
{
	PCHAR_NODE rand_char = (PCHAR_NODE)malloc(sizeof(CHAR_NODE));
	// 随机位置
	rand_char->y = 0;
	rand_char->x = rand() % WIDTH;
	// 随机长度
	rand_char->length = rand() % 15 + 5;
	// 随机速度
	rand_char->speed = rand() % 30 + 5;
	// 随机大小
	rand_char->size = rand() % 20 + 15;
	// 头插
	rand_char->next = char_rain->next;
	char_rain->next = rand_char;
}

void remove()
{
	for (PCHAR_NODE p = char_rain->next, rear = char_rain; p != NULL; rear = p, p = p->next)
	{
		// 如果字符雨最后一个字符超过屏幕高度则删除该字符雨
		if (p->y > HEIGHT + p->length * p->size)
		{
			rear->next = p->next;
			free(p);
			return;
		}
	}
}

void draw()
{
	BeginBatchDraw();
	//清空屏幕
	cleardevice(); 
	// 绘制字符
	for (PCHAR_NODE p = char_rain->next; p != NULL; p = p->next)
	{
		settextcolor(WHITE);
		settextstyle(p->size - 5, 10, L"Courier");
		int step = 200 / p->length;
		for (int i = 0; i < p->length; ++i)
		{
			outtextxy(p->x, p->y - i * p->size, rand() % 26 + 65);
			settextcolor(RGB(0, 255 - i * step, 0));
		}
		p->y += p->speed;
	}
	EndBatchDraw();
	Sleep(100);
}

int main()
{
	HWND hwnd = initgraph(WIDTH, HEIGHT);
	// 设置窗口位置
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, WIDTH, HEIGHT, SWP_SHOWWINDOW);
	// 去除标题栏
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	// 设置为透明
	LONG WindowLong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	SetWindowLong(hwnd, GWL_EXSTYLE, WindowLong);
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
	// 初始化字符雨链表
	char_rain = (PCHAR_NODE)malloc(sizeof(CHAR_NODE));
	char_rain->next = NULL;

	srand((unsigned)time(NULL));
	while (1)
	{
		// 添加字符雨
		add();
		// 移除超过屏幕的字符雨
		remove();
		// 绘制
		draw();
	}
	return 0;
}