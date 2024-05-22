#pragma once
#ifndef TEXTOBJECT_H_
#define TEXTOBJECT_H_

#include "Base.h"

class TextObject
{
public:
	TextObject();
	~TextObject();

	enum TextColor
	{
		Red = 0, 
		White = 1, 
		Black = 2,
	};

	bool LoadRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Free();

	void RenderText(SDL_Renderer* screen, int x_pos, int y_pos);

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	void setText(const std::string& text) { str_val = text; }
	std::string GetText() const { return str_val; }

private:
	std::string str_val;
	SDL_Color text_color = { 255, 255, 255, 255 };
	SDL_Texture* texture;
	int width;
	int height;
};

#endif // !TEXTOBJECT_H_
