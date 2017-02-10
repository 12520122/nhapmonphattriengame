
#include "DirectxGraphic.h"
#include "DirectxInput.h"
#include "camera.h"
#include "Sprite.h"
#include "cutman.h"
#include "boomman.h"
#include "rockman.h"
#include "BrickHidden.h"
#include "bubble.h"
#include "stair.h"

#define GameFps 60
class Cgame
{
private:
	
	HINSTANCE hInstance;
	int Width;
	int Height;
	char gameName[256];
	DirectxGraphic *mdxGraphic;
	DirectxInput *mdxInput;
	Sprite *cutmanSprite;
	Sprite *boommanSprite;
	Sprite *rockmanSprite;
	Sprite *brickhiddenSprite;
	Sprite *bubbleSprite;
	Sprite *stairSprite;
	camera gameCamera;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	HWND hWnd;
	Cgame(HINSTANCE hInstance, int Width, int Height, char* gameName);
	bool InitWindow();
	bool InitGame();
	void Update(LARGE_INTEGER stp);
	void Render();
	void ProcessInput();
	void UpdateCamera();
	void Reset();
	void ProcessGame();
	~Cgame(void);
};