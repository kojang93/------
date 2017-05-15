#pragma once

class Hell
{

public:
	Hell(int a, int b, int c) : HellX(a), HellY(b), count(c)
	{}

	Hell() :HellX(1200), HellY(3), count(0)
	{
		//Setdxdy(AntX, AntY);
	}

	int HellX, HellY;
	int count=0;


private:

};