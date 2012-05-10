#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>

#include "Frame.h"
class CAnimation
{
	std::vector<CFrame*> m_vFrames;
	int m_nFrameCount;
	int m_nImageID;

public:
	CAnimation(void);
	~CAnimation(void);

	void Update(float fDt);
	void Render();
};
#endif
