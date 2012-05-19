#ifndef FRAME_H
#define FRAME_H
#include <windows.h>
class CFrame
{

public:
	CFrame(void);
	~CFrame(void);

	void Update(float fDt);
	void Render();



	float	GetFrameTime() const { return m_fFrameTime; }
	void	SetFrameTime(float val) { m_fFrameTime = val; }

	RECT	GetFrame() const { return m_rFrame; }
	void	SetFrame(RECT val) { m_rFrame = val; }

	int		GetAnchorX() const { return m_nAnchorX; }
	void	SetAnchorX(int val) { m_nAnchorX = val; }

	int		GetAnchorY() const { return m_nAnchorY; }
	void	SetAnchorY(int val) { m_nAnchorY = val; }
private:
	
	RECT m_rFrame;
	int m_nAnchorX;
	
	int m_nAnchorY;
	
	float m_fFrameTime;
	
};

#endif