#pragma once
#include "DirectxGraphic.h"
#include "DirectxInput.h"
#include "camera.h"
#include <typeinfo>
#define granvity 0.0015f

enum collisionType 
{
	NONE = 0,
	TOP = 1,
	LEFT = 2,
	RIGHT = 3,
	BOTTOM = 4,
	BOXCOLLISION = 5,

};
enum SpriteIdentity
{
	ROCKMAN = 0,
	CUTMAN = 1,
	BRICKHIDDEN = 2,
	STAIR = 3,
};
class Sprite
{
protected:
	SpriteIdentity id;
	D3DXVECTOR3 currPosition;
	D3DXVECTOR3 lastPosition;
	D3DXVECTOR3 center;
	D3DXVECTOR3 BoxCenter;
	LPDIRECT3DDEVICE9 d3ddev;
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE SpriteHandler;
	camera * x;
	float Vx;
	float lastVx;
	float Vy;
	float lastVy;
	float Ax;
	float Ay;
	float FaceDirection;
public:
	Sprite();
	Sprite(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler);
	virtual bool Init();
	virtual void Render(camera gameCamera);
	virtual void UpdateRender(LARGE_INTEGER stp);
	collisionType checkCollision(Sprite*sprite);
	virtual void ProcessCollision(collisionType type, Sprite *sprite);
	void FixCollision(collisionType type, float deltaX, float deltaY);
	virtual void ProcessSignalKeyBoard(char* signalState, DIDEVICEOBJECTDATA* signalEvent);
	virtual void ProcessSignalKeyboardEvent(DIDEVICEOBJECTDATA* signal);
	virtual void UpdatePosition();
	virtual void UpdateVelocity();
	float getVx();
	float getVy();
	float getlastVx();
	float getlastVy();
	D3DXVECTOR3 getPosition();
	D3DXVECTOR3 getlastPosition();
	SpriteIdentity getId();
	virtual void Reset();
	~Sprite();
};