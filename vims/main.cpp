#include "ui.h"
#include "function.h"

HANDLE hIn, hOut;
COORD mouse_pos;
DWORD Result;
INPUT_RECORD Buf;

void init();

int main()
{
	init();
	init_window();
	while (1) 
	{
		ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
		menu_cursor(); //根据鼠标位置绘制菜单光标
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
		{
			if (mouse_pos.X > 65 && mouse_pos.X < 77)
			{
				switch (mouse_pos.Y)
				{
				case 11: //添加车辆
					add_car();
					init_window();
					break;
				case 13: //浏览全部
					browse_cars(NULL, get_all_car_number());
					init_window();
					break;
				case 15: //查询车辆
					find_car();
					init_window();
					break;
				case 17: //退出
					if(exit_app()) return 0;
					init_window();
				}
			}
			if (!ReadConsoleInput(hIn, &Buf, 1, &Result)) break;
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
	DWORD mode;
	GetConsoleMode(hIn, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE; //移除快速编辑模式
	mode &= ~ENABLE_INSERT_MODE; //移除插入模式
	SetConsoleMode(hIn, mode);
	//隐藏光标
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOut, &CursorInfo);//光标信息
	CursorInfo.bVisible = 0; //隐藏光标
	SetConsoleCursorInfo(hOut, &CursorInfo);//设置光标状态
	load_car(); //加载车辆信息
}