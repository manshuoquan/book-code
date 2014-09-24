#include "Astar.h"
#include "Astaritem.h"

Astar::Astar(void)
{
}

Astar::~Astar(void)
{
    open->removeAllObjects();
    close->removeAllObjects();
    path->removeAllObjects();
}
__Array *Astar::findPath(int curX, int curY, int aimX, int aimY, TMXTiledMap* passmap)
{
	curCol = curX;
    curRow = curY;
	aimCol = aimX;
	aimRow = aimY;
	map = passmap;
	path = __Array::create();
	open = __Array::create();
    AstarItem * temp = new AstarItem();
	open->addObject(temp);
	AstarItem * temp1 = new AstarItem();
	temp1->setpos(curCol,curRow);
	temp1->setg(0);
	int ag = getH(curCol,curRow);
	temp1->seth(ag);
	temp1->setfid(0);
	temp1->setf(ag);
	open->addObject(temp1);
	close = __Array::create();
	while(open->count() > 1){
	   fromopentoclose();
	   int fatherid = close->count() - 1;
       int coldelta = abs(aimCol - ((AstarItem *)close->getObjectAtIndex(fatherid))->getcol());
       int rowdelta = abs(aimRow - ((AstarItem *)close->getObjectAtIndex(fatherid))->getrow());
	   if(coldelta <= 1 && rowdelta <= 1){
		   getpath();
		   break;
	   }else{
	       starseach(fatherid);
	   }
	}
	open->removeAllObjects();
	close->removeAllObjects();
	if(path->count() == 0){
       AstarItem * temp = new AstarItem();
       temp->setpos(aimCol,aimRow);
       path->addObject(temp);
	   return path;
	}else{
		if(((AstarItem *)path->getLastObject())->getcol() != aimCol || ((AstarItem *)path->getLastObject())->getrow() != aimRow){
		   AstarItem * temp = new AstarItem();
	       temp->setpos(aimCol,aimRow);
		   path->addObject(temp);
		}
		return path;
	}
}
void Astar::starseach(int fid)
{
	int col = ((AstarItem *)close->getObjectAtIndex(fid))->getcol();
	int row = ((AstarItem *)close->getObjectAtIndex(fid))->getrow();
	int mycol = col;
	int myrow = row - 1;
	if(myrow >= 0 && checkmap(mycol,myrow)){
		if(checkOpen(mycol,myrow,fid) && checkclose(mycol,myrow)){
		   addtoopen(mycol,myrow,fid);
		}
	}
	mycol = col - 1;
	myrow = row;
	if(mycol >= 0 && checkmap(mycol,myrow)){
		if(checkOpen(mycol,myrow,fid) && checkclose(mycol,myrow)){
		   addtoopen(mycol,myrow,fid);
		}
	}
	mycol = col;
	myrow = row + 1;
	if(myrow < map->getMapSize().width && checkmap(mycol,myrow)){
		if(checkOpen(mycol,myrow,fid) && checkclose(mycol,myrow)){
		   addtoopen(mycol,myrow,fid);
		}
	}
	mycol = col + 1;
	myrow = row;
	if(mycol < map->getMapSize().height && checkmap(mycol,myrow)){
		if(checkOpen(mycol,myrow,fid) && checkclose(mycol,myrow)){
		   addtoopen(mycol,myrow,fid);
		}
	}
}
void Astar::addtoopen(int col,int row,int id)
{
    AstarItem * temp = new AstarItem();
	temp->setpos(col,row);
	temp->setfid(id);
	int g = getG(col, row, id);
	int h = getH(col, row);
	temp->setg(g);
	temp->seth(h);
	temp->setf(g + h);
	open->addObject(temp);
	resetSort(open->count() - 1);

}
bool Astar::checkclose(int col,int row)
{
	for(int i = close->count() - 1;i > 0;i --){
        if(((AstarItem *)close->getObjectAtIndex(i))->getcol() == col && ((AstarItem *)close->getObjectAtIndex(i))->getrow() == row){
           return false; 
		}
	}
	return true;
}
bool Astar::checkOpen(int col,int row,int id)
{
	for(int i = open->count() - 1;i > 0;i --){
		if(((AstarItem *)open->getObjectAtIndex(i))->getcol() == col && ((AstarItem *)open->getObjectAtIndex(i))->getrow() == row){
		    int tempG = getG(col,row,id);
			if(tempG < ((AstarItem *)open->getObjectAtIndex(i))->getg()){
			   ((AstarItem *)open->getObjectAtIndex(i))->setg(tempG);
			   ((AstarItem *)open->getObjectAtIndex(i))->setfid(id);
			   ((AstarItem *)open->getObjectAtIndex(i))->setf(tempG + ((AstarItem *)open->getObjectAtIndex(i))->geth());
			   resetSort(i);
			}
			return false;
		}
	}
	return true;
}
bool Astar::checkmap(int col,int row)
{
   //if(abs(aimCol - col) > 1 || abs(aimRow - row) > 1){
	  TMXLayer* layer = map->getLayer("grass");
      int tilegid = layer->getTileGIDAt(Point(col,row));
      auto tiledic = map->getPropertiesForGID(tilegid);
      int mv = tiledic.asValueMap()["conflict"].asInt();
	  if(mv == 1){
	     return false;
	  } 
   //}
   return true;
}
void Astar::getpath()
{
    curCol = aimCol;
	curRow = aimRow;
    if(close->count() == 0){
       AstarItem * temp = new AstarItem();
       temp->setpos(aimCol,aimRow);
       path->addObject(temp);
       return;
    }
	if(path->count() == 0){
		path->addObject(close->getObjectAtIndex(close->count() - 1));
	}else{
	    path->insertObject(close->getObjectAtIndex(close->count() - 1),path->count() - 1);
	}
	while(true){
		if(((AstarItem *)path->getObjectAtIndex(0))->getg() == 0){
		   break;
		}
		path->insertObject(close->getObjectAtIndex(((AstarItem *)path->getObjectAtIndex(0))->getfid()),0);
	}
}
void Astar::fromopentoclose()
{
	AstarItem * temp = (AstarItem *)open->getObjectAtIndex(1);
	close->addObject(temp);
	open->removeObjectAtIndex(1);
}
void Astar::removefromopen()
{
}
void Astar::resetSort(int last)
{
	while(last > 1){
	   int half = last / 2;
        
	   if(((AstarItem *)open->getObjectAtIndex(half))->getf() <= ((AstarItem *)open->getObjectAtIndex(last))->getf())
		   break;
	   open->exchangeObjectAtIndex(half,last);
       last = half;
	}
}
int Astar::getG(int col,int row,int id)
{
	int fx = ((AstarItem *)close->getObjectAtIndex(id))->getcol();
	int fy = ((AstarItem *)close->getObjectAtIndex(id))->getrow();
	int fg = ((AstarItem *)close->getObjectAtIndex(id))->getg();
	if(fx - col != 0 && fy - row != 0){
	   return fg + 14;
	}else{
	   return fg + 10;
	}
}
int Astar::getH(int col,int row)
{
	return abs(aimCol - col) * 10 + abs(aimRow - row) * 10;
}