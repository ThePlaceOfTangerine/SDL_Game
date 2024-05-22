#pragma once
#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include "Game.h"
#include "Base.h"

#define Max_Tile 20

class TileMap : public Base
{
public:
	TileMap() { ; }
	~TileMap() { ; }
};

class GameMap
{
public: 
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap(const char* path);
	void LoadTile(SDL_Renderer* renderer);
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const { return game_map; }
	void setMap(Map& map_data) { game_map = map_data; }
private:
	Map game_map;
	TileMap tile_map[Max_Tile];
};

#endif // !GAMEMAP_H_
