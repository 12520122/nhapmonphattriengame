
#include "camera.h"

camera::camera()
{
}
camera::camera(int with, int height)
{
	this->with = with;
	this->height = height;
	this->position = D3DXVECTOR3(0, 400, 0);
}
D3DXVECTOR3 camera::intoCamera(D3DXVECTOR3 WorldPosition, float Direction)
{
	D3DXMATRIX matrixTransform;
	matrixTransform._11 = 1; matrixTransform._12 = 0;
	matrixTransform._21 = 0; matrixTransform._22 = -1;
	matrixTransform._31 = 0; matrixTransform._32 = 0;
	matrixTransform._41 = -this->position.x; matrixTransform._42 = this->position.y;
	D3DXMATRIX worldPosition;
	worldPosition._11 = WorldPosition.x;
	worldPosition._12 = WorldPosition.y;
	worldPosition._13 = 1;
	worldPosition._14 = 1;
	D3DXMATRIX systemPosition;
	systemPosition = worldPosition * matrixTransform;
	return D3DXVECTOR3(systemPosition._11, systemPosition._12, 0);
}
void camera::UpdatePosition()
{
}
int camera::getWidth()
{
	return this->with;
}
int camera::getHeight()
{
	return this->height;
}
D3DXVECTOR3 camera::getPosition()
{
	return this->position;
}
void camera::setPosition(D3DXVECTOR3 dest)
{
	this->position = dest;
}
camera::~camera()
{

}

