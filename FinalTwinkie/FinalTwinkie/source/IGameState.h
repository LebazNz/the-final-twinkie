#ifndef IGAMESTATE_H_
#define IGAMESTATE_H_

#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "BitmapFont.h"

class IGameState
{
public:
	virtual ~IGameState(void)
	{	/*DO NOTHING*/		}

	virtual void Enter(void) = 0;
	virtual void Exit(void)	= 0;
	virtual bool Input(void) = 0;
	virtual void Update(float fDt) = 0;
	virtual void Render(void) = 0;


};



#endif