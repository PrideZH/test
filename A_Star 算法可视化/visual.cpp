#include "visual.h"
#include "map.h"
#include "list.h"

void draw_map()
{
	BeginBatchDraw();
	for(int i = 0; i < PY; i++)
	{
		for(int j = 0; j < PX; j++)
		{
			switch(map[i][j])
			{
			case 0: // 0-�� 
				setfillcolor(WHITE);
				break;
			case 1: // 1-�ϰ� 
				setfillcolor(BLACK);
				break;
			case 2: // 2-���ҵ� 
				setfillcolor(GREEN);
				break;
			case 3: // 3-ʹ�õ� 
				setfillcolor(YELLOW);
				break;
			case 4: // 4-�յ�
				setfillcolor(RED);
				break;
			}
			fillrectangle(j * PIC, i * PIC, j * PIC + PIC, i * PIC + PIC);
		}
	}
	EndBatchDraw();
	Sleep(10);
}

void draw_path(int e_x, int e_y)
{
	int x = e_x;
	int y = e_y;
	BeginBatchDraw();
	setlinecolor(RED);
	// ���յ㿪ʼ��·��
	while(1)
	{
		int n_x = father[y][x][1];
		int n_y = father[y][x][0];
		// ��������˳�
		if(x == n_x && y == n_y)
		{
			break;
		}
		line(x * PIC + PIC / 2, y * PIC + PIC / 2, n_x * PIC + PIC / 2, n_y * PIC + PIC / 2);
		x = n_x;
		y = n_y;

	}
	EndBatchDraw();
}