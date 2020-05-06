#include "function.h"
#include "ui.h"

void add_car_fun()
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
			draw_set_windows(car);
			break;
		case EMPTY_BUTTON: //清空
			car_empty(car, mouse_pos.Y);
			draw_set_windows(car);
			break;
		case CONFIRM_BUTTON: //确定
			add_car(head, car);
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
		if (car->seat < 0) car->seat = 0; //输入小于0时按0处理
		break;
	case 16:
		popup_input_float("请输入排量(L):", &car->emission, MAX_CAR_EMISSION );
		if (car->emission < 0) car->emission = 0; //输入小于0时按0处理
		break;
	case 18:
		popup_input_str("请输入车辆变速箱:", car->gearbox, MAX_CAR_GEARBOX);
		break;
	case 20:
		popup_input_str("请输入车身颜色:", car->colour, MAX_CAR_COLOUR);
		break;
	case 22:
		popup_input_float("请输入车辆价格(万):", &car->price, MAX_CAR_PRICE);
		if (car->price < 0) car->price = 0; //输入小于0时按0处理
		break;
	}
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

void browse_car_fun(PCAR head)
{
	if (head->rear == NULL) //无车辆信息时弹窗提示并返回
	{
		popup_prompt("无车辆信息，无法查询...");
		return ;
	}
	sort(head, ID_ORDER); //按id顺序排序
	SORT sort_mode = ID_ORDER; //车辆排序方式
	int page = 0; //当前页数
	int cars_number = get_list_length(head); //车辆总数
	int all_page = (cars_number - 1) / 20; //总页数
	int page_cars_number = page == all_page ? cars_number - page * 20 : 20; //当前页车辆个数
	draw_browse_windows(); //绘制浏览车辆界面
	while (1)
	{
		draw_browse_page(page, all_page); //绘制页数信息
		draw_browse_sort(sort_mode); //绘制排序方式显示信息
		browse_print_cars(head, page); //显示指定页面车辆
		draw_browse_button(page_cars_number); //绘制按钮
		switch (browse_click())
		{
		case SORT_ID_BUTTON: //编号排序
			if (sort_mode != ID_ORDER) sort(head, sort_mode = ID_ORDER);
			else sort(head, sort_mode = ID_INVERTED);
			break;
		case SORT_SEAT_BUTTON: //座位数排序
			if (sort_mode != SEAT_ORDER) sort(head, sort_mode = SEAT_ORDER);
			else sort(head, sort_mode = SEAT_INVERTED);
			break;
		case SORT_EMISSION_BUTTON: //排量排序
			if (sort_mode != EMISSION_ORDER) sort(head, sort_mode = EMISSION_ORDER);
			else sort(head, sort_mode = EMISSION_INVERTED);
			break;
		case SORT_PRICE_BUTTON: //价格排序
			if (sort_mode != PRICE_ORDER) sort(head, sort_mode = PRICE_ORDER);
			else sort(head, sort_mode = PRICE_INVERTED);
			break;
		case SET_BUTTON: //修改
			if (mouse_pos.Y < 5 + page_cars_number)
			{
				set_car_fun(get_car(head, mouse_pos.Y - 5 + page * 20));
			}
			draw_browse_windows();
			break;
		case DELETE_BUTTON: //删除
			if (mouse_pos.Y < 5 + page_cars_number)
			{
				if (del_car_fun(get_car(head, mouse_pos.Y - 5 + page * 20)))
				{
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

void find_car_fun()
{
	Data data; //用户输入的查询信息
	PCAR list; //查询所得链表
	draw_find_windows(); //绘制查询界面窗口
	while (1)
	{
		draw_find_button(); //绘制按钮
		switch (find_click()) //判断鼠标点击
		{
		case FIND_ID_BUTTON: //编号
			popup_input_int("请输入编号:", &data.i, 4); //弹窗输入查询信息
			list = get_list(ID, data); //获取所有该信息车辆链表
			find_car_browse(list);
			break;
		case FIND_TYPE_BUTTON: //车辆型号
			popup_input_str("请输入车辆型号:", data.s, MAX_CAR_TYPE);
			list = get_list(TYPE, data);
			find_car_browse(list);
			break;
		case FIND_MANUFACTURER_BUTTON: //厂商
			popup_input_str("请输入厂商:", data.s, MAX_CAR_MANUFACTURER);
			list = get_list(MANUFACTURER, data);
			find_car_browse(list);
			break;
		case FIND_SEAT_BUTTON: //查询车辆
			popup_input_int("请输入座位数:", &data.i, MAX_CAR_SEAT);
			list = get_list(SEAT, data);
			find_car_browse(list);
			break;
		case FIND_GEARBOX_BUTTON: //变速箱
			popup_input_str("请输入变速箱:", data.s, MAX_CAR_GEARBOX);
			list = get_list(GEARBOX, data);
			find_car_browse(list);
			break;
		case FIND_PRICE_BUTTON: //车辆价格
			popup_input_float("请输入车辆价格:", &data.f, MAX_CAR_PRICE);
			list = get_list(PRICE, data);
			find_car_browse(list);
			break;
		case FIND_GRADE_BUTTON: //车型级别
			popup_input_str("请输入车型级别:", data.s, MAX_CAR_GRADE);
			list = get_list(GRADE, data);
			find_car_browse(list);
			break;
		case FIND_EMISSION_BUTTON: //排量
			popup_input_float("请输入排量:", &data.f, MAX_CAR_EMISSION);
			list = get_list(EMISSION, data);
			find_car_browse(list);
			break;
		case FIND_COLOUR_BUTTON: //车身颜色
			popup_input_str("请输入车身颜色:", data.s, MAX_CAR_COLOUR);
			list = get_list(COLOUR, data);
			find_car_browse(list);
			break;
		case RETURN_BUTTON: //返回
			return;
		}
	}
}

void find_car_browse(PCAR list)
{
	browse_car_fun(list); //浏览链表
	add_list(list); //将链表放回主链表
	draw_find_windows(); //绘制查询界面窗口
}

void set_car_fun(PCAR car)
{
	CAR car_inof = *car; //获得要修改的车信息
	draw_set_windows(&car_inof);
	while (1)
	{
		draw_set_button(); //绘制按钮
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

int del_car_fun(PCAR car)
{
	draw_del_windows();
	while (1)
	{
		draw_del_button(); //绘制按钮
		switch(del_click())
		{
		case CONFIRM_BUTTON: //确定
			del_car(car);
			popup_prompt("删除车辆成功...");
			return 1;
		case RETURN_BUTTON: //取消
			return 0;
		}
	}
}

int exit_fun()
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

