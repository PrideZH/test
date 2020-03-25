#include "car.h"
#include "ui.h"

PCAR head, tail;

void load_car()
{
	FILE *fp;
	if (0 != fopen_s(&fp, "data.dat", "a+b"))
	{
		perror("打开文件失败，原因是");
		_getch();
		exit(1);
	}
	PCAR car;
	head = (PCAR)malloc(sizeof(CAR));
	if (NULL == head)
	{
		printf("内存分配失败！\n");
		exit(EXIT_FAILURE);
	}
	head->front = NULL;
	head->rear = NULL;
	tail = head;
	while (1)
	{
		car = (PCAR)malloc(sizeof(CAR));
		if (fread(car, sizeof(CAR), 1, fp) == 0)
		{
			free(car);
			break;
		}
		car->front = tail;
		car->rear = NULL;
		tail->rear = car;
		tail = car;
	}
	fclose(fp);
}

void save_car()
{
	FILE *fp;
	if (0 != fopen_s(&fp, "data.dat", "w+"))
	{
		perror("打开文件失败，原因是");
		_getch();
		return;
	}
	PCAR car = head->rear;
	while (car != NULL)
	{
		fwrite(car, sizeof(CAR), 1, fp);
		car = car->rear;
	}
	fclose(fp);
}

void add_list(PCAR car)
{
	PCAR p = head->rear;
	if (car->id > tail->id) //汽车编号最大时用尾插法
	{
		car->front = tail;
		car->rear = NULL;
		tail->rear = car;
		tail = car;
		return;
	}
	while (p != NULL) //否则按id排列顺序插入
	{
		if (p->id > car->id)
		{
			car->rear = p;
			car->front = p->front;
			p->front->rear = car;
			p->front = car;
			return;
		}
		p = p->rear;
	}
}

void del_list(PCAR car)
{
	if (car->rear == NULL)
	{
		tail = car->front;
		tail->rear = NULL;
	}
	else
	{
		car->front->rear = car->rear;
		car->rear->front = car->front;
	}
	free(car);
}

int get_all_car_number()
{
	int count = 0;
	PCAR car = head->rear;
	while (car != NULL)
	{
		car = car->rear;
		count++;
	}
	return count;
}

int get_id()
{
	int id = 1;
	PCAR car = head->rear;
	while (car != NULL)
	{
		if (car->id != id)
		{
			break;
		}
		id++;
		car = car->rear;
	}
	return id;
}

