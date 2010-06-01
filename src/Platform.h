#ifndef PLATFORM_H
#define PLATFORM_H
#include <string>
#include <allegro.h>
class Platform
{
	public:
		//xo represents the top-leftmost coordinate and xf represents the bottom-rightmost coordinate of a platform
		//material must have been addded before anything can be added!
		Platform(BITMAP* path,float xo, float yo, float xf, float yf)
		{
			_path = path;
			_xo = xo;
			_xf = xf;
			_yo = yo;
			_yf = yf;
		}
		BITMAP* getPath(){ return _path; }
		float getXo(){return _xo;}
		float getXf(){return _xf;}
		float getYo(){return _yo;}
		float getYf(){return _yf;}
	private:
		BITMAP* _path;
		//xo represents the top-leftmost coordinate
		float _xo;
		float _yo;
		//xf represents the bottom-rightmost coordinate
		float _xf;
		float _yf;
};
#endif	
