#include "Cgame.h"

Cgame::Cgame(HINSTANCE hInstance, int Width, int Height, char* gameName)
{
	this->hInstance = hInstance;
	this->Width = Width;
	this->Height = Height;
	strcpy_s(this->gameName, gameName);
}

LRESULT CALLBACK Cgame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	//case WM_CREATE:
	//	MessageBox(NULL, "create", NULL, 0);
	//	break;
	case WM_DEVICECHANGE:
		MessageBox(NULL, "device change", NULL, 0);
		break;
	case WM_KEYDOWN:
		//MessageBox(NULL, "key down", NULL, 0);
		break;	
		
	case WM_CLOSE:
		//MessageBox(hWnd, "close", NULL, 0);
		DestroyWindow(hWnd);//gui WM_DESTROY to message queue
		break;
	case WM_DESTROY:
		MessageBox(NULL, "destroy", NULL, 0);
		PostQuitMessage(0);// bao cho OS biet la thread dang yeu cau kethuc gui WM_QUIT vao message queue, gui thong diep dang thread meassage - khong phai window message
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	//return 0;
}

bool Cgame::InitWindow()
{
	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hIconSm = 0;
	wndclass.hIcon = 0;
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hInstance = this->hInstance;
	wndclass.lpfnWndProc = (WNDPROC)WndProc;
	wndclass.lpszClassName = "Cgame";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	// dang ki 1 window voi OS, OS cap phat nhieu thu... 
	//+...
	//+OS tao ra message queue
	if (!RegisterClassEx(&wndclass)) 
	{
		return false;
	}
	this->hWnd = CreateWindow("Cgame", this->gameName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, this->Width, this->Height, NULL, NULL, this->hInstance, NULL);
	if (!this->hWnd)
		return false;
	ShowWindow(this->hWnd, SW_NORMAL);
	UpdateWindow(this->hWnd);
	return true;
}

bool Cgame::InitGame()
{
	bool result;
	mdxGraphic = new DirectxGraphic();
	result = mdxGraphic->InitD3D(this->hWnd);
	mdxInput = new DirectxInput();
	result = mdxInput->CreateInput();
	result = mdxInput->CreateKeyboardInput(this->hWnd);
	//boommanSprite = new boomman(mdxGraphic->getDevice(), mdxGraphic->getSpriteHandler());
	//boommanSprite->Init();
	//cutmanSprite = new cutman(mdxGraphic->getDevice(), mdxGraphic->getSpriteHandler());
	//cutmanSprite->Init();
	rockmanSprite = new rockman(mdxGraphic->getDevice(), mdxGraphic->getSpriteHandler());
	rockmanSprite->Init();
	cutmanSprite = new cutman(mdxGraphic->getDevice(), mdxGraphic->getSpriteHandler());
	cutmanSprite->Init();
	brickhiddenSprite = new BrickHidden(mdxGraphic->getDevice(), mdxGraphic->getSpriteHandler());
	brickhiddenSprite->Init();
	bubbleSprite = new bubble(mdxGraphic->getDevice(), mdxGraphic->getSpriteHandler());
	bubbleSprite->Init();
	stairSprite = new stair(mdxGraphic->getDevice(), mdxGraphic->getSpriteHandler());
	stairSprite->Init();
	gameCamera = camera(this->Width, this->Height);
	return result;
}
void Cgame::Render()
{
	this->mdxGraphic->getDevice()->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1, NULL);
	this->mdxGraphic->getDevice()->BeginScene();
	stairSprite->Render(gameCamera);
	cutmanSprite->Render(gameCamera);
	rockmanSprite->Render(gameCamera);
	bubbleSprite->Render(gameCamera);
	brickhiddenSprite->Render(gameCamera);
	
	//boommanSprite->Render();
	
	this->mdxGraphic->getDevice()->EndScene();
	this->mdxGraphic->getDevice()->Present(NULL, NULL, NULL, NULL);
}
void Cgame::Update(LARGE_INTEGER stp)
{
	
	//rockmanSprite->ProcessSignalKeyboardEvent(this->mdxInput->GetKeyBoardEvent()); //Trigger Vx, Vy
	//rockmanSprite->ProcessSignalKeyBoard(this->mdxInput->GetListKeyActive());
	
	
	rockmanSprite->UpdateVelocity();
	cutmanSprite->UpdateVelocity();

	

/*	cutmanSprite->ProcessCollision(cutmanSprite->checkCollision(brickhiddenSprite), brickhiddenSprite);
	rockmanSprite->ProcessCollision(rockmanSprite->checkCollision(brickhiddenSprite), brickhiddenSprite);
	rockmanSprite->ProcessCollision(rockmanSprite->checkCollision(cutmanSprite), cutmanSprite);*/ //check and Fix collision: Vx, Vy, x, y
	//rockmanSprite->ProcessCollision(rockmanSprite->checkCollision(stairSprite), stairSprite);


	//rockmanSprite->ProcessSignalKeyBoard(this->mdxInput->GetListKeyActive());
	
	rockmanSprite->UpdatePosition();
	rockmanSprite->UpdateRender(stp);
	cutmanSprite->UpdatePosition();
	cutmanSprite->UpdateRender(stp);
	bubbleSprite->UpdatePosition();
	bubbleSprite->UpdateRender(stp);
	this->UpdateCamera();

	


	//boommanSprite->Update();
	//cutmanSprite->Update();
}
void Cgame::ProcessInput()
{
	this->mdxInput->ProcessKeyBoard();
	rockmanSprite->ProcessSignalKeyBoard(this->mdxInput->GetListKeyActive(), this->mdxInput->GetKeyBoardEvent());
	rockmanSprite->ProcessSignalKeyboardEvent(this->mdxInput->GetKeyBoardEvent());
}
void Cgame::UpdateCamera()
{
	if (this->rockmanSprite->getPosition().x >= gameCamera.getWidth() / 2.0)
	{
		D3DXVECTOR3 dest;
		dest.x = gameCamera.getPosition().x + this->rockmanSprite->getVx()* (1000.0/60);
		dest.y = gameCamera.getHeight();
		dest.z = 0;
		gameCamera.setPosition(dest);
	}
}
void Cgame::Reset()
{
	rockmanSprite->Reset();
}
void Cgame::ProcessGame()
{
	cutmanSprite->ProcessCollision(cutmanSprite->checkCollision(brickhiddenSprite), brickhiddenSprite);
	rockmanSprite->ProcessCollision(rockmanSprite->checkCollision(brickhiddenSprite), brickhiddenSprite);
	rockmanSprite->ProcessCollision(rockmanSprite->checkCollision(cutmanSprite), cutmanSprite);
}
Cgame::~Cgame(void)
{
}


