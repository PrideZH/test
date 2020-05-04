#include "function.h"
#include "ui.h"

void add_car()
{
	PCAR car = (PCAR)calloc(1, sizeof(CAR));
	car->id = get_id(); //获得汽车编号
	draw_set_windows(car);
	while (1)
	{
		draw_set_button(); //绘制按钮
		switch (set_click()) 
		{
		case INPUT_BUTTON: //输入
			car_input(car, mouse_pos.Y);
			break;
		case EMPTY_BUTTON: //清空
			car_empty(car, mouse_pos.Y);
			break;
		case CONFIRM_BUTTON: //确定
			add_list(car);
			popup_prompt("汽车添加成功...");
			return;
		case RETURN_BUTTON: //返回
			return;
		}
	}
}

void car_input(PCAR car, int position)
{
	switch (position)
	{
	case 8:
		popup_input_str("请输入车辆型号:", car->type, MAX_CAR_TYPE);
		break;
	case 10:
		popup_input_str("请输入厂商:", car->manufacturer, MAX_CAR_MANUFACTURER);
		break;
	case 12:
		popup_input_str("请输入车辆级别:", car->grade, MAX_CAR_GRADE);
		break;
	case 14:
		popup_input_int("请输入车辆座位数:", &car->seat, MAX_CAR_SEAT);
		if (car->seat < 0)
		{
			car->seat = 0;
		}
		break;
	case 16:
		popup_input_float("请输入排量(L):", &car->emission, MAX_CAR_EMISSION );
		if (car->emission < 0)
		{
			car->emission = 0;
		}
		break;
	case 18:
		popup_input_str("请输入车辆变速箱:", car->gearbox, MAX_CAR_GEARBOX);
		break;
	case 20:
		popup_input_str("请输入车身颜色:", car->colour, MAX_CAR_COLOUR);
		break;
	case 22:
		popup_input_float("请输入车辆价格(万):", &car->price, MAX_CAR_PRICE);
		if (car->price < 0)
		{
			car->price = 0;
		}
		break;
	}
	draw_set_windows(car);
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
	draw_set_windows(car);
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
	draw_browse_windows(); //绘制浏览车辆界面
	while (1)
	{
		draw_browse_page(page, all_page); //页数信息显示
		draw_browse_sort(mode); //更新排序方式显示信息
		browse_print_cars(cars, page_cars_number, page); //显示第一页车辆
		draw_browse_button(page_cars_number); //绘制按钮
		switch (browse_click())
		{
		case SORT_ID_BUTTON: //编号排序
			browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2));
			break;
		case SORT_SEAT_BUTTON: //座位数排序
			browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2) + 2);
			break;
		case SORT_EMISSION_BUTTON: //排量排序
			browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2) + 4);
			break;
		case SORT_PRICE_BUTTON: //价格排序
			browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2) + 6);
			break;
		case SET_BUTTON: //修改
			if (mouse_pos.Y < 5 + page_cars_number)
			{
				set_car(cars[mouse_pos.Y - 5 + page * 20]);
			}
			draw_browse_windows();
			break;
		case DELETE_BUTTON: //删除
			if (mouse_pos.Y < 5 + page_cars_number)
			{
				int position = mouse_pos.Y - 5 + page * 20;
				if (del_car(cars[position])) //删除成功时去除此车辆下标
				{
					for (int j = position; j < cars_number; j++)
					{
						cars[j] = cars[j + 1];
					}
					if (0 == --cars_number) return; //没有车辆时返回上一菜单
					all_page = (cars_number - 1) / 20; //计算总页数
					if (page > all_page) page--; //如果当前页无车辆时，转到上一页
					page_cars_number = page == all_page ? cars_number - page * 20 : 20; //计算当前页汽车数量
				}
			}
			draw_browse_windows();
			break;
		case PREVIOUS_BUTTON: //上一页
			if (page > 0)
			{
				page--;
				draw_browse_windows();
				page_cars_number = page == all_page ? cars_number - page * 20 : 20; //计算当前页汽车数量
			}
			break;
		case NEXT_BUTTON: //下一页
			if (page < all_page)
			{
				page++;
				draw_browse_windows();
				page_cars_number = page == all_page ? cars_number - page * 20 : 20; //计算当前页汽车数量
			}
			break;
		case RETURN_BUTTON: //返回
			return;
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
	draw_find_windows();
	while (1)
	{
		PCAR car = head->rear;
		int cars_number = 0;
		draw_find_button(); //绘制按钮
		switch (find_click()) //判断鼠标点击
		{
		case FIND_ID_BUTTON: //编号
			popup_input_int("请输入编号:", &input_i, 4);
			do {
				if (car->id == input_i) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_MANUFACTURER_BUTTON: //厂商
			popup_input_str("请输入厂商:", input_s, MAX_CAR_MANUFACTURER);
			do {
				if (!strcmp(car->type, input_s)) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_SEAT_BUTTON: //查询车辆
			popup_input_int("请输入座位数:", &input_i, MAX_CAR_SEAT);
			do {
				if (car->seat == input_i) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_GEARBOX_BUTTON: //变速箱
			popup_input_str("请输入变速箱:", input_s, MAX_CAR_GEARBOX);
			do {
				if (!strcmp(car->gearbox, input_s)) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_PRICE_BUTTON: //车辆价格
			popup_input_float("请输入车辆价格:", &input_f, MAX_CAR_PRICE);
			do {
				if (car->price == input_f) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_TYPE_BUTTON: //车辆型号
			popup_input_str("请输入车辆型号:", input_s, MAX_CAR_TYPE);
			do {
				if (!strcmp(car->type, input_s)) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_GRADE_BUTTON: //车型级别
			popup_input_str("请输入车型级别:", input_s, MAX_CAR_GRADE);
			do {
				if (!strcmp(car->grade, input_s)) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_EMISSION_BUTTON: //排量
			popup_input_float("请输入排量:", &input_f, MAX_CAR_EMISSION);
			do {
				if (car->emission == input_f) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_COLOUR_BUTTON: //车身颜色
			popup_input_str("请输入车身颜色:", input_s, MAX_CAR_COLOUR);
			do {
				if (!strcmp(car->colour, input_s)) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case RETURN_BUTTON: //返回
			return;
		}
	}
}

void set_car(PCAR car)
{
	CAR car_inof = *car; //获得要修改的车信息
	draw_set_windows(&car_inof);
	while (1)
	{
		draw_set_button(); //根据鼠标位置绘制添加车辆界面的光标
		switch (set_click())
		{
		case INPUT_BUTTON: //输入
			car_input(&car_inof, mouse_pos.Y);
			break;
		case EMPTY_BUTTON: //清空
			car_empty(&car_inof, mouse_pos.Y);
			draw_set_windows(&car_inof);
			break;
		case CONFIRM_BUTTON: //确定
			*car = car_inof;
			popup_prompt("汽车修改成功...");
			return;
		case RETURN_BUTTON: //返回
			return;
		}
	}
}

int del_car(PCAR car)
{
	draw_del_windows();
	while (1)
	{
		draw_del_button(); //绘制按钮
		switch(del_click())
		{
		case CONFIRM_BUTTON: //确定
			del_list(car);
			popup_prompt("删除车辆成功...");
			return 1;
		case RETURN_BUTTON: //取消
			return 0;
		}
	}
}

int exit_app()
{
	draw_exit_windows();
	while (1)
	{
		draw_exit_button();
		switch (exit_click())
		{
		case YES: //是
			save_car();
			return 1;
		case NO: //否
			return 1;
		case CANCEL: //取消
			return 0;
		}
	}
	return 0;
}

