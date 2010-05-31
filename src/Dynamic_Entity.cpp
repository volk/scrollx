#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <allegro.h>
class Dynamic_Entity
{
	public:
		Entity(std::string entity_name, std::string bitmap_name, int width, int height, bool gravity_on, bool fall_off_platforms)
		{
			_name = name;
			_path = load_bitmap(path.c_str(), NULL);
		}
		std::string getName(){ return _name; }
		BITMAP* getPath(){ return _path; }
	private:
		std::string _name;
		BITMAP* _path;
};
#endif	
