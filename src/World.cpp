#ifndef VIDEO_H
#define VIDEO_H
#include <allegro.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "Material.cpp"
#include "Platform.cpp"
#include "Player.cpp"
#include "Gravity.cpp"

// I'll say one. when you construct the Players, pass a reference to the platforms vector./
class Video
{

public:
	int screenWidth(){ return _width; }
	int screenHeight(){ return _height; }
	//adds a material which can be later found by name parameter
	//--------------------------------------------------------------
	void addMaterial(std::string name, std::string location,float width, float height)
	{
		Material t(name, location, width, height);
		materials_.push_back(t);
	}
	//adds a platform which CANNOT be found later
	//------------------------------------------------
	void addPlatform(std::string material_name, float xo, float yo, float xf, float yf) 
	{
		Platform t(getMaterialPath(material_name),  xo, yo, xf, yf);
		platforms_.push_back(t);
	}
	//adds a player to the player database
	//--------------------------------------------------------------------------------------------------
	void addPlayer(std::string name, std::string material_name,int width, int height, float x, float y)
	{
		Player t(name, material_name, width, height, x, y); 
		players_.push_back(t);
	}
	//adds a base platform which must be added sooner or later, game will not work otherwise
	//there can only be one base floor
	//---------------------------------------------------------------------------------------
	void addBasePlatform(std::string material_name,float height) 
	{
			Platform t(getMaterialPath(material_name), 0, screenHeight()-height, screenWidth(), screenHeight());
			platforms_.insert(platforms_.begin(), t);
	}
	//constructor, takes the height, width, and color depth of the screen window
	//----------------------------------------------------------------------------
	Video(int height, int width, int color_depth)
	{
		_width = width;
		_height = height;
		_color_depth = color_depth;

		// generic allegro initialization, leave be
		allegro_init();
		install_keyboard();
		set_color_depth(_color_depth);

		if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, screenWidth(), screenHeight(), 0, 0))
		{
			allegro_message("Unable to set graphics mode.\n");
			exit(1);
		}

		if(!init_double_buffering())
		{
			set_gfx_mode(GFX_TEXT,0,0,0,0);
			allegro_message("Unable to initialize page flipping.\n");
			exit(1);
		}
	}
	//clears the keyboard buffer making it clean for next button push
	//----------------------------------------------------------------------
	void clearKeyboardBuffer()
	{
		// remove anything that might still remain in the keyboard buffer
		clear(buffer); 
		clear_keybuf();
	}
	//redraws and updates all things on the screen, usually called when something is updated
	//----------------------------------------------------------------------------
	void update(Orientation x_orien, Orientation y_orien)
	{
		players_[0].update(x_orien, y_orien, platforms_);
		update(); 
	}
	void update()
	{
		for(int i = 0; i < players_.size(); i++)
		{
			std::string s = players_[i].getFileName();
			draw_sprite(buffer, load_bitmap(s.c_str(), NULL) , players_[i].getX(), players_[i].getY());
		}

		//drawing all platforms by iterating through each element in the platform vector
		//the first element is the base floor
		for(int i = 0; i < platforms_.size(); i++)
		{
			//height of each platform, final y minus initial y 
			int height = platforms_[i].getYf() - platforms_[i].getYo();

			//find the material name associated with a given pointer to a path
			std::string s = getMaterialFileName(platforms_[i].getPath());

			stretch_sprite(buffer, load_bitmap(s.c_str(), NULL) , platforms_[i].getXo(), platforms_[i].getYo(),  platforms_[i].getXf(), height);
		}

		//draw buffer to screen
		blit(buffer, screen, 0,0,0,0, screenWidth(), screenHeight());
	}

private:
	BITMAP* buffer;
	int _width; // width of screen
	int _height;// height of screen
	int _color_depth;
	std::vector<Material> materials_; //textures of all objects including monsters and floors
	std::vector<Platform> platforms_;
	std::vector<Player> players_;
	friend class Player;
	
	//enables double buffering for improved frame rate
	//----------------------------------------------------
	int init_double_buffering()
	{
		buffer = create_bitmap(screenWidth(), screenHeight());

		if(!buffer)	
			return false;

		return true;
	}
	//returns the pointer of a bitmap such as "grass01" 
	//-------------------------------------------------------------------
	BITMAP* getMaterialPath(std::string query)
	{
		for(int i = 0; i < materials_.size(); i++)
		{
			if(materials_[i].getReferenceName() == query)
				return materials_[i].getPath();
		}

		return 0;
	}
	//returns the FILE NAME ("grass.bmp") of a material as opposed to the reference name of it "grass01"
	//--------------------------------------------------------------------------------------
	std::string getMaterialFileName(BITMAP* query)
	{
		for(int i = 0; i < materials_.size(); i++)
		{
			if(materials_[i].getPath() == query)
				return materials_[i].getFileName();
		}

		return 0;
	}

};
#endif
