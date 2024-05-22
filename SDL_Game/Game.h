#pragma once
#ifndef GAME_H_
#define GAME_H_

#include <Windows.h>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Screen
const int FPS = 30;
const int Screen_Width = 980;
const int Screen_Height = 480;
const int Screen_BPP = 32;

const int Color_Key_R = 167;
const int Color_Key_G = 175;
const int Color_Key_B = 180;

#define Tile_Size 48

#define Max_Map_X 43
#define Max_Map_Y 1000

struct Input
{
	int left;
	int right;
	int jump;
};

struct Map
{
	int start_x;
	int start_y;

	int Max_X;
	int Max_Y;

	int Tile_Map[Max_Map_Y][Max_Map_X];
	char* fileName;
};

#endif // !GAME_H_
