#ifndef GRAVITY_H
#define GRAVITY_H
#include <vector>
#include "Platform.cpp"

enum Orientation {NEITHER, WEST, EAST, NORTH, SOUTH};
class Gravity
{
	public:
		Gravity(float x, float y, int width, int height) : x_(x), y_(y), width_(width), height_(height)
		{
			//returns the  maximum increment an object will jump if it jumps
			max_height_ = 100;

			//setting to default
			run_ = false, ran_once_ = false;

			y_g_ = 1;
			x_g_ = 2;
			
		}
		float getX(){ return x_;}
		float getY(){ return y_;}
		virtual void update(){}

	protected:
		Orientation x_orien_, y_orien_;
		float x_, y_, max_height_, y_g_, x_g_;
		bool run_, ran_once_, on_ground_;
		int width_, height_;

		Orientation getXOrien() { return x_orien_; }
		Orientation getYOrien() { return y_orien_; }
		void setOrientation(Orientation x, Orientation y){ x_orien_ = x; y_orien_ = y; }
		void setXOrientation(Orientation x){ x_orien_ = x;}
		void setYOrientation(Orientation y){ y_orien_ = y;}
		void setX(float x){ x_ += x; }
		void setY(float y){ y_ += y; }
		void setAbsXY(float x, float y){ x_ = x; y_ = y; }

		void reset(){}
		void setRanOnce(bool ran_once) { ran_once_ = ran_once; }
		void setRun(bool run) { run_ = run; }

		bool getRanOnce() { return ran_once_; }
		bool getRun() { return run_; }
		float getMaxHeight() { return max_height_; }
		//returns a boolean of where there is a floor at a specified position
		//-----------------------------------------------------------
		bool checkFloor( std::vector<Platform>& platforms)
		{
			for(int i = 0; i < platforms.size(); i++)
			{
				if( (getY()+height_) == platforms[i].getYo() )
					if(getX() >= platforms[i].getXo() && getX() <= platforms[i].getXf())
						return true;
			}
			return false;
		}
		//returns a boolean of where there is a ceiling at a specified position
		//-----------------------------------------------------------
		bool checkCeiling(float x, float y, std::vector<Platform>& platforms)
		{
			for(int i = 0; i < platforms.size(); i++)
			{
				if( y_ == platforms[i].getYf() )
					if(x_ >= platforms[i].getXo() && x_ <= platforms[i].getXf())
						return true;
			}
			return false;
		}


};
/*  
const float X_G = .5;
const float Y_G = 15;
//const float FLOOR_LEVEL = 400-PLAYER_HEIGHT;

//CONTROL STRUCTURES
bool barrierCeiling(const float& x,const float& y)
{
	return false;
}
bool barrierFloor(const float& x,const float& y)
{
	if(y == FLOOR_LEVEL)
		return true;

	return false;
}



Gravity::Gravity(Orientation xorien, Orientation yorien, float y) : max_height_(y-MAX_HEIGHT), run_(true), xorien_(xorien), yorien_(yorien) {}


void update(Gravity & gravity){}

void updateGravity(Player& player)
{

	//
	//COLLISIONS AND RESETS
	//
	
	if(!barrierFloor(player.getX(),player.getY()) && !player.gravity_.getRanOnce())
		player.gravity_.setRanOnce(true);

	//if maximum height is reached, the entity has to fall back down
	if(player.getY()  >= player.gravity_.getMaxHeight() && player.gravity_.getYOrien() == NORTH) 
		player.gravity_.setYOrien(SOUTH);

	//checking for ceiling barriers and if hit
	if(player.gravity_.getYOrien() == NORTH && player.gravity_.getRanOnce() && barrierCeiling(player.getX(),player.getY()))
		player.gravity_.setYOrien(SOUTH);
	
	//reset the gravity aspect of the entity if he has landed on a barrier
	if(barrierFloor(player.getX(),player.getY()) && player.gravity_.getYOrien() == SOUTH && player.gravity_.getRanOnce())
		player.gravity_.reset();

	//
	//MOVEMENT
	//
	
	if(player.gravity_.getYOrien() == SOUTH)
		player.setY(Y_G);
	else if(player.gravity_.getYOrien() == NORTH)
		player.setY(-Y_G);

	if(player.gravity_.getXOrien() == EAST)
		player.setX(X_G);
	else if(player.gravity_.getXOrien() == WEST)
		player.setX(-X_G);
}*/
#endif
