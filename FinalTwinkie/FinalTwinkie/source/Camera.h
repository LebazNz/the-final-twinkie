#ifndef CAM_H
#define CAM_H

#include "Player.h"
class Camera
{
public:
	

	void	Update(CPlayer* pPlayer, int nWorldWidth, int nWorldHeight,float fDt );

	float	GetPosX() const { return m_fPosX; }
	void	SetPosX(float val) { m_fPosX = val; }

	float	GetPosY() const { return m_fPosY; }
	void	SetPosY(float val) { m_fPosY = val; }

	bool	GetPlayerCannotMove() const { return m_bPlayerCannotMove; }
	void	SetPlayerCannotMove(bool val) { m_bPlayerCannotMove = val; }

	static Camera* GetInstance();

private:

	float m_fPosX;
	float m_fPosY;
	
	bool m_bPlayerCannotMove;
	
	Camera(void);
	~Camera(void);
	Camera(const Camera&);
	Camera& operator=(const Camera&);
};

#endif
