
#include "Sprite.h"

class BrickHidden: public Sprite
{
private:
	LPDIRECT3DTEXTURE9 TextureSprite;
	int count;
public:
	BrickHidden(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler);
	bool Init();
	void Render(camera gameCamera);
	~BrickHidden();
};
