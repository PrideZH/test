#include "main.h"
#include "run.h"
#include "list.h"
#include "visual.h"
#include "map.h"

int main()
{
	// ��ʼ������
	initgraph(PX * PIC, PY * PIC);
	// �������\�յ㿪ʼִ��
	run(5, 10, 15, 10);
	while(1);
	return 0;
}