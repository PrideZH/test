#ifndef _MAP_H
#define _MAP_H

#define PY 20
#define PX 20
#define PIC 30

extern int map[PY][PX]; //0-空 1-障碍 2-待搜索点 3-已使用点 4-终点
extern int fgh[PY][PX][3]; // 存储各节点的gfh
extern int father[PY][PX][2]; //记录各节点的父节点

#endif