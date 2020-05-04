#include "ui.h"
#include "function.h"

HANDLE hIn, hOut;
COORD mouse_pos; //��¼�����λ��
DWORD Result;
INPUT_RECORD Buf; //�洢�������¼�

void init();

int main()
{
	init();
	draw_window();
	while (1) 
	{
		draw_menu_button(); //���ư�ť
		switch (menu_click()) //�ж������
		{
		case ADD_BUTTON: //��ӳ���
			add_car();
			draw_window();
			break;
		case BROWSE_BUTTON: //���ȫ��
			browse_cars(NULL, get_all_car_number());
			draw_window();
			break;
		case FIND_BUTTON: //��ѯ����
			find_car();
			draw_window();
			break;
		case EXIT_BUTTON: //�˳�
			if (exit_app()) return 0;	
			draw_window();
		}
	}
	return 0;
}

void init()
{
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTitle(L"������Ϣ����ϵͳ");
	SetConsoleTextAttribute(hOut, CONSOLE_COLOR); //���ÿ���̨��ɫ
	//���û�������С
	COORD size = { 142, 30 };
	SetConsoleScreenBufferSize(hOut, size);
	//���ô��ڴ�С
	SMALL_RECT rc = { 0,0, 141, 29 };
	SetConsoleWindowInfo(hOut, true, &rc);
	//���ÿ���̨ģʽ
	DWORD mode;
	GetConsoleMode(hIn, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE; //�Ƴ����ٱ༭ģʽ
	mode &= ~ENABLE_INSERT_MODE; //�Ƴ�����ģʽ
	SetConsoleMode(hIn, mode);
	//���ع��
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOut, &CursorInfo);//�����Ϣ
	CursorInfo.bVisible = 0; //���ع��
	SetConsoleCursorInfo(hOut, &CursorInfo);//���ù��״̬

	load_car(); //���س�����Ϣ
}