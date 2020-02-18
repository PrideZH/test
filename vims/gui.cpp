#include "gui.h"
#include "car.h"
#include "function.h"

void init_window() 
{
	gotoxy(8, 2);
	printf("╭——————————————————————————————————————————————————————————————╮\n");
	for (int i = 0; i < 24; i++)
	{
		gotoxy(8, 3 + i);
		printf("|                                                                                                                             |\n");
	}
	gotoxy(8, 27);
	printf("╰——————————————————————————————————————————————————————————————╯\n");
}

void init_popup()
{
	gotoxy(43, 11);
	printf("╭———————————————————————————╮\n");
	for (int i = 0; i < 5; i++)
	{
		gotoxy(43, 12 + i);
		printf("|                                                       |\n");
	}
	gotoxy(43, 17);
	printf("╰———————————————————————————╯\n");
}

void popup_prompt(const char *information)
{
	init_popup();
	gotoxy(71 - strlen(information) / 2, 13); //使消息居中
	printf("%s", information);
	gotoxy(63, 15);
	printf("%s", "（按任意键继续）");
	_getch();
}

void popup_input(const char *information, int content_lenght)
{
	init_popup();
	gotoxy(71 - (strlen(information) + content_lenght) / 2, 14); //使消息居中
	printf("%s", information);
	gotoxy(71 - (content_lenght - strlen(information)) / 2, 14); //在消息后面输入
	for (int i = 1; i < content_lenght; i++)
	{
		printf("_");
	}
	gotoxy(71 - (content_lenght - strlen(information)) / 2, 14); //在消息后面输入
}

void popup_input_str(const char *information, char *content, int content_lenght)
{
	popup_input(information, content_lenght);
	while (!scanf_s("%s", content, content_lenght))
	{
		rewind(stdin);
		popup_prompt("输入内容过长，请重写输入...");
		popup_input(information, content_lenght);
	}
}

void popup_input_int(const char *information, int *content, int content_lenght)
{
	popup_input(information, content_lenght);
	while (!scanf_s("%4d", content))
	{
		rewind(stdin);
		popup_prompt("输入内容过长或错误，请重写输入...");
		popup_input(information, content_lenght);
	}
	rewind(stdin);
}

void popup_input_float(const char *information, float *content, int content_lenght)
{
	popup_input(information, content_lenght);
	while (!scanf_s("%12f", content))
	{
		rewind(stdin);
		popup_prompt("输入内容过长或错误，请重写输入...");
		popup_input(information, content_lenght);
	}
	rewind(stdin);
}

void menu_cursor()
{
	gotoxy(66, 11);
	printf("增 添 车 辆");
	gotoxy(66, 13);
	printf("浏 览 全 部");
	gotoxy(66, 15);
	printf("查 询 车 辆");
	gotoxy(69, 17);
	printf("退 出");
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (mouse_pos.X > 65 && mouse_pos.X < 77)
	{
		switch (mouse_pos.Y)
		{
		case 11:
			gotoxy(66, 11);
			printf("增 添 车 辆");
			break;
		case 13:
			gotoxy(66, 13);
			printf("浏 览 全 部");
			break;
		case 15:
			gotoxy(66, 15);
			printf("查 询 车 辆");
			break;
		case 17:
			gotoxy(69, 17);
			printf("退 出");
			break;
		}
	}
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);
	Sleep(1000 / FPS);
}

void init_set_interface(PCAR car)
{
	init_window();
	gotoxy(49, 6);
	printf("编  号:%d", car->id);
	gotoxy(49, 8);
	printf("型  号:%s", car->type);
	gotoxy(49, 10);
	printf("厂  商:%s", car->manufacturer);
	gotoxy(49, 12);
	printf("级  别:%s", car->grade);
	gotoxy(49, 14);
	printf("座位数:%d", car->seat);
	gotoxy(49, 16);
	printf("排  量:%.2f", car->emission);
	gotoxy(49, 18);
	printf("变速箱:%s", car->gearbox);
	gotoxy(49, 20);
	printf("颜  色:%s", car->colour);
	gotoxy(49, 22);
	printf("价  格:%.2f", car->price);
	set_cursor();
}

void set_cursor()
{
	for (int n = 0; n < 16; n+=2)
	{
		gotoxy(79, 8 + n);
		printf("[输入]");
		gotoxy(86, 8 + n);
		printf("[清空]");
	}
	gotoxy(60, 24);
	printf("[确定]");
	gotoxy(70, 24);
	printf("[返回]");
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (mouse_pos.Y > 7 && mouse_pos.Y < 23 && 0 == mouse_pos.Y%2)
	{
		if (mouse_pos.X > 78 && mouse_pos.X < 85)
		{
			gotoxy(79, mouse_pos.Y);
			printf("[输入]");
		}
		else if (mouse_pos.X > 85 && mouse_pos.X < 92)
		{
			gotoxy(86, mouse_pos.Y);
			printf("[清空]");
		}
	}
	else if (24 == mouse_pos.Y)
	{
		if (mouse_pos.X > 59 && mouse_pos.X < 66) 
		{
			gotoxy(60, 24);
			printf("[确定]");
		}
		else if (mouse_pos.X > 69 && mouse_pos.X < 76)
		{
			gotoxy(70, 24);
			printf("[返回]");
		}
	}
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);
	Sleep(1000 / FPS);
}

void init_browse_interface()
{
	init_window();
	gotoxy(9, 3);
	printf("%-4s|%-23s|%-11s|%-11s|%s|%s|%-11s|%-11s|%-15s|%s\n",
		"编号↓", "        车辆型号", "    厂商", " 车型级别", "座位数—", "排量(L)—", "  变速箱", " 车身颜色", "车辆价格(万)—", "   操作");
	gotoxy(9, 4);
	printf("%s", "——————————————————————————————————————————————————————————————");
	gotoxy(9, 25);
	printf("%s", "——————————————————————————————————————————————————————————————");
	gotoxy(60, 26);
	printf("上一页  [ 1/1 ]  下一页                                      返回");
}

void browse_cursor(int page_cars_number)
{
	gotoxy(9, 3);
	printf("编号");
	gotoxy(64, 3);
	printf("座位数");
	gotoxy(73, 3);
	printf("排量(L)");
	gotoxy(107, 3);
	printf("车辆价格(万)");
	gotoxy(77, 26);
	printf("下一页");
	gotoxy(60, 26);
	printf("上一页");	
	gotoxy(121, 26);
	printf("返回");
	for (int n = 0; n < page_cars_number; n++)
	{
		gotoxy(124, 5 + n);
		printf("修改");
		gotoxy(129, 5 + n);
		printf("删除");
	}
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (3 == mouse_pos.Y) //排序操作
	{
		if (mouse_pos.X > 8 && mouse_pos.X < 13) 
		{
			gotoxy(9, 3);
			printf("编号");
		}
		else if (mouse_pos.X > 63 && mouse_pos.X < 70)
		{
			gotoxy(64, 3);
			printf("座位数");
		}
		else if (mouse_pos.X > 72 && mouse_pos.X < 80) 
		{
			gotoxy(73, 3);
			printf("排量(L)");
		}
		else if (mouse_pos.X > 106 && mouse_pos.X < 115) 
		{
			gotoxy(107, 3);
			printf("车辆价格(万)");
		}
	}
	else if(mouse_pos.Y > 4 && mouse_pos.Y < 26 && mouse_pos.Y < 5 + page_cars_number)//修改和删除操作
	{
		if (mouse_pos.X > 123 && mouse_pos.X < 128)
		{
			gotoxy(124, mouse_pos.Y);
			printf("修改");
		}
		else if (mouse_pos.X > 128 && mouse_pos.X < 133)
		{
			gotoxy(129, mouse_pos.Y);
			printf("删除");
		}
	}
	else if(26 == mouse_pos.Y) //换页和返回操作
	{	
		if (mouse_pos.X > 59 && mouse_pos.X < 66)
		{
			gotoxy(60, 26);
			printf("上一页");
		}
		else if (mouse_pos.X > 76 && mouse_pos.X < 83)
		{
			gotoxy(77, 26);
			printf("下一页");
		}
		else if (mouse_pos.X > 120 && mouse_pos.X < 125)
		{
			gotoxy(121, 26);
			printf("返回");
		}
	}
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);
	Sleep(1000 / FPS);
}

void browse_print_cars(int *cars_id, int page_cars_number, int page)
{
	for (int n = page * 20; n < page_cars_number + page * 20; n++)
	{
		gotoxy(9, 5 + n % 20);
		PCAR car;
		car = get_car(cars_id[n]);
		printf(" %-5d|%-23s|%-11s|%-11s|  %-6d| %-8.1f|%-11s|%-11s|%-15.2f| 修改 删除 ",
			car->id, car->type, car->manufacturer, car->grade, car->seat, car->emission, car->gearbox, car->colour, car->price);
	}
}

void update_browse_page(int page, int all_page)
{
	gotoxy(68, 26);
	printf("[%2d/%-2d]", page + 1, all_page + 1);
}

void update_browse_sort(int mode)
{
	gotoxy(13, 3);
	printf("—");
	gotoxy(70, 3);
	printf("—");
	gotoxy(80, 3);
	printf("—");
	gotoxy(119, 3);
	printf("—");
	switch (mode)
	{
	case 0:
		gotoxy(13, 3);
		printf("↓");
		break;
	case 1:
		gotoxy(13, 3);
		printf("↑");
		break;
	case 2:
		gotoxy(70, 3);
		printf("↓");
		break;
	case 3:
		gotoxy(70, 3);
		printf("↑");
		break;
	case 4:
		gotoxy(80, 3);
		printf("↓");
		break;
	case 5:
		gotoxy(80, 3);
		printf("↑");
		break;
	case 6:
		gotoxy(119, 3);
		printf("↓");
		break;
	case 7:
		gotoxy(119, 3);
		printf("↑");
		break;

	}
}

void init_find_interface()
{
	init_window();
	gotoxy(64, 3);
	printf("查询车辆信息");
	find_cursor();
}

void find_cursor()
{
	gotoxy(55, 8);
	printf("[  编  号  ]");
	gotoxy(75, 8);
	printf("[ 车辆型号 ]");
	gotoxy(55, 11);
	printf("[  厂  商  ]");
	gotoxy(75, 11);
	printf("[ 车型级别 ]");
	gotoxy(55, 14);
	printf("[  座位数  ]");
	gotoxy(75, 14);
	printf("[  排  量  ]");
	gotoxy(55, 17);
	printf("[  变速箱  ]");
	gotoxy(75, 17);
	printf("[ 车身颜色 ]");
	gotoxy(55, 20);
	printf("[ 车辆价格 ]");
	gotoxy(75, 20);
	printf("[  返  回  ]");
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (mouse_pos.X > 54 && mouse_pos.X < 67)
	{
		switch (mouse_pos.Y)
		{
		case 8:
			gotoxy(55, 8);
			printf("[  编  号  ]");
			break;
		case 11:
			gotoxy(55, 11);
			printf("[  厂  商  ]");
			break;
		case 14:
			gotoxy(55, 14);
			printf("[  座位数  ]");
			break;
		case 17:
			gotoxy(55, 17);
			printf("[  变速箱  ]");
			break;
		case 20:
			gotoxy(55, 20);
			printf("[ 车辆价格 ]");
			break;
		}
	}
	else if (mouse_pos.X > 74 && mouse_pos.X < 87)
	{
		switch (mouse_pos.Y)
		{
		case 8:
			gotoxy(75, 8);
			printf("[ 车辆型号 ]");
			break;
		case 11:
			gotoxy(75, 11);
			printf("[ 车型级别 ]");
			break;
		case 14:
			gotoxy(75, 14);
			printf("[  排  量  ]");
			break;
		case 17:
			gotoxy(75, 17);
			printf("[ 车身颜色 ]");
			break;
		case 20:
			gotoxy(75, 20);
			printf("[  返  回  ]");
			break;
		}
	}
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);
	Sleep(1000 / FPS);
}

void init_del_interface()
{
	init_popup();
	gotoxy(63, 13);
	printf("是否删除车辆信息");
	del_cursor();
}

void del_cursor()
{
	gotoxy(62, 15);
	printf("[确定]");
	gotoxy(74, 15);
	printf("[取消]");
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (15 == mouse_pos.Y)
	{
		if (mouse_pos.X > 61 && mouse_pos.X < 68)
		{
			gotoxy(62, 15);
			printf("[确定]");
		}
		else if (mouse_pos.X > 73 && mouse_pos.X < 80)
		{
			gotoxy(74, 15);
			printf("[取消]");
		}
	}
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);
	Sleep(1000 / FPS);
}

void exit_app_interface()
{
	init_popup();
	gotoxy(62, 13);
	printf("是否退出程序并保存");
}

void exit_cursor()
{
	gotoxy(61, 15);
	printf("[是]   [否]   [取消]");
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (15 == mouse_pos.Y)
	{
		if (mouse_pos.X > 60 && mouse_pos.X < 65)
		{
			gotoxy(61, 15);
			printf("[是]");
		}
		else if (mouse_pos.X > 67 && mouse_pos.X < 72)
		{
			gotoxy(68, 15);
			printf("[否]");
		}
		else if (mouse_pos.X > 74 && mouse_pos.X < 81)
		{
			gotoxy(75, 15);
			printf("[取消]");
		}
	}
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);
	Sleep(1000 / FPS);
}

void gotoxy(int x, int y)
{
	COORD cursor_pos;
	cursor_pos.X = x;
	cursor_pos.Y = y;
	SetConsoleCursorPosition(hOut, cursor_pos);
}