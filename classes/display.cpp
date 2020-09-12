#include "display.h"
#include <SDL/SDL.h>

int Display::getWidth()
{
	const SDL_VideoInfo * info;

	info = SDL_GetVideoInfo();
	return info->current_w;
}


int Display::getHeight()
{
	const SDL_VideoInfo * info;

	info = SDL_GetVideoInfo();
	return info->current_h;
}
