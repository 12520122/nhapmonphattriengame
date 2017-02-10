#include "boomman.h"
#define IMAGE_LOCATION "./anhlamgame/icon_master_final.png"
boommancpp::boommancpp(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler) : Sprite(d3ddev, SpriteHandler)
{
}
void boommancpp::Update()
{
	this->currPosition.y += 1;
}
boommancpp::~boommancpp()
{

}