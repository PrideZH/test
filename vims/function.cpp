#include "function.h"
#include "ui.h"

void add_car_fun()
{
	PCAR car = (PCAR)calloc(1, sizeof(CAR));
	car->id = get_id(); //����������
	draw_set_windows(car);
	while (1)
	{
		draw_set_button(); //���ư�ť
		switch (set_click()) 
		{
		case INPUT_BUTTON: //����
			car_input(car, mouse_pos.Y);
			draw_set_windows(car);
			break;
		case EMPTY_BUTTON: //���
			car_empty(car, mouse_pos.Y);
			draw_set_windows(car);
			break;
		case CONFIRM_BUTTON: //ȷ��
			add_car(head, car);
			popup_prompt("������ӳɹ�...");
			return;
		case RETURN_BUTTON: //����
			return;
		}
	}
}

void car_input(PCAR car, int position)
{
	switch (position)
	{
	case 8:
		popup_input_str("�����복���ͺ�:", car->type, MAX_CAR_TYPE);
		break;
	case 10:
		popup_input_str("�����볧��:", car->manufacturer, MAX_CAR_MANUFACTURER);
		break;
	case 12:
		popup_input_str("�����복������:", car->grade, MAX_CAR_GRADE);
		break;
	case 14:
		popup_input_int("�����복����λ��:", &car->seat, MAX_CAR_SEAT);
		if (car->seat < 0) car->seat = 0; //����С��0ʱ��0����
		break;
	case 16:
		popup_input_float("����������(L):", &car->emission, MAX_CAR_EMISSION );
		if (car->emission < 0) car->emission = 0; //����С��0ʱ��0����
		break;
	case 18:
		popup_input_str("�����복��������:", car->gearbox, MAX_CAR_GEARBOX);
		break;
	case 20:
		popup_input_str("�����복����ɫ:", car->colour, MAX_CAR_COLOUR);
		break;
	case 22:
		popup_input_float("�����복���۸�(��):", &car->price, MAX_CAR_PRICE);
		if (car->price < 0) car->price = 0; //����С��0ʱ��0����
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
	if (head->rear == NULL) //�޳�����Ϣʱ������ʾ������
	{
		popup_prompt("�޳�����Ϣ���޷���ѯ...");
		return ;
	}
	sort(head, ID_ORDER); //��id˳������
	SORT sort_mode = ID_ORDER; //��������ʽ
	int page = 0; //��ǰҳ��
	int cars_number = get_list_length(head); //��������
	int all_page = (cars_number - 1) / 20; //��ҳ��
	int page_cars_number = page == all_page ? cars_number - page * 20 : 20; //��ǰҳ��������
	draw_browse_windows(); //���������������
	while (1)
	{
		draw_browse_page(page, all_page); //����ҳ����Ϣ
		draw_browse_sort(sort_mode); //��������ʽ��ʾ��Ϣ
		browse_print_cars(head, page); //��ʾָ��ҳ�泵��
		draw_browse_button(page_cars_number); //���ư�ť
		switch (browse_click())
		{
		case SORT_ID_BUTTON: //�������
			if (sort_mode != ID_ORDER) sort(head, sort_mode = ID_ORDER);
			else sort(head, sort_mode = ID_INVERTED);
			break;
		case SORT_SEAT_BUTTON: //��λ������
			if (sort_mode != SEAT_ORDER) sort(head, sort_mode = SEAT_ORDER);
			else sort(head, sort_mode = SEAT_INVERTED);
			break;
		case SORT_EMISSION_BUTTON: //��������
			if (sort_mode != EMISSION_ORDER) sort(head, sort_mode = EMISSION_ORDER);
			else sort(head, sort_mode = EMISSION_INVERTED);
			break;
		case SORT_PRICE_BUTTON: //�۸�����
			if (sort_mode != PRICE_ORDER) sort(head, sort_mode = PRICE_ORDER);
			else sort(head, sort_mode = PRICE_INVERTED);
			break;
		case SET_BUTTON: //�޸�
			if (mouse_pos.Y < 5 + page_cars_number)
			{
				set_car_fun(get_car(head, mouse_pos.Y - 5 + page * 20));
			}
			draw_browse_windows();
			break;
		case DELETE_BUTTON: //ɾ��
			if (mouse_pos.Y < 5 + page_cars_number)
			{
				if (del_car_fun(get_car(head, mouse_pos.Y - 5 + page * 20)))
				{
					if (0 == --cars_number) return; //û�г���ʱ������һ�˵�
					all_page = (cars_number - 1) / 20; //������ҳ��
					if (page > all_page) page--; //�����ǰҳ�޳���ʱ��ת����һҳ
					page_cars_number = page == all_page ? cars_number - page * 20 : 20; //���㵱ǰҳ��������
				}
			}
			draw_browse_windows();
			break;
		case PREVIOUS_BUTTON: //��һҳ
			if (page > 0)
			{
				page--;
				draw_browse_windows();
				page_cars_number = page == all_page ? cars_number - page * 20 : 20; //���㵱ǰҳ��������
			}
			break;
		case NEXT_BUTTON: //��һҳ
			if (page < all_page)
			{
				page++;
				draw_browse_windows();
				page_cars_number = page == all_page ? cars_number - page * 20 : 20; //���㵱ǰҳ��������
			}
			break;
		case RETURN_BUTTON: //����
			return;
		}
	}
}

void find_car_fun()
{
	Data data; //�û�����Ĳ�ѯ��Ϣ
	PCAR list; //��ѯ��������
	draw_find_windows(); //���Ʋ�ѯ���洰��
	while (1)
	{
		draw_find_button(); //���ư�ť
		switch (find_click()) //�ж������
		{
		case FIND_ID_BUTTON: //���
			popup_input_int("��������:", &data.i, 4); //���������ѯ��Ϣ
			list = get_list(ID, data); //��ȡ���и���Ϣ��������
			find_car_browse(list);
			break;
		case FIND_TYPE_BUTTON: //�����ͺ�
			popup_input_str("�����복���ͺ�:", data.s, MAX_CAR_TYPE);
			list = get_list(TYPE, data);
			find_car_browse(list);
			break;
		case FIND_MANUFACTURER_BUTTON: //����
			popup_input_str("�����볧��:", data.s, MAX_CAR_MANUFACTURER);
			list = get_list(MANUFACTURER, data);
			find_car_browse(list);
			break;
		case FIND_SEAT_BUTTON: //��ѯ����
			popup_input_int("��������λ��:", &data.i, MAX_CAR_SEAT);
			list = get_list(SEAT, data);
			find_car_browse(list);
			break;
		case FIND_GEARBOX_BUTTON: //������
			popup_input_str("�����������:", data.s, MAX_CAR_GEARBOX);
			list = get_list(GEARBOX, data);
			find_car_browse(list);
			break;
		case FIND_PRICE_BUTTON: //�����۸�
			popup_input_float("�����복���۸�:", &data.f, MAX_CAR_PRICE);
			list = get_list(PRICE, data);
			find_car_browse(list);
			break;
		case FIND_GRADE_BUTTON: //���ͼ���
			popup_input_str("�����복�ͼ���:", data.s, MAX_CAR_GRADE);
			list = get_list(GRADE, data);
			find_car_browse(list);
			break;
		case FIND_EMISSION_BUTTON: //����
			popup_input_float("����������:", &data.f, MAX_CAR_EMISSION);
			list = get_list(EMISSION, data);
			find_car_browse(list);
			break;
		case FIND_COLOUR_BUTTON: //������ɫ
			popup_input_str("�����복����ɫ:", data.s, MAX_CAR_COLOUR);
			list = get_list(COLOUR, data);
			find_car_browse(list);
			break;
		case RETURN_BUTTON: //����
			return;
		}
	}
}

void find_car_browse(PCAR list)
{
	browse_car_fun(list); //�������
	add_list(list); //������Ż�������
	draw_find_windows(); //���Ʋ�ѯ���洰��
}

void set_car_fun(PCAR car)
{
	CAR car_inof = *car; //���Ҫ�޸ĵĳ���Ϣ
	draw_set_windows(&car_inof);
	while (1)
	{
		draw_set_button(); //���ư�ť
		switch (set_click())
		{
		case INPUT_BUTTON: //����
			car_input(&car_inof, mouse_pos.Y);
			break;
		case EMPTY_BUTTON: //���
			car_empty(&car_inof, mouse_pos.Y);
			draw_set_windows(&car_inof);
			break;
		case CONFIRM_BUTTON: //ȷ��
			*car = car_inof;
			popup_prompt("�����޸ĳɹ�...");
			return;
		case RETURN_BUTTON: //����
			return;
		}
	}
}

int del_car_fun(PCAR car)
{
	draw_del_windows();
	while (1)
	{
		draw_del_button(); //���ư�ť
		switch(del_click())
		{
		case CONFIRM_BUTTON: //ȷ��
			del_car(car);
			popup_prompt("ɾ�������ɹ�...");
			return 1;
		case RETURN_BUTTON: //ȡ��
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
		case YES: //��
			save_car();
			return 1;
		case NO: //��
			return 1;
		case CANCEL: //ȡ��
			return 0;
		}
	}
	return 0;
}

