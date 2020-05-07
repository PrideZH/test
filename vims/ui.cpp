#include "ui.h"
#include "car.h"
#include "function.h"

//�˵����水ť
BYTTON_INFO add_but = { 66, 11, 10, "�� �� �� ��" };
BYTTON_INFO browse_but = { 66, 13, 10, "� �� ȫ ��" };
BYTTON_INFO find_but = { 66, 15, 10, "�� ѯ �� ��" };
BYTTON_INFO exit_but = { 69, 17, 4, "�� ��" };
//��ӽ��水ť
BYTTON_INFO set_confirm_but = { 60, 24, 5, "[ȷ��]" };
BYTTON_INFO set_return_but = { 70, 24, 5, "[����]" };
//������水ť
BYTTON_INFO id_but = { 9, 3, 3, "���" };
BYTTON_INFO seat_but = { 64, 3, 5, "��λ��" };
BYTTON_INFO emission_but = { 73, 3, 6, "����(L)" };
BYTTON_INFO price_but = { 107, 3, 11, "�����۸�(��)" };
BYTTON_INFO next_but = { 77, 26, 5, "��һҳ" };
BYTTON_INFO previous_but = { 60, 26, 5, "��һҳ" };
BYTTON_INFO browse_return_but = { 121, 26, 3, "����" };
//��ѯ���水ť
BYTTON_INFO find_id_but = { 55, 8, 11, "[  ��  ��  ]" };
BYTTON_INFO find_type_but = { 75, 8, 11, "[ �����ͺ� ]" };
BYTTON_INFO find_manufacturer_but = { 55, 11, 11, "[  ��  ��  ]" };
BYTTON_INFO find_grade_but = { 75, 11, 11, "[ ���ͼ��� ]" };
BYTTON_INFO find_seat_but = { 55, 14, 11, "[  ��λ��  ]" };
BYTTON_INFO find_emission_but = { 75, 14, 11, "[  ��  ��  ]" };
BYTTON_INFO find_gearbox_but = { 55, 17, 11, "[  ������  ]" };
BYTTON_INFO find_colour_but = { 75, 17, 11, "[ ������ɫ ]" };
BYTTON_INFO find_price_but = { 55, 20, 11, "[ �����۸� ]" };
BYTTON_INFO find_return_but = { 75, 20, 11, "[  ��  ��  ]" };
//ɾ����������
BYTTON_INFO del_confirm_but = { 62, 15, 5, "[ȷ��]" };
BYTTON_INFO del_return_but = { 74, 15, 5, "[ȡ��]" };
//�˳����水ť
BYTTON_INFO exit_yes_but = { 61, 15, 3, "[��]" };
BYTTON_INFO exit_no_but = { 68, 15, 3, "[��]" };
BYTTON_INFO exit_cancel_but = { 75, 15, 5, "[ȡ��]" };

void draw_window() 
{
	gotoxy(8, 2);
	printf("�q�����������������������������������������������������������������������������������������������������������������������������r\n");
	for (int i = 0; i < 24; i++)
	{
		gotoxy(8, 3 + i);
		printf("|                                                                                                                             |\n");
	}
	gotoxy(8, 27);
	printf("�t�����������������������������������������������������������������������������������������������������������������������������s\n");
}

void draw_popup()
{
	gotoxy(43, 11);
	printf("�q�������������������������������������������������������r\n");
	for (int i = 0; i < 5; i++)
	{
		gotoxy(43, 12 + i);
		printf("|                                                       |\n");
	}
	gotoxy(43, 17);
	printf("�t�������������������������������������������������������s\n");
}

void popup_prompt(const char *information)
{
	draw_popup();
	gotoxy(71 - strlen(information) / 2, 13); //ʹ��Ϣ����
	printf("%s", information);
	gotoxy(63, 15);
	printf("%s", "���������������");
	_getch();
}

void popup_input(const char *information, int content_lenght)
{
	draw_popup();
	gotoxy(71 - (strlen(information) + content_lenght) / 2, 14); //ʹ��Ϣ����
	printf("%s", information);
	gotoxy(71 - (content_lenght - strlen(information)) / 2, 14); //����Ϣ��������
	for (int i = 1; i < content_lenght; i++)
	{
		printf("_");
	}
	gotoxy(71 - (content_lenght - strlen(information)) / 2, 14); //����Ϣ��������
}

void popup_input_str(const char *information, char *content, int content_lenght)
{
	popup_input(information, content_lenght);
	while (!scanf_s("%s", content, content_lenght))
	{
		rewind(stdin);
		popup_prompt("�������ݹ���������д����...");
		popup_input(information, content_lenght);
	}
}

void popup_input_int(const char *information, int *content, int content_lenght)
{
	popup_input(information, content_lenght);
	while (!scanf_s("%4d", content))
	{
		rewind(stdin);
		popup_prompt("�������ݹ������������д����...");
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
		popup_prompt("�������ݹ������������д����...");
		popup_input(information, content_lenght);
	}
	rewind(stdin);
}

void draw_menu_button()
{
	//���ư�ť
	draw_button(add_but); //���� [�� �� �� ��]
	draw_button(browse_but); //���� [� �� ȫ ��]
	draw_button(find_but); //���� [�� ѯ �� ��]
	draw_button(exit_but); //���� [�� ��]
	//���ư�ť���
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if(is_in_button(add_but)) draw_button(add_but); //���� [�� �� �� ��]
	else if (is_in_button(browse_but)) draw_button(browse_but); //���� [� �� ȫ ��]
	else if (is_in_button(find_but)) draw_button(find_but); //���� [�� ѯ �� ��]
	else if (is_in_button(exit_but)) draw_button(exit_but); //���� [�� ��]
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON menu_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
	{
		if (is_in_button(add_but)) return ADD_BUTTON; //��ӳ���
		else if (is_in_button(browse_but)) return BROWSE_BUTTON; //���ȫ��
		else if (is_in_button(find_but)) return FIND_BUTTON; //��ѯ����
		else if (is_in_button(exit_but)) return EXIT_BUTTON; //�˳�
		ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
	}
	return NONE;
}

void draw_set_windows(PCAR car)
{
	draw_window();
	gotoxy(49, 6);
	printf("��  ��:%d", car->id);
	gotoxy(49, 8);
	printf("��  ��:%s", car->type);
	gotoxy(49, 10);
	printf("��  ��:%s", car->manufacturer);
	gotoxy(49, 12);
	printf("��  ��:%s", car->grade);
	gotoxy(49, 14);
	printf("��λ��:%d", car->seat);
	gotoxy(49, 16);
	printf("��  ��:%.2f", car->emission);
	gotoxy(49, 18);
	printf("������:%s", car->gearbox);
	gotoxy(49, 20);
	printf("��  ɫ:%s", car->colour);
	gotoxy(49, 22);
	printf("��  ��:%.2f", car->price);
}

void draw_set_button()
{
	//���ư�ť
	for (int n = 0; n < 16; n+=2)
	{
		gotoxy(79, 8 + n);
		printf("[����]");
		gotoxy(86, 8 + n);
		printf("[���]");
	}
	draw_button(set_confirm_but); //���� [ȷ��]
	draw_button(set_return_but); //���� [����]
	//���ư�ť���
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (mouse_pos.Y > 7 && mouse_pos.Y < 23 && 0 == mouse_pos.Y%2)
	{
		if (mouse_pos.X >= 79 && mouse_pos.X <= 84)
		{
			gotoxy(79, mouse_pos.Y);
			printf("[����]");
		}
		else if (mouse_pos.X > 85 && mouse_pos.X < 92)
		{
			gotoxy(86, mouse_pos.Y);
			printf("[���]");
		}
	}
	else if(is_in_button(set_confirm_but)) draw_button(set_confirm_but); //���� [ȷ��]
	else if (is_in_button(set_return_but)) draw_button(set_return_but); //���� [����]
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);
	Sleep(1000 / FPS);
}

BUTTON set_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result);
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
	{
		if (mouse_pos.Y > 7 && mouse_pos.Y < 23 && 0 == mouse_pos.Y % 2)
		{
			if (mouse_pos.X > 78 && mouse_pos.X < 85) //����
			{
				return INPUT_BUTTON;
			}
			else if (mouse_pos.X > 85 && mouse_pos.X < 92) //���
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
		"��š�", "        �����ͺ�", "    ����", " ���ͼ���", "��λ����", "����(L)��", "  ������", " ������ɫ", "�����۸�(��)��", "   ����");
	gotoxy(9, 4);
	printf("%s", "����������������������������������������������������������������������������������������������������������������������������");
	gotoxy(9, 25);
	printf("%s", "����������������������������������������������������������������������������������������������������������������������������");
}

void draw_browse_button(int page_cars_number)
{
	//���ư�ť
	draw_button(id_but); //���� [���]
	draw_button(seat_but); //���� [��λ��]
	draw_button(emission_but); //���� [����(L)]
	draw_button(price_but); //���� [�����۸�(��)]
	draw_button(next_but); //���� [��һҳ]
	draw_button(previous_but); //���� [��һҳ]
	draw_button(browse_return_but); //���� [����]
	for (int n = 0; n < page_cars_number; n++)
	{
		gotoxy(124, 5 + n);
		printf("�޸�");
		gotoxy(129, 5 + n);
		printf("ɾ��");
	}
	//���ư�ť���
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (is_in_button(id_but)) draw_button(id_but); //���� [���]
	else if (is_in_button(seat_but)) draw_button(seat_but); //���� [��λ��]
	else if (is_in_button(emission_but)) draw_button(emission_but); //���� [����(L)]
	else if (is_in_button(price_but)) draw_button(price_but); //���� [�����۸�(��)]
	else if(mouse_pos.Y > 4 && mouse_pos.Y < 26 && mouse_pos.Y < 5 + page_cars_number)//�޸ĺ�ɾ������
	{
		if (mouse_pos.X > 123 && mouse_pos.X < 128)
		{
			gotoxy(124, mouse_pos.Y);
			printf("�޸�");
		}
		else if (mouse_pos.X > 128 && mouse_pos.X < 133)
		{
			gotoxy(129, mouse_pos.Y);
			printf("ɾ��");
		}
	}
	else if (is_in_button(next_but)) draw_button(next_but); //���� [��һҳ]
	else if (is_in_button(previous_but)) draw_button(previous_but); //���� [��һҳ]
	else if (is_in_button(browse_return_but)) draw_button(browse_return_but); //���� [����]
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON browse_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
	{
		if (is_in_button(id_but))return SORT_ID_BUTTON; //���
		else if (is_in_button(seat_but)) return SORT_SEAT_BUTTON; //��λ��
		else if (is_in_button(emission_but)) return SORT_EMISSION_BUTTON; //����
		else if (is_in_button(price_but)) return SORT_PRICE_BUTTON; //�����۸�
		else if (mouse_pos.Y > 4 && mouse_pos.Y < 26)
		{
			if (mouse_pos.X > 123 && mouse_pos.X < 128) //�޸�
			{
				return SET_BUTTON;
			}
			else if (mouse_pos.X > 128 && mouse_pos.X < 133) //ɾ��
			{
				return DELETE_BUTTON;
			}
		}
		else if (is_in_button(previous_but)) return PREVIOUS_BUTTON; //��һҳ
		else if (is_in_button(next_but)) return NEXT_BUTTON; //��һҳ
		else if (is_in_button(browse_return_but)) return RETURN_BUTTON; //����  
		ReadConsoleInput(hIn, &Buf, 1, &Result);
	}
	return NONE;
}

void browse_print_cars(PCAR head, int page)
{
	//���ָ��ҳ���һ����
	PCAR car = head->rear;
	for (int i = 0; i < page * 20; i++) 
	{
		car = car->rear;
	}
	//��ӡ��ҳ�泵��
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
	printf("��");
	gotoxy(70, 3);
	printf("��");
	gotoxy(80, 3);
	printf("��");
	gotoxy(119, 3);
	printf("��");
	switch (sort_mode)
	{
	case 0:
		gotoxy(13, 3);
		printf("��");
		break;
	case 1:
		gotoxy(13, 3);
		printf("��");
		break;
	case 2:
		gotoxy(70, 3);
		printf("��");
		break;
	case 3:
		gotoxy(70, 3);
		printf("��");
		break;
	case 4:
		gotoxy(80, 3);
		printf("��");
		break;
	case 5:
		gotoxy(80, 3);
		printf("��");
		break;
	case 6:
		gotoxy(119, 3);
		printf("��");
		break;
	case 7:
		gotoxy(119, 3);
		printf("��");
		break;

	}
}

void draw_find_windows()
{
	draw_window();
	gotoxy(64, 3);
	printf("��ѯ������Ϣ");
}

void draw_find_button()
{
	//���ư�ť
	draw_button(find_id_but); //���� [  ��  ��  ]
	draw_button(find_type_but); //���� [ �����ͺ� ]
	draw_button(find_manufacturer_but); //���� [  ��  ��  ]
	draw_button(find_grade_but); //���� [ ���ͼ��� ]
	draw_button(find_seat_but); //���� [  ��λ��  ]
	draw_button(find_emission_but); //���� [  ��  ��  ]
	draw_button(find_gearbox_but); //���� [  ������  ]
	draw_button(find_colour_but); //���� [ ������ɫ ]
	draw_button(find_price_but); //���� [ �����۸� ]
	draw_button(find_return_but); //���� [  ��  ��  ]
	//���ư�ť���
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (is_in_button(find_id_but)) draw_button(find_id_but); //���� [  ��  ��  ]
	else if (is_in_button(find_type_but)) draw_button(find_type_but); //���� [ �����ͺ� ]
	else if (is_in_button(find_manufacturer_but)) draw_button(find_manufacturer_but); //���� [  ��  ��  ]
	else if (is_in_button(find_grade_but)) draw_button(find_grade_but); //���� [ ���ͼ��� ]
	else if (is_in_button(find_seat_but)) draw_button(find_seat_but); //���� [  ��λ��  ]
	else if (is_in_button(find_emission_but)) draw_button(find_emission_but); //���� [  ��  ��  ]
	else if (is_in_button(find_gearbox_but)) draw_button(find_gearbox_but); //���� [  ������  ]
	else if (is_in_button(find_colour_but)) draw_button(find_colour_but); //���� [ ������ɫ ]
	else if (is_in_button(find_price_but)) draw_button(find_price_but); //���� [ �����۸� ]
	else if (is_in_button(find_return_but)) draw_button(find_return_but); //���� [  ��  ��  ]
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON find_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
	{
		if (is_in_button(find_id_but)) return FIND_ID_BUTTON; //���
		else if (is_in_button(find_type_but)) return FIND_TYPE_BUTTON; //�ͺ�
		else if (is_in_button(find_manufacturer_but)) return FIND_MANUFACTURER_BUTTON; //����
		else if (is_in_button(find_grade_but)) return FIND_GRADE_BUTTON; //����
		else if (is_in_button(find_seat_but)) return FIND_SEAT_BUTTON; //��λ��
		else if (is_in_button(find_emission_but)) return FIND_EMISSION_BUTTON; //����
		else if (is_in_button(find_gearbox_but)) return FIND_GEARBOX_BUTTON; //������
		else if (is_in_button(find_colour_but)) return FIND_COLOUR_BUTTON; //������ɫ
		else if (is_in_button(find_price_but)) return FIND_PRICE_BUTTON; //�۸�
		else if (is_in_button(find_return_but)) return RETURN_BUTTON; //����
		ReadConsoleInput(hIn, &Buf, 1, &Result);
	}
	return NONE;
}

void draw_del_windows()
{
	draw_popup();
	gotoxy(63, 13);
	printf("�Ƿ�ɾ��������Ϣ");
	draw_del_button();
}

void draw_del_button()
{
	//���ư�ť
	draw_button(del_confirm_but); //���� [ȷ��]
	draw_button(del_return_but); //���� [ȡ��]
	//���ư�ť���
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (is_in_button(del_confirm_but)) draw_button(del_confirm_but); //���� [ȷ��]
	else if (is_in_button(del_return_but)) draw_button(del_return_but); //���� [ȡ��]
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON del_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
	{
		if (is_in_button(del_confirm_but)) return CONFIRM_BUTTON; //ȷ��
		else if (is_in_button(del_return_but)) return RETURN_BUTTON; //ȡ��
		ReadConsoleInput(hIn, &Buf, 1, &Result);
	}
	return NONE;
}

void draw_exit_windows()
{
	draw_popup();
	gotoxy(62, 13);
	printf("�Ƿ��˳����򲢱���");
}

void draw_exit_button()
{
	//���ư�ť
	draw_button(exit_yes_but); //���� [��]
	draw_button(exit_no_but); //���� [��]
	draw_button(exit_cancel_but); //���� [ȡ��]
	//���ư�ť���
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (is_in_button(exit_yes_but)) draw_button(exit_yes_but); //���� [��]
	else if (is_in_button(exit_no_but)) draw_button(exit_no_but); //���� [��]
	else if (is_in_button(exit_cancel_but)) draw_button(exit_cancel_but); //���� [ȡ��]
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON exit_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
	{
		if (is_in_button(exit_yes_but)) return YES; //��
		else if (is_in_button(exit_no_but)) return NO; //��
		else if (is_in_button(exit_cancel_but)) return CANCEL; //ȡ��
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