#include "TextObject.h"

TextObject::TextObject()
{
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	texture = NULL;
}

TextObject::~TextObject()
{

}

bool TextObject::LoadRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	texture = SDL_CreateTextureFromSurface(screen, textSurface);
	width = textSurface->w;
	height = textSurface->h;

	SDL_FreeSurface(textSurface);

	return texture != NULL;
}

void TextObject::Free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void TextObject::RenderText(SDL_Renderer* screen, int x_pos, int y_pos)
{
	SDL_Rect renderQuad = { x_pos, y_pos, width, height };
	
	SDL_RenderCopy(screen, texture, NULL, &renderQuad);
}