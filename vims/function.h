#pragma once

#include"car.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32

extern HANDLE hIn, hOut;
extern COORD mouse_pos; //存储鼠标位置
extern DWORD Result; //存储读取记录
extern INPUT_RECORD Buf; //存储操作事件

/***********************************************************************
 * 说明：  录入车辆信息功能
 ***********************************************************************/
void add_car(); 

/***********************************************************************
 * 说明：  录入或修改车辆界面的输入信息功能
 ***********************************************************************/
void car_input(PCAR car, int position);

/***********************************************************************
 * 说明：  录入或修改车辆界面的清空信息功能
 ***********************************************************************/
void car_empty(PCAR car, int position);

/***********************************************************************
 * 说明：  浏览车辆功能
 * 参数：  cars-存放要显示车辆的结构体指针数组 NULL-显示所有车辆
 *         cars_number-车辆数量
 ***********************************************************************/
void browse_cars(PCAR *cars, int cars_number);

/***********************************************************************
 * 说明：  快速排序
 ***********************************************************************/
void browse_qsort(PCAR *cars, int _left, int _right, int mode);

/***********************************************************************
 * 说明：  快速排序取中位数为基准
 ***********************************************************************/
PCAR get_pivot(PCAR *cars, int _left, int _right, int mode);

/***********************************************************************
 * 说明：  查询车辆功能
 ***********************************************************************/
void find_car(); 

/***********************************************************************
 * 说明：  修改车辆功能
 ***********************************************************************/
void set_car(PCAR car); 

/***********************************************************************
 * 说明：  删除车辆功能
 ***********************************************************************/
int del_car(PCAR car);  

/***********************************************************************
 * 说明：  退出程序功能
 ***********************************************************************/
int exit_app();




