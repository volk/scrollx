#ifndef MATERIAL_H
#define MATERIAL_H
#include <string>
#include <allegro.h>
class Material 
{
	public:
		Material(std::string name, std::string path,float width, float height)
		{
			_reference_name = name;
			_file_name = path.c_str();
			_path = load_bitmap(path.c_str(), NULL);
			_width = width;
			_height = height;
		}
		std::string getReferenceName(){ return _reference_name; }
		std::string getFileName(){ return _file_name; }
		BITMAP* getPath(){ return _path; }
	private:
		std::string _reference_name;
		std::string _file_name;
		BITMAP* _path;
		float _width;
		float _height;
};
#endif	
