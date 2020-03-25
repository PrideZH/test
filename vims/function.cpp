#include "function.h"
#include "ui.h"

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

void browse_cars(PCAR *cars, int cars_number)
{
	if (NULL == cars) //如果cars参数为NULL，则获取所有车辆
	{
		cars = (PCAR *)malloc(get_all_car_number() * sizeof(PCAR)); 
		PCAR car = head->rear;
		for (int i = 0; car != NULL; car = car->rear, i++) cars[i] = car;
	}
	if (0 == cars_number) //无车辆信息时弹窗提示并返回
	{
		popup_prompt("无车辆信息，无法查询...");
		return ;
	}
	int mode = 0; //车辆排序方式
	int page = 0; //当前页数
	int all_page = (cars_number - 1) / 20; //计算总页数
	int page_cars_number = page == all_page ? cars_number - page * 20 : 20; //计算当前页汽车数量
	init_browse_interface(); //绘制浏览车辆界面
	update_browse_page(page, all_page); //页数信息显示
	browse_print_cars(cars, page_cars_number, page); //显示第一页车辆
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
					browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2));
					browse_print_cars(cars, page_cars_number, page); //显示车辆
					update_browse_sort(mode); //更新排序方式显示信息
				}
				else if (mouse_pos.X > 63 && mouse_pos.X < 70) //座位数
				{
					browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2) + 2);
					browse_print_cars(cars, page_cars_number, page); //显示车辆
					update_browse_sort(mode); //更新排序方式显示信息
				}
				else if (mouse_pos.X > 72 && mouse_pos.X < 80) //排量
				{
					browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2) + 4);
					browse_print_cars(cars, page_cars_number, page); //显示车辆
					update_browse_sort(mode); //更新排序方式显示信息
				}
				else if (mouse_pos.X > 106 && mouse_pos.X < 115) //车辆价格
				{
					browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2) + 6);
					browse_print_cars(cars, page_cars_number, page); //显示车辆
					update_browse_sort(mode); //更新排序方式显示信息
				}
			}
			else if (mouse_pos.Y > 4 && mouse_pos.Y < 26 && mouse_pos.Y < 5 + page_cars_number)
			{
				if (mouse_pos.X > 123 && mouse_pos.X < 128) //修改
				{
					set_car(cars[mouse_pos.Y - 5 + page * 20]);
					init_browse_interface();
					update_browse_page(page, all_page); //更新页数显示
					update_browse_sort(mode); //更新排序方式显示信息
					browse_print_cars(cars, page_cars_number, page); //显示车辆
				}
				else if (mouse_pos.X > 128 && mouse_pos.X < 133) //删除
				{
					int position = mouse_pos.Y - 5 + page * 20;
					if (del_car(cars[position])) //删除成功时去除此车辆下标
					{
						for (int j = position; j < cars_number; j++)
						{
							cars[j] = cars[j + 1];
						}
						if (0 == --cars_number) return; //没有车辆时返回上一菜单
						init_browse_interface();
						all_page = (cars_number - 1) / 20; //计算总页数
						if (page > all_page) page--; //如果当前页无车辆时，转到上一页
						page_cars_number = page == all_page ? cars_number - page * 20 : 20; //计算当前页汽车数量
					}
					init_browse_interface();
					update_browse_page(page, all_page); //更新页数显示
					update_browse_sort(mode); //更新排序方式显示信息
					browse_print_cars(cars, page_cars_number, page); //显示车辆
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
						page_cars_number = page == all_page ? cars_number - page * 20 : 20; //计算当前页汽车数量
						browse_print_cars(cars, page_cars_number, page); //显示车辆
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
						page_cars_number = page == all_page ? cars_number - page * 20 : 20; //计算当前页汽车数量
						browse_print_cars(cars, page_cars_number, page); //显示车辆
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

void browse_qsort(PCAR *cars, int _left, int _right, int mode)
{
	if (_left >= _right) return;
	int left = _left;
	int right = _right;
	PCAR pivot = get_pivot(cars, _left, _right, mode); 
	while (left < right)
	{
		switch (mode)
		{
		case 0:
			while (right > left && cars[right]->id >= pivot->id) right--;
			cars[left] = cars[right];
			while (right > left && cars[left]->id <= pivot->id) left++;
			cars[right] = cars[left];
			break;
		case 1:
			while (right > left && cars[right]->id <= pivot->id) right--;
			cars[left] = cars[right];
			while (right > left && cars[left]->id >= pivot->id) left++;
			cars[right] = cars[left];
			break;
		case 2:
			while (right > left && cars[right]->seat >= pivot->seat) right--;
			cars[left] = cars[right];
			while (right > left && cars[left]->seat <= pivot->seat) left++;
			cars[right] = cars[left];
			break;
		case 3:
			while (right > left && cars[right]->seat <= pivot->seat) right--;
			cars[left] = cars[right];
			while (right > left && cars[left]->seat >= pivot->seat) left++;
			cars[right] = cars[left];
			break;
		case 4:
			while (right > left && cars[right]->emission >= pivot->emission) right--;
			if(right > left) cars[left] = cars[right];
			while (right > left && cars[left]->emission <= pivot->emission) left++;
			if (right > left) cars[right] = cars[left];
			break;
		case 5:
			while (right > left && cars[right]->emission <= pivot->emission) right--;
			cars[left] = cars[right];
			while (right > left && cars[left]->emission >= pivot->emission) left++;
			cars[right] = cars[left];
			break;
		case 6:
			while (right > left && cars[right]->price >= pivot->price) right--;
			cars[left] = cars[right];
			while (right > left && cars[left]->price <= pivot->price) left++;
			cars[right] = cars[left];
			break;
		case 7:
			while (right > left && cars[right]->price <= pivot->price) right--;
			cars[left] = cars[right];
			while (right > left && cars[left]->price >= pivot->price) left++;
			cars[right] = cars[left];
			break;
		}
	}
	cars[left] = pivot;
	browse_qsort(cars, _left, right - 1, mode);
	browse_qsort(cars, left + 1, _right, mode);
}

PCAR get_pivot(PCAR *cars, int left, int right, int mode)
{
	int i_m, i_l, i_r;
	float f_m, f_l, f_r;
	switch (mode)
	{
	case 0:
	case 1:
		i_m = cars[(right - left) / 2]->id;
		i_r = cars[right]->id;
		i_l = cars[left]->id;
		if (i_l < i_m && i_m < i_r || i_r < i_m && i_m < i_l)
		{
			PCAR temp = cars[(right - left) / 2];
			cars[(right - left) / 2] = cars[left];
			cars[left] = temp;
		}
		else if (i_l < i_r && i_r < i_m || i_m < i_r && i_r < i_l)
		{
			PCAR temp = cars[right];
			cars[right] = cars[left];
			cars[left] = temp;
		}
		return cars[left];
	case 2:
	case 3:
		i_m = cars[(right - left) / 2]->seat;
		i_r = cars[right]->seat;
		i_l = cars[left]->seat;
		if (i_l < i_m && i_m < i_r || i_r < i_m && i_m < i_l)
		{
			PCAR temp = cars[(right - left) / 2];
			cars[(right - left) / 2] = cars[left];
			cars[left] = temp;
		}
		else if (i_l < i_r && i_r < i_m || i_m < i_r && i_r < i_l)
		{
			PCAR temp = cars[right];
			cars[right] = cars[left];
			cars[left] = temp;
		}
		return cars[left];
	case 4:
	case 5:
		f_m = cars[(right - left) / 2]->emission;
		f_r = cars[right]->emission;
		f_l = cars[left]->emission;
		if (f_l < f_m && f_m < f_r || f_r < f_m && f_m < f_l)
		{
			PCAR temp = cars[(right - left) / 2];
			cars[(right - left) / 2] = cars[left];
			cars[left] = temp;
		}
		else if (f_l < f_r && f_r < f_m || f_m < f_r && f_r < f_l)
		{
			PCAR temp = cars[right];
			cars[right] = cars[left];
			cars[left] = temp;
		}
		return cars[left];
	case 6:
	case 7:
		f_m = cars[(right - left) / 2]->price;
		f_r = cars[right]->price;
		f_l = cars[left]->price;
		if (f_l < f_m && f_m < f_r || f_r < f_m && f_m < f_l)
		{
			PCAR temp = cars[(right - left) / 2];
			cars[(right - left) / 2] = cars[left];
			cars[left] = temp;
		}
		else if (f_l < f_r && f_r < f_m || f_m < f_r && f_r < f_l)
		{
			PCAR temp = cars[right];
			cars[right] = cars[left];
			cars[left] = temp;
		}
		return cars[left];
	}
	return cars[left];
}

void find_car()
{
	int input_i;
	float input_f;
	char input_s[24];
	PCAR *cars = (PCAR *)malloc(get_all_car_number() * sizeof(PCAR)); 
	init_find_interface();
	while (1)
	{
		PCAR car = head->rear;
		int cars_number = 0;
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
					do {
						if (car->id == input_i) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 11: //厂商
					popup_input_str("请输入厂商:", input_s, MAX_CAR_MANUFACTURER);
					do {
						if (!strcmp(car->type, input_s)) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 14: //座位数
					popup_input_int("请输入座位数:", &input_i, MAX_CAR_SEAT);
					do {
						if (car->seat == input_i) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 17: //变速箱
					popup_input_str("请输入变速箱:", input_s, MAX_CAR_GEARBOX);
					do {
						if (!strcmp(car->gearbox, input_s)) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 20: //车辆价格
					popup_input_float("请输入车辆价格:", &input_f, MAX_CAR_PRICE);
					do {
						if (car->price == input_f) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
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
					do {
						if (!strcmp(car->type, input_s)) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 11: //车型级别
					popup_input_str("请输入车型级别:", input_s, MAX_CAR_GRADE);
					do {
						if (!strcmp(car->grade, input_s)) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 14: //排量
					popup_input_float("请输入排量:", &input_f, MAX_CAR_EMISSION);
					do {
						if (car->emission == input_f) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 17: //车身颜色
					popup_input_str("请输入车身颜色:", input_s, MAX_CAR_COLOUR);
					do {
						if (!strcmp(car->colour, input_s)) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
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

