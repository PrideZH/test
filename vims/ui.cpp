#include "ui.h"
#include "car.h"
#include "function.h"

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
	gotoxy(66, 11);
	printf("�� �� �� ��");
	gotoxy(66, 13);
	printf("� �� ȫ ��");
	gotoxy(66, 15);
	printf("�� ѯ �� ��");
	gotoxy(69, 17);
	printf("�� ��");
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (mouse_pos.X > 65 && mouse_pos.X < 77)
	{
		switch (mouse_pos.Y)
		{
		case 11:
			gotoxy(66, 11);
			printf("�� �� �� ��");
			break;
		case 13:
			gotoxy(66, 13);
			printf("� �� ȫ ��");
			break;
		case 15:
			gotoxy(66, 15);
			printf("�� ѯ �� ��");
			break;
		case 17:
			gotoxy(69, 17);
			printf("�� ��");
			break;
		}
	}
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON menu_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
	{
		if(mouse_pos.X > 65 && mouse_pos.X < 77)
		{
			switch (mouse_pos.Y)
			{
			case 11: //��ӳ���
				return ADD_BUTTON;
			case 13: //���ȫ��
				return BROWSE_BUTTON;
			case 15: //��ѯ����
				return FIND_BUTTON;
			case 17: //�˳�
				return EXIT_BUTTON;
			}
		}
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
	for (int n = 0; n < 16; n+=2)
	{
		gotoxy(79, 8 + n);
		printf("[����]");
		gotoxy(86, 8 + n);
		printf("[���]");
	}
	gotoxy(60, 24);
	printf("[ȷ��]");
	gotoxy(70, 24);
	printf("[����]");
	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (mouse_pos.Y > 7 && mouse_pos.Y < 23 && 0 == mouse_pos.Y%2)
	{
		if (mouse_pos.X > 78 && mouse_pos.X < 85)
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
	else if (24 == mouse_pos.Y)
	{
		if (mouse_pos.X > 59 && mouse_pos.X < 66) 
		{
			gotoxy(60, 24);
			printf("[ȷ��]");
		}
		else if (mouse_pos.X > 69 && mouse_pos.X < 76)
		{
			gotoxy(70, 24);
			printf("[����]");
		}
	}
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
		else if (24 == mouse_pos.Y)
		{
			if (mouse_pos.X > 59 && mouse_pos.X < 66)  //ȷ��
			{
				return CONFIRM_BUTTON;
			}
			else if (mouse_pos.X > 69 && mouse_pos.X < 76) //����
			{
				return RETURN_BUTTON;
			}
		}
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
	gotoxy(9, 3);
	printf("���");
	gotoxy(64, 3);
	printf("��λ��");
	gotoxy(73, 3);
	printf("����(L)");
	gotoxy(107, 3);
	printf("�����۸�(��)");
	gotoxy(77, 26);
	printf("��һҳ");
	gotoxy(60, 26);
	printf("��һҳ");	
	gotoxy(121, 26);
	printf("����");
	for (int n = 0; n < page_cars_number; n++)
	{
		gotoxy(124, 5 + n);
		printf("�޸�");
		gotoxy(129, 5 + n);
		printf("ɾ��");
	}

	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (3 == mouse_pos.Y) //�������
	{
		if (mouse_pos.X > 8 && mouse_pos.X < 13) 
		{
			gotoxy(9, 3);
			printf("���");
		}
		else if (mouse_pos.X > 63 && mouse_pos.X < 70)
		{
			gotoxy(64, 3);
			printf("��λ��");
		}
		else if (mouse_pos.X > 72 && mouse_pos.X < 80) 
		{
			gotoxy(73, 3);
			printf("����(L)");
		}
		else if (mouse_pos.X > 106 && mouse_pos.X < 115) 
		{
			gotoxy(107, 3);
			printf("�����۸�(��)");
		}
	}
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
	else if(26 == mouse_pos.Y) //��ҳ�ͷ��ز���
	{	
		if (mouse_pos.X > 59 && mouse_pos.X < 66)
		{
			gotoxy(60, 26);
			printf("��һҳ");
		}
		else if (mouse_pos.X > 76 && mouse_pos.X < 83)
		{
			gotoxy(77, 26);
			printf("��һҳ");
		}
		else if (mouse_pos.X > 120 && mouse_pos.X < 125)
		{
			gotoxy(121, 26);
			printf("����");
		}
	}
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON browse_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
	{
		if (3 == mouse_pos.Y) //�������
		{
			if (mouse_pos.X > 8 && mouse_pos.X < 13)  //���
			{
				return SORT_ID_BUTTON;
			}
			else if (mouse_pos.X > 63 && mouse_pos.X < 70) //��λ��
			{
				return SORT_SEAT_BUTTON;
			}
			else if (mouse_pos.X > 72 && mouse_pos.X < 80) //����
			{
				return SORT_EMISSION_BUTTON;
			}
			else if (mouse_pos.X > 106 && mouse_pos.X < 115) //�����۸�
			{
				return SORT_PRICE_BUTTON;
			}
		}
		else if (mouse_pos.Y > 4 && mouse_pos.Y < 26 && mouse_pos.Y)
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
		else if (26 == mouse_pos.Y) //��ҳ�ͷ��ز���
		{
			if (mouse_pos.X > 59 && mouse_pos.X < 66) //��һҳ
			{
				return PREVIOUS_BUTTON;
			}
			else if (mouse_pos.X > 76 && mouse_pos.X < 83) //��һҳ
			{
				return NEXT_BUTTON;
			}
			else if (mouse_pos.X > 120 && mouse_pos.X < 125) //����  
			{
				return RETURN_BUTTON;
			}
		}
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
	gotoxy(55, 8);
	printf("[  ��  ��  ]");
	gotoxy(75, 8);
	printf("[ �����ͺ� ]");
	gotoxy(55, 11);
	printf("[  ��  ��  ]");
	gotoxy(75, 11);
	printf("[ ���ͼ��� ]");
	gotoxy(55, 14);
	printf("[  ��λ��  ]");
	gotoxy(75, 14);
	printf("[  ��  ��  ]");
	gotoxy(55, 17);
	printf("[  ������  ]");
	gotoxy(75, 17);
	printf("[ ������ɫ ]");
	gotoxy(55, 20);
	printf("[ �����۸� ]");
	gotoxy(75, 20);
	printf("[  ��  ��  ]");

	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (mouse_pos.X > 54 && mouse_pos.X < 67)
	{
		switch (mouse_pos.Y)
		{
		case 8:
			gotoxy(55, 8);
			printf("[  ��  ��  ]");
			break;
		case 11:
			gotoxy(55, 11);
			printf("[  ��  ��  ]");
			break;
		case 14:
			gotoxy(55, 14);
			printf("[  ��λ��  ]");
			break;
		case 17:
			gotoxy(55, 17);
			printf("[  ������  ]");
			break;
		case 20:
			gotoxy(55, 20);
			printf("[ �����۸� ]");
			break;
		}
	}
	else if (mouse_pos.X > 74 && mouse_pos.X < 87)
	{
		switch (mouse_pos.Y)
		{
		case 8:
			gotoxy(75, 8);
			printf("[ �����ͺ� ]");
			break;
		case 11:
			gotoxy(75, 11);
			printf("[ ���ͼ��� ]");
			break;
		case 14:
			gotoxy(75, 14);
			printf("[  ��  ��  ]");
			break;
		case 17:
			gotoxy(75, 17);
			printf("[ ������ɫ ]");
			break;
		case 20:
			gotoxy(75, 20);
			printf("[  ��  ��  ]");
			break;
		}
	}
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON find_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
	{
		if (mouse_pos.X > 54 && mouse_pos.X < 67)
		{
			switch (mouse_pos.Y)
			{
			case 8: //���
				return FIND_ID_BUTTON;
			case 11: //����
				return FIND_MANUFACTURER_BUTTON;
			case 14: //��λ��
				return FIND_SEAT_BUTTON;
			case 17: //������
				return FIND_GEARBOX_BUTTON;
			case 20: //�����۸�
				return FIND_PRICE_BUTTON;
			}
		}
		else if (mouse_pos.X > 74 && mouse_pos.X < 87)
		{
			switch (mouse_pos.Y)
			{
			case 8: //�����ͺ�
				return FIND_TYPE_BUTTON;
			case 11: //���ͼ���
				return FIND_GRADE_BUTTON;
			case 14: //����
				return FIND_EMISSION_BUTTON;
			case 17: //������ɫ
				return FIND_COLOUR_BUTTON;
			case 20: //����
				return RETURN_BUTTON;
			}
		}
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
	gotoxy(62, 15);
	printf("[ȷ��]");
	gotoxy(74, 15);
	printf("[ȡ��]");

	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (15 == mouse_pos.Y)
	{
		if (mouse_pos.X > 61 && mouse_pos.X < 68)
		{
			gotoxy(62, 15);
			printf("[ȷ��]");
		}
		else if (mouse_pos.X > 73 && mouse_pos.X < 80)
		{
			gotoxy(74, 15);
			printf("[ȡ��]");
		}
	}
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);
	Sleep(1000 / FPS);
}

BUTTON del_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
	{
		if (15 == mouse_pos.Y)
		{
			if (mouse_pos.X > 61 && mouse_pos.X < 68) //ȷ��
			{
				return CONFIRM_BUTTON;
			}
			else if (mouse_pos.X > 73 && mouse_pos.X < 80) //ȡ��
			{
				return RETURN_BUTTON;
			}
		}
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
	gotoxy(61, 15);
	printf("[��]   [��]   [ȡ��]");

	mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
	SetConsoleTextAttribute(hOut, CURSOR_COLOR);
	if (15 == mouse_pos.Y)
	{
		if (mouse_pos.X > 60 && mouse_pos.X < 65)
		{
			gotoxy(61, 15);
			printf("[��]");
		}
		else if (mouse_pos.X > 67 && mouse_pos.X < 72)
		{
			gotoxy(68, 15);
			printf("[��]");
		}
		else if (mouse_pos.X > 74 && mouse_pos.X < 81)
		{
			gotoxy(75, 15);
			printf("[ȡ��]");
		}
	}
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR);

	Sleep(1000 / FPS);
}

BUTTON exit_click()
{
	ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
	while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
	{
		if (15 == mouse_pos.Y)
		{
			if (mouse_pos.X > 60 && mouse_pos.X < 65) //��
			{
				return YES;
			}
			else if (mouse_pos.X > 67 && mouse_pos.X < 72) //��
			{
				return NO;
			}
			else if (mouse_pos.X > 74 && mouse_pos.X < 81) //ȡ��
			{
				return CANCEL;
			}
		}
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