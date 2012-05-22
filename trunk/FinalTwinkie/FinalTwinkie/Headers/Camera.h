#ifndef CAM_H
#define CAM_H

#include "../GameObjects/Player.h"

#include "../SGD Wrappers/SGD_Math.h"


class Camera
{
public:
	

	void	Update(CPlayer* pPlayer, int nWorldWidth, int nWorldHeight,float fDt );

	tVector2D GetOldPos(void) { return m_vOldPos;}

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

	tVector2D m_vOldPos;
	
	bool m_bPlayerCannotMove;
	
	Camera(void);
	~Camera(void);
	Camera(const Camera&);
	Camera& operator=(const Camera&);
};

#endif
