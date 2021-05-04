#include "SDL2.h"
#include "game.h"

using namespace std;
SDL_Color black={0,0,0};
int lenh;
int board;
int k;
int kiemtra;
int initRandom;
int start_time;
int image;
int timeFinal;
int movesFinal;
int countHint=0;
SDL_Window *window;
SDL_Renderer *renderer;
bool playagain;
bool running =false;
bool menu;
bool start_game;
bool choose_an_image=true;
SDL_Event e;
int moves=0;
Button start,b_playagain,b_menu,b_quit,b3,b4,hint;
Button image1,image2,image3;
ToaDo mouse;
TTF_Font *font;

int main(int argc, char* argv[])
{

    srand(time(NULL));
    initSDL(window,renderer);
    font = TTF_OpenFont("font.ttf",150);
    SDL_Texture* background1= loadTexture("image/background1.bmp",renderer);
    SDL_Texture* image_1    = loadTexture("image/image1/anhchinh.bmp",renderer);
    SDL_Texture* image_2    = loadTexture("image/image2/anhchinh.bmp",renderer);
    SDL_Texture* image_3    = loadTexture("image/image3/anhchinh.bmp",renderer);
    SDL_Texture* white_image= loadTexture("image/white.bmp",renderer);
    SDL_Texture* text3      = loadttf(renderer,font,"3x3",black);
    SDL_Texture* text4      = loadttf(renderer,font,"4x4",black);
    SDL_Texture* textTime   = loadttf(renderer,font,"time: ",black);
    SDL_Texture* textMoves  = loadttf(renderer,font,"moves: ",black);
    SDL_Texture* textStart  = loadttf(renderer,font,"start",black);
    SDL_Texture* textHint  = loadttf(renderer,font,"hint",black);
    SDL_Texture* textPlayagain  = loadttf(renderer,font,"play again",black);
    SDL_Texture* textMenu  = loadttf(renderer,font,"menu",black);
    SDL_Texture* textQuit  = loadttf(renderer,font,"quit",black);
    SDL_Texture* timeCount      = NULL;
    SDL_Texture* movesCount  = NULL;
    set_buttonStart_Hint(start,hint);
    set_buttonEnd(b_playagain,b_menu,b_quit);
    set_buttonMenu(b3,b4);
    set_image(image1,image2,image3);
    do{
        if(menu)
        {
            image=0;
            choose_an_image=true;
        }
        while(!running) // chon so board;
        {
            int t=0;
            SDL_SetRenderDrawColor(renderer,255,255,255,0);
            if(choose_an_image)
                print_image(renderer,image_1,image_2,image_3);
            else
            {
                SDL_RenderClear(renderer);
                renderTexture(background1,renderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
            }

            while(SDL_PollEvent(&e))
            {
                if(e.type==SDL_QUIT) quitSDL(window,renderer);
                if(choose_an_image)
                {
                    if(e.type==SDL_MOUSEBUTTONDOWN)
                    {
                        numberofImage(e,image1,image2,image3,image);
                    }
                    if(image!=0){
                        choose_an_image=false;
                    }

                }
                if(!choose_an_image)
                {
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        numberofBoard(e,b3,b4,board);
                        if(board!=0)
                            running=true;
                    }
                }

                break;
            }
            if(e.type== SDL_MOUSEMOTION)
            {
                if(choose_an_image)
                {
                    motion_image(renderer,e,image1,image_1,white_image);
                    motion_image(renderer,e,image2,image_2,white_image);
                    motion_image(renderer,e,image3,image_3,white_image);
                }

                else
                    motion_menu(renderer,e,b3,b4,t,text3,text4);

            }
            if(t==0 && !choose_an_image){
                renderText(renderer,text3,b3.x+(b3.width/4),(b3.height/4)+b3.y,b3.width/2,b3.height/2);
                renderText(renderer,text4,b4.x+(b4.width/4),(b4.height/4)+b4.y,b4.width/2,b4.height/2);
            }
            SDL_RenderPresent(renderer);
            if(running) break;
        }
        int cell= area_play/board; // kich thuoc môi ô vuông
        SDL_Texture* check[board][board];
        SDL_Texture* images[board][board]; // mảng chứa ảnh mỗi ô
        update1(k,kiemtra,initRandom);
        stringstream image_cell,number_of_image;
        image_cell<<board;
        number_of_image<<image;
        string anhchinh1="image/image"+number_of_image.str()+"/anhchinh.bmp";
        for(int i =0 ; i<board; ++i){
            for(int j=0; j<board; ++j)
            {
                if( i*j==(board-1)*(board-1))
                {
                    images[i][j]=NULL;
                    check[i][j]= NULL;
                }
                else
                {
                    stringstream ss;
                    ss<<k;
                    string text = "image/image"+number_of_image.str()+"/"+image_cell.str()+ "/anh"+ss.str()+".bmp";
                    images[i][j]=loadTexture(text.c_str(),renderer);
                    check[i][j]= images[i][j];
                }
                k++;
            }
        }
        SDL_Texture *anhchinh = loadTexture(anhchinh1.c_str(),renderer);
        SDL_Rect empty_board;
        empty_board.w=empty_board.h=cell;
        start_game =false;
        while(running) // choi game
        {

            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderClear(renderer);
            Clock(renderer,start_time,initRandom,textTime,timeCount,font,black);
            print_moves(renderer,moves,textMoves,movesCount,font,black);
            if(start_game)
            {
                for(int i=0 ; i< board; ++i)
                    for(int j=0; j<board; ++j)
                    {
                        if(images[i][j]!=0)
                            renderTexture(images[i][j],renderer,padding_right+j*cell,padding_top+i*cell,cell,cell);
                        else
                        {
                            empty_board.x=padding_right+ j*cell;
                            empty_board.y=padding_top+i*cell;
                            SDL_SetRenderDrawColor(renderer,0,0,0,255);
                            SDL_RenderFillRect(renderer,&empty_board);
                        }
                    }
                if(click_button(e,hint))
                {
                    int q=SDL_GetTicks()/1000;
                    while(SDL_GetTicks()/1000-q<4)
                    {
                        SDL_SetRenderDrawColor(renderer,255,255,255,255);
                        SDL_RenderClear(renderer);
                        Clock(renderer,start_time,initRandom,textTime,timeCount,font,black);
                        renderTexture(anhchinh,renderer,padding_right,padding_top,area_play,area_play);
                        SDL_RenderPresent(renderer);
                        while(SDL_PollEvent(&e))
                        {
                            if(e.type == SDL_QUIT) quitSDL(window,renderer);
                        }
                    }
                    countHint++;
                }

            }
            else
               renderTexture(anhchinh,renderer,padding_right,padding_top,area_play,area_play);



            motion_play(renderer,e,start_game,cell,board);
            qwe(renderer,e,start_game,start,hint,textStart,textHint);

            SDL_RenderPresent(renderer);
            if(initRandom>0 && start_game)
                        lenh=rand()%4 +1;
            if(initRandom==0)
            {
                for(int i=0; i<board; ++i)
                    for(int j=0; j<board; ++j)
                    {
                        if(images[i][j]==check[i][j])
                            kiemtra++;
                        else {
                            kiemtra=0;
                            i=board;
                            break;
                        }
                    }
                if(kiemtra== board*board)
                {
                    renderTexture(anhchinh,renderer,padding_right,padding_top,area_play,area_play);
                    SDL_RenderPresent(renderer);
                    timeFinal=SDL_GetTicks()/1000-start_time;
                    SDL_Delay(2000);
                    running=false;
                }
            }
            while(SDL_PollEvent(&e))
            {
                if(e.type==SDL_QUIT){
                    quitSDL(window,renderer);
                }
                else if(e.type== SDL_MOUSEBUTTONDOWN)
                {
                    if(e.button.x>padding_right && e.button.x <(padding_right+board*cell) && e.button.y > padding_top && e.button.y <(padding_top+board*cell))
                    {
                        mouse.i=(e.button.y-padding_top)/cell;
                        mouse.j=(e.button.x-padding_right)/cell;
                        if(images[mouse.i-1][mouse.j]==NULL && mouse.i!=0) lenh=1;
                        else if(images[mouse.i+1][mouse.j]==NULL&& mouse.i!=board-1) lenh=2;
                        else if(images[mouse.i][mouse.j+1]==NULL && mouse.j!=board-1) lenh=3;
                        else if(images[mouse.i][mouse.j-1]==NULL && mouse.j !=0) lenh=4;
                    }
                    else if(click_button(e,start)) start_game=true;
                }

                break;
            }
            if(initRandom==0&&lenh!=0) moves++;

            switch(lenh){
                case 1:
                    for( int i=0; i<board; ++i)
                        for(int j=0; j<board;++j)
                            if(images[i][j]==NULL && i!=board-1)
                            {
                                images[i][j]=images[i+1][j];
                                images[i+1][j]=NULL;
                                i=board;
                                break;
                            }
                    break;
                case 2:
                    for( int i=0; i<board; ++i)
                        for(int j=0; j<board;++j)
                            if(images[i][j]==NULL && i!=0)
                            {
                                images[i][j]=images[i-1][j];
                                images[i-1][j]=NULL;
                                i=board;
                                break;
                            }
                    break;
                case 3:
                    for(int i=0; i <board; ++i)
                        for(int j=0; j<board; ++j)
                            if(images[i][j]==NULL && j!=0)
                            {
                                images[i][j]=images[i][j-1];
                                images[i][j-1]=NULL;
                                i=board;
                                break;
                            }
                    break;
                case 4:
                    for(int i=0; i <board; ++i)
                        for(int j=0; j<board; ++j)
                            if(images[i][j]==NULL && j!=board-1)
                            {
                                images[i][j]=images[i][j+1];
                                images[i][j+1]=NULL;
                                i=board;
                                break;
                            }
                    break;
            }
            lenh=0;
            if(initRandom>0 && start_game)
                initRandom--;
        }
        playagain=false;
        menu=false;
        while(!running) // ket thuc
        {
            int n=0;

            SDL_SetRenderDrawColor(renderer,115, 140, 128,255);
            SDL_RenderClear(renderer);
            renderTexture(anhchinh,renderer,0,0,300,300);
            printFinalResult(renderer,font,black,timeFinal,moves,countHint);
            while(SDL_PollEvent(&e))
            {
                if(e.type==SDL_MOUSEBUTTONDOWN)
               {
                    if(click_button(e,b_playagain))
                          playagain=true;
                    else if(click_button(e,b_menu))
                        menu=true;
                    else if(click_button(e,b_quit))
                      quitSDL(window,renderer);
               }
               else if (e.type==SDL_QUIT) quitSDL(window,renderer);
               break;
            }
            if(e.type==SDL_MOUSEMOTION)
            {
                motion_endgame(renderer,e,b_playagain,b_menu,b_quit,textPlayagain,textMenu,textQuit,n);
            }
            if(n==0)
                print_end(renderer,b_playagain,b_menu,b_quit,textPlayagain,textMenu,textQuit);


            if(playagain)
            {
                running=true;
                break;
            }
           else if(menu)
           {
               running=false;
               break;
           }
           SDL_RenderPresent(renderer);
        }
    moves=0;
    countHint=0;
    SDL_RenderClear(renderer);
    }
    while( playagain  || menu);
    quitSDL(window,renderer);
    return 0;
}






