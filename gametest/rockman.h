
#include "Sprite.h"
#include "DirectxInput.h"
enum State
{
	STAND = 0,
	MOVE = 1,
	JUMP = 2,
	COLLISION = 3,
	JUMP_FIRE = 4,
	MOVE_FIRE = 5,
	STAND_FIRE = 6,
	CLIMB = 7,
};
class rockman : public Sprite
{
private:
	LARGE_INTEGER lastStp;
	LPDIRECT3DTEXTURE9 currTextureSprite;
	int currIndexState;
	State currState;
	bool * enableState;
	bool * IsState;
	bool IsAuto;
	LPDIRECT3DTEXTURE9 *listTextureSprite;
	LPDIRECT3DTEXTURE9 *listTextureEffect;
public:
	rockman(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler);
	void UpdateRender(LARGE_INTEGER stp);
	bool Init();
	void Render(camera gameCamera);
	void ProcessCollision(collisionType type, Sprite *sprite);
	void FixCollision(collisionType type, float deltaX, float deltaY);
	RECT getRectState(State state);
	D3DXVECTOR3 getCenterState(State state);
	void ProcessSignalKeyBoard(char *signalState, DIDEVICEOBJECTDATA* signalEvent);
	void ProcessSignalKeyboardEvent(DIDEVICEOBJECTDATA* signal);
	void UpdatePosition();
	void UpdateVelocity();
	void Reset();
	void UpdateState();
	void UpdateTotal();
	void JumpProcess();
	~rockman();
};