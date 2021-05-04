#include "game.h"
#include "SDL2.h"
using namespace std;



void set_buttonMenu(Button &b3, Button &b4)
{
    b3.x=b4.x= 243;
    b3.y=87;
    b4.y=220;
    b3.height=b4.height=102;
    b3.width=b4.width=215;
}
void set_buttonEnd(Button &playagain, Button &menu, Button &quit)
{
    playagain.x=menu.x=quit.x=275;
    playagain.width=menu.width=quit.width=250;
    playagain.height=menu.height=quit.height=150;
    playagain.y=250;
    menu.y=350;
    quit.y=450;
}

void set_buttonStart_Hint(Button &start,Button &hint)
{
    start.x=SCREEN_WIDTH*3/4;
    start.y=SCREEN_HEIGHT-100;
    start.width=100;
    start.height=100;
    hint.x=SCREEN_WIDTH*3/4;
    start.y =100;
    hint.width=100;
    hint.height=100;
}

void set_image(Button &image1,Button &image2, Button &image3)
{
    image1.x=image2.x=image3.x=600;
    image1.y=0;
    image2.y=200;
    image3.y=400;
    image1.width=image2.width=image3.width=image1.height=image2.height=image3.height=200;
}
bool click_button(SDL_Event e, Button button)
{
    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        if(e.button.x>=button.x && e.button.x <= button.x + button.width
        && e.button.y >= button.y && e.button.y<= button.y + button.height)
            return true;
        else
            return false;
    }
    else return false;
}
 void update1(int &k, int &kiemtra, int &initRandom)
 {
     k=1;
     kiemtra=0;
     initRandom=250;
 }

int numberofBoard(SDL_Event e,Button b3, Button b4, int &board)
{
    if(click_button(e,b3))
                        board=3;
    else if(click_button(e,b4))
                        board=4;

    else board=0;
    return board;
}
int numberofImage(SDL_Event e,Button image1,Button image2, Button image3, int &image)
{
    if(click_button(e,image1))
        image=1;
    else if(click_button(e,image2))
        image=2;
    else if(click_button(e,image3))
        image=3;
    else
        image=0;
    return image;
}
bool mouse_motion(SDL_Event e,Button b)
{
    if(e.motion.x>=b.x && e.motion.x<= b.x+b.width && e.motion.y>=b.y && e.motion.y<= b.y+ b.height)
        return true;
    else
        return false;
}


SDL_Texture* loadttf(SDL_Renderer *renderer,TTF_Font *font,std::string text,SDL_Color color)
{
    SDL_Texture *tex=nullptr;
    SDL_Surface *textsurface = TTF_RenderText_Solid(font,text.c_str(),color);
    if(textsurface!=nullptr)
    {
        tex=SDL_CreateTextureFromSurface(renderer,textsurface);
        SDL_FreeSurface(textsurface);
    }
    return tex;
}

void renderText(SDL_Renderer *ren,SDL_Texture *tex,int x,int y,int w,int h)
{
    SDL_Rect desRect;
    desRect.x=x;
    desRect.y=y;
    desRect.w=w;
    desRect.h=h;
    SDL_RenderCopy(ren,tex,NULL,&desRect);
}
void motion_menu(SDL_Renderer* renderer,SDL_Event e,Button b3, Button b4,int &t,SDL_Texture *text3,SDL_Texture *text4)
{
    if(mouse_motion(e,b3))
    {
        renderText(renderer,text3,b3.x,+b3.y,b3.width,b3.height);
        renderText(renderer,text4,b4.x+(b4.width/4),(b4.height/4)+b4.y,b4.width/2,b4.height/2);
        t=1;
    }
    else if(mouse_motion(e,b4))
    {
        renderText(renderer,text3,b3.x+(b3.width/4),(b3.height/4)+b3.y,b3.width/2,b3.height/2);
        renderText(renderer,text4,b4.x,b4.y,b4.width,b4.height);
        t=1;
    }
}

void print_image(SDL_Renderer *renderer,SDL_Texture *tex1,SDL_Texture *tex2,SDL_Texture *tex3)
{
    renderTexture(tex1,renderer,600,0,200,200);
    renderTexture(tex2,renderer,600,200,200,200);
    renderTexture(tex3,renderer,600,400,200,200);
    SDL_RenderPresent(renderer);
}
void motion_image(SDL_Renderer *renderer,SDL_Event e,Button image,SDL_Texture *tex,SDL_Texture *tex2)
{
    if(mouse_motion(e,image))
        renderTexture(tex,renderer,0,0,600,600);
    else if(e.motion.x<=600 || e.motion.x >= 800)
        renderTexture(tex2,renderer,0,0,600,600);
    SDL_RenderPresent(renderer);

}


void Clock(SDL_Renderer* renderer,int &start_time,int initRandom,SDL_Texture *textTime,SDL_Texture* timeCount,TTF_Font *font,SDL_Color color)
{
    stringstream text_time;
    renderText(renderer,textTime,500,150,200,200);
    if(initRandom>0)
    {
        start_time=SDL_GetTicks()/1000;
    }
    text_time.str("");
    text_time << (SDL_GetTicks()/1000)-start_time;
    if(timeCount==NULL)
    {
        SDL_DestroyTexture(timeCount);
        timeCount=loadttf(renderer,font,text_time.str(),color);
        renderText(renderer,timeCount,700,150,50,200);
        SDL_DestroyTexture(timeCount);
    }
}


void print_moves(SDL_Renderer* renderer,int moves,SDL_Texture *textMoves,SDL_Texture *movesCount,TTF_Font *font,SDL_Color color)
{
    stringstream text_moves;
    text_moves.str("");
    text_moves << moves;
    renderText(renderer,textMoves,500,300,200,200);
    if(movesCount==NULL)
    {
        SDL_DestroyTexture(movesCount);
        movesCount=loadttf(renderer,font,text_moves.str(),color);
        renderText(renderer,movesCount,700,300,50,200);
        SDL_DestroyTexture(movesCount);
    }

}

void motion_play(SDL_Renderer* renderer,SDL_Event e,bool start_game,int cell,int board)
{
    ToaDo mouse;
    SDL_Rect motion;
    motion.w=motion.h=cell;
    if(e.type== SDL_MOUSEMOTION && start_game)
    {
        if(e.motion.x>padding_right && e.motion.x <(padding_right+board*cell) && e.motion.y > padding_top && e.motion.y <(padding_top+board*cell))
        {
            mouse.i=(e.motion.y-padding_top)/cell;
            mouse.j=(e.motion.x-padding_right)/cell;
            motion.x=padding_right+mouse.j*cell;
            motion.y=padding_top+mouse.i *cell;
            SDL_SetRenderDrawColor(renderer,255,0,0,255);
            SDL_RenderDrawRect(renderer,&motion);
        }
    }
}

void qwe(SDL_Renderer* renderer,SDL_Event e,bool start_game,Button start,Button hint,SDL_Texture *textStart,SDL_Texture *textHint)
{
    if(!start_game)
    {
        if(e.type==SDL_MOUSEMOTION)
        {
            if(e.motion.x>=start.x&& e.motion.x<=start.x+start.width&& e.motion.y>=start.y&& e.motion.y<=start.y+start.height)
                renderText(renderer,textStart,start.x,start.y,start.width,start.height);
            else
                renderText(renderer,textStart,start.x+(start.width/4),start.y+start.height/4,start.width/2,start.height/2);
        }
        else
            renderText(renderer,textStart,start.x+(start.width/4),start.y+start.height/4,start.width/2,start.height/2);
    }
    else
    {
        if(e.motion.x>=hint.x&& e.motion.x<=hint.x+hint.width&& e.motion.y>=hint.y&& e.motion.y<=hint.y+hint.height)
            renderText(renderer,textHint,hint.x,hint.y,hint.width,hint.height);
        else
            renderText(renderer,textHint,hint.x+(hint.width/4),hint.y+hint.height/4,hint.width/2,hint.height/2);
    }
}

void motion_endgame(SDL_Renderer *renderer,SDL_Event e,Button playagain,Button menu,Button quit,SDL_Texture *tex1,SDL_Texture *tex2,SDL_Texture *tex3,int &k)
{
    if(mouse_motion(e,playagain))
       {
            renderText(renderer,tex1,playagain.x,playagain.y,playagain.width,playagain.height);
            renderText(renderer,tex2,menu.x+25,menu.y+25,menu.width-50,menu.height-50);
            renderText(renderer,tex3,quit.x+25,quit.y+25,quit.width-50,quit.height-50);
           k=1;
       }
    else if(mouse_motion(e,menu))
       {
            renderText(renderer,tex1,playagain.x+25,playagain.y+25,playagain.width-50,playagain.height-50);
            renderText(renderer,tex2,menu.x,menu.y,menu.width,menu.height);
            renderText(renderer,tex3,quit.x+25,quit.y+25,quit.width-50,quit.height-50);
           k=1;
       }
     else if(mouse_motion(e,quit))
       {
            renderText(renderer,tex1,playagain.x+25,playagain.y+25,playagain.width-50,playagain.height-50);
            renderText(renderer,tex2,menu.x+25,menu.y+25,menu.width-50,menu.height-50);
            renderText(renderer,tex3,quit.x,quit.y,quit.width,quit.height);
           k=1;
       }
        else k=0;
}
void print_end(SDL_Renderer *renderer,Button playagain,Button menu,Button quit,SDL_Texture *tex1,SDL_Texture *tex2,SDL_Texture *tex3)
{
    renderText(renderer,tex1,playagain.x+25,playagain.y+25,playagain.width-50,playagain.height-50);
    renderText(renderer,tex2,menu.x+25,menu.y+25,menu.width-50,menu.height-50);
    renderText(renderer,tex3,quit.x+25,quit.y+25,quit.width-50,quit.height-50);
}

void printFinalResult(SDL_Renderer *ren,TTF_Font *font, SDL_Color color,int timeFinal,int moves,int hint)
{
    SDL_Texture *tex1= loadttf(ren,font,"   Final Result   ",color);
    stringstream textTime,textMoves,textHint;
    textTime << timeFinal;
    textMoves<< moves;
    textHint<< hint;
    string text1="Time: " + textTime.str();
    string text2="Moves: " + textMoves.str();
    string text3="Hint:  " + textHint.str();
    SDL_Texture *tex2= loadttf(ren,font,text1,color);
    SDL_Texture *tex3= loadttf(ren,font,text2,color);
    SDL_Texture *tex4= loadttf(ren,font,text3,color);
    if(tex1!=NULL && tex2 != NULL && tex3 !=NULL && tex4 !=NULL)
    {
        renderText(ren,tex1,350,0,400,100);
        renderText(ren,tex2,400,100,300,66);
        renderText(ren,tex3,400,166,300,66);
        renderText(ren,tex4,400,232,300,66);
        SDL_DestroyTexture(tex1);
        SDL_DestroyTexture(tex2);
        SDL_DestroyTexture(tex3);
        SDL_DestroyTexture(tex4);
    }

}



