#include "function.h"
#include "ui.h"

void add_car()
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
			break;
		case EMPTY_BUTTON: //���
			car_empty(car, mouse_pos.Y);
			break;
		case CONFIRM_BUTTON: //ȷ��
			add_list(car);
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
		if (car->seat < 0)
		{
			car->seat = 0;
		}
		break;
	case 16:
		popup_input_float("����������(L):", &car->emission, MAX_CAR_EMISSION );
		if (car->emission < 0)
		{
			car->emission = 0;
		}
		break;
	case 18:
		popup_input_str("�����복��������:", car->gearbox, MAX_CAR_GEARBOX);
		break;
	case 20:
		popup_input_str("�����복����ɫ:", car->colour, MAX_CAR_COLOUR);
		break;
	case 22:
		popup_input_float("�����복���۸�(��):", &car->price, MAX_CAR_PRICE);
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
	if (NULL == cars) //���cars����ΪNULL�����ȡ���г���
	{
		cars = (PCAR *)malloc(get_all_car_number() * sizeof(PCAR)); 
		PCAR car = head->rear;
		for (int i = 0; car != NULL; car = car->rear, i++) cars[i] = car;
	}
	if (0 == cars_number) //�޳�����Ϣʱ������ʾ������
	{
		popup_prompt("�޳�����Ϣ���޷���ѯ...");
		return ;
	}
	int mode = 0; //��������ʽ
	int page = 0; //��ǰҳ��
	int all_page = (cars_number - 1) / 20; //������ҳ��
	int page_cars_number = page == all_page ? cars_number - page * 20 : 20; //���㵱ǰҳ��������
	draw_browse_windows(); //���������������
	while (1)
	{
		draw_browse_page(page, all_page); //ҳ����Ϣ��ʾ
		draw_browse_sort(mode); //��������ʽ��ʾ��Ϣ
		browse_print_cars(cars, page_cars_number, page); //��ʾ��һҳ����
		draw_browse_button(page_cars_number); //���ư�ť
		switch (browse_click())
		{
		case SORT_ID_BUTTON: //�������
			browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2));
			break;
		case SORT_SEAT_BUTTON: //��λ������
			browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2) + 2);
			break;
		case SORT_EMISSION_BUTTON: //��������
			browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2) + 4);
			break;
		case SORT_PRICE_BUTTON: //�۸�����
			browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2) + 6);
			break;
		case SET_BUTTON: //�޸�
			if (mouse_pos.Y < 5 + page_cars_number)
			{
				set_car(cars[mouse_pos.Y - 5 + page * 20]);
			}
			draw_browse_windows();
			break;
		case DELETE_BUTTON: //ɾ��
			if (mouse_pos.Y < 5 + page_cars_number)
			{
				int position = mouse_pos.Y - 5 + page * 20;
				if (del_car(cars[position])) //ɾ���ɹ�ʱȥ���˳����±�
				{
					for (int j = position; j < cars_number; j++)
					{
						cars[j] = cars[j + 1];
					}
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
		draw_find_button(); //���ư�ť
		switch (find_click()) //�ж������
		{
		case FIND_ID_BUTTON: //���
			popup_input_int("��������:", &input_i, 4);
			do {
				if (car->id == input_i) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_MANUFACTURER_BUTTON: //����
			popup_input_str("�����볧��:", input_s, MAX_CAR_MANUFACTURER);
			do {
				if (!strcmp(car->type, input_s)) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_SEAT_BUTTON: //��ѯ����
			popup_input_int("��������λ��:", &input_i, MAX_CAR_SEAT);
			do {
				if (car->seat == input_i) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_GEARBOX_BUTTON: //������
			popup_input_str("�����������:", input_s, MAX_CAR_GEARBOX);
			do {
				if (!strcmp(car->gearbox, input_s)) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_PRICE_BUTTON: //�����۸�
			popup_input_float("�����복���۸�:", &input_f, MAX_CAR_PRICE);
			do {
				if (car->price == input_f) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_TYPE_BUTTON: //�����ͺ�
			popup_input_str("�����복���ͺ�:", input_s, MAX_CAR_TYPE);
			do {
				if (!strcmp(car->type, input_s)) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_GRADE_BUTTON: //���ͼ���
			popup_input_str("�����복�ͼ���:", input_s, MAX_CAR_GRADE);
			do {
				if (!strcmp(car->grade, input_s)) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_EMISSION_BUTTON: //����
			popup_input_float("����������:", &input_f, MAX_CAR_EMISSION);
			do {
				if (car->emission == input_f) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case FIND_COLOUR_BUTTON: //������ɫ
			popup_input_str("�����복����ɫ:", input_s, MAX_CAR_COLOUR);
			do {
				if (!strcmp(car->colour, input_s)) cars[cars_number++] = car;
			} while ((car = car->rear) != NULL);
			browse_cars(cars, cars_number);
			draw_find_windows();
			break;
		case RETURN_BUTTON: //����
			return;
		}
	}
}

void set_car(PCAR car)
{
	CAR car_inof = *car; //���Ҫ�޸ĵĳ���Ϣ
	draw_set_windows(&car_inof);
	while (1)
	{
		draw_set_button(); //�������λ�û�����ӳ�������Ĺ��
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

int del_car(PCAR car)
{
	draw_del_windows();
	while (1)
	{
		draw_del_button(); //���ư�ť
		switch(del_click())
		{
		case CONFIRM_BUTTON: //ȷ��
			del_list(car);
			popup_prompt("ɾ�������ɹ�...");
			return 1;
		case RETURN_BUTTON: //ȡ��
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

