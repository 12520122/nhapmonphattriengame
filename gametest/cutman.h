
#include "Sprite.h"

class cutman: public Sprite
{
private:
public:
	cutman(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler);
	void UpdateRender(LARGE_INTEGER stp);
	void Render(camera gameCamera);
	void ProcessCollision(collisionType type, Sprite * sprite);
	void UpdatePosition();
	void UpdateVelocity();
	bool Init();
	~cutman();
};