#include "ui.h"
#include "function.h"

HANDLE hIn, hOut;
COORD mouse_pos; //记录鼠标点击位置
DWORD Result;
INPUT_RECORD Buf; //存储鼠标操作事件

void init();

int main()
{
	init();
	draw_window();
	while (1) 
	{
		draw_menu_button(); //绘制按钮
		switch (menu_click()) //判断鼠标点击
		{
		case ADD_BUTTON: //添加车辆
			add_car_fun();
			draw_window();
			break;
		case BROWSE_BUTTON: //浏览全部
			browse_car_fun(head);
			draw_window();
			break;
		case FIND_BUTTON: //查询车辆
			find_car_fun();
			draw_window();
			break;
		case EXIT_BUTTON: //退出
			if (exit_fun()) return 0;	
			draw_window();
		}
	}
	return 0;
}

void init()
{
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTitle(L"车辆信息管理系统");
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR); //设置控制台颜色
	//设置缓冲区大小
	COORD size = { 142, 30 };
	SetConsoleScreenBufferSize(hOut, size);
	//设置窗口大小
	SMALL_RECT rc = { 0,0, 141, 29 };
	SetConsoleWindowInfo(hOut, true, &rc);
	//设置控制台模式
	DWORD sort_mode;
	GetConsoleMode(hIn, &sort_mode);
	sort_mode &= ~ENABLE_QUICK_EDIT_MODE; //移除快速编辑模式
	sort_mode &= ~ENABLE_INSERT_MODE; //移除插入模式
	SetConsoleMode(hIn, sort_mode);
	//隐藏光标
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOut, &CursorInfo);//光标信息
	CursorInfo.bVisible = 0; //隐藏光标
	SetConsoleCursorInfo(hOut, &CursorInfo);//设置光标状态

	load_car(); //加载车辆信息
}