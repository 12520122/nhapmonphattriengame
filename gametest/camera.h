#pragma once
#include <d3dx9.h>

class camera
{
private:

	D3DXVECTOR3 position;
	int with;
	int height;
public:
	camera();
	camera(int with, int height);
	D3DXVECTOR3 intoCamera(D3DXVECTOR3 WorldPosition, float Direction);
	void UpdatePosition();
	int getWidth();
	int getHeight();
	D3DXVECTOR3 getPosition();
	void setPosition(D3DXVECTOR3 dest);
	~camera();
};

class Sprite;