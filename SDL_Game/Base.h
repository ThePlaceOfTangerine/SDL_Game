#pragma once
#ifndef BASE_H_
#define BASE_H_

#include "Game.h"

class Base
{
public:
	Base();
	~Base();

	void setRect(const int& x, const int& y)
	{
		rect.x = x;
		rect.y = y;
	}

	SDL_Rect getRect() const { return rect; }
	SDL_Texture* getTexture() const { return texture; }

	virtual bool LoadImage(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* screen, const SDL_Rect* clip = NULL);
	void Free();

protected:
	SDL_Texture* texture;
	SDL_Rect rect;
};

#endif // !BASE_H_

