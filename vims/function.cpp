#include "function.h"
#include "gui.h"

void add_car()
{
	PCAR car = (PCAR)calloc(1, sizeof(CAR));
	car->id = get_id(); //获得汽车编号
	init_set_interface(car);
	while (1)
	{
		ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
		set_cursor(); //根据鼠标位置绘制添加车辆界面的光标
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
		{
			if (mouse_pos.Y > 7 && mouse_pos.Y < 23 && 0 == mouse_pos.Y % 2)
			{
				if (mouse_pos.X > 78 && mouse_pos.X < 85) //输入
				{
					car_input(car, mouse_pos.Y); 
				}
				else if (mouse_pos.X > 85 && mouse_pos.X < 92) //清空
				{
					car_empty(car, mouse_pos.Y);
					init_set_interface(car);
				}
			}
			else if (24 == mouse_pos.Y)
			{
				if (mouse_pos.X > 59 && mouse_pos.X < 66)  //确定
				{
					add_list(car);
					popup_prompt("汽车添加成功...");
					return;
				}
				else if (mouse_pos.X > 69 && mouse_pos.X < 76) //返回
				{
					return;
				}
			}
			if (!ReadConsoleInput(hIn, &Buf, 1, &Result)) break;
		}
	}
}

void car_input(PCAR car, int position)
{
	switch (position)
	{
	case 8:
		popup_input_str("请输入车辆型号:", car->type, MAX_CAR_TYPE);
		init_set_interface(car);
		break;
	case 10:
		popup_input_str("请输入厂商:", car->manufacturer, MAX_CAR_MANUFACTURER);
		init_set_interface(car);
		break;
	case 12:
		popup_input_str("请输入车辆级别:", car->grade, MAX_CAR_GRADE);
		init_set_interface(car);
		break;
	case 14:
		popup_input_int("请输入车辆座位数:", &car->seat, MAX_CAR_SEAT);
		init_set_interface(car);
		if (car->seat < 0)
		{
			car->seat = 0;
		}
		break;
	case 16:
		popup_input_float("请输入排量(L):", &car->emission, MAX_CAR_EMISSION );
		init_set_interface(car);
		if (car->emission < 0)
		{
			car->emission = 0;
		}
		break;
	case 18:
		popup_input_str("请输入车辆变速箱:", car->gearbox, MAX_CAR_GEARBOX);
		init_set_interface(car);
		break;
	case 20:
		popup_input_str("请输入车身颜色:", car->colour, MAX_CAR_COLOUR);
		init_set_interface(car);
		break;
	case 22:
		popup_input_float("请输入车辆价格(万):", &car->price, MAX_CAR_PRICE);
		init_set_interface(car);
		if (car->price < 0)
		{
			car->price = 0;
		}
		break;
	}
	rewind(stdin);
	init_set_interface(car);
}

void car_empty(PCAR car, int position)
{
	switch (mouse_pos.Y)
	{
	case 8:
		strcpy_s(car->type, " ");
		break;
	case 10:
		strcpy_s(car->manufacturer, " ");
		break;
	case 12:
		strcpy_s(car->grade, " ");
		break;
	case 14:
		car->seat = 0;
		break;
	case 16:
		car->emission = 0;
		break;
	case 18:
		strcpy_s(car->gearbox, " ");
		break;
	case 20:
		strcpy_s(car->colour, " ");
		break;
	case 22:
		car->price = 0;
		break;
	}
}

void browse_cars(int *cars_id, int cars_id_number)
{
	if (NULL == cars_id)
	{
		cars_id = (int *)malloc((get_all_car_number()) * sizeof(int));
		PCAR car = head->rear;
		for (int i = 0; car != NULL; car = car->rear, i++) //获取所有车辆下标
		{
			cars_id[i] = car->id;
		}
	}
	if (0 == cars_id_number) //无车辆信息时弹窗提示并返回
	{
		popup_prompt("无车辆信息，无法查询...");
		return ;
	}
	int mode = 0; //车辆排序方式
	int page = 0; //当前页数
	int all_page = (cars_id_number - 1) / 20; //计算总页数
	int page_cars_number = page == all_page ? cars_id_number - page * 20 : 20; //计算当前页汽车数量
	init_browse_interface(); //绘制浏览车辆界面
	update_browse_page(page, all_page); //页数信息显示
	browse_print_cars(cars_id, page_cars_number, page); //显示第一页车辆
	while (1)
	{
		ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
		browse_cursor(page_cars_number); //根据鼠标位置绘制菜单光标
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
		{
			if (3 == mouse_pos.Y) //排序操作
			{
				if (mouse_pos.X > 8 && mouse_pos.X < 13)  //编号
				{
					browse_sort(cars_id, cars_id_number, mode = !(mode % 2));
					browse_print_cars(cars_id, page_cars_number, page); //显示车辆
				}
				else if (mouse_pos.X > 63 && mouse_pos.X < 70) //座位数
				{
					browse_sort(cars_id, cars_id_number, mode = !(mode % 2) + 2);
					browse_print_cars(cars_id, page_cars_number, page); //显示车辆
				}
				else if (mouse_pos.X > 72 && mouse_pos.X < 80) //排量
				{
					browse_sort(cars_id, cars_id_number, mode = !(mode % 2) + 4);
					browse_print_cars(cars_id, page_cars_number, page); //显示车辆
				}
				else if (mouse_pos.X > 106 && mouse_pos.X < 115) //车辆价格
				{
					browse_sort(cars_id, cars_id_number, mode = !(mode % 2) + 6);
					browse_print_cars(cars_id, page_cars_number, page); //显示车辆
				}
			}
			else if (mouse_pos.Y > 4 && mouse_pos.Y < 26 && mouse_pos.Y < 5 + page_cars_number)
			{
				if (mouse_pos.X > 123 && mouse_pos.X < 128) //修改
				{
					set_car(get_car(cars_id[mouse_pos.Y - 5 + page * 20]));
					init_browse_interface();
					update_browse_page(page, all_page); //更新页数显示
					update_browse_sort(mode); //更新排序方式显示信息
					browse_print_cars(cars_id, page_cars_number, page); //显示车辆
				}
				else if (mouse_pos.X > 128 && mouse_pos.X < 133) //删除
				{
					int position = mouse_pos.Y - 5 + page * 20;
					if (del_car(get_car(cars_id[position]))) //删除成功时去除此车辆下标
					{
						for (int j = position; j < cars_id_number; j++)
						{
							cars_id[j] = cars_id[j + 1];
						}
						if (0 == --cars_id_number) return; //没有车辆时返回上一菜单
						init_browse_interface();
						all_page = (cars_id_number - 1) / 20; //计算总页数
						if (page > all_page) page--; //如果当前页无车辆时，转到上一页
						update_browse_page(page, all_page); //更新页数显示
						update_browse_sort(mode); //更新排序方式显示信息
						page_cars_number = page == all_page ? cars_id_number - page * 20 : 20; //计算当前页汽车数量
						browse_print_cars(cars_id, page_cars_number, page); //显示车辆
					}
				}
			}
			else if (26 == mouse_pos.Y) //换页和返回操作
			{
				if (mouse_pos.X > 59 && mouse_pos.X < 66) //上一页
				{
					if (page > 0)
					{
						page--;
						init_browse_interface();
						page_cars_number = page == all_page ? cars_id_number - page * 20 : 20; //计算当前页汽车数量
						browse_print_cars(cars_id, page_cars_number, page); //显示车辆
						update_browse_page(page, all_page); //更新页数显示
						update_browse_sort(mode); //更新排序方式显示信息
					}
				}
				else if (mouse_pos.X > 76 && mouse_pos.X < 83) //下一页
				{
					if (page < all_page)
					{
						page++;
						init_browse_interface();
						page_cars_number = page == all_page ? cars_id_number - page * 20 : 20; //计算当前页汽车数量
						browse_print_cars(cars_id, page_cars_number, page); //显示车辆
						update_browse_page(page, all_page); //更新页数显示
						update_browse_sort(mode); //更新排序方式显示信息
					}
				}
				else if (mouse_pos.X > 120 && mouse_pos.X < 125) //返回  
				{
					return;
				}
			}
			if (!ReadConsoleInput(hIn, &Buf, 1, &Result)) break;
		}
	}
}

void browse_sort(int *cars_id, int cars_id_number, int mode)
{
	PCAR car = head->rear;
	int tmp_i;
	float tmp_f;
	update_browse_sort(mode); //更新排序方式显示信息
	switch (mode)
	{
	case 0: //编号-顺序
	{
		for (int i = 0; i < cars_id_number - 1; i++)
		{
			for (int j = i + 1; j < cars_id_number; j++)
			{
				if (cars_id[j] < cars_id[i])
				{
					cars_id[j] ^= cars_id[i];
					cars_id[i] ^= cars_id[j];
					cars_id[j] ^= cars_id[i];
				}
			}
		}
		break;
	}
	case 1: //编号-逆序
	{
		for (int i = 0; i < cars_id_number - 1; i++)
		{
			for (int j = i + 1; j < cars_id_number; j++)
			{
				if (cars_id[j] > cars_id[i])
				{
					cars_id[j] ^= cars_id[i];
					cars_id[i] ^= cars_id[j];
					cars_id[j] ^= cars_id[i];
				}
			}
		}
		break;
	}
	case 2: //座位数-顺序
	{
		int *cars_seat = (int *)malloc((cars_id_number) * sizeof(int));
		int i;
		for (i = 0; i < cars_id_number; i++)
		{
			cars_seat[i] = get_car(cars_id[i])->seat;
		}
		for (i = 0; i < cars_id_number; i++)
		{
			tmp_i = i;
			for (int j = i + 1; j < cars_id_number; j++)
			{
				if (cars_seat[j] < cars_seat[tmp_i])
				{
					cars_seat[j] ^= cars_seat[tmp_i];
					cars_seat[tmp_i] ^= cars_seat[j];
					cars_seat[j] ^= cars_seat[tmp_i];

					cars_id[j] ^= cars_id[tmp_i];
					cars_id[tmp_i] ^= cars_id[j];
					cars_id[j] ^= cars_id[tmp_i];
				}
			}
		}
		break;
	}
	case 3: //座位数-逆序
	{
		int *cars_seat = (int *)malloc((cars_id_number) * sizeof(int));
		int i;
		for (i = 0; i < cars_id_number; i++)
		{
			cars_seat[i] = get_car(cars_id[i])->seat;
		}
		for (i = 0; i < cars_id_number; i++)
		{
			tmp_i = i;
			for (int j = i + 1; j < cars_id_number; j++)
			{
				if (cars_seat[j] > cars_seat[tmp_i])
				{
					cars_seat[j] ^= cars_seat[tmp_i];
					cars_seat[tmp_i] ^= cars_seat[j];
					cars_seat[j] ^= cars_seat[tmp_i];

					cars_id[j] ^= cars_id[tmp_i];
					cars_id[tmp_i] ^= cars_id[j];
					cars_id[j] ^= cars_id[tmp_i];
				}
			}
		}
		break;
	}
	case 4: //排量-顺序
	{
		float *cars_emission = (float *)malloc((cars_id_number) * sizeof(float));
		int i;
		for (i = 0; i < cars_id_number; i++)
		{
			cars_emission[i] = get_car(cars_id[i])->emission;
		}
		for (i = 0; i < cars_id_number; i++)
		{
			tmp_i = i;
			for (int j = i + 1; j < cars_id_number; j++)
			{
				if (cars_emission[j] < cars_emission[tmp_i])
				{
					cars_emission[j] += cars_emission[tmp_i];
					cars_emission[tmp_i] = cars_emission[j] - cars_emission[tmp_i];
					cars_emission[j] -= cars_emission[tmp_i];

					cars_id[j] ^= cars_id[tmp_i];
					cars_id[tmp_i] ^= cars_id[j];
					cars_id[j] ^= cars_id[tmp_i];
				}
			}
		}
		break;
	}
	case 5: //排量-逆序
	{
		float *cars_emission = (float *)malloc((cars_id_number) * sizeof(float));
		int i;
		for (i = 0; i < cars_id_number; i++)
		{
			cars_emission[i] = get_car(cars_id[i])->emission;
		}
		for (i = 0; i < cars_id_number; i++)
		{
			tmp_i = i;
			for (int j = i + 1; j < cars_id_number; j++)
			{
				if (cars_emission[j] > cars_emission[tmp_i])
				{
					cars_emission[j] += cars_emission[tmp_i];
					cars_emission[tmp_i] = cars_emission[j] - cars_emission[tmp_i];
					cars_emission[j] -= cars_emission[tmp_i];

					cars_id[j] ^= cars_id[tmp_i];
					cars_id[tmp_i] ^= cars_id[j];
					cars_id[j] ^= cars_id[tmp_i];
				}
			}
		}
		break;
	}
	case 6: //价格-顺序
	{
		float *cars_price = (float *)malloc((cars_id_number) * sizeof(float));
		int i;
		for (i = 0; i < cars_id_number; i++)
		{
			cars_price[i] = get_car(cars_id[i])->price;
		}
		for (i = 0; i < cars_id_number; i++)
		{
			tmp_i = i;
			for (int j = i + 1; j < cars_id_number; j++)
			{
				if (cars_price[j] < cars_price[tmp_i])
				{
					cars_price[j] += cars_price[tmp_i];
					cars_price[tmp_i] = cars_price[j] - cars_price[tmp_i];
					cars_price[j] -= cars_price[tmp_i];

					cars_id[j] ^= cars_id[tmp_i];
					cars_id[tmp_i] ^= cars_id[j];
					cars_id[j] ^= cars_id[tmp_i];
				}
			}
		}
		break;
	}
	case 7: //价格-逆序
	{
		float *cars_price = (float *)malloc((cars_id_number) * sizeof(float));
		int i;
		for (i = 0; i < cars_id_number; i++)
		{
			cars_price[i] = get_car(cars_id[i])->price;
		}
		for (i = 0; i < cars_id_number; i++)
		{
			tmp_i = i;
			for (int j = i + 1; j < cars_id_number; j++)
			{
				if (cars_price[j] > cars_price[tmp_i])
				{
					cars_price[j] += cars_price[tmp_i];
					cars_price[tmp_i] = cars_price[j] - cars_price[tmp_i];
					cars_price[j] -= cars_price[tmp_i];

					cars_id[j] ^= cars_id[tmp_i];
					cars_id[tmp_i] ^= cars_id[j];
					cars_id[j] ^= cars_id[tmp_i];
				}
			}
		}
		break;
	}
	}
}

void find_car()
{
	int input_i;
	float input_f;
	char input_s[24];
	PCAR car;
	int cars_id_number;
	int *cars_id = (int *)malloc((get_all_car_number()) * sizeof(int));
	init_find_interface();
	while (1)
	{
		car = head->rear;
		cars_id_number = 0;
		ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
		find_cursor(); //根据鼠标位置绘制查询车辆的光标
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
		{
			if (mouse_pos.X > 54 && mouse_pos.X < 67)
			{
				switch (mouse_pos.Y) 
				{
				case 8: //编号
					popup_input_int("请输入编号:", &input_i, 4);
					do
					{
						if (car->id == input_i)
						{
							cars_id[cars_id_number] = car->id;
							cars_id_number++;
						}
					} while ((car = car->rear) != NULL);
					browse_cars(cars_id, cars_id_number);
					init_find_interface();
					break;
				case 11: //厂商
					popup_input_str("请输入厂商:", input_s, MAX_CAR_MANUFACTURER);
					do
					{
						if (!strcmp(car->type, input_s))
						{
							cars_id[cars_id_number] = car->id;
							cars_id_number++;
						}
					} while ((car = car->rear) != NULL);
					browse_cars(cars_id, cars_id_number);
					init_find_interface();
					break;
				case 14: //座位数
					popup_input_int("请输入座位数:", &input_i, MAX_CAR_SEAT);
					do
					{
						if (car->seat == input_i)
						{
							cars_id[cars_id_number] = car->id;
							cars_id_number++;
						}
					} while ((car = car->rear) != NULL);
					browse_cars(cars_id, cars_id_number);
					init_find_interface();
					break;
				case 17: //变速箱
					popup_input_str("请输入变速箱:", input_s, MAX_CAR_GEARBOX);
					do
					{
						if (!strcmp(car->gearbox, input_s))
						{
							cars_id[cars_id_number] = car->id;
							cars_id_number++;
						}
					} while ((car = car->rear) != NULL);
					browse_cars(cars_id, cars_id_number);
					init_find_interface();
					break;
				case 20: //车辆价格
					popup_input_float("请输入车辆价格:", &input_f, MAX_CAR_PRICE);
					do
					{
						if (car->price == input_f)
						{
							cars_id[cars_id_number] = car->id;
							cars_id_number++;
						}
					} while ((car = car->rear) != NULL);
					browse_cars(cars_id, cars_id_number);
					init_find_interface();
					break;
				}
			}
			else if (mouse_pos.X > 74 && mouse_pos.X < 87)
			{
				switch (mouse_pos.Y)
				{
				case 8: //车辆型号
					popup_input_str("请输入车辆型号:", input_s, MAX_CAR_TYPE);
					do
					{
						if (!strcmp(car->type, input_s))
						{
							cars_id[cars_id_number] = car->id;
							cars_id_number++;
						}
					} while ((car = car->rear) != NULL);
					browse_cars(cars_id, cars_id_number);
					init_find_interface();
					break;
				case 11: //车型级别
					popup_input_str("请输入车型级别:", input_s, MAX_CAR_GRADE);
					do
					{
						if (!strcmp(car->grade, input_s))
						{
							cars_id[cars_id_number] = car->id;
							cars_id_number++;
						}
					} while ((car = car->rear) != NULL);
					browse_cars(cars_id, cars_id_number);
					init_find_interface();
					break;
				case 14: //排量
					popup_input_float("请输入排量:", &input_f, MAX_CAR_EMISSION);
					do
					{
						if (car->emission == input_i)
						{
							cars_id[cars_id_number] = car->id;
							cars_id_number++;
						}
					} while ((car = car->rear) != NULL);
					browse_cars(cars_id, cars_id_number);
					init_find_interface();
					break;
				case 17: //车身颜色
					popup_input_str("请输入车身颜色:", input_s, MAX_CAR_COLOUR);
					do
					{
						if (!strcmp(car->colour, input_s))
						{
							cars_id[cars_id_number] = car->id;
							cars_id_number++;
						}
					} while ((car = car->rear) != NULL);
					browse_cars(cars_id, cars_id_number);
					init_find_interface();
					break;
				case 20: //返回
					return;
				}
			}
			if (!ReadConsoleInput(hIn, &Buf, 1, &Result)) break;
		}
	}
}

void set_car(PCAR car)
{
	CAR car_inof = *car; //获得要修改的车信息
	init_set_interface(&car_inof);
	while (1)
	{
		ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
		set_cursor(); //根据鼠标位置绘制添加车辆界面的光标
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
		{
			if (mouse_pos.Y > 7 && mouse_pos.Y < 23 && 0 == mouse_pos.Y % 2)
			{
				if (mouse_pos.X > 78 && mouse_pos.X < 85) //输入
				{
					car_input(&car_inof, mouse_pos.Y);
				}
				else if (mouse_pos.X > 85 && mouse_pos.X < 92) //清空
				{
					car_empty(&car_inof, mouse_pos.Y);
					init_set_interface(&car_inof);
				}
			}
			else if (24 == mouse_pos.Y)
			{
				if (mouse_pos.X > 59 && mouse_pos.X < 66)  //确定
				{
					*car = car_inof;
					popup_prompt("汽车修改成功...");
					return;
				}
				else if (mouse_pos.X > 69 && mouse_pos.X < 76) //返回
				{
					return;
				}
			}
			if (!ReadConsoleInput(hIn, &Buf, 1, &Result)) break;
		}
	}
}

int del_car(PCAR car)
{
	init_del_interface();
	while (1)
	{
		ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
		del_cursor(); //根据鼠标位置绘制添加车辆界面的光标
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
		{
			if (15 == mouse_pos.Y)
			{
				if (mouse_pos.X > 61 && mouse_pos.X < 68) //确定
				{
					del_list(car);
					popup_prompt("删除车辆成功...");
					return 1;
				}
				else if (mouse_pos.X > 73 && mouse_pos.X < 80) //取消
				{
					return 0;
				}
			}
			if (!ReadConsoleInput(hIn, &Buf, 1, &Result)) break;
		}
	}
}

int exit_app()
{
	exit_app_interface();
	while (1)
	{
		ReadConsoleInput(hIn, &Buf, 1, &Result); //读取操作事件
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //获得鼠标位置
		exit_cursor();
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键点击
		{
			if (15 == mouse_pos.Y)
			{
				if (mouse_pos.X > 60 && mouse_pos.X < 65) //是
				{
					save_car();
					return 1;
				}
				else if (mouse_pos.X > 67 && mouse_pos.X < 72) //否
				{
					return 1;
				}
				else if (mouse_pos.X > 74 && mouse_pos.X < 81) //取消
				{
					return 0;
				}
			}
			if (!ReadConsoleInput(hIn, &Buf, 1, &Result)) break;
		}
	}
	return 0;
}

