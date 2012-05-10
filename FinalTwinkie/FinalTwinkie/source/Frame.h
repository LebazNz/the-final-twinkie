#ifndef FRAME_H
#define FRAME_H
class CFrame
{
	int m_nHeight;
	int m_nWidth;
	int m_nPosX;
	int m_nPosY;
	float m_fFrameTime;
public:
	CFrame(void);
	~CFrame(void);

	void Update(float fDt);
	void Render();
};

#endif