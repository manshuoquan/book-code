#pragma once
#include "cocos2d.h"
#include "AstarItem.h"
using namespace cocos2d;
class Astar
{
private:
	int curCol, curRow, aimCol, aimRow;
	int AimX, AimY, AimW, AimH; 
	TMXTiledMap* map;
    __Array *open;
    __Array *close;
    __Array *path;
public:
	Astar(void);
	~Astar(void);
	int getG(int col,int row,int id);//获得g（）
	int getH(int col,int row);//获得h（）
	void fromopentoclose();//将close列表中的元素导入到close列表中
	void removefromopen();//从open列表中删除元素
	void getpath();//获得整个路径
	void starseach(int fid);//搜索
	void resetSort(int last);//排序
	bool checkclose(int col,int row);//检查close列表
	void addtoopen(int col,int row,int id);//向open列表中添加元素
	bool checkmap(int col,int row);//检查地图
	bool checkOpen(int col,int row,int id);//检查open列表
    __Array *findPath(int curX, int curY, int aimX, int aimY, TMXTiledMap* passmap);//入口函数
};
