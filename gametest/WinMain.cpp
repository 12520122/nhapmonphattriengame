#include "Cgame.h"

//HINSTANCE de OS nhan dang ra instance nao cua ung dung. 
//1 application co the co nhieu HINSTANCE va 1 HINSTANCE co the co nhieu cua so (HWND).
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	Cgame gameX(hInstance,600,400, "X");
	if (!gameX.InitWindow())
	{
		MessageBox(NULL, "Can't init", "Error", MB_OK);
		return 0;
	}
	gameX.InitGame();
	ZeroMemory(&msg, sizeof(msg)); //fill all memory of msg with zero;
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;
	LARGE_INTEGER frequence;
	double gameTime = 0;
	QueryPerformanceFrequency(&frequence);
	QueryPerformanceCounter(&startTime);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) //return 0 if no message in queue(don't block), PM_REMOVE delete cac message khoi queue sau khi xu ly xong.
		{
			//TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			QueryPerformanceCounter(&endTime);
			gameTime = ((endTime.QuadPart - startTime.QuadPart) / (double)frequence.QuadPart) * 1000;// tinh bang milisecond
			
			if (gameTime >= (1000.0 /GameFps))
			{
				gameX.Reset();
				gameX.ProcessInput();
				gameX.ProcessGame();
				gameX.Update(startTime);
				gameX.Render();
			}
			
		}
	}
}