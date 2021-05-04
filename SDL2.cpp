#include "SDL2.h"
using namespace std;

const string WINDOW_TITLE = "Sliding Puzzle by Đinh Quốc Hưng";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void logSDLError(std::ostream& os,
 const std::string &msg, bool fatal)
{
 os << msg << " Error: " << SDL_GetError() << std::endl;
 if (fatal) {
 SDL_Quit();
 exit(1);
 }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
 if (SDL_Init(SDL_INIT_EVERYTHING) != 0) logSDLError(std::cout, "SDL_Init", true);
 if (TTF_Init()!=0) logSDLError(std::cout, "TTF_Init",true);
 window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
 SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
 //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
 //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
 if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
 //Khi thông thường chạy với môi trường bình thường ở nhà
 renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
 SDL_RENDERER_PRESENTVSYNC);
 //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
 //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
 if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
 SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
 SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
}

void waitUntilKeyPressed()
{
 SDL_Event e;
 while (true) {
 if ( SDL_WaitEvent(&e) != 0 &&
 (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
 return;
 SDL_Delay(0);
 }
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	//Khởi tạo là nullptr để tránh lỗi 'dangling pointer'
	SDL_Texture *texture = nullptr;
	//Nạp ảnh từ tên file (với đường dẫn)
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Đảm bảo việc chuyển đổi không có lỗi
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
