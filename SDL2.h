#ifndef SDL2_H_INCLUDED
#define SDL2_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL.h>
#include<SDL_ttf.h>
using namespace std;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void logSDLError(std::ostream& os,
 const std::string &msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

SDL_Texture* loadTexture(const std::string &file,SDL_Renderer *ren);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

#endif // SDL2_H_INCLUDED
