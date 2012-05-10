#ifndef CAM_H
#define CAM_H

#include "Player.h"
class Camera
{
public:
	Camera(void);
	~Camera(void);


private:

	int m_nPosX;
	int m_nPosY;
	int m_nWidth;
	int m_nHeight;

	CPlayer* m_pPlayer;
};

#endif
