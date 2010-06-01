#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Gravity.cpp"
#include "Material.cpp"
#include "Platform.cpp"
class Player : public Gravity
{
	public:
		Player(std::string name, std::string material_name, int width, int height, float xo, float yo  ) : Gravity(xo,yo, width, height), material_(name+"01", material_name, width, height), name_(name)
		{
			
		}
		void update(Orientation x, Orientation y, std::vector<Platform>& platforms)
		{ 
			//order of operations is important in this function!
		  	if(on_ground_)
				setXOrientation(x);
		  	else 
				setXOrientation(NEITHER);

			if(getXOrien() == EAST)
				setX(x_g_);
			else if(getXOrien() == WEST)
				setX(-1*x_g_);
			
			if(getYOrien() == NORTH)
				setY(-1*y_g_);
			else if(getYOrien() == SOUTH)
				setY(y_g_);

			if(!checkFloor(platforms))
			{
				setXOrientation(NEITHER);
				setY(y_g_);
			}
			else
				on_ground_ = true;
		}
		std::string getFileName(){ return material_.getFileName(); }
	private:
		std::string name_;
		Material material_;
};
#endif
