#include "Sprite.h"

class boommancpp: public Sprite
{
public:
	boommancpp(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler);
	void Update();
	~boommancpp();
};