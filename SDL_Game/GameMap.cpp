#include "GameMap.h"

void GameMap::LoadMap(const char* path)
{
	FILE* fp = NULL;
	fopen_s(&fp, path, "rb");
	if (fp == NULL) return;

	game_map.Max_X = game_map.Max_Y = 0;

	for (int i = 0; i < Max_Map_Y; i++)
	{
		for (int j = 0; j < Max_Map_X; j++)
		{
			fscanf_s(fp, "%d", &game_map.Tile_Map[i][j]);
			int val = game_map.Tile_Map[i][j];
			if (val > 0)
			{
				if (j > game_map.Max_X)
				{
					game_map.Max_X = j;
				}

				if (i > game_map.Max_Y)
				{
					game_map.Max_Y = i;
				}
			}
		}
	}

	game_map.Max_X = (game_map.Max_X + 1)*Tile_Size;
	game_map.Max_Y = (game_map.Max_Y + 1) * Tile_Size;

	game_map.start_x = 0;
	game_map.start_y = 0;

	// game_map.fileName = path;
	fclose(fp);
}

void GameMap::LoadTile(SDL_Renderer* screen)
{
	char file_img[30];
	FILE* fp = NULL;

	for (int i = 0; i < Max_Tile; i++)
	{
		sprintf_s(file_img, "map/%d.png", i);

		fopen_s(&fp, file_img, "rb");
		if (fp == NULL) continue;

		fclose(fp);

		tile_map[i].LoadImage(file_img, screen);
	}
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = game_map.start_x / Tile_Size;
	x1 = (game_map.start_x % Tile_Size) * -1;
	x2 = x1 + Screen_Width + (x1 == 0 ? 0 : Tile_Size);

	map_y = game_map.start_y / Tile_Size;
	y1 = (game_map.start_y % Tile_Size) * -1;
	y2 = y1 + Screen_Height + (y1 == 0 ? 0 : Tile_Size);

	for (int i = y1; i < y2; i += Tile_Size)
	{
		map_x = game_map.start_x / Tile_Size;
		for (int j = x1; j < x2; j += Tile_Size)
		{
			int val = game_map.Tile_Map[map_y][map_x];
			if (val > 0)
			{
				tile_map[val].setRect(j, i);
				tile_map[val].Render(screen);
			}
			map_x++;
		}
		map_y++;
	}
}