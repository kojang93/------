#pragma once


class Ant 
{

public:
	Ant(int a, int b,int c) :AntX(a), AntY(b),Velocity(1)
	{}
	
	
	Ant():AntX(1200),AntY(3),count(0)
	{
		//Setdxdy(AntX, AntY);
	}
	
    int AntX, AntY;
    int count;
	int Velocity;
	int x;
	int AntDamage = 100;
private:
};

class FireAnt : public Ant
{
public:
	FireAnt(int a, int b, int c) :AntX(a),AntY(b), Velocity(1)
	{}


	FireAnt() :AntX(1200), AntY(3), count(0)
	{
		//Setdxdy(AntX, AntY);
	}

	int AntX, AntY;
	int count;
	int Velocity;
	int x = 2;
private:
	
};