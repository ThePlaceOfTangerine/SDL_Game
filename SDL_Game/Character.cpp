 #include "Character.h"

Character::Character()
{
	frame = 0;
	x_pos = 0;
	y_pos = 0;
	x = 0;
	y = 0;
	map_x = 0;
	map_y = 0;

	Width_Frame = 0;
	Height_Frame = 0;

	status = -1;
	input_type.left = 0;
	input_type.right = 0;
	input_type.jump = 0;
	on_ground = false;
	first_step_ground = false;
	Win_game = 0;
}

Character::~Character()
{

}

bool Character::LoadImage(std::string path, SDL_Renderer* screen)
{
	bool ret = Base::LoadImage(path, screen);

	if (ret == true)
	{
		Width_Frame = rect.w / 8;
		Height_Frame = rect.h;
	}

	return ret;
}

void Character::SetSprite()
{
	if (Width_Frame > 0 and Height_Frame > 0)
	{
		frame_clip[0].x = 0;
		frame_clip[0].y = 0;
		frame_clip[0].w = Width_Frame;
		frame_clip[0].h = Height_Frame;

		frame_clip[1].x = Width_Frame;;
		frame_clip[1].y = 0;
		frame_clip[1].w = Width_Frame;
		frame_clip[1].h = Height_Frame;
		 
		frame_clip[2].x = 2 * Width_Frame;;
		frame_clip[2].y = 0;
		frame_clip[2].w = Width_Frame;
		frame_clip[2].h = Height_Frame;

		frame_clip[3].x = 3 * Width_Frame;
		frame_clip[3].y = 0;
		frame_clip[3].w = Width_Frame;
		frame_clip[3].h = Height_Frame;

		frame_clip[4].x = 4 * Width_Frame;
		frame_clip[4].y = 0;
		frame_clip[4].w = Width_Frame;
		frame_clip[4].h = Height_Frame;

		frame_clip[5].x = 5 * Width_Frame;
		frame_clip[5].y = 0;
		frame_clip[5].w = Width_Frame;
		frame_clip[5].h = Height_Frame;

		frame_clip[6].x = 6 * Width_Frame;
		frame_clip[6].y = 0;
		frame_clip[6].w = Width_Frame;
		frame_clip[6].h = Height_Frame;

		frame_clip[7].x = 7 * Width_Frame;
		frame_clip[7].y = 0;
		frame_clip[7].w = Width_Frame;
		frame_clip[7].h = Height_Frame;
	}
}

void Character::Show(SDL_Renderer* renderer)
{
	if (on_ground == true)
	{
		if (status == Walk_Left)
		{
			LoadImage("GameAssets/Character/LeftWalk.png", renderer);
		}
	
		else if(status == Walk_Right)
		{
			LoadImage("GameAssets/Character/RightWalk.png", renderer);
		}
	}

	if (input_type.left == 1 || input_type.right == 1) frame = (frame + 1) % 8;
	else frame = 0;

	rect.x = (x_pos - map_x);
	rect.y = (y_pos - map_y);

	SDL_Rect* current_clip = &frame_clip[frame];

	SDL_Rect renderQuad = { rect.x, rect.y, Width_Frame, Height_Frame };

	SDL_RenderCopy(renderer, texture, current_clip, &renderQuad);
}

void Character::Handle(SDL_Event event, SDL_Renderer* screen)
{
	if (first_step_ground == true)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_d:
			case SDLK_RIGHT:
			{
				status = Walk_Right;
				input_type.right = 1;
				input_type.left = 0;
				if (on_ground == false)
				{
					LoadImage("GameAssets/Character/RightWalk.png", screen);
				}
			}
			break;

			case SDLK_a:
			case SDLK_LEFT:
			{
				status = Walk_Left;
				input_type.left = 1;
				input_type.right = 0;
				if (on_ground == false)
				{
					LoadImage("GameAssets/Character/LeftWalk.png", screen);
				}
			}
			break;

			default:
				break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_d:
			case SDLK_RIGHT:
			{
				status = Walk_Right;
				input_type.right = 0;
			}
			break;

			case SDLK_a:
			case SDLK_LEFT:
			{
				status = Walk_Left;
				input_type.left = 9;
			}
			break;

			default:
				break;
			}
		}

		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
				input_type.jump = 1;
		}
	}
}

void Character::DoPlayer(Map& map_data)
{
	x = 0;
	if (!first_step_ground) {
		y += 100;
	}
	else {
		y += Gravity;
		if (y >= Max_Fall_Speed) y = Max_Fall_Speed;
	}

	if (input_type.left == 1) x -= Player_Speed;
	else if (input_type.right == 1) x += Player_Speed;

	if (input_type.jump == 1)
	{
		if (on_ground == true)
		{
			y = -Player_Jump_Height;
		}

		on_ground = false;
		input_type.jump = 0;
	}

	CheckToMap(map_data);
	CenterCamera(map_data);
}

void Character::CheckToMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//Check horizontal 
	int height_min = min(Height_Frame, Tile_Size);
	
	x1 = (x_pos + x) / Tile_Size; 
	x2 = (x_pos + x + Width_Frame - 1) / Tile_Size; 

	y1 = (y_pos) / Tile_Size;
	y2 = (y_pos + height_min - 1) / Tile_Size;

	if (x1 >= 0 and x2 < Max_Map_X and y1 >= 0 and y2 < Max_Map_Y)
	{
		if (x > 0)
		{
			if (map_data.Tile_Map[y1][x2] != 0 || map_data.Tile_Map[y2][x2] != 0)
			{
				x_pos = x2 * Tile_Size;
				x_pos -= (Width_Frame + 1);
				x = 0;

				if (map_data.Tile_Map[y1][x2] == 11 || map_data.Tile_Map[y2][x2] == 11)
				{
					Win_game = true;
				}
			}
		}
		else if (x < 0)
		{
			if (map_data.Tile_Map[y1][x1] != 0 || map_data.Tile_Map[y2][x1] != 0)
			{
				x_pos = (x1 + 1) * Tile_Size;
				x = 0;
			}
		}
	}

	//Check vertical

	int width_min = min(Width_Frame, Tile_Size);
	x1 = (x_pos) / Tile_Size;
	x2 = (x_pos + width_min) / Tile_Size;

	y1 = (y_pos + y) / Tile_Size;
	y2 = (y_pos + y + Height_Frame - 1) / Tile_Size;
		
	if (x1 >= 0 and x2 < Max_Map_X and y1 >= 0 and y2 < Max_Map_Y)
	{
		if (y > 0)
		{
			if (map_data.Tile_Map[y2][x1] != 0 || map_data.Tile_Map[y2][x2] != 0)
			{
				y_pos = y2 * Tile_Size;
				y_pos -= (Height_Frame + 1);
				y = 0;
				on_ground = true;
				if (first_step_ground == false) first_step_ground = true;
			}
		}	
		else if (y < 0)
		{
			if (map_data.Tile_Map[y1][x1] != 0 || map_data.Tile_Map[y1][x2] != 0)
			{
				y_pos = (y1 + 1) * Tile_Size;
				y = 0;
			}
		}
	}

	x_pos += x;
	y_pos += y;

	if (x_pos < 0) x_pos = 0;
	else if (x_pos + Width_Frame > map_data.Max_X) x_pos = map_data.Max_X - Width_Frame - 1;
}

void Character::CenterCamera(Map& map_data)
{
	map_data.start_x = x_pos - (Screen_Width / 2);
	if (map_data.start_x < 0)
	{
		map_data.start_x = 0;
	}
	else if (map_data.start_x + Screen_Width >= map_data.Max_X)
	{
		map_data.start_x = map_data.Max_X - Screen_Width;
	}

	map_data.start_y = y_pos - (Screen_Height / 2);
	if (map_data.start_y < 0) map_data.start_y = 0;
	else if (map_data.start_y + Screen_Height >= map_data.Max_Y) map_data.start_y = map_data.Max_Y - Screen_Height;

}