#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Game.h"
#include "Base.h"
#include "GameMap.h"
#include "Character.h"
#include "ImpTimer.h"

Base g_background;
Mix_Music* music;

const char* path = "map/map01.txt";

bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("Game Cpp SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		Screen_Width, Screen_Height, SDL_WINDOW_SHOWN);

	if (g_window == NULL) success = false;
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) success = false;
		else {
			SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) and imgFlags)) success = false;
		}
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	return success;
}

bool LoadBackground()
{
	bool ret = g_background.LoadImage("GameAssets/Background/background.png", g_screen);
	if (ret == false) return false;
	return true;
}

void close()
{
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	Mix_FreeMusic(music);
	music = NULL;

	IMG_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	ImpTimer Timer;

	if (InitData() == false) return -1; 
	if (LoadBackground() == false) return -1;

	music = Mix_LoadMUS("sound/GameTheme.mp3");
	Mix_PlayMusic(music, -1);

	GameMap game_map;
	game_map.LoadMap(path);
	game_map.LoadTile(g_screen);

	Character player;
	player.LoadImage("GameAssets/Character/RightWalk.png", g_screen);
	player.SetSprite();

	bool is_quit = false;
	while (!is_quit)
	{
		Timer.start();
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}

			player.Handle(g_event, g_screen);
		}

		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);
		Map map_data = game_map.getMap();

		player.setMapXY(map_data.start_x, map_data.start_y);
		player.DoPlayer(map_data);
		player.Show(g_screen);
		if (player.check() == true) is_quit = true;

		game_map.setMap(map_data);
		game_map.DrawMap(g_screen);

		SDL_RenderPresent(g_screen);

		int real_time = Timer.get_ticks();
		int frame_time = 1000 / FPS;

		if (real_time < frame_time)
		{
			int delay_time = frame_time - real_time;
			if (delay_time >= 0) SDL_Delay(delay_time);
		}
	}
	
	return 0;
}