#include "car.h"
#include "ui.h"

PCAR head;

void load_car()
{
	FILE *fp;
	if (0 != fopen_s(&fp, "data.dat", "a+b"))
	{
		perror("打开文件失败，原因是");
		_getch();
		exit(1);
	}
	PCAR car, tail;
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

void add_car(PCAR head, PCAR car)
{
	//头插法
	if (head->rear == NULL)
	{
		head->rear = car;
		car->front = head;
		car->rear = NULL;
	}
	else
	{
		car->rear = head->rear;
		car->rear->front = car;
		car->front = head;
		head->rear = car;
	}
}

void add_list(PCAR list_head)
{
	if (list_head->rear == NULL) return; //为空列表返回
	//获得主链表末尾节点
	PCAR car = head;
	while (car->rear != NULL)
	{
		car = car->rear;
	}
	//将链表添加到主链表末尾
	PCAR list_car = list_head->rear;
	car->rear = list_car;
	list_car->front = car;
}

void del_car(PCAR car)
{
	if (car->rear == NULL)
	{
		car->front->rear = NULL;
	}
	else
	{
		car->front->rear = car->rear;
		car->rear->front = car->front;
	}
	free(car);
}

int get_list_length(PCAR head)
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
	sort(head, ID_ORDER);
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

PCAR get_car(PCAR head, int index)
{
	int i = 0;
	PCAR car = head;
	while ((car = car->rear) != NULL)
	{
		if (index == i)
		{
			return car;
		}
		i++;
	}
	return NULL;
}

PCAR get_list(INFO info, Data data)
{
	PCAR car = head->rear, car_tem;
	PCAR list_head = (PCAR)malloc(sizeof(CAR));
	list_head->rear = NULL;
	while (car != NULL)
	{
		if (matching(car, info, data))
		{
			//获得车辆数据
			PCAR list_car = (PCAR)malloc(sizeof(CAR));
			car_tem = car;
			*list_car = *car_tem;

			car = car->front;

			del_car(car_tem); //删除主链表车辆
			add_car(list_head, list_car); //将车辆添加到链表
		}
		car = car->rear;
	}
	return list_head;
}

int matching(PCAR car, INFO info, Data data)
{
	switch (info)
	{
	case ID: 
		if (car->id == data.i) return 1; 
		break;
	case TYPE: 
		if (!strcmp(car->type, data.s)) return 1; 
		break;
	case MANUFACTURER: 
		if (!strcmp(car->manufacturer, data.s)) return 1; 
		break;
	case GRADE: 
		if (!strcmp(car->grade, data.s)) return 1; 
		break;
	case SEAT: 
		if (car->seat == data.i) return 1; 
		break;
	case EMISSION: 
		if (car->emission == data.f) return 1; 
		break;
	case GEARBOX: 
		if (!strcmp(car->gearbox, data.s)) return 1; 
		break;
	case COLOUR: 
		if (!strcmp(car->colour, data.s)) return 1; 
		break;
	case PRICE: 
		if (car->price == data.f) return 1; 
		break;
	}
	return 0;
}

void sort(PCAR head, SORT sort_type)
{
	head->rear = merge_sort(head->rear, sort_type);
}

PCAR merge_sort(PCAR head, SORT sort_type) {
	if (head == NULL || head->rear == NULL) //空链表或只有1个元素时停止分割
	{
		return head;
	}
	else
	{
		//快慢指针找到中间节点
		PCAR fast = head, slow = head;
		while (fast->rear != NULL && fast->rear->rear != NULL)
		{
			fast = fast->rear->rear;
			slow = slow->rear;
		}
		//获得2个链表
		fast = slow;
		slow = slow->rear;
		fast->rear = NULL;
		fast->front = NULL;
		//合并链表
		return merge(merge_sort(head, sort_type), merge_sort(slow, sort_type), sort_type);
	}
}

PCAR merge(PCAR head1, PCAR head2, SORT sort_type)
{
	if (head1 == NULL) return head2;
	if (head2 == NULL) return head1;
	PCAR head, p;
	if (comparer(head1, head2, sort_type))
	{
		head = head1;
		head1 = head1->rear;
	}
	else
	{
		head = head2;
		head2 = head2->rear;
	}
	p = head;

	while (head1 != NULL && head2 != NULL)
	{
		if (comparer(head1, head2, sort_type))
		{
			p->rear = head1;
			head1->front = p;
			head1 = head1->rear;
		}
		else
		{
			p->rear = head2;
			head2->front = p;
			head2 = head2->rear;
		}
		p = p->rear;
	}
	if (head1 != NULL)
	{
		p->rear = head1;
		head1->front = p;
	}
	else if (head2 != NULL)
	{
		p->rear = head2;
		head2->front = p;
	}
	return head;
}

int comparer(PCAR head1, PCAR head2, SORT sort_type)
{
	switch (sort_type)
	{
	case ID_ORDER:
		return head1->id < head2->id;
	case ID_INVERTED:
		return head1->id > head2->id;
	case SEAT_ORDER:
		return head1->seat < head2->seat;
	case SEAT_INVERTED:
		return head1->seat > head2->seat;
	case EMISSION_ORDER:
		return head1->emission < head2->emission;
	case EMISSION_INVERTED:
		return head1->emission > head2->emission;
	case PRICE_ORDER:
		return head1->price < head2->price;
	case PRICE_INVERTED:
		return head1->price > head2->price;
	}
	return 0;
}

