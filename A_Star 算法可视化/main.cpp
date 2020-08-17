#include "main.h"
#include "run.h"
#include "list.h"
#include "visual.h"
#include "map.h"

int main()
{
	// 初始化窗口
	initgraph(PX * PIC, PY * PIC);
	// 输入起点\终点开始执行
	run(5, 10, 15, 10);
	while(1);
	return 0;
}