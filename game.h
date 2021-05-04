#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int padding_right=50;
const int padding_top=100;
const int padding_bottom= 100;
const int area_play =400;



struct Button{
    int x;
    int y;
    int width;
    int height;
    };
struct ToaDo{
    int i;
    int j;
};
void set_buttonMenu(Button &b3, Button &b4);

void set_buttonEnd(Button &playagain, Button &menu, Button &quit);

void set_buttonStart_Hint(Button &start,Button &hint);

void set_image(Button &image1,Button &image2, Button &image3);

bool click_button(SDL_Event e, Button button);

void update1(int &k, int &kiemtra, int &initRandom);

int numberofBoard(SDL_Event e,Button b3, Button b4, int &board);

int numberofImage(SDL_Event e,Button image1,Button image2, Button image3, int &image);

SDL_Texture* loadttf(SDL_Renderer *renderer,TTF_Font *font,std::string text,SDL_Color color);

void renderText(SDL_Renderer *ren,SDL_Texture *tex,int x,int y,int w,int h);


void motion_menu(SDL_Renderer* renderer,SDL_Event e,Button b3, Button b4,int &t,SDL_Texture *text3,SDL_Texture *text4);

void print_image(SDL_Renderer *renderer,SDL_Texture *tex1,SDL_Texture *tex2,SDL_Texture *tex3);

void motion_image(SDL_Renderer *renderer,SDL_Event e,Button image,SDL_Texture *tex,SDL_Texture *tex2);



void Clock(SDL_Renderer* renderer,int &start_time,int initRandom,SDL_Texture *textTime,SDL_Texture* timeCount,TTF_Font *font,SDL_Color color);

void print_moves(SDL_Renderer* renderer,int moves,SDL_Texture *textMoves,SDL_Texture *movesCount,TTF_Font *font,SDL_Color color);

void motion_play(SDL_Renderer* renderer,SDL_Event e,bool start_game,int cell,int board);

void qwe(SDL_Renderer* renderer,SDL_Event e,bool start_game,Button start,Button hint,SDL_Texture *textStart,SDL_Texture *textHint);

void motion_endgame(SDL_Renderer *renderer,SDL_Event e,Button playagain,Button menu,Button quit,SDL_Texture *tex1,SDL_Texture *tex2,SDL_Texture *tex3,int &k);

void print_end(SDL_Renderer *renderer,Button playagain,Button menu,Button quit,SDL_Texture *tex1,SDL_Texture *tex2,SDL_Texture *tex3);

void printFinalResult(SDL_Renderer *ren,TTF_Font *font, SDL_Color color,int timeFinal,int moves,int hint);





#endif // GAME_H_INCLUDED
