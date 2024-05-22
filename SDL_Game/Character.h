#pragma once
#ifndef CHARACTER_H_

#include "Game.h"
#include "Base.h"

#define Gravity 1.2
#define Max_Fall_Speed 8
#define Player_Speed 7.5
#define Player_Jump_Height 20

class Character : public Base
{
public:
	Character();
	~Character();

	enum WalkType
	{
		Walk_Right = 0,
		Walk_Left = 1,
	};

	virtual bool LoadImage(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* renderer);
	void Handle(SDL_Event event, SDL_Renderer* screen);
	void SetSprite();

	void DoPlayer(Map& map_data); 
	void CheckToMap(Map& map_data);

	void setMapXY(const int Map_x, const int Map_y) { map_x = Map_x; map_y = Map_y; }
	void CenterCamera(Map& map_data);

	bool check() { return Win_game; }
private:
	float x, y;
	float x_pos, y_pos;
	int map_x, map_y;

	int Width_Frame;
	int Height_Frame;

	SDL_Rect frame_clip[8];
	Input input_type;
	int frame;
	int status;
	bool on_ground;
	bool first_step_ground;
	bool Win_game;
};

#endif // !CHARACTER_H_
