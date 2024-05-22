#include "Base.h"

Base::Base()
{
	texture = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

Base::~Base()
{
	Free();
}

bool Base::LoadImage(std::string path, SDL_Renderer* screen)
{
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_Surface = IMG_Load(path.c_str());
	if (load_Surface != NULL)
	{
		SDL_SetColorKey(load_Surface, SDL_TRUE, SDL_MapRGB(load_Surface->format, Color_Key_R, Color_Key_G, Color_Key_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_Surface);
		if (new_texture != NULL)
		{
			rect.w = load_Surface->w;
			rect.h = load_Surface->h;
		}

		SDL_FreeSurface(load_Surface);

		texture = new_texture;
		
		return texture != NULL;
	}
}

void Base::Render(SDL_Renderer* screen, const SDL_Rect* clip /*= NULL*/)
{
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };

	SDL_RenderCopy(screen, texture, clip, &renderquad);
}

void Base::Free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}