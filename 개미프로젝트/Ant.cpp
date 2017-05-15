#include "stdafx.h"
#include "Ant.h"





//void Ant::MoveToCake(int x1, int y1, int x2, int y2)
//{
//	/*AntX += 1;
//	AntY += 1;*/
//	
//	int addX, addY;
//	int counter = 0;
//
//	int dx = x2 - x1;
//	int dy = y2 - y1;
//	 
//	if (dx < 0)
//	{
//		addX = -1;
//		dx = -dx;
//	}
//	else
//	{
//		addX = 1;
//	}
//	if (dy < 0)
//	{
//		addY = -1;
//		dy = -dy;
//	}
//	else
//	{
//		addY = 1;
//	}
//
//	int x = x1;
//	int y = y1;
//
//	if (dx >= dy)
//	{
//		for (int i= 0; i < dx; i++)
//		{
//			AntX += addX * 1;
//			counter += dy;
//			if (counter >= dx)
//			{
//				AntY += addY * 1;
//				counter -= dx;
//			}
//		}
//	}
//	else
//	{
//		for (int i = 0; i < dy; i++)
//		{
//			AntY += addY * 1;
//			counter += dx;
//			if (counter >= dy)
//			{
//				AntX += addX * 1;
//				counter -= dy;
//			}
//		}
//	}	
//}