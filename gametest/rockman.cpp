#include "rockman.h"
#define IMG_LOCATION_ROCKMAN_STAND "./anhlamgame/rockman/rockman_stand.png"
#define IMG_LOCATION_ROCKMAN_MOVE "./anhlamgame/rockman/rockman_run.png"
#define IMG_LOCATION_ROCKMAN_JUMP "./anhlamgame/rockman/rockman_jump.png"
#define IMG_LOCATION_ROCKMAN_COLLISION "./anhlamgame/rockman/rockman_collide.png"
#define IMG_LOCATION_ROCKMAN_JUMP_FIRE "./anhlamgame/rockman/rockman_jump_fire.png"
#define IMG_LOCATION_ROCKMAN_MOVE_FIRE "./anhlamgame/rockman/rockman_run_fire.png"
#define IMG_LOCATION_ROCKMAN_STAND_FIRE "./anhlamgame/rockman/rockman_stand_fire.png"
#define MAX_STAND_INDEX 2
#define MAX_MOVE_INDEX 3
#define MAX_JUMP_INDEX 1
#define MAX_STAND_FIRE_INDEX 1
#define MAX_JUMP_FIRE_INDEX 1
#define MAX_MOVE_FIRE_INDEX 3
#define MAX_COLLISION_INDEX 2
#define ROCKMAN_DEFAULT_STATE STAND
#define DEFAULT_POSITION_X 400
#define DEFAULT_POSITION_Y 90
#define ROCKMAN_MOVE_RATE 7 // so hinh cho 1 chuyendong
#define ROCKMAN_MOVE_FIRE_RATE 7
#define ROCKMAN_STAND_RATE 20
#define ROCKMAN_STAND_FIRE_RATE 1
#define ROCKMAN_COLLISION_RATE 7
#define ROCKMAN_MOVE_SPEED 0.1f
#define ROCKMAN_JUMP_SPEED 0.6f
#include <iostream>
using namespace std;

rockman::rockman(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler) : Sprite(d3ddev, SpriteHandler)
{
	this->id = ROCKMAN;
	this->listTextureSprite = new LPDIRECT3DTEXTURE9[7];
	this->listTextureEffect = new LPDIRECT3DTEXTURE9[2];
	this->currState = STAND;
	this->enableState = new bool[7]{ false };
	this->IsState = new bool[7]{ false };
	this->currIndexState = 0;
	this->IsAuto = false;
	this->currPosition = { DEFAULT_POSITION_X, DEFAULT_POSITION_Y, 0 };
	this->center = { 12,12,0 };
	this->Vx = 0;
	this->Vy = 0;
	//this->a = 0.00006;
	this->Ax = 0;
	this->Ay = -granvity;
}
void rockman::UpdateRender(LARGE_INTEGER stp)
{
	LARGE_INTEGER frequence;
	QueryPerformanceFrequency(&frequence);
	double t = ((stp.QuadPart - this->lastStp.QuadPart) / (double)frequence.QuadPart) * 1000;
	this->currIndexState++;

	//if (t >= (1000.0 / 60)*RATE)
	//{
	//	this->currIndexState++;
	//	this->currIndexState = this->currIndexState % 2;

	//	this->lastStp = stp;
	//}
	//this->Vx += a * (1000.0 / 60);
	//this->currPosition.x += this->Vx * (1000.0 / 60);
}

bool rockman::Init()
{
	HRESULT result;
	D3DXIMAGE_INFO ImageSprite;
	//STAND
	result = D3DXGetImageInfoFromFile(IMG_LOCATION_ROCKMAN_STAND, &ImageSprite);
	result = D3DXCreateTextureFromFileEx(this->d3ddev, IMG_LOCATION_ROCKMAN_STAND, ImageSprite.Width, ImageSprite.Height,
	1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &ImageSprite, NULL,
	&this->listTextureSprite[0]);
	//MOVE
	result = D3DXGetImageInfoFromFile(IMG_LOCATION_ROCKMAN_MOVE, &ImageSprite);
	result = D3DXCreateTextureFromFileEx(this->d3ddev, IMG_LOCATION_ROCKMAN_MOVE, ImageSprite.Width, ImageSprite.Height,
		1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &ImageSprite, NULL,
		&this->listTextureSprite[1]);
	//JUMP
	result = D3DXGetImageInfoFromFile(IMG_LOCATION_ROCKMAN_JUMP, &ImageSprite);
	result = D3DXCreateTextureFromFileEx(this->d3ddev, IMG_LOCATION_ROCKMAN_JUMP, ImageSprite.Width, ImageSprite.Height,
		1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &ImageSprite, NULL,
		&this->listTextureSprite[2]);
	//COLLISION
	result = D3DXGetImageInfoFromFile(IMG_LOCATION_ROCKMAN_COLLISION, &ImageSprite);
	result = D3DXCreateTextureFromFileEx(this->d3ddev, IMG_LOCATION_ROCKMAN_COLLISION, ImageSprite.Width, ImageSprite.Height,
		1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &ImageSprite, NULL,
		&this->listTextureSprite[3]);
	//JUMP_FIRE
	result = D3DXGetImageInfoFromFile(IMG_LOCATION_ROCKMAN_JUMP_FIRE, &ImageSprite);
	result = D3DXCreateTextureFromFileEx(this->d3ddev, IMG_LOCATION_ROCKMAN_JUMP_FIRE, ImageSprite.Width, ImageSprite.Height,
		1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &ImageSprite, NULL,
		&this->listTextureSprite[4]);
	//MOVE_FIRE
	result = D3DXGetImageInfoFromFile(IMG_LOCATION_ROCKMAN_MOVE_FIRE, &ImageSprite);
	result = D3DXCreateTextureFromFileEx(this->d3ddev, IMG_LOCATION_ROCKMAN_MOVE_FIRE, ImageSprite.Width, ImageSprite.Height,
		1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &ImageSprite, NULL,
		&this->listTextureSprite[5]);
	//STAND_FIRE
	result = D3DXGetImageInfoFromFile(IMG_LOCATION_ROCKMAN_STAND_FIRE, &ImageSprite);
	result = D3DXCreateTextureFromFileEx(this->d3ddev, IMG_LOCATION_ROCKMAN_STAND_FIRE, ImageSprite.Width, ImageSprite.Height,
		1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &ImageSprite, NULL,
		&this->listTextureSprite[6]);

	D3DXIMAGE_INFO ImageEffect;

	if (result != D3D_OK)
	{
		return false;
	}
	return true;
}
void rockman::Render(camera gameCamera)
{
	D3DXMATRIX matrixTransform;
	D3DXVECTOR2 scale(this->FaceDirection, 1);
	D3DXMatrixTransformation2D(&matrixTransform, &(D3DXVECTOR2)gameCamera.intoCamera(this->currPosition, NULL), 0, &scale, &(D3DXVECTOR2)this->getCenterState(this->currState), NULL, NULL);
	this->SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	this->SpriteHandler->SetTransform(&matrixTransform);
	this->SpriteHandler->Draw(this->listTextureSprite[this->currState], &this->getRectState(this->currState), &this->getCenterState(this->currState), &gameCamera.intoCamera(this->currPosition, NULL), D3DCOLOR_XRGB(255,255,255));
	this->SpriteHandler->End();
}

RECT rockman::getRectState(State state)
{
	RECT currRect;
	switch (state)
	{
	case STAND:
	{
		this->currIndexState = this->currIndexState % (ROCKMAN_STAND_RATE*MAX_STAND_INDEX);
		if (ROCKMAN_STAND_RATE > currIndexState && currIndexState >= 0)
		{
			currRect.top = 0;
			currRect.left = 0;
			currRect.bottom = 24;
			currRect.right = 21;
		}
		if (2 * ROCKMAN_STAND_RATE > currIndexState && currIndexState >= ROCKMAN_STAND_RATE)
		{
			currRect.top = 0;
			currRect.left = 21;
			currRect.bottom = 24;
			currRect.right = 42;
		}
		break;
	}	
	case MOVE:
	{
		this->currIndexState = this->currIndexState % (ROCKMAN_MOVE_RATE*MAX_MOVE_INDEX);
		if (ROCKMAN_MOVE_RATE > currIndexState && currIndexState >= 0)
		{
			currRect.top = 0;
			currRect.left = 0;
			currRect.bottom = 24;
			currRect.right = 24;
		}
		if (2 * ROCKMAN_MOVE_RATE > currIndexState && currIndexState >= ROCKMAN_MOVE_RATE)
		{
			currRect.top = 0;
			currRect.left = 24;
			currRect.bottom = 24;
			currRect.right = 48;
		}
		if (3 * ROCKMAN_MOVE_RATE > currIndexState && currIndexState >= 2 *ROCKMAN_MOVE_RATE)
		{
			currRect.top = 0;
			currRect.left = 48;
			currRect.bottom = 24;
			currRect.right = 72;
		}
		break;
	}
	case MOVE_FIRE:
	{
		this->currIndexState = this->currIndexState % (ROCKMAN_MOVE_FIRE_RATE*MAX_MOVE_FIRE_INDEX);
		if (ROCKMAN_MOVE_FIRE_RATE > currIndexState && currIndexState >= 0)
		{
			currRect.top = 0;
			currRect.left = 0;
			currRect.bottom = 24;
			currRect.right = 32;
		}
		if (2 * ROCKMAN_MOVE_FIRE_RATE > currIndexState && currIndexState >= ROCKMAN_MOVE_FIRE_RATE)
		{
			currRect.top = 0;
			currRect.left = 32;
			currRect.bottom = 24;
			currRect.right = 64;
		}
		if (3 * ROCKMAN_MOVE_FIRE_RATE > currIndexState && currIndexState >= 2 * ROCKMAN_MOVE_FIRE_RATE)
		{
			currRect.top = 0;
			currRect.left = 64;
			currRect.bottom = 24;
			currRect.right = 96;
		}
		break;
	}
	case JUMP:
	{
		this->currIndexState = this->currIndexState % (ROCKMAN_MOVE_RATE*MAX_JUMP_INDEX);
		currRect.top = 0;
		currRect.left = 0;
		currRect.bottom = 30;
		currRect.right = 26;
		break;
	}
	case COLLISION:
	{
		this->currIndexState = this->currIndexState % (ROCKMAN_COLLISION_RATE*MAX_COLLISION_INDEX);
		if (ROCKMAN_COLLISION_RATE > currIndexState && currIndexState >= 0)
		{
			currRect.top = 0;
			currRect.left = 0;
			currRect.bottom = 28;
			currRect.right = 26;
		}
		if (2 * ROCKMAN_COLLISION_RATE > currIndexState && currIndexState >= ROCKMAN_COLLISION_RATE)
		{
			currRect.top = 0;
			currRect.left = 26;
			currRect.bottom = 28;
			currRect.right = 52;
		}
		break;
	}
	case JUMP_FIRE:
	{
		this->currIndexState = this->currIndexState % (ROCKMAN_MOVE_RATE*MAX_JUMP_INDEX);
		currRect.top = 0;
		currRect.left = 0;
		currRect.bottom = 30;
		currRect.right = 29;
		break;
	}
	case STAND_FIRE:
	{
		this->currIndexState = this->currIndexState % (ROCKMAN_STAND_FIRE_RATE*MAX_STAND_FIRE_INDEX);
		currRect.top = 0;
		currRect.left = 0;
		currRect.bottom = 24;
		currRect.right = 31;
		break;
	}
	default:
		break;
	}
	return currRect;
}
D3DXVECTOR3 rockman::getCenterState(State state)
{
	D3DXVECTOR3 center;
	switch (state)
	{
	case STAND:
	{
		center.x = center.y = 12;
		center.z = 0;
		break;
	}
	case MOVE:
	{
		center.x = center.y = 12;
		center.z = 0;
		break;
	}
	case JUMP:
	{
		center.x = 14;
		center.y = 15;
		center.z = 0;
		break;
	}
	case COLLISION:
	{
		center.x = 13;
		center.y = 14;
		center.z = 0;
		break;
	}
	case JUMP_FIRE:
	{
		center.x = 14;
		center.y = 15;
		center.z = 0;
	}
	case MOVE_FIRE:
	{
		center.x = 16;
		center.y = 16;
		center.z = 0;
	}
	case STAND_FIRE:
	{
		center.x = 15;
		center.y = 15;
		center.z = 0;
	}
	default:
		break;
	}
	return center;
}
void rockman::ProcessCollision(collisionType type, Sprite *sprite)
{
	SpriteIdentity id = sprite->getId();
	switch (id)
	{
	//case CUTMAN:
	//{
	//	if (type == LEFT)
	//	{
	//		this->Vx = -0.2;
	//		this->Vy = 0.18;
	//		this->currState = COLLISION;
	//		this->IsAuto = true;
	//	}
	//	if (type == RIGHT)
	//	{
	//		this->Vx = 0.2;
	//		this->Vy = 0.18;
	//		this->currState = COLLISION;
	//		this->IsAuto = true;
	//	}
	//	if (type == TOP)
	//	{
	//		this->Vx = sprite->getVx();
	//		if(this->Vy < 0)
	//		{
	//			this->Vy = sprite->getVy();
	//		}
	//		else
	//		{
	//			this->Vy = this->Vy + sprite->getVy();
	//		}
	//		
	//		if (this->currState == JUMP)
	//		{
	//			this->currState = STAND;
	//		}
	//		this->enableState[JUMP] = true;
	//		this->IsState[MOVE] = false;
	//		this->IsState[JUMP] = false;
	//		this->IsState[STAND] = false;
	//		this->IsState[STAND_FIRE] = false;
	//	}
	//	if (type == BOTTOM)
	//	{
	//		this->Vy = -0.18;
	//		this->currState = COLLISION;
	//	}
	//	break;
	//}
		
	case BRICKHIDDEN:
	{
		//if (type == LEFT)
		//{
		//	this->Vx = -0.2;
		//	this->Vy = 0.18;
		//	this->currState = COLLISION;
		//}
		//if (type == RIGHT)
		//{
		//	this->Vx = 0.2;
		//	this->Vy = 0.18;
		//	this->currState = COLLISION;
		//}
		if (type == TOP)
		{
			if (this->Vy < 0)
			{
				this->Vy = 0;	
			}
			this->IsAuto = false;
			this->enableState[JUMP] = true;
			this->IsState[MOVE] = false;
			this->IsState[JUMP] = false;
			this->IsState[STAND] = false;
			this->IsState[STAND_FIRE] = false;
		}
		//if (type == BOTTOM)
		//{
		//	this->Vy = -0.18;
		//	this->currState = COLLISION;
		//}
		//break;
	}
	//case STAIR:
	//{
	//	if (type == LEFT|| type == RIGHT)
	//	{
	//		this->currState = STAND_FIRE;
	//	}
	//	if (type == TOP)
	//	{
	//		this->Vx = this->Vx;
	//		if (this->Vy < 0)
	//		{
	//			this->Vy = sprite->getVy();

	//		}
	//		this->currState = STAND;
	//	}
	//	break;
	//}
	default:
		break;
	}

}
void rockman::FixCollision(collisionType type, float deltaX, float deltaY)
{

}
void rockman::ProcessSignalKeyBoard(char* signalState, DIDEVICEOBJECTDATA* signalEvent)
{
	if (!this->IsAuto)
	{
		//State
		if (signalState[DIK_RIGHT] & 0x80)
		{
			this->FaceDirection = 1.0;
			this->IsState[MOVE] = true;
		}
		if (signalState[DIK_LEFT] & 0x80)
		{
			this->FaceDirection = -1.0;
			this->IsState[MOVE] = true;
		}
		if (signalState[DIK_Z] & 0x80)
		{
			this->IsState[STAND_FIRE] = true;
		}


		//Event
		for (int i = 0; i < KEYBOARD_BUFFER_SIZE; i++)
		{
			if (signalEvent[i].dwOfs == DIK_LEFT)
			{
				if (signalEvent[i].dwData == 0)
				{
					this->IsState[MOVE] = false;
					ZeroMemory(&signalEvent[i], sizeof(DIDEVICEOBJECTDATA));
				}
			}
			if (signalEvent[i].dwOfs == DIK_RIGHT)
			{
				if (signalEvent[i].dwData == 0)
				{
					this->IsState[MOVE] = false;
					ZeroMemory(&signalEvent[i], sizeof(DIDEVICEOBJECTDATA));
				}
			}
			if (signalEvent[i].dwOfs == DIK_Z)
			{
				if (signalEvent[i].dwData == 0)
				{
					this->IsState[STAND_FIRE] = false;
					ZeroMemory(&signalEvent[i], sizeof(DIDEVICEOBJECTDATA));
				}
			}
			if (signalEvent[i].dwOfs == DIK_SPACE)
			{
				if (signalEvent[i].dwData == 0)
				{
					if (this->Vy > 0)
					{
						this->Vy = 0;
					}
					ZeroMemory(&signalEvent[i], sizeof(DIDEVICEOBJECTDATA));
				}
				if (signalEvent[i].dwData == 128)
				{
					this->IsState[JUMP] = true;
					ZeroMemory(&signalEvent[i], sizeof(DIDEVICEOBJECTDATA));
				}
			}
		}
	}
}

void rockman::ProcessSignalKeyboardEvent(DIDEVICEOBJECTDATA* signal)
{
	//for (int i = 0; i < KEYBOARD_BUFFER_SIZE; i++)
	//{
	//	if (signal[i].dwOfs == DIK_LEFT)
	//	{
	//		if (signal[i].dwData == 0)
	//		{
	//			this->Vx = 0;
	//			this->currState = STAND;
	//			ZeroMemory(&signal[i], sizeof(DIDEVICEOBJECTDATA));
	//		}
	//	}
	//	if (signal[i].dwOfs == DIK_RIGHT)
	//	{
	//		if (signal[i].dwData == 0)
	//		{
	//			this->Vx = 0 ;
	//			this->currState = STAND;
	//			ZeroMemory(&signal[i], sizeof(DIDEVICEOBJECTDATA));
	//		}
	//	}
	//	if (signal[i].dwOfs == DIK_Z)
	//	{
	//		if (signal[i].dwData == 0)
	//		{
	//			this->currState = STAND;
	//		}
	//	}
	//	if (signal[i].dwOfs == DIK_SPACE)
	//	{
	//		if (signal[i].dwData == 0)
	//		{
	//			if (this->Vy > 0)
	//			{
	//				this->Vy = 0;
	//			}
	//			ZeroMemory(&signal[i], sizeof(DIDEVICEOBJECTDATA));
	//		}
	//		if (signal[i].dwData == 128)
	//		{
	//			if (this->enableState[JUMP])
	//			{
	//				this->Vy = 0.6;
	//				this->currState = JUMP;
	//				this->enableState[JUMP] = false;
	//				ZeroMemory(&signal[i], sizeof(DIDEVICEOBJECTDATA));
	//			}
	//		}
	//		
	//	}

	//}
}
void rockman::UpdatePosition()
{
	this->currPosition.x += this->Vx * (1000.0 / 60);
	this->currPosition.y += this->Vy * (1000.0 / 60);
}
void rockman::UpdateVelocity()
{
	this->Vx += Ax * (1000.0 / 60);
	this->Vy += Ay * (1000.0 / 60);
}
void rockman::Reset()
{
	this->Vx = 0;
	this->Vy = 0;
	this->currState = ROCKMAN_DEFAULT_STATE;
	this->IsState[7] = { false };
	this->enableState[7] = { false };
	this->IsAuto = false;
}
void rockman::UpdateState()
{
	if (IsState[JUMP] == true)
	{
		this->currState = JUMP;
	}
	if (IsState[MOVE] == true)
	{
		this->currState = MOVE;
	}
	if (IsState[STAND] == true)
	{
		this->currState = STAND;
	}
	if (IsState[STAND_FIRE] == true)
	{
		this->currState = STAND_FIRE;
	}
	if (IsState[JUMP] && IsState[MOVE])
	{
		this->currState = JUMP;
	}
	if (IsState[MOVE] && IsState[STAND_FIRE])
	{
		this->currState = MOVE_FIRE;
	}
	if (IsState[JUMP] && IsState[STAND])
	{
		this->currState = JUMP;
	}
	if (IsState[JUMP] && IsState[STAND_FIRE])
	{
		this->currState = JUMP_FIRE;
		this->IsState[STAND_FIRE] = false;
	}
}
void rockman::JumpProcess()
{
	if (this->Vy == 0)
	{
		this->Vy = ROCKMAN_JUMP_SPEED;
	}
	if (this->Vy <= 0 && this->Vy > -ROCKMAN_JUMP_SPEED)
	{

	}
}
void rockman::UpdateTotal()
{
}
rockman::~rockman()
{

}