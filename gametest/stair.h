#include "Sprite.h"

class stair : public Sprite
{
private:
	int count;
public:
	stair(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler);
	void UpdateRender(LARGE_INTEGER stp);
	void Render(camera gameCamera);
	void ProcessCollision(collisionType type, Sprite * sprite);
	bool Init();
	~stair();
};
