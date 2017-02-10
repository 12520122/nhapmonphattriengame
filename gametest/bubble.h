#include "Sprite.h"
enum BubbleState
{
	FLY = 0,

};
class bubble : public Sprite
{
private:
	int currIndexState;
	BubbleState currState;
public:
	bubble(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler);
	void UpdateRender(LARGE_INTEGER stp);
	void Render(camera gameCamera);
	void ProcessCollision(collisionType type, Sprite * sprite);
	void UpdatePosition();
	void UpdateVelocity();
	bool Init();
	D3DXVECTOR3 getCenterState(BubbleState state);
	RECT getRectState(BubbleState state);
	~bubble();
};
