#include "function.h"
#include "gui.h"

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

void browse_cars(int *cars_id, int cars_id_number)
{
	if (NULL == cars_id)
	{
		cars_id = (int *)malloc((get_all_car_number()) * sizeof(int));
		PCAR car = head->rear;
		for (int i = 0; car != NULL; car = car->rear, i++) //��ȡ���г����±�
		{
			cars_id[i] = car->id;
		}
	}
	if (0 == cars_id_number) //�޳�����Ϣʱ������ʾ������
	{
		popup_prompt("�޳�����Ϣ���޷���ѯ...");
		return ;
	}
	int mode = 0; //��������ʽ
	int page = 0; //��ǰҳ��
	int all_page = (cars_id_number - 1) / 20; //������ҳ��
	int page_cars_number = page == all_page ? cars_id_number - page * 20 : 20; //���㵱ǰҳ��������
	init_browse_interface(); //���������������
	update_browse_page(page, all_page); //ҳ����Ϣ��ʾ
	browse_print_cars(cars_id, page_cars_number, page); //��ʾ��һҳ����
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
					browse_sort(cars_id, cars_id_number, mode = !(mode % 2));
					browse_print_cars(cars_id, page_cars_number, page); //��ʾ����
				}
				else if (mouse_pos.X > 63 && mouse_pos.X < 70) //��λ��
				{
					browse_sort(cars_id, cars_id_number, mode = !(mode % 2) + 2);
					browse_print_cars(cars_id, page_cars_number, page); //��ʾ����
				}
				else if (mouse_pos.X > 72 && mouse_pos.X < 80) //����
				{
					browse_sort(cars_id, cars_id_number, mode = !(mode % 2) + 4);
					browse_print_cars(cars_id, page_cars_number, page); //��ʾ����
				}
				else if (mouse_pos.X > 106 && mouse_pos.X < 115) //�����۸�
				{
					browse_sort(cars_id, cars_id_number, mode = !(mode % 2) + 6);
					browse_print_cars(cars_id, page_cars_number, page); //��ʾ����
				}
			}
			else if (mouse_pos.Y > 4 && mouse_pos.Y < 26 && mouse_pos.Y < 5 + page_cars_number)
			{
				if (mouse_pos.X > 123 && mouse_pos.X < 128) //�޸�
				{
					set_car(get_car(cars_id[mouse_pos.Y - 5 + page * 20]));
					init_browse_interface();
					update_browse_page(page, all_page); //����ҳ����ʾ
					update_browse_sort(mode); //��������ʽ��ʾ��Ϣ
					browse_print_cars(cars_id, page_cars_number, page); //��ʾ����
				}
				else if (mouse_pos.X > 128 && mouse_pos.X < 133) //ɾ��
				{
					int position = mouse_pos.Y - 5 + page * 20;
					if (del_car(get_car(cars_id[position]))) //ɾ���ɹ�ʱȥ���˳����±�
					{
						for (int j = position; j < cars_id_number; j++)
						{
							cars_id[j] = cars_id[j + 1];
						}
						if (0 == --cars_id_number) return; //û�г���ʱ������һ�˵�
						init_browse_interface();
						all_page = (cars_id_number - 1) / 20; //������ҳ��
						if (page > all_page) page--; //�����ǰҳ�޳���ʱ��ת����һҳ
						update_browse_page(page, all_page); //����ҳ����ʾ
						update_browse_sort(mode); //��������ʽ��ʾ��Ϣ
						page_cars_number = page == all_page ? cars_id_number - page * 20 : 20; //���㵱ǰҳ��������
						browse_print_cars(cars_id, page_cars_number, page); //��ʾ����
					}
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
						page_cars_number = page == all_page ? cars_id_number - page * 20 : 20; //���㵱ǰҳ��������
						browse_print_cars(cars_id, page_cars_number, page); //��ʾ����
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
						page_cars_number = page == all_page ? cars_id_number - page * 20 : 20; //���㵱ǰҳ��������
						browse_print_cars(cars_id, page_cars_number, page); //��ʾ����
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

void browse_sort(int *cars_id, int cars_id_number, int mode)
{
	PCAR car = head->rear;
	int tmp_i;
	float tmp_f;
	update_browse_sort(mode); //��������ʽ��ʾ��Ϣ
	switch (mode)
	{
	case 0: //���-˳��
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
	case 1: //���-����
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
	case 2: //��λ��-˳��
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
	case 3: //��λ��-����
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
	case 4: //����-˳��
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
	case 5: //����-����
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
	case 6: //�۸�-˳��
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
	case 7: //�۸�-����
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
				case 11: //����
					popup_input_str("�����볧��:", input_s, MAX_CAR_MANUFACTURER);
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
				case 14: //��λ��
					popup_input_int("��������λ��:", &input_i, MAX_CAR_SEAT);
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
				case 17: //������
					popup_input_str("�����������:", input_s, MAX_CAR_GEARBOX);
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
				case 20: //�����۸�
					popup_input_float("�����복���۸�:", &input_f, MAX_CAR_PRICE);
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
				case 8: //�����ͺ�
					popup_input_str("�����복���ͺ�:", input_s, MAX_CAR_TYPE);
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
				case 11: //���ͼ���
					popup_input_str("�����복�ͼ���:", input_s, MAX_CAR_GRADE);
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
				case 14: //����
					popup_input_float("����������:", &input_f, MAX_CAR_EMISSION);
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
				case 17: //������ɫ
					popup_input_str("�����복����ɫ:", input_s, MAX_CAR_COLOUR);
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

