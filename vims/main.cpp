#include "ui.h"
#include "function.h"

HANDLE hIn, hOut;
COORD mouse_pos;
DWORD Result;
INPUT_RECORD Buf;

void init();

int main()
{
	init();
	init_window();
	while (1) 
	{
		ReadConsoleInput(hIn, &Buf, 1, &Result); //��ȡ�����¼�
		mouse_pos = Buf.Event.MouseEvent.dwMousePosition; //������λ��
		menu_cursor(); //�������λ�û��Ʋ˵����
		while (Buf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //���������
		{
			if (mouse_pos.X > 65 && mouse_pos.X < 77)
			{
				switch (mouse_pos.Y)
				{
				case 11: //��ӳ���
					add_car();
					init_window();
					break;
				case 13: //���ȫ��
					browse_cars(NULL, get_all_car_number());
					init_window();
					break;
				case 15: //��ѯ����
					find_car();
					init_window();
					break;
				case 17: //�˳�
					if(exit_app()) return 0;
					init_window();
				}
			}
			if (!ReadConsoleInput(hIn, &Buf, 1, &Result)) break;
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