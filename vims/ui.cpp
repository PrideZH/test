#include "ui.h"
#include "car.h"
#include "function.h"

//菜单界面按钮
BYTTON_INFO add_but = { 66, 11, 10, "增 添 车 辆" };
BYTTON_INFO browse_but = { 66, 13, 10, "浏 览 全 部" };
BYTTON_INFO find_but = { 66, 15, 10, "查 询 车 辆" };
BYTTON_INFO exit_but = { 69, 17, 4, "退 出" };
//添加界面按钮
BYTTON_INFO set_confirm_but = { 60, 24, 5, "[确定]" };
BYTTON_INFO set_return_but = { 70, 24, 5, "[返回]" };
//浏览界面按钮
BYTTON_INFO id_but = { 9, 3, 3, "编号" };
BYTTON_INFO seat_but = { 64, 3, 5, "座位数" };
BYTTON_INFO emission_but = { 73, 3, 6, "排量(L)" };
BYTTON_INFO price_but = { 107, 3, 11, "车辆价格(万)" };
BYTTON_INFO next_but = { 77, 26, 5, "下一页" };
BYTTON_INFO previous_but = { 60, 26, 5, "上一页" };
BYTTON_INFO browse_return_but = { 121, 26, 3, "返回" };
//查询界面按钮
BYTTON_INFO find_id_but = { 55, 8, 11, "[  编  号  ]" };
BYTTON_INFO find_type_but = { 75, 8, 11, "[ 车辆型号 ]" };
BYTTON_INFO find_manufacturer_but = { 55, 11, 11, "[  厂  商  ]" };
BYTTON_INFO find_grade_but = { 75, 11, 11, "[ 车型级别 ]" };
BYTTON_INFO find_seat_but = { 55, 14, 11, "[  座位数  ]" };
BYTTON_INFO find_emission_but = { 75, 14, 11, "[  排  量  ]" };
BYTTON_INFO find_gearbox_but = { 55, 17, 11, "[  变速箱  ]" };
BYTTON_INFO find_colour_but = { 75, 17, 11, "[ 车身颜色 ]" };
BYTTON_INFO find_price_but = { 55, 20, 11, "[ 车辆价格 ]" };
BYTTON_INFO find_return_but = { 75, 20, 11, "[  返  回  ]" };
//删除车辆界面
BYTTON_INFO del_confirm_but = { 62, 15, 5, "[确定]" };
BYTTON_INFO del_return_but = { 74, 15, 5, "[取消]" };
//退出界面按钮
BYTTON_INFO exit_yes_but = { 61, 15, 3, "[是]" };
BYTTON_INFO exit_no_but = { 68, 15, 3, "[否]" };
BYTTON_INFO exit_cancel_but = { 75, 15, 5, "[取消]" };

void draw_window() 
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

void draw_popup()
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
	draw_popup();
	gotoxy(71 - strlen(information) / 2, 13); //使消息居中
	printf("%s", information);
	gotoxy(63, 15);
	printf("%s", "（按任意键继续）");
	_getch();
}

void popup_input(const char *information, int content_lenght)
{
	draw_popup();
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

void draw_menu_button()
{
	//绘制按钮
	draw_button(add_but); //绘制 [增 添 车 辆]
	draw_button(browse_but); //绘制 [浏 览 全 部]
	draw_button(find_but); //绘制 [查 询 车 辆]
	draw_button(exit_but); //绘制 [退 出]
	//绘制按钮光标
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if(is_in_button(add_but)) draw_button(add_but); //绘制 [增 添 车 辆]
	else if (is_in_button(browse_but)) draw_button(browse_but); //绘制 [浏 览 全 部]
	else if (is_in_button(find_but)) draw_button(find_but); //绘制 [查 询 车 辆]
	else if (is_in_button(exit_but)) draw_button(exit_but); //绘制 [退 出]
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON menu_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
	{
		if (is_in_button(add_but)) return ADD_BUTTON; //添加车辆
		else if (is_in_button(browse_but)) return BROWSE_BUTTON; //浏览全部
		else if (is_in_button(find_but)) return FIND_BUTTON; //查询车辆
		else if (is_in_button(exit_but)) return EXIT_BUTTON; //退出
		ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
	}
	return NONE;
}

void draw_set_windows(PCAR car)
{
	draw_window();
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
}

void draw_set_button()
{
	//绘制按钮
	for (int n = 0; n < 16; n+=2)
	{
		gotoxy(79, 8 + n);
		printf("[输入]");
		gotoxy(86, 8 + n);
		printf("[清空]");
	}
	draw_button(set_confirm_but); //绘制 [确定]
	draw_button(set_return_but); //绘制 [返回]
	//绘制按钮光标
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (mouse_pos.Y > 7 && mouse_pos.Y < 23 && 0 == mouse_pos.Y%2)
	{
		if (mouse_pos.X >= 79 && mouse_pos.X <= 84)
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
	else if(is_in_button(set_confirm_but)) draw_button(set_confirm_but); //绘制 [确定]
	else if (is_in_button(set_return_but)) draw_button(set_return_but); //绘制 [返回]
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);
	Sleep(1000 / FPS);
}

BUTTON set_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result);
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
	{
		if (mouse_pos.Y > 7 && mouse_pos.Y < 23 && 0 == mouse_pos.Y % 2)
		{
			if (mouse_pos.X > 78 && mouse_pos.X < 85) //输入
			{
				return INPUT_BUTTON;
			}
			else if (mouse_pos.X > 85 && mouse_pos.X < 92) //清空
			{
				return EMPTY_BUTTON;
			}
		}
		else if (is_in_button(set_confirm_but)) return CONFIRM_BUTTON;
		else if (is_in_button(set_return_but)) return RETURN_BUTTON;
		ReadConsoleInput(hIn, &Buf, 1, &Result);
	}
	return NONE;
}

void draw_browse_windows()
{
	draw_window();
	gotoxy(9, 3);
	printf("%-4s|%-23s|%-11s|%-11s|%s|%s|%-11s|%-11s|%-15s|%s\n",
		"编号↓", "        车辆型号", "    厂商", " 车型级别", "座位数—", "排量(L)—", "  变速箱", " 车身颜色", "车辆价格(万)—", "   操作");
	gotoxy(9, 4);
	printf("%s", "——————————————————————————————————————————————————————————————");
	gotoxy(9, 25);
	printf("%s", "——————————————————————————————————————————————————————————————");
}

void draw_browse_button(int page_cars_number)
{
	//绘制按钮
	draw_button(id_but); //绘制 [编号]
	draw_button(seat_but); //绘制 [座位数]
	draw_button(emission_but); //绘制 [排量(L)]
	draw_button(price_but); //绘制 [车辆价格(万)]
	draw_button(next_but); //绘制 [下一页]
	draw_button(previous_but); //绘制 [上一页]
	draw_button(browse_return_but); //绘制 [返回]
	for (int n = 0; n < page_cars_number; n++)
	{
		gotoxy(124, 5 + n);
		printf("修改");
		gotoxy(129, 5 + n);
		printf("删除");
	}
	//绘制按钮光标
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (is_in_button(id_but)) draw_button(id_but); //绘制 [编号]
	else if (is_in_button(seat_but)) draw_button(seat_but); //绘制 [座位数]
	else if (is_in_button(emission_but)) draw_button(emission_but); //绘制 [排量(L)]
	else if (is_in_button(price_but)) draw_button(price_but); //绘制 [车辆价格(万)]
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
	else if (is_in_button(next_but)) draw_button(next_but); //绘制 [下一页]
	else if (is_in_button(previous_but)) draw_button(previous_but); //绘制 [上一页]
	else if (is_in_button(browse_return_but)) draw_button(browse_return_but); //绘制 [返回]
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON browse_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
	{
		if (is_in_button(id_but))return SORT_ID_BUTTON; //编号
		else if (is_in_button(seat_but)) return SORT_SEAT_BUTTON; //座位数
		else if (is_in_button(emission_but)) return SORT_EMISSION_BUTTON; //排量
		else if (is_in_button(price_but)) return SORT_PRICE_BUTTON; //车辆价格
		else if (mouse_pos.Y > 4 && mouse_pos.Y < 26)
		{
			if (mouse_pos.X > 123 && mouse_pos.X < 128) //修改
			{
				return SET_BUTTON;
			}
			else if (mouse_pos.X > 128 && mouse_pos.X < 133) //删除
			{
				return DELETE_BUTTON;
			}
		}
		else if (is_in_button(previous_but)) return PREVIOUS_BUTTON; //上一页
		else if (is_in_button(next_but)) return NEXT_BUTTON; //下一页
		else if (is_in_button(browse_return_but)) return RETURN_BUTTON; //返回  
		ReadConsoleInput(hIn, &Buf, 1, &Result);
	}
	return NONE;
}

void browse_print_cars(PCAR head, int page)
{
	//获得指定页面第一俩车
	PCAR car = head->rear;
	for (int i = 0; i < page * 20; i++) 
	{
		car = car->rear;
	}
	//打印该页面车辆
	for (int n = 0; n < 20; n++)
	{
		if (car == NULL) break;
		gotoxy(9, 5 + n % 20);
		printf(" %-5d|%-23s|%-11s|%-11s|  %-6d| %-8.1f|%-11s|%-11s|%-15.2f|",
			car->id, car->type, car->manufacturer, car->grade, car->seat, car->emission, car->gearbox, car->colour, car->price);
		car = car->rear;
	}
}

void draw_browse_page(int page, int all_page)
{
	gotoxy(68, 26);
	printf("[%2d/%-2d]", page + 1, all_page + 1);
}

void draw_browse_sort(int sort_mode)
{
	gotoxy(13, 3);
	printf("—");
	gotoxy(70, 3);
	printf("—");
	gotoxy(80, 3);
	printf("—");
	gotoxy(119, 3);
	printf("—");
	switch (sort_mode)
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

void draw_find_windows()
{
	draw_window();
	gotoxy(64, 3);
	printf("查询车辆信息");
}

void draw_find_button()
{
	//绘制按钮
	draw_button(find_id_but); //绘制 [  编  号  ]
	draw_button(find_type_but); //绘制 [ 车辆型号 ]
	draw_button(find_manufacturer_but); //绘制 [  厂  商  ]
	draw_button(find_grade_but); //绘制 [ 车型级别 ]
	draw_button(find_seat_but); //绘制 [  座位数  ]
	draw_button(find_emission_but); //绘制 [  排  量  ]
	draw_button(find_gearbox_but); //绘制 [  变速箱  ]
	draw_button(find_colour_but); //绘制 [ 车身颜色 ]
	draw_button(find_price_but); //绘制 [ 车辆价格 ]
	draw_button(find_return_but); //绘制 [  返  回  ]
	//绘制按钮光标
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (is_in_button(find_id_but)) draw_button(find_id_but); //绘制 [  编  号  ]
	else if (is_in_button(find_type_but)) draw_button(find_type_but); //绘制 [ 车辆型号 ]
	else if (is_in_button(find_manufacturer_but)) draw_button(find_manufacturer_but); //绘制 [  厂  商  ]
	else if (is_in_button(find_grade_but)) draw_button(find_grade_but); //绘制 [ 车型级别 ]
	else if (is_in_button(find_seat_but)) draw_button(find_seat_but); //绘制 [  座位数  ]
	else if (is_in_button(find_emission_but)) draw_button(find_emission_but); //绘制 [  排  量  ]
	else if (is_in_button(find_gearbox_but)) draw_button(find_gearbox_but); //绘制 [  变速箱  ]
	else if (is_in_button(find_colour_but)) draw_button(find_colour_but); //绘制 [ 车身颜色 ]
	else if (is_in_button(find_price_but)) draw_button(find_price_but); //绘制 [ 车辆价格 ]
	else if (is_in_button(find_return_but)) draw_button(find_return_but); //绘制 [  返  回  ]
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON find_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
	{
		if (is_in_button(find_id_but)) return FIND_ID_BUTTON; //编号
		else if (is_in_button(find_type_but)) return FIND_TYPE_BUTTON; //型号
		else if (is_in_button(find_manufacturer_but)) return FIND_MANUFACTURER_BUTTON; //厂商
		else if (is_in_button(find_grade_but)) return FIND_GRADE_BUTTON; //级别
		else if (is_in_button(find_seat_but)) return FIND_SEAT_BUTTON; //座位数
		else if (is_in_button(find_emission_but)) return FIND_EMISSION_BUTTON; //排量
		else if (is_in_button(find_gearbox_but)) return FIND_GEARBOX_BUTTON; //变速箱
		else if (is_in_button(find_colour_but)) return FIND_COLOUR_BUTTON; //车身颜色
		else if (is_in_button(find_price_but)) return FIND_PRICE_BUTTON; //价格
		else if (is_in_button(find_return_but)) return RETURN_BUTTON; //返回
		ReadConsoleInput(hIn, &Buf, 1, &Result);
	}
	return NONE;
}

void draw_del_windows()
{
	draw_popup();
	gotoxy(63, 13);
	printf("是否删除车辆信息");
	draw_del_button();
}

void draw_del_button()
{
	//绘制按钮
	draw_button(del_confirm_but); //绘制 [确定]
	draw_button(del_return_but); //绘制 [取消]
	//绘制按钮光标
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (is_in_button(del_confirm_but)) draw_button(del_confirm_but); //绘制 [确定]
	else if (is_in_button(del_return_but)) draw_button(del_return_but); //绘制 [取消]
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON del_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
	{
		if (is_in_button(del_confirm_but)) return CONFIRM_BUTTON; //确定
		else if (is_in_button(del_return_but)) return RETURN_BUTTON; //取消
		ReadConsoleInput(hIn, &Buf, 1, &Result);
	}
	return NONE;
}

void draw_exit_windows()
{
	draw_popup();
	gotoxy(62, 13);
	printf("是否退出程序并保存");
}

void draw_exit_button()
{
	//绘制按钮
	draw_button(exit_yes_but); //绘制 [是]
	draw_button(exit_no_but); //绘制 [否]
	draw_button(exit_cancel_but); //绘制 [取消]
	//绘制按钮光标
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (is_in_button(exit_yes_but)) draw_button(exit_yes_but); //绘制 [是]
	else if (is_in_button(exit_no_but)) draw_button(exit_no_but); //绘制 [否]
	else if (is_in_button(exit_cancel_but)) draw_button(exit_cancel_but); //绘制 [取消]
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON exit_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
	{
		if (is_in_button(exit_yes_but)) return YES; //是
		else if (is_in_button(exit_no_but)) return NO; //否
		else if (is_in_button(exit_cancel_but)) return CANCEL; //取消
		ReadConsoleInput(hIn, &Buf, 1, &Result);
	}
	return NONE;
}

void gotoxy(int x, int y)
{
	COORD cursor_pos;
	cursor_pos.X = x;
	cursor_pos.Y = y;
	SetConsoleCursorPosition(hOut, cursor_pos);
}

void draw_button(BYTTON_INFO but)
{
	gotoxy(but.x, but.y);
	printf(but.content);
}

int is_in_button(BYTTON_INFO but)
{
	if (but.y == mouse_pos.Y && mouse_pos.X >= but.x && mouse_pos.X <= but.x + but.size)
	{
		return 1;
	}
	return 0;
}