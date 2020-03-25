#include "function.h"
#include "ui.h"

void add_car()
{
	PCAR car = (PCAR)calloc(1, sizeof(CAR));
	car->id = get_id(); //����������
	init_set_interface(car);
	while (1)
	{
		ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
		set_cursor(); //�������λ�û�����ӳ�������Ĺ��
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
		{
			if (mouse_pos.Y > 7 && mouse_pos.Y < 23 && 0 == mouse_pos.Y % 2)
			{
				if (mouse_pos.X > 78 && mouse_pos.X < 85) //����
				{
					car_input(car, mouse_pos.Y); 
				}
				else if (mouse_pos.X > 85 && mouse_pos.X < 92) //���
				{
					car_empty(car, mouse_pos.Y);
					init_set_interface(car);
				}
			}
			else if (24 == mouse_pos.Y)
			{
				if (mouse_pos.X > 59 && mouse_pos.X < 66)  //ȷ��
				{
					add_list(car);
					popup_prompt("������ӳɹ�...");
					return;
				}
				else if (mouse_pos.X > 69 && mouse_pos.X < 76) //����
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
		popup_input_str("�����복���ͺ�:", car->type, MAX_CAR_TYPE);
		init_set_interface(car);
		break;
	case 10:
		popup_input_str("�����볧��:", car->manufacturer, MAX_CAR_MANUFACTURER);
		init_set_interface(car);
		break;
	case 12:
		popup_input_str("�����복������:", car->grade, MAX_CAR_GRADE);
		init_set_interface(car);
		break;
	case 14:
		popup_input_int("�����복����λ��:", &car->seat, MAX_CAR_SEAT);
		init_set_interface(car);
		if (car->seat < 0)
		{
			car->seat = 0;
		}
		break;
	case 16:
		popup_input_float("����������(L):", &car->emission, MAX_CAR_EMISSION );
		init_set_interface(car);
		if (car->emission < 0)
		{
			car->emission = 0;
		}
		break;
	case 18:
		popup_input_str("�����복��������:", car->gearbox, MAX_CAR_GEARBOX);
		init_set_interface(car);
		break;
	case 20:
		popup_input_str("�����복����ɫ:", car->colour, MAX_CAR_COLOUR);
		init_set_interface(car);
		break;
	case 22:
		popup_input_float("�����복���۸�(��):", &car->price, MAX_CAR_PRICE);
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
	init_browse_interface(); //���������������
	update_browse_page(page, all_page); //ҳ����Ϣ��ʾ
	browse_print_cars(cars, page_cars_number, page); //��ʾ��һҳ����
	while (1)
	{
		ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
		browse_cursor(page_cars_number); //�������λ�û��Ʋ˵����
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
		{
			if (3 == mouse_pos.Y) //�������
			{
				if (mouse_pos.X > 8 && mouse_pos.X < 13)  //���
				{
					browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2));
					browse_print_cars(cars, page_cars_number, page); //��ʾ����
					update_browse_sort(mode); //��������ʽ��ʾ��Ϣ
				}
				else if (mouse_pos.X > 63 && mouse_pos.X < 70) //��λ��
				{
					browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2) + 2);
					browse_print_cars(cars, page_cars_number, page); //��ʾ����
					update_browse_sort(mode); //��������ʽ��ʾ��Ϣ
				}
				else if (mouse_pos.X > 72 && mouse_pos.X < 80) //����
				{
					browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2) + 4);
					browse_print_cars(cars, page_cars_number, page); //��ʾ����
					update_browse_sort(mode); //��������ʽ��ʾ��Ϣ
				}
				else if (mouse_pos.X > 106 && mouse_pos.X < 115) //�����۸�
				{
					browse_qsort(cars, 0, cars_number - 1, mode = !(mode % 2) + 6);
					browse_print_cars(cars, page_cars_number, page); //��ʾ����
					update_browse_sort(mode); //��������ʽ��ʾ��Ϣ
				}
			}
			else if (mouse_pos.Y > 4 && mouse_pos.Y < 26 && mouse_pos.Y < 5 + page_cars_number)
			{
				if (mouse_pos.X > 123 && mouse_pos.X < 128) //�޸�
				{
					set_car(cars[mouse_pos.Y - 5 + page * 20]);
					init_browse_interface();
					update_browse_page(page, all_page); //����ҳ����ʾ
					update_browse_sort(mode); //��������ʽ��ʾ��Ϣ
					browse_print_cars(cars, page_cars_number, page); //��ʾ����
				}
				else if (mouse_pos.X > 128 && mouse_pos.X < 133) //ɾ��
				{
					int position = mouse_pos.Y - 5 + page * 20;
					if (del_car(cars[position])) //ɾ���ɹ�ʱȥ���˳����±�
					{
						for (int j = position; j < cars_number; j++)
						{
							cars[j] = cars[j + 1];
						}
						if (0 == --cars_number) return; //û�г���ʱ������һ�˵�
						init_browse_interface();
						all_page = (cars_number - 1) / 20; //������ҳ��
						if (page > all_page) page--; //�����ǰҳ�޳���ʱ��ת����һҳ
						page_cars_number = page == all_page ? cars_number - page * 20 : 20; //���㵱ǰҳ��������
					}
					init_browse_interface();
					update_browse_page(page, all_page); //����ҳ����ʾ
					update_browse_sort(mode); //��������ʽ��ʾ��Ϣ
					browse_print_cars(cars, page_cars_number, page); //��ʾ����
				}
			}
			else if (26 == mouse_pos.Y) //��ҳ�ͷ��ز���
			{
				if (mouse_pos.X > 59 && mouse_pos.X < 66) //��һҳ
				{
					if (page > 0)
					{
						page--;
						init_browse_interface();
						page_cars_number = page == all_page ? cars_number - page * 20 : 20; //���㵱ǰҳ��������
						browse_print_cars(cars, page_cars_number, page); //��ʾ����
						update_browse_page(page, all_page); //����ҳ����ʾ
						update_browse_sort(mode); //��������ʽ��ʾ��Ϣ
					}
				}
				else if (mouse_pos.X > 76 && mouse_pos.X < 83) //��һҳ
				{
					if (page < all_page)
					{
						page++;
						init_browse_interface();
						page_cars_number = page == all_page ? cars_number - page * 20 : 20; //���㵱ǰҳ��������
						browse_print_cars(cars, page_cars_number, page); //��ʾ����
						update_browse_page(page, all_page); //����ҳ����ʾ
						update_browse_sort(mode); //��������ʽ��ʾ��Ϣ
					}
				}
				else if (mouse_pos.X > 120 && mouse_pos.X < 125) //����  
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
		ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
		find_cursor(); //�������λ�û��Ʋ�ѯ�����Ĺ��
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
		{
			if (mouse_pos.X > 54 && mouse_pos.X < 67)
			{
				switch (mouse_pos.Y) 
				{
				case 8: //���
					popup_input_int("��������:", &input_i, 4);
					do {
						if (car->id == input_i) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 11: //����
					popup_input_str("�����볧��:", input_s, MAX_CAR_MANUFACTURER);
					do {
						if (!strcmp(car->type, input_s)) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 14: //��λ��
					popup_input_int("��������λ��:", &input_i, MAX_CAR_SEAT);
					do {
						if (car->seat == input_i) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 17: //������
					popup_input_str("�����������:", input_s, MAX_CAR_GEARBOX);
					do {
						if (!strcmp(car->gearbox, input_s)) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 20: //�����۸�
					popup_input_float("�����복���۸�:", &input_f, MAX_CAR_PRICE);
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
				case 8: //�����ͺ�
					popup_input_str("�����복���ͺ�:", input_s, MAX_CAR_TYPE);
					do {
						if (!strcmp(car->type, input_s)) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 11: //���ͼ���
					popup_input_str("�����복�ͼ���:", input_s, MAX_CAR_GRADE);
					do {
						if (!strcmp(car->grade, input_s)) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 14: //����
					popup_input_float("����������:", &input_f, MAX_CAR_EMISSION);
					do {
						if (car->emission == input_f) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 17: //������ɫ
					popup_input_str("�����복����ɫ:", input_s, MAX_CAR_COLOUR);
					do {
						if (!strcmp(car->colour, input_s)) cars[cars_number++] = car;
					} while ((car = car->rear) != NULL);
					browse_cars(cars, cars_number);
					init_find_interface();
					break;
				case 20: //����
					return;
				}
			}
			if (!ReadConsoleInput(hIn, &Buf, 1, &Result)) break;
		}
	}
}

void set_car(PCAR car)
{
	CAR car_inof = *car; //���Ҫ�޸ĵĳ���Ϣ
	init_set_interface(&car_inof);
	while (1)
	{
		ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
		set_cursor(); //�������λ�û�����ӳ�������Ĺ��
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
		{
			if (mouse_pos.Y > 7 && mouse_pos.Y < 23 && 0 == mouse_pos.Y % 2)
			{
				if (mouse_pos.X > 78 && mouse_pos.X < 85) //����
				{
					car_input(&car_inof, mouse_pos.Y);
				}
				else if (mouse_pos.X > 85 && mouse_pos.X < 92) //���
				{
					car_empty(&car_inof, mouse_pos.Y);
					init_set_interface(&car_inof);
				}
			}
			else if (24 == mouse_pos.Y)
			{
				if (mouse_pos.X > 59 && mouse_pos.X < 66)  //ȷ��
				{
					*car = car_inof;
					popup_prompt("�����޸ĳɹ�...");
					return;
				}
				else if (mouse_pos.X > 69 && mouse_pos.X < 76) //����
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
		ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
		del_cursor(); //�������λ�û�����ӳ�������Ĺ��
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
		{
			if (15 == mouse_pos.Y)
			{
				if (mouse_pos.X > 61 && mouse_pos.X < 68) //ȷ��
				{
					del_list(car);
					popup_prompt("ɾ�������ɹ�...");
					return 1;
				}
				else if (mouse_pos.X > 73 && mouse_pos.X < 80) //ȡ��
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
		ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
		exit_cursor();
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
		{
			if (15 == mouse_pos.Y)
			{
				if (mouse_pos.X > 60 && mouse_pos.X < 65) //��
				{
					save_car();
					return 1;
				}
				else if (mouse_pos.X > 67 && mouse_pos.X < 72) //��
				{
					return 1;
				}
				else if (mouse_pos.X > 74 && mouse_pos.X < 81) //ȡ��
				{
					return 0;
				}
			}
			if (!ReadConsoleInput(hIn, &Buf, 1, &Result)) break;
		}
	}
	return 0;
}

