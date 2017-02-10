
#include "Sprite.h"
Sprite::Sprite()
{
}
Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler)
{
	this->d3ddev = d3ddev;
	D3DXCreateSprite(this->d3ddev, &this->SpriteHandler);
	this->FaceDirection = 1;
}
bool Sprite::Init() 
{
	//D3DXIMAGE_INFO ImageSprite;
	//LPCSTR ImageLocation;
	//HRESULT result = D3DXGetImageInfoFromFile(ImageLocation, &ImageSprite);
	//if (result != D3D_OK)
	//{
	//	return false;
	//}
	//result = D3DXCreateTextureFromFileEx(this->d3ddev, ImageLocation, ImageSprite.Width, ImageSprite.Height,
	//	1,D3DUSAGE_DYNAMIC,D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &ImageSprite, NULL,
	//	&this->texture);
	//D3DXCreateSprite(this->d3ddev, &this->SpriteHandler);

	return true;
}
void Sprite::Render(camera gameCamera)
{	
	//this->d3ddev->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1, NULL);
	//this->d3ddev->BeginScene();
	this->SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	this->SpriteHandler->Draw(texture, NULL, &this->center, &this->currPosition, D3DCOLOR_XRGB(255, 255, 255));
	this->SpriteHandler->End();
	//this->d3ddev->EndScene();
	//this->d3ddev->Present(NULL, NULL, NULL, NULL);
}
void Sprite::UpdateRender(LARGE_INTEGER stp)
{

}
collisionType Sprite::checkCollision(Sprite *sprite)
{
	float dxEntry = 0;
	float dyEntry = 0;
	float txEntry = 0;
	float tyEntry = 0;
	float dxExit = 0;
	float dyExit = 0;
	float txExit = 0;
	float tyExit = 0;
	collisionType tempResultX = NONE;
	collisionType tempResultY = NONE;
	float thisVx = this->Vx - sprite->getVx();
	float thisVy = this->Vy - sprite->getVy();

		if (thisVx > 0)
		{
			dxEntry = (sprite->currPosition.x - this->currPosition.x) - (sprite->center.x + this->center.x);
			dxExit = (sprite->currPosition.x + sprite->center.x) - (this->currPosition.x - this->center.x);
			txEntry = dxEntry / (thisVx * (1000.0 / 60));
			txExit = dxExit / (thisVx * (1000.0 / 60));
		}
		if (thisVx < 0)
		{
			dxEntry = (this->currPosition.x - this->center.x) - (sprite->currPosition.x + sprite->center.x);
			dxExit = (this->currPosition.x + this->center.x) - (sprite->currPosition.x - sprite->center.x);
			txEntry = dxEntry / (-thisVx * (1000.0 / 60));
			txExit = dxExit / (-thisVx * (1000.0 / 60));
		}
		if (thisVx == 0)
		{
			dxEntry = fabs(this->currPosition.x - sprite->currPosition.x) - (this->center.x + sprite->center.x);
			dxExit = fabs(this->currPosition.x - sprite->currPosition.x) + (this->center.x + sprite->center.x);
			if (dxEntry > 0)
			{
				txEntry = +INFINITY;
			}
			if (dxEntry <= 0)
			{
				txEntry = -INFINITY;
			}
			if (dxExit > 0)
			{
				txExit = +INFINITY;
			}
			if (dxExit <= 0)
			{
				txExit = +INFINITY;
			}
		}
		if (txEntry >= 0 && txEntry < 1)
		{
			if (thisVx > 0)
			{
				tempResultX = LEFT;
			}
			if (thisVx < 0)
			{
				tempResultX = RIGHT;
			}
			if (thisVx == 0)
			{
				tempResultX = NONE;
			}
		}

//
		if(thisVy > 0)
		{
			dyEntry = (sprite->currPosition.y - sprite->center.y) - (this->currPosition.y + this->center.y);
			dyExit = (sprite->currPosition.y + sprite->center.y) - (this->currPosition.y - this->center.y);
			tyEntry = dyEntry / (thisVy * (1000.0 / 60));
			tyExit = dyExit / (thisVy * (1000.0 / 60));
		}
		if (thisVy < 0)
		{
			dyEntry = (this->currPosition.y - this->center.y) - (sprite->currPosition.y + sprite->center.y);
			dyExit = (this->currPosition.y + this->center.y) - (sprite->currPosition.y - sprite->center.y);
			tyEntry = dyEntry / (-thisVy * (1000.0 / 60));
			tyExit = dyExit / (-thisVy * (1000.0 / 60));
		}
		if(thisVy == 0)
		{
			dyEntry = fabs(this->currPosition.y - sprite->currPosition.y) - (this->center.y + sprite->center.y);
			dyExit = fabs(this->currPosition.y - sprite->currPosition.y) + (this->center.y + sprite->center.y);
			if (dyEntry > 0)
			{
				tyEntry = +INFINITY;
			}
			if (dyEntry <= 0)
			{
				tyEntry = -INFINITY;
			}
			if (dyExit > 0)
			{
				tyExit = +INFINITY;
			}
			if (dyExit <= 0)
			{
				tyExit = +INFINITY;
			}
		}
		if (tyEntry >=0 && tyEntry < 1)
		{
			if (thisVy > 0)
			{
				tempResultY = BOTTOM;
			}
			if (thisVy < 0)
			{
				tempResultY = TOP;
			}
			if (thisVy == 0)
			{
				tempResultY = NONE;
			}
		}
//process
	if (tyEntry > txEntry)
	{
		if (tempResultY != NONE)
		{
			if (dxExit < 0)
			{
				tempResultY = NONE;
			}
			this->FixCollision(tempResultY, dxEntry, dyEntry);
		}
		return tempResultY;
	}
	else
	{
		if (tempResultX != NONE)
		{
			if (dyExit < 0)
			{
				tempResultX = NONE;
			}
			this->FixCollision(tempResultX, dxEntry, dyEntry);
		}
		return tempResultX;
	}
}

void Sprite::FixCollision(collisionType type, float deltaX, float deltaY)
{
	if (type == LEFT)
	{
		this->currPosition.x += deltaX;
	}
	if (type == RIGHT)
	{
		this->currPosition.x -= deltaX;
	}
}
void Sprite::ProcessSignalKeyBoard(char* signalState, DIDEVICEOBJECTDATA* signalEvent)
{

}
void Sprite::ProcessSignalKeyboardEvent(DIDEVICEOBJECTDATA* signal)
{

}
void Sprite::ProcessCollision(collisionType type, Sprite *sprite)
{
}

void Sprite::UpdatePosition()
{

}
void Sprite::UpdateVelocity()
{

}
float Sprite::getVx()
{
	return this->Vx;
}
float Sprite::getVy()
{
	return this->Vy;
}
float Sprite::getlastVx()
{
	return this->lastVx;
}
float Sprite::getlastVy()
{
	return this->lastVy;
}
D3DXVECTOR3 Sprite::getPosition()
{
	return this->currPosition;
}
D3DXVECTOR3 Sprite::getlastPosition()
{
	return this->lastPosition;
}
SpriteIdentity Sprite::getId()
{
	return this->id;
}
void Sprite::Reset()
{
}
Sprite::~Sprite()
{

}